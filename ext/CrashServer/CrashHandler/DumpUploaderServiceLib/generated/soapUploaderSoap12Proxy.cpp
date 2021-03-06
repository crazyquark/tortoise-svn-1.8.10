/* soapUploaderSoap12Proxy.cpp
   Generated by gSOAP 2.8.0 from DumpUploader.h
   Copyright(C) 2000-2010, Robert van Engelen, Genivia Inc. All Rights Reserved.
   The generated code is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#include "soapUploaderSoap12Proxy.h"

UploaderSoap12Proxy::UploaderSoap12Proxy()
{   UploaderSoap12Proxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

UploaderSoap12Proxy::UploaderSoap12Proxy(const struct soap &_soap) : soap(_soap)
{ }

UploaderSoap12Proxy::UploaderSoap12Proxy(soap_mode iomode)
{   UploaderSoap12Proxy_init(iomode, iomode);
}

UploaderSoap12Proxy::UploaderSoap12Proxy(soap_mode imode, soap_mode omode)
{   UploaderSoap12Proxy_init(imode, omode);
}

void UploaderSoap12Proxy::UploaderSoap12Proxy_init(soap_mode imode, soap_mode omode)
{   soap_imode(this, imode);
    soap_omode(this, omode);
    soap_endpoint = NULL;
    static const struct Namespace namespaces[] =
{
    {"SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope", "http://www.w3.org/2003/05/soap-envelope", NULL},
    {"SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding", "http://www.w3.org/2003/05/soap-encoding", NULL},
    {"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
    {"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
    {"xop", "http://www.w3.org/2004/08/xop/include", NULL, NULL},
    {"ns2", "http://microsoft.com/wsdl/types/", NULL, NULL},
    {"ns3", "https://www.crash-server.com/UploaderSoap", NULL, NULL},
    {"ns1", "https://www.crash-server.com/", NULL, NULL},
    {"ns4", "https://www.crash-server.com/UploaderSoap12", NULL, NULL},
    {NULL, NULL, NULL, NULL}
};
    this->namespaces = namespaces;
}

UploaderSoap12Proxy::~UploaderSoap12Proxy()
{ }

void UploaderSoap12Proxy::destroy()
{   soap_destroy(this);
    soap_end(this);
}

void UploaderSoap12Proxy::soap_noheader()
{   header = NULL;
}

const SOAP_ENV__Fault *UploaderSoap12Proxy::soap_fault()
{   return this->fault;
}

const char *UploaderSoap12Proxy::soap_fault_string()
{   return *soap_faultstring(this);
}

const char *UploaderSoap12Proxy::soap_fault_detail()
{   return *soap_faultdetail(this);
}

int UploaderSoap12Proxy::soap_close_socket()
{   return soap_closesock(this);
}

void UploaderSoap12Proxy::soap_print_fault(FILE *fd)
{   ::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
void UploaderSoap12Proxy::soap_stream_fault(std::ostream& os)
{   ::soap_stream_fault(this, os);
}

char *UploaderSoap12Proxy::soap_sprint_fault(char *buf, size_t len)
{   return ::soap_sprint_fault(this, buf, len);
}
#endif

int UploaderSoap12Proxy::Hello(_ns1__Hello *ns1__Hello, _ns1__HelloResponse *ns1__HelloResponse)
{   struct soap *soap = this;
    struct __ns4__Hello soap_tmp___ns4__Hello;
    const char *soap_action = NULL;
    if (!soap_endpoint)
        soap_endpoint = "http://localhost:59175/DumpUploader.asmx";
    soap_action = "https://www.crash-server.com/Hello";
    soap->encodingStyle = NULL;
    soap_tmp___ns4__Hello.ns1__Hello = ns1__Hello;
    soap_begin(soap);
    soap_serializeheader(soap);
    soap_serialize___ns4__Hello(soap, &soap_tmp___ns4__Hello);
    if (soap_begin_count(soap))
        return soap->error;
    if (soap->mode & SOAP_IO_LENGTH)
    {   if (soap_envelope_begin_out(soap)
         || soap_putheader(soap)
         || soap_body_begin_out(soap)
         || soap_put___ns4__Hello(soap, &soap_tmp___ns4__Hello, "-ns4:Hello", NULL)
         || soap_body_end_out(soap)
         || soap_envelope_end_out(soap))
             return soap->error;
    }
    if (soap_end_count(soap))
        return soap->error;
    if (soap_connect(soap, soap_endpoint, soap_action)
     || soap_envelope_begin_out(soap)
     || soap_putheader(soap)
     || soap_body_begin_out(soap)
     || soap_put___ns4__Hello(soap, &soap_tmp___ns4__Hello, "-ns4:Hello", NULL)
     || soap_body_end_out(soap)
     || soap_envelope_end_out(soap)
     || soap_end_send(soap))
        return soap_closesock(soap);
    if (!ns1__HelloResponse)
        return soap_closesock(soap);
    ns1__HelloResponse->soap_default(soap);
    if (soap_begin_recv(soap)
     || soap_envelope_begin_in(soap)
     || soap_recv_header(soap)
     || soap_body_begin_in(soap))
        return soap_closesock(soap);
    ns1__HelloResponse->soap_get(soap, "ns1:HelloResponse", "");
    if (soap->error)
        return soap_recv_fault(soap, 0);
    if (soap_body_end_in(soap)
     || soap_envelope_end_in(soap)
     || soap_end_recv(soap))
        return soap_closesock(soap);
    return soap_closesock(soap);
}

int UploaderSoap12Proxy::UploadMiniDump(_ns1__UploadMiniDump *ns1__UploadMiniDump, _ns1__UploadMiniDumpResponse *ns1__UploadMiniDumpResponse)
{   struct soap *soap = this;
    struct __ns4__UploadMiniDump soap_tmp___ns4__UploadMiniDump;
    const char *soap_action = NULL;
    if (!soap_endpoint)
        soap_endpoint = "http://localhost:59175/DumpUploader.asmx";
    soap_action = "https://www.crash-server.com/UploadMiniDump";
    soap->encodingStyle = NULL;
    soap_tmp___ns4__UploadMiniDump.ns1__UploadMiniDump = ns1__UploadMiniDump;
    soap_begin(soap);
    soap_serializeheader(soap);
    soap_serialize___ns4__UploadMiniDump(soap, &soap_tmp___ns4__UploadMiniDump);
    if (soap_begin_count(soap))
        return soap->error;
    if (soap->mode & SOAP_IO_LENGTH)
    {   if (soap_envelope_begin_out(soap)
         || soap_putheader(soap)
         || soap_body_begin_out(soap)
         || soap_put___ns4__UploadMiniDump(soap, &soap_tmp___ns4__UploadMiniDump, "-ns4:UploadMiniDump", NULL)
         || soap_body_end_out(soap)
         || soap_envelope_end_out(soap))
             return soap->error;
    }
    if (soap_end_count(soap))
        return soap->error;
    if (soap_connect(soap, soap_endpoint, soap_action)
     || soap_envelope_begin_out(soap)
     || soap_putheader(soap)
     || soap_body_begin_out(soap)
     || soap_put___ns4__UploadMiniDump(soap, &soap_tmp___ns4__UploadMiniDump, "-ns4:UploadMiniDump", NULL)
     || soap_body_end_out(soap)
     || soap_envelope_end_out(soap)
     || soap_end_send(soap))
        return soap_closesock(soap);
    if (!ns1__UploadMiniDumpResponse)
        return soap_closesock(soap);
    ns1__UploadMiniDumpResponse->soap_default(soap);
    if (soap_begin_recv(soap)
     || soap_envelope_begin_in(soap)
     || soap_recv_header(soap)
     || soap_body_begin_in(soap))
        return soap_closesock(soap);
    ns1__UploadMiniDumpResponse->soap_get(soap, "ns1:UploadMiniDumpResponse", "");
    if (soap->error)
        return soap_recv_fault(soap, 0);
    if (soap_body_end_in(soap)
     || soap_envelope_end_in(soap)
     || soap_end_recv(soap))
        return soap_closesock(soap);
    return soap_closesock(soap);
}

int UploaderSoap12Proxy::UploadAdditionalInfo(_ns1__UploadAdditionalInfo *ns1__UploadAdditionalInfo, _ns1__UploadAdditionalInfoResponse *ns1__UploadAdditionalInfoResponse)
{   struct soap *soap = this;
    struct __ns4__UploadAdditionalInfo soap_tmp___ns4__UploadAdditionalInfo;
    const char *soap_action = NULL;
    if (!soap_endpoint)
        soap_endpoint = "http://localhost:59175/DumpUploader.asmx";
    soap_action = "https://www.crash-server.com/UploadAdditionalInfo";
    soap->encodingStyle = NULL;
    soap_tmp___ns4__UploadAdditionalInfo.ns1__UploadAdditionalInfo = ns1__UploadAdditionalInfo;
    soap_begin(soap);
    soap_serializeheader(soap);
    soap_serialize___ns4__UploadAdditionalInfo(soap, &soap_tmp___ns4__UploadAdditionalInfo);
    if (soap_begin_count(soap))
        return soap->error;
    if (soap->mode & SOAP_IO_LENGTH)
    {   if (soap_envelope_begin_out(soap)
         || soap_putheader(soap)
         || soap_body_begin_out(soap)
         || soap_put___ns4__UploadAdditionalInfo(soap, &soap_tmp___ns4__UploadAdditionalInfo, "-ns4:UploadAdditionalInfo", NULL)
         || soap_body_end_out(soap)
         || soap_envelope_end_out(soap))
             return soap->error;
    }
    if (soap_end_count(soap))
        return soap->error;
    if (soap_connect(soap, soap_endpoint, soap_action)
     || soap_envelope_begin_out(soap)
     || soap_putheader(soap)
     || soap_body_begin_out(soap)
     || soap_put___ns4__UploadAdditionalInfo(soap, &soap_tmp___ns4__UploadAdditionalInfo, "-ns4:UploadAdditionalInfo", NULL)
     || soap_body_end_out(soap)
     || soap_envelope_end_out(soap)
     || soap_end_send(soap))
        return soap_closesock(soap);
    if (!ns1__UploadAdditionalInfoResponse)
        return soap_closesock(soap);
    ns1__UploadAdditionalInfoResponse->soap_default(soap);
    if (soap_begin_recv(soap)
     || soap_envelope_begin_in(soap)
     || soap_recv_header(soap)
     || soap_body_begin_in(soap))
        return soap_closesock(soap);
    ns1__UploadAdditionalInfoResponse->soap_get(soap, "ns1:UploadAdditionalInfoResponse", "");
    if (soap->error)
        return soap_recv_fault(soap, 0);
    if (soap_body_end_in(soap)
     || soap_envelope_end_in(soap)
     || soap_end_recv(soap))
        return soap_closesock(soap);
    return soap_closesock(soap);
}

int UploaderSoap12Proxy::UploadSymbol(_ns1__UploadSymbol *ns1__UploadSymbol, _ns1__UploadSymbolResponse *ns1__UploadSymbolResponse)
{   struct soap *soap = this;
    struct __ns4__UploadSymbol soap_tmp___ns4__UploadSymbol;
    const char *soap_action = NULL;
    if (!soap_endpoint)
        soap_endpoint = "http://localhost:59175/DumpUploader.asmx";
    soap_action = "https://www.crash-server.com/UploadSymbol";
    soap->encodingStyle = NULL;
    soap_tmp___ns4__UploadSymbol.ns1__UploadSymbol = ns1__UploadSymbol;
    soap_begin(soap);
    soap_serializeheader(soap);
    soap_serialize___ns4__UploadSymbol(soap, &soap_tmp___ns4__UploadSymbol);
    if (soap_begin_count(soap))
        return soap->error;
    if (soap->mode & SOAP_IO_LENGTH)
    {   if (soap_envelope_begin_out(soap)
         || soap_putheader(soap)
         || soap_body_begin_out(soap)
         || soap_put___ns4__UploadSymbol(soap, &soap_tmp___ns4__UploadSymbol, "-ns4:UploadSymbol", NULL)
         || soap_body_end_out(soap)
         || soap_envelope_end_out(soap))
             return soap->error;
    }
    if (soap_end_count(soap))
        return soap->error;
    if (soap_connect(soap, soap_endpoint, soap_action)
     || soap_envelope_begin_out(soap)
     || soap_putheader(soap)
     || soap_body_begin_out(soap)
     || soap_put___ns4__UploadSymbol(soap, &soap_tmp___ns4__UploadSymbol, "-ns4:UploadSymbol", NULL)
     || soap_body_end_out(soap)
     || soap_envelope_end_out(soap)
     || soap_end_send(soap))
        return soap_closesock(soap);
    if (!ns1__UploadSymbolResponse)
        return soap_closesock(soap);
    ns1__UploadSymbolResponse->soap_default(soap);
    if (soap_begin_recv(soap)
     || soap_envelope_begin_in(soap)
     || soap_recv_header(soap)
     || soap_body_begin_in(soap))
        return soap_closesock(soap);
    ns1__UploadSymbolResponse->soap_get(soap, "ns1:UploadSymbolResponse", "");
    if (soap->error)
        return soap_recv_fault(soap, 0);
    if (soap_body_end_in(soap)
     || soap_envelope_end_in(soap)
     || soap_end_recv(soap))
        return soap_closesock(soap);
    return soap_closesock(soap);
}
/* End of client proxy code */
