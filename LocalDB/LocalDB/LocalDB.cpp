#include "common.hpp"

HRESULT CreateDB (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
        TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->CreateandDeleteDataBase (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

HRESULT DeleteDB (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
        TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->CreateandDeleteDataBase (pArgc, pArgv, FALSE);

    delete localdatabase;
    return S_OK;
}

HRESULT CreateTable (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
        TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->CreateTable (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

HRESULT DeleteTable (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
        TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->DeleteTable (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

HRESULT AlterTable (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
        TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->AlterTable (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

HRESULT InsertData (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
        TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->InsertData (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

HRESULT DeleteData (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
        TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->DeleteData (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

HRESULT ShowTableData(Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
    TLocalDataBase* localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->ShowTableData (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

HRESULT UpdateTableData (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
    TLocalDataBase* localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->UpdateTableData (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

HRESULT ForeignKey (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
    TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->ForeignKey (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

TLocalDataBase::TLocalDataBase (StrPtr* pResult, Long* pResultSize)
{
    vResult     = pResult;
    vResultSize = pResultSize;
    vDllPath    = nullptr;
    vDllPathLen = 0;
}

TLocalDataBase::~TLocalDataBase ()
{
    if (vDllPath) {

        free (vDllPath);
        vDllPath = nullptr;
    }
}

void TLocalDataBase::UTF8ToUTF16 (WStrPtr pDestination, CAStrPtr pSource, UInt32 pLength)
{
    MultiByteToWideChar (CP_UTF8, 0, (LPCCH) pSource, pLength, pDestination, pLength * sizeof (Char));

    pDestination[pLength] = (WChar)'\0';
}

void TLocalDataBase::UTF16ToAscii (AStrPtr pDest, CWStrPtr pSrc, Long pSrcLen)
{
    while (pSrcLen--)
        if (*pSrc > MAX_ASCII_CHAR_LIMIT) {

            *pDest++ = '?';
            pSrc++;

        }
        else
            *pDest++ = (AChar)*pSrc++;

    *pDest = '\0';
}

void TLocalDataBase::AsciiToUTF16 (WStrPtr pDestination, CAStrPtr pSource, UInt32 pLength)
{
    while (pLength--) {

        // copy to destination as UTF16
        *(pDestination++) = *(pSource++);
    }

    *pDestination = (WChar)'\0';
}

void TLocalDataBase::SetResult (CWStrPtr pVal)
{
    *vResultSize = (Long) wcslen (pVal) + 1;

    *vResult = static_cast<WStrPtr> (CoTaskMemAlloc (*vResultSize * sizeof (WChar)));

    memcpy (*vResult, pVal, *vResultSize * sizeof (WChar));
}

void TLocalDataBase::SetResult (CAStrPtr pVal)
{
    *vResultSize = (Long) strlen (pVal) + 1;

    *vResult = static_cast<WStrPtr> (CoTaskMemAlloc (*vResultSize * sizeof (WChar)));

    AsciiToUTF16 (*vResult, pVal, *vResultSize);
}

eGoodBad TLocalDataBase::GetDllPath (Char * pDllPath)
{
        HMODULE  module_handle;

    module_handle = GetModuleHandle (DLL_FILE_NAME);

    if (module_handle != NULL) {

        if (GetModuleFileName (module_handle, pDllPath, MAX_PATH_LENGTH) > 0) {

            StrPtr last_slash = _tcsrchr (pDllPath, '\\');

            if (last_slash != nullptr) {

                *(last_slash + 1) = '\0';

                vDllPathLen = (ULong)_tcslen(pDllPath) + 1;
                vDllPath = (StrPtr) malloc ((vDllPathLen) * sizeof(Char));

                _tcscpy_s (vDllPath, vDllPathLen, pDllPath);

                return GOOD;
            }
        }
    }
    return BAD;
}

eGoodBad TLocalDataBase::WriteResponeFile (AStrPtr pResponseData, CStrPtr pFileName)
{
        HANDLE  file;
        CStrPtr file_name                   = nullptr;
        Char    dll_path [MAX_PATH_LENGTH];
        ULong   num_bytes_written;

    file_name = pFileName ? pFileName : DATABASE_TABLE_DATA_FILE_NAME;

    if (GetDllPath (dll_path) != BAD) {

        _tcscat_s (dll_path, (vDllPathLen + (ULong)_tcslen (file_name)), file_name);

        file = CreateFile (dll_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if (file == INVALID_HANDLE_VALUE)
            return BAD;

        WriteFile (file, pResponseData, (ULong) strlen (pResponseData), &num_bytes_written, NULL);

        CloseHandle (file);
    }

    return GOOD;
}

eGoodBad TLocalDataBase::CreateandDeleteDataBase (Word pArgc, WStrPtr* pArgv, eBool pCreateDB)
{
        AStrPtr    server               = nullptr;
        AStrPtr    username             = nullptr;
        AStrPtr    password             = nullptr;
        AStrPtr    databasename         = nullptr;
        StrPtr     bad_response         = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        eGoodBad   rc                   = BAD;

    if (pArgc != 4) {

        SetResult (INSUFFICIENT_PARAMS_CREATEDB);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[0]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[0], server_len);

    username_len = (ULong) _tcslen (pArgv[1]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[1], username_len);

    password_len = (ULong) _tcslen (pArgv[2]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[2], password_len);

    databasename_len = (ULong) _tcslen (pArgv[3]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[3], databasename_len);

    if (DataBase (server, username, password, databasename, pCreateDB, bad_response) == BAD) {

        SetResult (bad_response);
        goto end;
    }

    if (pCreateDB) {

        SetResult (DATABASE_CREATED);

    } else {

        SetResult (DATABASE_DELETED);
    }

    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    if (bad_response) free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::DataBase (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, 
                                   eBool pCreateDb, StrPtr & pBadResponse)
{
        Driver *              driver;
        Connection *          con         = nullptr;
        Statement *           stmt        = nullptr;
        PreparedStatement *   pstmt       = nullptr;
        ResultSet *           res         = nullptr;
        CAStrPtr              bad_resp    = nullptr;
        ULong                 len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException &e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);
        return BAD;
    }

    try {

        stmt  = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        bool db_exists = res->next ();

        if (pCreateDb) {

            if (db_exists) {

                bad_resp     = "Database already exists";
                len          = (ULong) strlen (bad_resp);
                pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

                UTF8ToUTF16 (pBadResponse, bad_resp, len);

                delete res;
                delete pstmt;
                delete stmt;
                delete con;
                return BAD;

            } else {
                
                stmt->execute ("CREATE DATABASE " + string (pDataBaseName));
                con->setSchema (pDataBaseName);
            }
        } else {

            if (!db_exists) {

                bad_resp     = "Database does not exist";
                len          = (ULong) strlen (bad_resp);
                pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

                UTF8ToUTF16 (pBadResponse, bad_resp, len);

                delete res;
                delete pstmt;
                delete stmt;
                delete con;
                return BAD;

            } else {

                stmt->execute ("DROP DATABASE " + string (pDataBaseName));
            }
        }

        delete res;
        delete pstmt;
        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {
        
        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof(Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete res;
        delete pstmt;
        delete stmt;
        delete con;

        return BAD;
    }

    return GOOD;
}

eGoodBad TLocalDataBase::CreateTable (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server               = nullptr;
        AStrPtr    username             = nullptr;
        AStrPtr    password             = nullptr;
        AStrPtr    databasename         = nullptr;
        AStrPtr    table_name           = nullptr;
        AStrPtr    column_name          = nullptr;
        AStrPtr    column_datatype      = nullptr;
        StrPtr     bad_response         = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        ULong      column_name_len;
        ULong      column_datatype_len;
        eGoodBad   rc                   = BAD;

    if (pArgc != 7) {

        SetResult (INSUFFICIENT_PARAMS_CREATE_TABLE);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[0]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[0], server_len);

    username_len = (ULong) _tcslen (pArgv[1]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[1], username_len);

    password_len = (ULong) _tcslen (pArgv[2]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[2], password_len);

    databasename_len = (ULong) _tcslen (pArgv[3]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[3], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[4]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[4], table_name_len);

    column_name_len = (ULong) _tcslen (pArgv[5]);
    column_name    = (AStrPtr) malloc ((column_name_len + 1) * sizeof (AChar));
    UTF16ToAscii(column_name, pArgv[5], column_name_len);

    column_datatype_len = (ULong) _tcslen (pArgv[6]);
    column_datatype     = (AStrPtr) malloc ((column_datatype_len + 1) * sizeof (AChar));
    UTF16ToAscii(column_datatype, pArgv[6], column_datatype_len);

    if (CreateLocalTable (server, username, password, databasename, table_name, column_name, column_datatype, bad_response) == BAD) {

        SetResult (bad_response);
        goto end;
    }

    SetResult (TABLE_CREATED);
    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    free (column_name);
    free (column_datatype);
    if (bad_response) free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::DeleteTable (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server               = nullptr;
        AStrPtr    username             = nullptr;
        AStrPtr    password             = nullptr;
        AStrPtr    databasename         = nullptr;
        AStrPtr    table_name           = nullptr;
        StrPtr     bad_response         = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        eGoodBad   rc                   = BAD;

    if (pArgc != 5) {

        SetResult (INSUFFICIENT_PARAMS_DELETE_TABLE);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[0]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[0], server_len);

    username_len = (ULong) _tcslen (pArgv[1]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[1], username_len);

    password_len = (ULong) _tcslen (pArgv[2]);
    password     = (AStrPtr)malloc((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[2], password_len);

    databasename_len = (ULong) _tcslen (pArgv[3]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[3], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[4]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[4], table_name_len);

    if (DeleteLocalTable (server, username, password, databasename, table_name, bad_response) == BAD) {

        SetResult (bad_response);
        goto end;
    }
    SetResult (TABLE_DELETED);

    rc = GOOD;
end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    if (bad_response) free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::AlterTable (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server                  = nullptr;
        AStrPtr    username                = nullptr;
        AStrPtr    password                = nullptr;
        AStrPtr    databasename            = nullptr;
        AStrPtr    table_name              = nullptr;
        AStrPtr    column_name             = nullptr;
        AStrPtr    column_datatype         = nullptr;
        StrPtr     bad_response            = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        ULong      column_name_len;
        ULong      column_datatype_len;
        eGoodBad   rc                      = BAD;

    if (pArgc != 7) {

        SetResult (INSUFFICIENT_PARAMS_ALTER_TABLE);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[0]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[0], server_len);

    username_len = (ULong) _tcslen (pArgv[1]);
    username     = (AStrPtr)malloc((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[1], username_len);

    password_len = (ULong) _tcslen (pArgv[2]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[2], password_len);

    databasename_len = (ULong) _tcslen (pArgv[3]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[3], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[4]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[4], table_name_len);

    column_name_len = (ULong) _tcslen (pArgv[5]);
    column_name     = (AStrPtr) malloc ((column_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (column_name, pArgv[5], column_name_len);

    column_datatype_len = (ULong) _tcslen (pArgv[6]);
    column_datatype     = (AStrPtr) malloc ((column_datatype_len + 1) * sizeof (AChar));
    UTF16ToAscii (column_datatype, pArgv[6], column_datatype_len);

    if (AlterLocalTable (server, username, password, databasename, table_name, column_name, column_datatype, bad_response) == BAD) {

        SetResult (bad_response);
        goto end;
    }

    SetResult (TABLE_ALTERED);
    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    free (column_name);
    free (column_datatype);
    if (bad_response) free (bad_response);

    return rc;
}


eGoodBad TLocalDataBase::CreateLocalTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName, AStrPtr pColumnDataType, StrPtr& pBadResponse)
{
        Driver *               driver;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        CAStrPtr               bad_resp    = nullptr;
        ULong                  len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        stmt  = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = "Database does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof(Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        con->setSchema (pDataBaseName);

        delete res;
        delete pstmt;
        delete stmt;

        // Now proceed to create the table
        stmt = con->createStatement ();

        // Check if the table already exists
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res = pstmt->executeQuery ();

        if (res->next ()) {

            // Table already exists
            bad_resp     = "Table already exists";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

         stmt->execute ("CREATE TABLE " + string(pTableName) + " (" + string(pColumnName) + " " + string (pColumnDataType) + ");");

        delete res;
        delete pstmt;
        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete res;
        delete pstmt;
        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::DeleteLocalTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, StrPtr& pBadResponse)
{
        Driver *               driver;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        CAStrPtr               bad_resp    = nullptr;
        ULong                  len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        stmt  = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = "Database does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        con->setSchema (pDataBaseName);

        delete res;
        delete pstmt;
        delete stmt;

        stmt  = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        
        res   = pstmt->executeQuery ();

        if (res->next ()) {

            stmt->execute ("DROP TABLE " + string (pTableName));

        } else {

            bad_resp     = "Table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete res;
        delete pstmt;
        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::AlterLocalTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, 
                                          AStrPtr pColumnName, AStrPtr pColumnDataType, StrPtr& pBadResponse)
{
        Driver *               driver;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        CAStrPtr               bad_resp    = nullptr;
        ULong                  len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);
        return BAD;
    }

    try {

        stmt  = con->createStatement ();

        // Check if the database exists
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = "Database does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        con->setSchema (pDataBaseName);

        delete res;
        res = nullptr;

        delete pstmt;
        pstmt = nullptr;

        delete stmt;
        stmt = nullptr;

        stmt  = con->createStatement ();

        // Check if the table exists
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = "Table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        delete res;
        res = nullptr;

        delete pstmt;
        pstmt = nullptr;

        // Check if the column exists
        pstmt = con->prepareStatement ("SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ? AND COLUMN_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        pstmt->setString (3, pColumnName);
        res   = pstmt->executeQuery ();

        if (res->next ()) {

            bad_resp     = "Column already exists";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        delete res;
        res = nullptr;

        delete pstmt;
        pstmt = nullptr;

        stmt = con->createStatement ();

        stmt->execute ("ALTER TABLE " + string(pTableName) + " ADD COLUMN " + string(pColumnName) + " " + string(pColumnDataType) + ";");

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete res;
        delete pstmt;
        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::InsertData (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server               = nullptr;
        AStrPtr    username             = nullptr;
        AStrPtr    password             = nullptr;
        AStrPtr    databasename         = nullptr;
        AStrPtr    table_name           = nullptr;
        AStrPtr    column_names         = nullptr;
        AStrPtr    values               = nullptr;
        StrPtr     bad_response         = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        ULong      column_names_len;
        ULong      values_len;
        eGoodBad   rc                  = BAD;

    if (pArgc != 7) {

        SetResult (INSUFFICIENT_PARAMS_INSERT_DATA);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[0]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[0], server_len);

    username_len = (ULong) _tcslen (pArgv[1]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[1], username_len);

    password_len = (ULong) _tcslen (pArgv[2]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[2], password_len);

    databasename_len = (ULong) _tcslen (pArgv[3]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[3], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[4]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[4], table_name_len);

    column_names_len = (ULong) _tcslen (pArgv[5]);
    column_names     = (AStrPtr) malloc ((column_names_len + 1) * sizeof (AChar));
    UTF16ToAscii (column_names, pArgv[5], column_names_len);

    values_len = (ULong) _tcslen (pArgv[6]);
    values     = (AStrPtr) malloc ((values_len + 1) * sizeof (AChar));
    UTF16ToAscii (values, pArgv[6], values_len);

    if (InsertDataIntoTable (server, username, password, databasename, table_name, column_names, values, bad_response) == BAD) {

        SetResult (bad_response);
        goto end;
    }
    SetResult (DATA_INSERTED);
    rc = GOOD;
end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    free (column_names);
    free (values);
    if (bad_response) free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::DeleteData (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server                = nullptr;
        AStrPtr    username              = nullptr;
        AStrPtr    password              = nullptr;
        AStrPtr    databasename          = nullptr;
        AStrPtr    table_name            = nullptr;
        AStrPtr    condition             = nullptr;
        StrPtr     bad_response          = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        ULong      condition_len;
        eGoodBad   rc                     = BAD;

    if (pArgc != 5 && pArgc != 6) {

        SetResult (INSUFFICIENT_PARAMS_DELETE_DATA);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[0]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[0], server_len);

    username_len = (ULong) _tcslen (pArgv[1]);
    username     = (AStrPtr)malloc((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[1], username_len);

    password_len = (ULong) _tcslen (pArgv[2]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[2], password_len);

    databasename_len = (ULong) _tcslen (pArgv[3]);
    databasename     = (AStrPtr)malloc((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[3], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[4]);
    table_name     = (AStrPtr )malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[4], table_name_len);

    if (pArgc == 6) {

        condition_len = (ULong) _tcslen (pArgv[5]);
        condition     = (AStrPtr) malloc ((condition_len + 1) * sizeof (AChar));
        UTF16ToAscii (condition, pArgv[5], condition_len);
    }
    if (DeleteDataFromTable (pArgc, server, username, password, databasename, table_name, condition, bad_response) == BAD) {

        SetResult (bad_response);
        goto end;
    }
    SetResult (DATA_DELETED);

    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    free (condition);
    if (bad_response) free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::ShowTableData (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server               = nullptr;
        AStrPtr    username             = nullptr;
        AStrPtr    password             = nullptr;
        AStrPtr    databasename         = nullptr;
        AStrPtr    table_name           = nullptr;
        AStrPtr    column_name_1        = nullptr;
        AStrPtr    column_name_2        = nullptr;
        StrPtr     bad_response         = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        ULong      column_name_1_len;
        ULong      column_name_2_len;
        eGoodBad   rc                   = BAD;

    if (pArgc != 5 && pArgc != 6 && pArgc != 7) {

        SetResult (INSUFFICIENT_PARAMS_SHOW_DATA);
        return rc;

    }
    server_len = (ULong) _tcslen (pArgv[0]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[0], server_len);

    username_len = (ULong) _tcslen (pArgv[1]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[1], username_len);

    password_len = (ULong) _tcslen (pArgv[2]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[2], password_len);

    databasename_len = (ULong) _tcslen (pArgv[3]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[3], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[4]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[4], table_name_len);

    if (pArgc == 6) {

        column_name_1_len = (ULong) _tcslen (pArgv[5]);
        column_name_1     = (AStrPtr) malloc ((column_name_1_len + 1) * sizeof (AChar));
        UTF16ToAscii (column_name_1, pArgv[5], column_name_1_len);

    } else if (pArgc == 7) {

        column_name_1_len = (ULong) _tcslen (pArgv[5]);
        column_name_1     = (AStrPtr) malloc ((column_name_1_len + 1) * sizeof (AChar));
        UTF16ToAscii (column_name_1, pArgv[5], column_name_1_len);

        column_name_2_len = (ULong) _tcslen (pArgv[6]);
        column_name_2     = (AStrPtr) malloc ((column_name_2_len + 1) * sizeof (AChar));
        UTF16ToAscii (column_name_2, pArgv[6], column_name_2_len);
    }

    if (ShowTableColumnData (pArgc ,server, username, password, databasename, table_name, column_name_1, column_name_2, bad_response) == BAD) {

        SetResult (bad_response);
        goto end;
    }

    SetResult (SHOW_TABLE_COLUMN_DATA);
    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    free (column_name_1);
    free (column_name_2);
    if (bad_response) free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::UpdateTableData (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server                    = nullptr;
        AStrPtr    username                  = nullptr;
        AStrPtr    password                  = nullptr;
        AStrPtr    databasename              = nullptr;
        AStrPtr    table_name                = nullptr;
        AStrPtr    column_name_value         = nullptr;
        AStrPtr    condition_data            = nullptr;
        StrPtr     bad_response              = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        ULong      column_name_value_len;
        ULong      condition_data_len;
        eGoodBad   rc                        = BAD;

    if (pArgc != 7) {

        SetResult (INSUFFICIENT_PARAMS_UPDATE_COLUMN_DATA);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[0]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[0], server_len);

    username_len = (ULong) _tcslen (pArgv[1]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[1], username_len);

    password_len = (ULong) _tcslen (pArgv[2]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[2], password_len);

    databasename_len = (ULong) _tcslen (pArgv[3]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[3], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[4]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[4], table_name_len);

    column_name_value_len = (ULong) _tcslen (pArgv[5]);
    column_name_value     = (AStrPtr) malloc ((column_name_value_len + 1) * sizeof (AChar));
    UTF16ToAscii (column_name_value, pArgv[5], column_name_value_len);

    condition_data_len = (ULong) _tcslen (pArgv[6]);
    condition_data     = (AStrPtr) malloc ((condition_data_len + 1) * sizeof (AChar));
    UTF16ToAscii (condition_data, pArgv[6], condition_data_len);

    if (UpdateColumnData (server, username, password, databasename, table_name, column_name_value, condition_data, bad_response) == BAD) {

        SetResult (bad_response);
        goto end;
    }

    SetResult (TABLE_COLUMN_DATA_UPDATED);
    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    free (column_name_value);
    free (condition_data);
    if (bad_response) free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::ForeignKey (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server                  = nullptr;
        AStrPtr    username                = nullptr;
        AStrPtr    password                = nullptr;
        AStrPtr    databasename            = nullptr;
        AStrPtr    table_name              = nullptr;
        AStrPtr    reference_table_name    = nullptr;
        AStrPtr    column_name             = nullptr;
        StrPtr     bad_response            = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        ULong      reference_table_name_len;
        ULong      column_name_len;
        eGoodBad   rc                      = BAD;

    if (pArgc != 6 && pArgc != 7) {

        SetResult (INSUFFICIENT_PARAMS_ADD_FOREIGN_KEY);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[0]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[0], server_len);

    username_len = (ULong) _tcslen (pArgv[1]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[1], username_len);

    password_len = (ULong) _tcslen (pArgv[2]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[2], password_len);

    databasename_len = (ULong) _tcslen (pArgv[3]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[3], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[4]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[4], table_name_len);

    column_name_len = (ULong) _tcslen (pArgv[5]);
    column_name     = (AStrPtr)malloc((column_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (column_name, pArgv[5], column_name_len);

    if (pArgc == 7) {

        reference_table_name_len = (ULong) _tcslen (pArgv[6]);
        reference_table_name     = (AStrPtr) malloc ((reference_table_name_len + 1) * sizeof (AChar));
        UTF16ToAscii (reference_table_name, pArgv[6], reference_table_name_len);

        if (AddForeignKey (server, username, password, databasename, table_name, reference_table_name, column_name, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
        SetResult (ADD_FOREIGN_KEY);

    } else {

        if (DropForeignKey (server, username, password, databasename, table_name, column_name, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
        SetResult (DROP_FOREIGN_KEY);
    }

    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    free (column_name);

    if (reference_table_name) free (reference_table_name);
    if (bad_response)         free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::InsertDataIntoTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnNames, AStrPtr pValues, StrPtr& pBadResponse)
{
        Driver*               driver      = nullptr;
        Connection *          con         = nullptr;
        Statement *           stmt        = nullptr;
        PreparedStatement *   pstmt       = nullptr;
        ResultSet *           res         = nullptr;
        string                query;
        CAStrPtr              bad_resp    = nullptr;
        ULong                 len;

    try {
        
        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        // Check if the database exists
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            // Database does not exist
            bad_resp     = "Database does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            // Table does not exist
            bad_resp     = "Table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        stmt = con->createStatement ();

        // Construct the SQL query to insert data into the table
        query = "INSERT INTO " + string (pTableName) + " (" + string (pColumnNames) + ") VALUES (" + string (pValues) + ");";

        // Execute the query
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::DeleteDataFromTable (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pCondition,StrPtr& pBadResponse)
{
        Driver *               driver      = nullptr;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        string                 query;
        CAStrPtr               bad_resp    = nullptr;
        ULong                  len;

    try {
        
        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {
        
        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = "Database does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            // Table does not exist
            bad_resp     = "Table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        // Delete all data from the table
        stmt = con->createStatement ();

        if (pArgc == 6) {

            query = "DELETE FROM " + string (pTableName) + " WHERE " + string (pCondition) + ";";

        } else {

            query = "DELETE FROM " + string (pTableName) + ";";
        }


        // Execute the query
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::ShowTableColumnData(Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumn1, AStrPtr pColumn2, StrPtr& pBadResponse)
{
        Driver *               driver            = nullptr;
        Connection *           con               = nullptr;
        Statement *            stmt              = nullptr;
        PreparedStatement *    pstmt             = nullptr;
        ResultSet *            res               = nullptr;
        ResultSetMetaData *    meta_data         = nullptr;
        AStrPtr                result_string;
        string                 query;
        CAStrPtr               bad_resp          = nullptr;
        ULong                  len;
        int                    column_count;

    try {

        driver = get_driver_instance();
        con    = driver->connect(pServer, pUserName, pPassword);

    } catch (SQLException& e) {
        
        bad_resp     = e.what();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp      = "Database does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        pstmt = nullptr;

        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = "Table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        pstmt = nullptr;

        stmt = con->createStatement ();

        if (pArgc == 6) {

            query = "SELECT " + string (pColumn1) + " FROM " + string (pTableName);

        } else if (pArgc == 7) {

            query = "SELECT " + string (pColumn1) + ", " + string (pColumn2) + " FROM " + string (pTableName);

        } else {

            query = "SELECT * FROM " + string (pTableName);
        }

        res          = stmt->executeQuery (query);
        meta_data    = res->getMetaData ();
        column_count = meta_data->getColumnCount ();

        rapidjson::Document json_document;
        json_document.SetObject ();

        // Array for columns
        rapidjson::Value columns_array (rapidjson::kArrayType);

        for (int i = 1; i <= column_count; ++i) {

            rapidjson::Value column_object (rapidjson::kObjectType);
            rapidjson::Value column_name;
            rapidjson::Value column_type;

            column_name.SetString (meta_data->getColumnName (i).c_str (), json_document.GetAllocator ());
            column_type.SetString (meta_data->getColumnTypeName (i).c_str (), json_document.GetAllocator ());

            column_object.AddMember ("Name", column_name, json_document.GetAllocator ());
            column_object.AddMember ("Type", column_type, json_document.GetAllocator ());

            columns_array.PushBack (column_object, json_document.GetAllocator ());
        }
        json_document.AddMember ("ColumnsData", columns_array, json_document.GetAllocator ());

        // Array for rows
        rapidjson::Value data_array (rapidjson::kArrayType);

        while (res->next ()) {

            rapidjson::Value row_object (rapidjson::kObjectType);

            for (int j = 1; j <= column_count; ++j) {

                rapidjson::Value column_name;
                rapidjson::Value column_value;

                column_name.SetString (meta_data->getColumnName (j).c_str (), json_document.GetAllocator ());
                column_value.SetString (res->getString (j).c_str (), json_document.GetAllocator ());

                row_object.AddMember (column_name, column_value, json_document.GetAllocator ());
            }
            data_array.PushBack (row_object, json_document.GetAllocator ());
        }
        json_document.AddMember ("RowsData", data_array, json_document.GetAllocator ());

        // Convert JSON document to string
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer (buffer);
        json_document.Accept (writer);

        result_string = (AStrPtr) buffer.GetString ();
        WriteResponeFile (result_string);

        delete stmt;
        delete con;
        delete res;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;
        return BAD;
    }
}


eGoodBad TLocalDataBase::UpdateColumnData (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, 
                                           AStrPtr pColumnDataValue, AStrPtr pConditionData, StrPtr& pBadResponse)
{
        Driver *               driver    = nullptr;
        Connection *           con       = nullptr;
        Statement *            stmt      = nullptr;
        PreparedStatement *    pstmt     = nullptr;
        ResultSet *            res       = nullptr;
        string                 query;
        CAStrPtr               bad_resp  = nullptr;
        ULong                  len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = "Database does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res   = pstmt->executeQuery ();

        if (!res->next()) {

            // Table does not exist
            bad_resp     = "Table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        // Delete all data from the table
        stmt  = con->createStatement ();
        query = "UPDATE " + string (pTableName) + " SET " + string (pColumnDataValue) + " WHERE " + string (pConditionData) + ";";

        // Execute the query
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::AddForeignKey (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                        AStrPtr pReferenceTableName, AStrPtr pColumnName, StrPtr& pBadResponse)
{
        Driver *               driver      = nullptr;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        string                 query;
        CAStrPtr               bad_resp    = nullptr;
        ULong                  len;

    try {
        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

        // Check connection
        if (!con) {
           
            bad_resp     = "Connection error";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);
            return BAD;
        }

        con->setSchema (pDataBaseName);

        // Check if the database exists
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = "Database does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        // Check if the main table exists
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = "Table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        // Check if the reference table exists
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pReferenceTableName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = "Reference table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);
            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        // Execute the ALTER TABLE query to add foreign key constraint
        stmt  = con->createStatement ();
        string query = "ALTER TABLE " + string (pTableName) + " ADD CONSTRAINT fk_" + string (pColumnName) + " FOREIGN KEY (" + string (pColumnName) + ") REFERENCES " + string (pReferenceTableName) + "(" + string (pColumnName) + ") ON DELETE CASCADE ON UPDATE CASCADE;";
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::DropForeignKey (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                         AStrPtr pColumnName, StrPtr& pBadResponse)
{
        Driver *               driver      = nullptr;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        string                 query;
        CAStrPtr               bad_resp    = nullptr;
        ULong                  len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

        // Check connection
        if (!con) {

            bad_resp     = "Connection error";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);
            return BAD;
        }

        con->setSchema (pDataBaseName);

        // Check if the database exists
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp = "Database does not exist";
            len = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);
            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        // Check if the table exists
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {
            bad_resp     = "Table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);
            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        // Check if the foreign key constraint related to the specified column exists
        pstmt = con->prepareStatement ("SELECT CONSTRAINT_NAME FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ? AND COLUMN_NAME = ? AND POSITION_IN_UNIQUE_CONSTRAINT IS NOT NULL");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        pstmt->setString (3, pColumnName);
        res = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = "Foreign key constraint for the specified column does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);
            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        string fk_name = res->getString ("CONSTRAINT_NAME");

        delete res;
        delete pstmt;

        // Execute the ALTER TABLE query to drop the foreign key constraint
        stmt  = con->createStatement ();
        query = "ALTER TABLE " + string (pTableName) + " DROP FOREIGN KEY " + fk_name + ";";
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;

        return BAD;
    }
}
