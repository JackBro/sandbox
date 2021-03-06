//--------------------------------------------------------------------------------------
// File: main.cpp
//--------------------------------------------------------------------------------------
#include "stdafx.h"
#include <shellapi.h>

//--------------------------------------------------------------------------------------
// Constants
const TCHAR* kWebLoginBaseUrl   = _T("https://member.gungho.jp/front/member/webgs/rocenter.aspx?SIID=");
const TCHAR* kIdFormLoginName   = _T("ctl00_ctl00_MainContent_TopContent_loginNameControl_txtLoginName");
const TCHAR* kIdFormPassword    = _T("ctl00_ctl00_MainContent_TopContent_passwordControl_txtPassword");
const TCHAR* kIdFormSubmit      = _T("ctl00_ctl00_MainContent_TopContent_ibtNext1");

//--------------------------------------------------------------------------------------
HRESULT RunClient(const _bstr_t& gameID, const _bstr_t& gamePassword)
{
    if ((gameID.length()==0) || (gamePassword.length()==0))
        return E_FAIL;
    if ((Config.execName.length()==0) || (Config.execPath.length()==0))
        return E_FAIL;

    _tprintf(_T("GameID: %s\n"), static_cast<TCHAR*>(gameID));
    _tprintf(_T("OTP: %s\n"), static_cast<TCHAR*>(gamePassword));

    _bstr_t execFull = Config.execPath;
#if 0
    execFull += _T("\\");
    execFull += Config.execName;
#else
    execFull += _T("\\Ragexe.exe");
#endif

    TCHAR param[1024];
    _stprintf(param, _T("1rag1 -w -u:%s -p:%s"), static_cast<TCHAR*>(gameID), static_cast<TCHAR*>(gamePassword));

    HINSTANCE result = ::ShellExecute(NULL, _T("open"), execFull, param, Config.execPath, SW_SHOWNORMAL);
    if (reinterpret_cast<int>(result) > 32)
        return S_OK;
    else
        return E_FAIL;
}

//--------------------------------------------------------------------------------------
void IEWaitComplete(const SHDocVw::IWebBrowser2Ptr& web) throw(_com_error)
{
    int second = Config.ackWait;

    for (int i=0; i<second; i++)
    {
        if ((web->Busy!=VARIANT_TRUE) &&
            (web->ReadyState==READYSTATE_COMPLETE))
            return;
        ::Sleep(1000);
    }

    _com_raise_error(E_FAIL);
}

//--------------------------------------------------------------------------------------
void WebStartup(const SHDocVw::IWebBrowser2Ptr& web) throw(_com_error)
{
    try
    {
        MSHTML::IHTMLDocument3Ptr html3 = web->Document;

        MSHTML::IHTMLObjectElementPtr elmActiveX = html3->getElementById(_T("LoadPrgAx"));
        if (elmActiveX == NULL)
        {
            _tprintf(_T("Please logout currently account.\n"));
            web->put_Visible(VARIANT_TRUE);
            _com_raise_error(E_FAIL);
        }

        MSHTML::IHTMLElementCollectionPtr collection = html3->getElementsByTagName(_T("param"));
        _bstr_t name1 = _T("AttractionID");
        _bstr_t name2 = _T("Password");
        _bstr_t gameID;
        _bstr_t gamePassword;

        for (long i=0; i<collection->length; i++)
        {
            MSHTML::IHTMLParamElementPtr elmParam = collection->item(i, 0);
            if (elmParam->name == name1)
                gameID = elmParam->value;
            if (elmParam->name == name2)
                gamePassword = elmParam->value;
        }

        web->Quit();

        HRESULT hr = RunClient(gameID, gamePassword);
        if (FAILED(hr))
            _com_raise_error(hr);
    }
    catch (_com_error& e)
    {
        throw e;
    }
}

void MasterLogin(const SHDocVw::IWebBrowser2Ptr& web, const ACCOUNTINFO& account) throw(_com_error)
{
    try
    {
        MSHTML::IHTMLDocument3Ptr html3 = web->Document;
        MSHTML::IHTMLInputTextElementPtr elmInput;

        // LoginName
        elmInput = NULL;
        elmInput = html3->getElementById(kIdFormLoginName);
        elmInput->put_value(account.varGunghoID);
#if defined(_DBG)
        _tprintf(_T("LoginName: %s -> %s\n"), static_cast<TCHAR*>(account.varGunghoID), static_cast<TCHAR*>(elmInput->Getvalue()));
#else
        _tprintf(_T("LoginName: %s\n"), static_cast<TCHAR*>(elmInput->Getvalue()));
#endif

        // Password
        elmInput = NULL;
        elmInput = html3->getElementById(kIdFormPassword);
        elmInput->put_value(account.varPassword);
#if defined(_DBG)
        _tprintf(_T("Password: %s -> %s\n"), static_cast<TCHAR*>(account.varPassword), static_cast<TCHAR*>(elmInput->Getvalue()));
#else
        _tprintf(_T("Password: *\n"));
#endif

        // Click submit button
        MSHTML::IHTMLElementPtr elmSubmit = html3->getElementById(kIdFormSubmit);
        elmSubmit->click();

        IEWaitComplete(web);
#if defined(_DBG)
        _tprintf(_T("%s\n"), static_cast<TCHAR*>(web->LocationURL));
#endif
    }
    catch (_com_error& e)
    {
        throw e;
    }
}

//--------------------------------------------------------------------------------------
HRESULT WebLogin(const ACCOUNTINFO& account)
{
    try
    {
        _bstr_t url = kWebLoginBaseUrl;
        url += account.varSIID;
#if defined(_DBG)
        _tprintf(_T("%s\n"), static_cast<TCHAR*>(url));
#endif

        // Create InternetExplorer
        SHDocVw::IWebBrowser2Ptr web = NULL;
        web.CreateInstance(__uuidof(SHDocVw::InternetExplorer));

        // Connect
        web->Navigate(url);
        IEWaitComplete(web);
#if defined(_DBG)
        _tprintf(_T("%s\n"), static_cast<TCHAR*>(web->LocationURL));
#endif

        if (url != web->LocationURL)
            MasterLogin(web, account);

        WebStartup(web);
    }
    catch (_com_error& e)
    {
#if defined(_DBG) && defined(_UNICODE)
        _tprintf(_T("*** %s\n"), e.ErrorMessage());
#endif
        return e.Error();
    }

    return S_OK;
}
