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

    localdatabase->AlterTable(pArgc, pArgv);

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

HRESULT DeleteAllData (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
        TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase(pResult, pResultSize);

    localdatabase->DeleteAllData (pArgc, pArgv);

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

    *vResult = static_cast<WStrPtr> (CoTaskMemAlloc(*vResultSize * sizeof(WChar)));

    memcpy(*vResult, pVal, *vResultSize * sizeof(WChar));
}

void TLocalDataBase::SetResult(CAStrPtr pVal)
{
    *vResultSize = (Long) strlen (pVal) + 1;

    *vResult = static_cast<WStrPtr> (CoTaskMemAlloc(*vResultSize * sizeof(WChar)));

    AsciiToUTF16 (*vResult, pVal, *vResultSize);
}

eGoodBad TLocalDataBase::CreateandDeleteDataBase (Word pArgc, WStrPtr* pArgv, eBool pCreateDB)
{
        AStrPtr    server               = nullptr;
        AStrPtr    username             = nullptr;
        AStrPtr    password             = nullptr;
        AStrPtr    databasename         = nullptr;
        CAStrPtr   bad_response         = nullptr;
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

    return rc;
}

eGoodBad TLocalDataBase::DataBase (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, 
                                   eBool pCreateDb, CAStrPtr & pBadResponse)
{
        Driver *              driver;
        Connection *          con     = nullptr;
        Statement *           stmt    = nullptr;
        PreparedStatement *   pstmt   = nullptr;
        ResultSet *           res     = nullptr;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (sql::SQLException& e) {

        pBadResponse = e.what ();
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

                pBadResponse = "Database already exists";
                delete res;
                delete pstmt;
                delete stmt;
                delete con;
                return BAD;

            } else {
                
                stmt->execute ("CREATE DATABASE " + std::string(pDataBaseName));
                con->setSchema (pDataBaseName);
            }
        } else {

            if (!db_exists) {

                pBadResponse = "Database does not exist";
                delete res;
                delete pstmt;
                delete stmt;
                delete con;
                return BAD;

            } else {

                stmt->execute ("DROP DATABASE " + std::string (pDataBaseName));
            }
        }

        delete res;
        delete pstmt;
        delete stmt;
        delete con;

        return GOOD;

    } catch (sql::SQLException& e) {

        pBadResponse = e.what ();
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
        CAStrPtr   bad_response         = nullptr;
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
    SetResult(TABLE_CREATED);
    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    free (column_name);
    free (column_datatype);

    return rc;
}

eGoodBad TLocalDataBase::DeleteTable (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server               = nullptr;
        AStrPtr    username             = nullptr;
        AStrPtr    password             = nullptr;
        AStrPtr    databasename         = nullptr;
        AStrPtr    table_name           = nullptr;
        CAStrPtr   bad_response         = nullptr;
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
    UTF16ToAscii(server, pArgv[0], server_len);

    username_len = (ULong) _tcslen (pArgv[1]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii(username, pArgv[1], username_len);

    password_len = (ULong) _tcslen (pArgv[2]);
    password     = (AStrPtr)malloc((password_len + 1) * sizeof (AChar));
    UTF16ToAscii(password, pArgv[2], password_len);

    databasename_len = (ULong) _tcslen (pArgv[3]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii(databasename, pArgv[3], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[4]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii(table_name, pArgv[4], table_name_len);

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
        CAStrPtr   bad_response            = nullptr;
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

    return rc;
}


eGoodBad TLocalDataBase::CreateLocalTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName, AStrPtr pColumnDataType, CAStrPtr& pBadResponse)
{
        Driver *               driver;
        Connection *           con     = nullptr;
        Statement *            stmt    = nullptr;
        PreparedStatement *    pstmt   = nullptr;
        ResultSet *            res     = nullptr;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (sql::SQLException& e) {

        pBadResponse = e.what ();
        return BAD;
    }

    try {

        stmt = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res = pstmt->executeQuery ();

        if (!res->next ()) {

            pBadResponse = "Database does not exist";
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
        stmt = con->createStatement();

        // Check if the table already exists
        pstmt = con->prepareStatement("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString(1, pDataBaseName);
        pstmt->setString(2, pTableName);
        res = pstmt->executeQuery();

        if (res->next()) {

            // Table already exists
            pBadResponse = "Table already exists";
            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

         stmt->execute("CREATE TABLE " + std::string(pTableName) + " (" + std::string(pColumnName) + " " + std::string(pColumnDataType) + ");");

        delete res;
        delete pstmt;
        delete stmt;
        delete con;

        return GOOD;

    } catch (sql::SQLException& e) {

        pBadResponse = e.what();
        delete res;
        delete pstmt;
        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::DeleteLocalTable(AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, CAStrPtr& pBadResponse)
{
        Driver *               driver;
        Connection *           con     = nullptr;
        Statement *            stmt    = nullptr;
        PreparedStatement *    pstmt   = nullptr;
        ResultSet *            res     = nullptr;

    try {

        driver = get_driver_instance();
        con    = driver->connect(pServer, pUserName, pPassword);

    } catch (sql::SQLException& e) {

        pBadResponse = e.what();
        return BAD;
    }

    try {

        stmt = con->createStatement();

        pstmt = con->prepareStatement("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString(1, pDataBaseName);
        res = pstmt->executeQuery();

        if (!res->next()) {

            pBadResponse = "Database does not exist";
            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        con->setSchema(pDataBaseName);

        delete res;
        delete pstmt;
        delete stmt;

        stmt = con->createStatement();

        pstmt = con->prepareStatement("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString(1, pDataBaseName);
        pstmt->setString(2, pTableName);
        res = pstmt->executeQuery();

        if (res->next()) {

            stmt->execute("DROP TABLE " + std::string(pTableName));

        } else {

            pBadResponse = "Table does not exist";
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

    } catch (sql::SQLException& e) {

        pBadResponse = e.what();
        delete res;
        delete pstmt;
        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::AlterLocalTable(AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName, AStrPtr pColumnDataType, CAStrPtr& pBadResponse)
{
    Driver* driver;
    Connection* con = nullptr;
    Statement* stmt = nullptr;
    PreparedStatement* pstmt = nullptr;
    ResultSet* res = nullptr;

    try {

        driver = get_driver_instance();
        con = driver->connect(pServer, pUserName, pPassword);

    } catch (sql::SQLException& e) {

        pBadResponse = e.what();
        return BAD;
    }

    try {

        stmt = con->createStatement();

        // Check if the database exists
        pstmt = con->prepareStatement("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString(1, pDataBaseName);
        res = pstmt->executeQuery();

        if (!res->next()) {

            pBadResponse = "Database does not exist";
            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        con->setSchema(pDataBaseName);

        delete res;
        res = nullptr;
        delete pstmt;
        pstmt = nullptr;
        delete stmt;
        stmt = nullptr;

        stmt = con->createStatement();

        // Check if the table exists
        pstmt = con->prepareStatement("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString(1, pDataBaseName);
        pstmt->setString(2, pTableName);
        res = pstmt->executeQuery();

        if (!res->next()) {

            pBadResponse = "Table does not exist";
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
        pstmt = con->prepareStatement("SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ? AND COLUMN_NAME = ?");
        pstmt->setString(1, pDataBaseName);
        pstmt->setString(2, pTableName);
        pstmt->setString(3, pColumnName);
        res = pstmt->executeQuery();

        if (res->next()) {

            pBadResponse = "Column already exists";
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

        stmt = con->createStatement();

        stmt->execute("ALTER TABLE " + std::string(pTableName) + " ADD COLUMN " + std::string(pColumnName) + " " + std::string(pColumnDataType) + ";");

        delete stmt;
        delete con;

        return GOOD;

    } catch (sql::SQLException& e) {

        pBadResponse = e.what();
        delete res;
        delete pstmt;
        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::InsertData(Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server               = nullptr;
        AStrPtr    username             = nullptr;
        AStrPtr    password             = nullptr;
        AStrPtr    databasename         = nullptr;
        AStrPtr    table_name           = nullptr;
        AStrPtr    column_names         = nullptr;
        AStrPtr    values               = nullptr;
        CAStrPtr   bad_response         = nullptr;
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
    UTF16ToAscii(server, pArgv[0], server_len);

    username_len = (ULong) _tcslen (pArgv[1]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii(username, pArgv[1], username_len);

    password_len = (ULong) _tcslen (pArgv[2]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii(password, pArgv[2], password_len);

    databasename_len = (ULong) _tcslen (pArgv[3]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii(databasename, pArgv[3], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[4]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii(table_name, pArgv[4], table_name_len);

    column_names_len = (ULong) _tcslen (pArgv[5]);
    column_names     = (AStrPtr) malloc ((column_names_len + 1) * sizeof (AChar));
    UTF16ToAscii(column_names, pArgv[5], column_names_len);

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
    return rc;
}

eGoodBad TLocalDataBase::DeleteAllData (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server                = nullptr;
        AStrPtr    username              = nullptr;
        AStrPtr    password              = nullptr;
        AStrPtr    databasename          = nullptr;
        AStrPtr    table_name            = nullptr;
        CAStrPtr   bad_response          = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        eGoodBad   rc                     = BAD;

    if (pArgc != 5) {

        SetResult (INSUFFICIENT_PARAMS_DELETE_ALL_DATA);

    }
    server_len = (ULong) _tcslen (pArgv[0]);
    server = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii(server, pArgv[0], server_len);

    username_len = (ULong) _tcslen (pArgv[1]);
    username = (AStrPtr)malloc((username_len + 1) * sizeof (AChar));
    UTF16ToAscii(username, pArgv[1], username_len);

    password_len = (ULong) _tcslen (pArgv[2]);
    password = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii(password, pArgv[2], password_len);

    databasename_len = (ULong) _tcslen (pArgv[3]);
    databasename = (AStrPtr)malloc((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii(databasename, pArgv[3], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[4]);
    table_name = (AStrPtr )malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii(table_name, pArgv[4], table_name_len);

    if (DeleteAllDataFromTable (server, username, password, databasename, table_name, bad_response) == BAD) {

        SetResult (bad_response);
        goto end;
    }
    SetResult (ALL_DATA_DELETED);
    rc = GOOD;
end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    return rc;
}

eGoodBad TLocalDataBase::InsertDataIntoTable(AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnNames, AStrPtr pValues, CAStrPtr& pBadResponse)
{
        Driver*               driver   = nullptr;
        Connection *          con      = nullptr;
        Statement *           stmt     = nullptr;
        PreparedStatement *   pstmt    = nullptr;
        ResultSet *           res      = nullptr;

    try {

        driver = get_driver_instance();
        con = driver->connect(pServer, pUserName, pPassword);

        // Check if the database exists
        pstmt = con->prepareStatement("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString(1, pDataBaseName);
        res = pstmt->executeQuery();

        if (!res->next()) {

            // Database does not exist
            pBadResponse = "Database does not exist";
            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema(pDataBaseName);
        pstmt = con->prepareStatement("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString(1, pDataBaseName);
        pstmt->setString(2, pTableName);
        res = pstmt->executeQuery();

        if (!res->next()) {

            // Table does not exist
            pBadResponse = "Table does not exist";
            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        stmt = con->createStatement();
        // Construct the SQL query to insert data into the table
        std::string query = "INSERT INTO " + std::string(pTableName) + " (" + std::string(pColumnNames) + ") VALUES (" + std::string(pValues) + ");";

        // Execute the query
        stmt->execute(query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (sql::SQLException& e) {

        pBadResponse = e.what();
        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::DeleteAllDataFromTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, CAStrPtr& pBadResponse)
{
        Driver *               driver   = nullptr;
        Connection *           con      = nullptr;
        Statement *            stmt     = nullptr;
        PreparedStatement *    pstmt    = nullptr;
        ResultSet *            res      = nullptr;

    try {

        driver = get_driver_instance();
        con = driver->connect(pServer, pUserName, pPassword);

        pstmt = con->prepareStatement("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString(1, pDataBaseName);
        res = pstmt->executeQuery();

        if (!res->next()) {

            pBadResponse = "Database does not exist";
            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema(pDataBaseName);
        pstmt = con->prepareStatement("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString(1, pDataBaseName);
        pstmt->setString(2, pTableName);
        res = pstmt->executeQuery();

        if (!res->next()) {

            // Table does not exist
            pBadResponse = "Table does not exist";
            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        // Delete all data from the table
        stmt = con->createStatement();
        std::string query = "DELETE FROM " + std::string(pTableName) + ";";

        // Execute the query
        stmt->execute(query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (sql::SQLException& e) {

        pBadResponse = e.what();
        delete stmt;
        delete con;
        return BAD;
    }
}
