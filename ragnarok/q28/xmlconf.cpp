//--------------------------------------------------------------------------------------
// File: xmlconf.cpp
//--------------------------------------------------------------------------------------
#include "stdafx.h"

//--------------------------------------------------------------------------------------
// Constants
// const TCHAR* = _T("/CONFIG/ACCOUNTINFO/ACCOUNT");

//--------------------------------------------------------------------------------------
MASTERCONFIG Config;
ACCOUNTLIST AccountList;

//--------------------------------------------------------------------------------------
void GetNodeValue(const MSXML2::IXMLDOMNodePtr& node, _variant_t& value) throw(_com_error)
{
    try
    {
        MSXML2::IXMLDOMNodePtr nodeVal;
        node->get_firstChild(&nodeVal);
        nodeVal->get_nodeValue(&value);
    }
    catch (_com_error& e)
    {
        throw e;
    }
}

//--------------------------------------------------------------------------------------
void LoadMaster(const MSXML2::IXMLDOMDocumentPtr& xml) throw(_com_error)
{
    try
    {
        _variant_t value;
        MSXML2::IXMLDOMNodePtr node1;

        xml->selectSingleNode(_T("/CONFIG/CLIENT/FILE"), &node1);
        GetNodeValue(node1, value);
        Config.execName = value;

        xml->selectSingleNode(_T("/CONFIG/CLIENT/PATH"), &node1);
        GetNodeValue(node1, value);
        Config.execPath = value;

        xml->selectSingleNode(_T("/CONFIG/WEB/ACKWAIT"), &node1);
        GetNodeValue(node1, value);
        Config.ackWait = value;
    }
    catch (_com_error& e)
    {
        throw e;
    }
}

void LoadAccount(const MSXML2::IXMLDOMNodePtr& node) throw(_com_error)
{
    try
    {
        MSXML2::IXMLDOMElementPtr element = node;

        _variant_t varName;
        element->getAttribute(_T("NAME"), &varName);

        VARIANT_BOOL hasChild;
        node->hasChildNodes(&hasChild);

        if (hasChild != VARIANT_TRUE)
            _com_raise_error(E_FAIL);
        else
        {
            _variant_t value;
            MSXML2::IXMLDOMNodePtr node2;

            ACCOUNTINFO account;
            account.varName = varName;

            node2 = NULL;
            node->selectSingleNode(_T("SIID"), &node2);
            GetNodeValue(node2, value);
            account.varSIID = value;

            node2 = NULL;
            node->selectSingleNode(_T("GUNGHOID"), &node2);
            GetNodeValue(node2, value);
            account.varGunghoID = value;

            node2 = NULL;
            node->selectSingleNode(_T("PASSWORD"), &node2);
            GetNodeValue(node2, value);
            account.varPassword = value;

            AccountList.push_back(account);
        }
    }
    catch (_com_error& e)
    {
        throw e;
    }
}

HRESULT LoadXml(const TCHAR* XmlFileName)
{
    try
    {
        // Create XMLDocument
        MSXML2::IXMLDOMDocumentPtr xml = NULL;
        xml.CreateInstance(__uuidof(MSXML2::DOMDocument30));

        // Non-async
        xml->put_async(VARIANT_FALSE);

        // Load
        VARIANT_BOOL isSuccessful;
        xml->load(_variant_t(XmlFileName), &isSuccessful);
        if (isSuccessful != VARIANT_TRUE)
            _com_raise_error(E_FAIL);

        // Load master config
        LoadMaster(xml);

        // Select
        LONG listLength;
        MSXML2::IXMLDOMNodeListPtr nodeList;

        // Get ACCOUNTINFOs
        nodeList = NULL;
        xml->selectNodes(_T("/CONFIG/ACCOUNTINFO/ACCOUNT"), &nodeList);

        listLength = 0;
        nodeList->get_length(&listLength);

        for (LONG i=0; i<listLength; i++)
        {
            MSXML2::IXMLDOMNodePtr node = NULL;
            nodeList->get_item(i, &node);
            LoadAccount(node);
        }
    }
    catch(_com_error& e)
    {
#if defined(_DBG) && defined(_UNICODE)
        _tprintf(_T("*** %s\n"), e.ErrorMessage());
#endif
        return e.Error();
    }

    return S_OK;
}
