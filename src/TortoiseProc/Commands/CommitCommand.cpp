// TortoiseSVN - a Windows shell extension for easy version control

// Copyright (C) 2007-2014 - TortoiseSVN

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
#include "stdafx.h"
#include "CommitCommand.h"

#include "CommitDlg.h"
#include "SVNProgressDlg.h"
#include "StringUtils.h"
#include "Hooks.h"
#include "AppUtils.h"

CString CommitCommand::LoadLogMessage()
{
    CString msg;
    if (parser.HasKey(_T("logmsg")))
    {
        msg = parser.GetVal(_T("logmsg"));
    }
    if (parser.HasKey(_T("logmsgfile")))
    {
        CString logmsgfile = parser.GetVal(_T("logmsgfile"));
        CStringUtils::ReadStringFromTextFile(logmsgfile, msg);
    }
    return msg;
}

void CommitCommand::InitProgressDialog
    ( CCommitDlg& commitDlg
    , CSVNProgressDlg& progDlg)
{
    progDlg.SetChangeList(commitDlg.m_sChangeList, !!commitDlg.m_bKeepChangeList);
    progDlg.SetAutoClose (parser);
    progDlg.SetCommand(CSVNProgressDlg::SVNProgress_Commit);
    progDlg.SetOptions(commitDlg.m_bKeepLocks ? ProgOptKeeplocks : ProgOptNone);
    progDlg.SetPathList(commitDlg.m_pathList);
    progDlg.SetCommitMessage(commitDlg.m_sLogMessage);
    progDlg.SetDepth(commitDlg.m_bRecursive ? svn_depth_infinity : svn_depth_empty);
    progDlg.SetSelectedList(commitDlg.m_selectedPathList);
    progDlg.SetItemCount(commitDlg.m_itemsCount);
    progDlg.SetBugTraqProvider(commitDlg.m_BugTraqProvider);
    progDlg.SetRevisionProperties(commitDlg.m_revProps);
}

bool CommitCommand::IsOutOfDate(const svn_error_t* pErr) const
{
    while (pErr)
    {
        const apr_status_t errorStatus = pErr->apr_err;
        if ((errorStatus == SVN_ERR_FS_TXN_OUT_OF_DATE)||
            (errorStatus == SVN_ERR_RA_OUT_OF_DATE)||
            (errorStatus == SVN_ERR_FS_CONFLICT))
        {
            return true;
        }
        pErr = pErr->child;
    }
    return false;
}

bool CommitCommand::Execute()
{
    bool bRet = false;
    bool bFailed = true;
    CTSVNPathList selectedList;
    if (parser.HasKey(_T("logmsg")) && (parser.HasKey(_T("logmsgfile"))))
    {
        TSVNMessageBox(GetExplorerHWND(), IDS_ERR_TWOLOGPARAMS, IDS_APPNAME, MB_ICONERROR);
        return false;
    }
    CString sLogMsg = LoadLogMessage();
    bool bSelectFilesForCommit = !!DWORD(CRegStdDWORD(_T("Software\\TortoiseSVN\\SelectFilesForCommit"), TRUE));
    DWORD exitcode = 0;
    CString error;
    ProjectProperties props;
    props.ReadPropsPathList(pathList);
    CHooks::Instance().SetProjectProperties(pathList.GetCommonRoot(), props);
    if (CHooks::Instance().StartCommit(GetExplorerHWND(), pathList, sLogMsg, exitcode, error))
    {
        if (exitcode)
        {
            CString temp;
            temp.Format(IDS_ERR_HOOKFAILED, (LPCTSTR)error);
            MessageBox(GetExplorerHWND(), temp, _T("TortoiseSVN"), MB_ICONERROR);
            return false;
        }
    }
    CTSVNPathList updatelist = pathList;
    CTSVNPathList origPathList = pathList;
    std::map<CString, CString> restorepaths;
    CString sBugID;
    if (parser.HasKey(L"bugid"))
    {
        sBugID = parser.GetVal(L"bugid");
    }
    while (bFailed)
    {
        bFailed = false;
        CCommitDlg dlg;
        dlg.m_sBugID = sBugID;
        dlg.m_ProjectProperties = props;
        dlg.m_sLogMessage = sLogMsg;
        dlg.m_pathList = pathList;
        dlg.m_checkedPathList = selectedList;
        dlg.m_bSelectFilesForCommit = bSelectFilesForCommit;
        dlg.m_restorepaths = restorepaths;
        if (dlg.DoModal() == IDOK)
        {
            if (dlg.m_pathList.GetCount()==0)
                return false;
            // if the user hasn't changed the list of selected items
            // we don't use that list. Because if we would use the list
            // of pre-checked items, the dialog would show different
            // checked items on the next startup: it would only try
            // to check the parent folder (which might not even show)
            // instead, we simply use an empty list and let the
            // default checking do its job.
            if (!dlg.m_pathList.IsEqual(pathList))
                selectedList = dlg.m_pathList;
            pathList = dlg.m_updatedPathList;
            updatelist = dlg.m_updatedPathList;
            sLogMsg = dlg.m_sLogMessage;
            sBugID = dlg.m_sBugID;
            bSelectFilesForCommit = true;
            CSVNProgressDlg progDlg;
            InitProgressDialog (dlg, progDlg);
            progDlg.SetRestorePaths(dlg.m_restorepaths);
            restorepaths = dlg.m_restorepaths;
            progDlg.SetProjectProperties(props);
            progDlg.SetOrigPathList(origPathList);
            progDlg.DoModal();

            if (IsOutOfDate(progDlg.GetSVNError()))
            {
                // the commit failed at least one of the items was outdated.
                // -> suggest to update them
                if(CAppUtils::AskToUpdate(NULL, progDlg.GetLastErrorMessage(40)))
                {
                    // auto-update
                    CSVNProgressDlg updateProgDlg;
                    InitProgressDialog (dlg, updateProgDlg);
                    updateProgDlg.SetPathList(updatelist);
                    updateProgDlg.SetCommand (CSVNProgressDlg::SVNProgress_Update);
                    // always update with svn_depth_unknown (the depth of the wc).
                    // because otherwise we would change the depth here which is
                    // not what we want!
                    updateProgDlg.SetDepth(svn_depth_unknown);
                    updateProgDlg.SetProjectProperties(props);
                    CRegDWORD updateExternals(L"Software\\TortoiseSVN\\IncludeExternals", true);
                    int options = DWORD(updateExternals) ? 0 : ProgOptIgnoreExternals;
                    updateProgDlg.SetOptions(options);
                    updateProgDlg.DoModal();

                    // re-open commit dialog only if update *SUCCEEDED*
                    // (don't pass update errors to caller and *never*
                    // auto-reopen commit dialog upon error)

                    bFailed =    !updateProgDlg.DidErrorsOccur()
                              && !updateProgDlg.DidConflictsOccur();
                    bRet = bFailed;
                    CRegDWORD (_T("Software\\TortoiseSVN\\ErrorOccurred"), FALSE)
                        = bRet ? TRUE : FALSE;

                    continue;
                }
            }

            // If there was an error and the user set the
            // "automatically re-open commit dialog" option, do so.

            CRegDWORD err = CRegDWORD(_T("Software\\TortoiseSVN\\ErrorOccurred"), FALSE);
            err = (DWORD)progDlg.DidErrorsOccur();
            bFailed = progDlg.DidErrorsOccur();
            bRet = !progDlg.DidErrorsOccur();
            CRegDWORD bFailRepeat = CRegDWORD(_T("Software\\TortoiseSVN\\OutOfDateRetry"), TRUE);
            if (DWORD(bFailRepeat)==0)
                bFailed = false;        // do not repeat if the user chose not to in the settings.
        }
    }
    if (!restorepaths.empty())
    {
        for (auto it = restorepaths.cbegin(); it != restorepaths.cend(); ++it)
        {
            CopyFile(it->first, it->second, FALSE);
        }
    }
    return bRet;
}