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

    localdatabase = ALLOC_TLocalDataBase(pResult, pResultSize);

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

    localdatabase = ALLOC_TLocalDataBase(pResult, pResultSize);

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

TLocalDataBase::TLocalDataBase (StrPtr* pResult, Long* pResultSize)
{
    vResult     = pResult;
    vResultSize = pResultSize;
}

TLocalDataBase::~TLocalDataBase ()
{
}

void TLocalDataBase::UTF8ToUTF16(WStrPtr pDestination, CAStrPtr pSource, UInt32 pLength)
{
    MultiByteToWideChar (CP_UTF8, 0, (LPCCH)pSource, pLength, pDestination, pLength * sizeof(Char));

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

    memcpy(*vResult, pVal, *vResultSize * sizeof (WChar));
}

void TLocalDataBase::SetResult (CAStrPtr pVal)
{
    *vResultSize = (Long) strlen (pVal) + 1;

    *vResult = static_cast<WStrPtr> (CoTaskMemAlloc (*vResultSize * sizeof (WChar)));

    AsciiToUTF16 (*vResult, pVal, *vResultSize);
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
    }
    else {

        SetResult (DATABASE_DELETED);
    }

    rc = GOOD;
end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (bad_response);

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

        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16(pBadResponse, bad_resp, len);
        return BAD;
    }

    try {

        stmt = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res = pstmt->executeQuery ();

        bool db_exists = res->next ();

        if (pCreateDb) {

            if (db_exists) {

                bad_resp = "Database already exists";
                len = (ULong) strlen (bad_resp);
                pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

                UTF8ToUTF16(pBadResponse, bad_resp, len);

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

                bad_resp = "Database does not exist";
                len = (ULong) strlen (bad_resp);
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
        
        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
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
    free (bad_response);

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
    free (bad_response);

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
    free (bad_response);

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

        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        stmt = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp = "Database does not exist";
            len = (ULong) strlen (bad_resp);
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
            bad_resp = "Table already exists";
            len = (ULong) strlen (bad_resp);
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

        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
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

        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        stmt = con->createStatement ();

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
            delete stmt;
            delete con;
            return BAD;
        }

        con->setSchema (pDataBaseName);

        delete res;
        delete pstmt;
        delete stmt;

        stmt = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res = pstmt->executeQuery ();

        if (res->next ()) {

            stmt->execute ("DROP TABLE " + string (pTableName));

        } else {

            bad_resp = "Table does not exist";
            len = (ULong) strlen (bad_resp);
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

        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
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
        con = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);
        return BAD;
    }

    try {

        stmt = con->createStatement ();

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

        stmt = con->createStatement ();

        // Check if the table exists
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp = "Table does not exist";
            len = (ULong) strlen (bad_resp);
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
        res = pstmt->executeQuery ();

        if (res->next ()) {

            bad_resp = "Column already exists";
            len = (ULong) strlen (bad_resp);
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

        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
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
    free (bad_response);
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

    if (pArgc != 5 || pArgc != 6) {

        SetResult (INSUFFICIENT_PARAMS_DELETE_DATA);

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
    free (bad_response);
    free (condition);
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
        StrPtr     result               = nullptr;
        StrPtr     bad_response         = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        ULong      column_name_1_len;
        ULong      column_name_2_len;
        eGoodBad   rc                   = BAD;

    if (pArgc != 5 || pArgc != 6 || pArgc != 7) {

        SetResult (INSUFFICIENT_PARAMS_SHOW_DATA);

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

    if (ShowTableColumnData (pArgc ,server, username, password, databasename, table_name, column_name_1, column_name_2, result, bad_response) == BAD) {

        SetResult(bad_response);
        goto end;
    }
    SetResult(result);
    rc = GOOD;
end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    free (bad_response);
    free (column_name_1);
    free (column_name_2);
    free (result);

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
    free (bad_response);
    free (column_name_value);
    free (condition_data);
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
        con = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        // Check if the database exists
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res = pstmt->executeQuery ();

        if (!res->next ()) {

            // Database does not exist
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
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res = pstmt->executeQuery ();

        if (!res->next ()) {

            // Table does not exist
            bad_resp = "Table does not exist";
            len = (ULong) strlen (bad_resp);
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

        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
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
        con = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {
        
        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

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
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res = pstmt->executeQuery ();

        if (!res->next ()) {

            // Table does not exist
            bad_resp = "Table does not exist";
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

eGoodBad TLocalDataBase::ShowTableColumnData (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumn1, AStrPtr pColumn2, StrPtr& pResult, StrPtr& pBadResponse) 
{
        Driver *               driver            = nullptr;
        Connection *           con               = nullptr;
        Statement *            stmt              = nullptr;
        PreparedStatement *    pstmt             = nullptr;
        ResultSet *            res               = nullptr;
        ResultSetMetaData*     meta_data         = nullptr;
        string                 result_string;
        string                 query;
        CAStrPtr               bad_resp          = nullptr;
        ULong                  len;
        int                    column_count;

    try {
        driver = get_driver_instance ();
        con = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
        UTF8ToUTF16 (pBadResponse, bad_resp, len);
        return BAD;
    }

    try {
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
        pstmt = nullptr;

        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp = "Table does not exist";
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
        pstmt = nullptr;

        stmt = con->createStatement ();

        if (pArgc == 6) {

            query = "SELECT " + string(pColumn1) + " FROM " + string(pTableName);

        } else if (pArgc == 7) {

            query = "SELECT " + string(pColumn1) + ", " + string(pColumn2) + " FROM " + string(pTableName);

        } else {

            query = "SELECT * FROM " + string(pTableName);
        }

        res = stmt->executeQuery (query);
        meta_data = res->getMetaData ();
        column_count = meta_data->getColumnCount ();

        for (int i = 1; i <= column_count; i++) {

            result_string += "\"" + meta_data->getColumnName (i) + "\"";

            if (i != column_count) {

                result_string += ", ";
            }
        }
        result_string += " || ";

        while (res->next ()) {

            for (int j = 1; j <= column_count; j++) {

                result_string += "\"" + res->getString (j) + "\"";

                if (j != column_count) {

                    result_string += ", ";
                }
            }
            if (!res->isLast ()) {

                result_string += " || ";
            }
        }
        
        pResult = (StrPtr) malloc ((result_string.size () + 1) * sizeof (Char));

        UTF8ToUTF16 (pResult, result_string.c_str (), result_string.size ());
        delete stmt;
        delete con;
        delete res;

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
        con = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

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
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res = pstmt->executeQuery ();

        if (!res->next()) {

            // Table does not exist
            bad_resp = "Table does not exist";
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

        // Delete all data from the table
        stmt = con->createStatement ();
        query = "UPDATE " + string (pTableName) + " SET " + string (pColumnDataValue) + " WHERE " + string (pConditionData) + ";";

        // Execute the query
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp = e.what ();
        len      = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;
        return BAD;
    }
}