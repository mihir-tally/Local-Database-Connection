#include "common.hpp"

TSqlServer::TSqlServer (void)
{
    vEnvHandle  = nullptr;
    vConnHandle = nullptr;
    vStmtHandle = nullptr;

}

TSqlServer::~TSqlServer (void)
{
    if (vStmtHandle) 
        SQLFreeHandle (SQL_HANDLE_STMT, vStmtHandle);

    if (vConnHandle) 
        SQLDisconnect (vConnHandle);

    if (vConnHandle) 
        SQLFreeHandle (SQL_HANDLE_DBC, vConnHandle);

    if (vEnvHandle) 
        SQLFreeHandle (SQL_HANDLE_ENV, vEnvHandle);
}

eGoodBad TSqlServer::SqlDataBase (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName,
                                  eBool pCreateDb, StrPtr& pBadResponse)
{
    if (Initialize () == BAD) {

        HandleBadReponse (SQL_HANDLE_NOT_INITIALIZE, pBadResponse);

        return BAD;
    }

    if (ConnectSqlServer (pServer, pUserName, pPassword, pBadResponse) == BAD) {

        return BAD;
    }
    if (CreateDatabase (pDataBaseName, pCreateDb, pBadResponse) == BAD) {

        return BAD;
    }

    return GOOD;
}

eGoodBad TSqlServer::SqlCreateLocalTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, 
                                          AStrPtr pColumnNameAndDataType, StrPtr& pBadResponse) 
{
    if (Initialize () == BAD) {

        HandleBadReponse (SQL_HANDLE_NOT_INITIALIZE, pBadResponse);

        return BAD;
    }

    if (ConnectSqlServer (pServer, pUserName, pPassword, pBadResponse) == BAD) {

        return BAD;
    }
    if (CreateLocalTable (pDataBaseName, pTableName, pColumnNameAndDataType, pBadResponse) == BAD) {

        return BAD;
    }
    return GOOD;
}

eGoodBad TSqlServer::SqlDeleteLocalTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, StrPtr& pBadResponse)
{
    if (Initialize() == BAD) {

        HandleBadReponse (SQL_HANDLE_NOT_INITIALIZE, pBadResponse);

        return BAD;
    }

    if (ConnectSqlServer (pServer, pUserName, pPassword, pBadResponse) == BAD) {

        return BAD;
    }

    if (DeleteLocalTable (pDataBaseName, pTableName, pBadResponse) == BAD) {

        return BAD;
    }
    return GOOD;
}

eGoodBad TSqlServer::SqlAlterLocalTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                         AStrPtr pColumnName, AStrPtr pColumnDataType, StrPtr& pBadResponse)
{
    if (Initialize () == BAD) {

        HandleBadReponse (SQL_HANDLE_NOT_INITIALIZE, pBadResponse);

        return BAD;
    }

    if (ConnectSqlServer (pServer, pUserName, pPassword, pBadResponse) == BAD) {

        return BAD;
    }

    if (AlterLocalTable (pDataBaseName, pTableName, pColumnName, pColumnDataType, pBadResponse) == BAD) {

        return BAD;
    }
    return GOOD;
}

eGoodBad TSqlServer::SqlInsertDataIntoTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr* pTableNameArray,
                                             AStrPtr* pColumnNamesArray, AStrPtr* pValuesArray, ULong pArraySize, StrPtr& pBadResponse)
{
    if (Initialize () == BAD) {

        HandleBadReponse (SQL_HANDLE_NOT_INITIALIZE, pBadResponse);

        return BAD;
    }

    if (ConnectSqlServer (pServer, pUserName, pPassword, pBadResponse) == BAD) {

        return BAD;
    }

    if (InsertDataIntoTable (pDataBaseName, pTableNameArray, pColumnNamesArray, pValuesArray, pArraySize, pBadResponse) == BAD) {

        return BAD;
    }
    return GOOD;
}

eGoodBad TSqlServer::SqlDeleteDataFromTable (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName,
                                               AStrPtr pTableName, AStrPtr pCondition, StrPtr& pBadResponse)
{
    if (Initialize () == BAD) {

        HandleBadReponse (SQL_HANDLE_NOT_INITIALIZE, pBadResponse);

        return BAD;
    }

    if (ConnectSqlServer (pServer, pUserName, pPassword, pBadResponse) == BAD) {

        return BAD;
    }

    if (DeleteDataIntoTable (pArgc, pDataBaseName, pTableName, pCondition, pBadResponse) == BAD) {

        return BAD;
    }
    return GOOD;
}

eGoodBad TSqlServer::SqlShowTableColumnData (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName, StrPtr pDllPath, ULong pDllPathLen, AStrPtr &pResultString, StrPtr& pBadResponse)
{
        AStrPtr dll_path = nullptr;

    if (Initialize () == BAD) {

        HandleBadReponse (SQL_HANDLE_NOT_INITIALIZE, pBadResponse);

        return BAD;
    }

    if (ConnectSqlServer (pServer, pUserName, pPassword, pBadResponse) == BAD) {

        return BAD;
    }

    dll_path = (AStrPtr) malloc ((pDllPathLen + 1) * sizeof(AChar));
    UTF16ToAscii (dll_path, pDllPath, pDllPathLen);

    if (ShowTableColumnData (pArgc, pDataBaseName, pTableName, pColumnName, dll_path, pResultString, pBadResponse) == BAD) {

        free (dll_path);
        return BAD;
    }
    free (dll_path);
    return GOOD;
}

eGoodBad TSqlServer::SqlUpdateColumnData (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                          AStrPtr pColumnDataValue, AStrPtr pConditionData, StrPtr& pBadResponse)
{
    if (Initialize () == BAD) {

        HandleBadReponse (SQL_HANDLE_NOT_INITIALIZE, pBadResponse);

        return BAD;
    }

    if (ConnectSqlServer (pServer, pUserName, pPassword, pBadResponse) == BAD) {

        return BAD;
    }

    if (UpdateColumnData (pDataBaseName, pTableName, pColumnDataValue, pConditionData, pBadResponse) == BAD) {

        return BAD;
    }
    return GOOD;
}

eGoodBad TSqlServer::SqlAddForeignKey (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                       AStrPtr pForeignKeyName, AStrPtr pColumnName, AStrPtr pReferenceTableName, StrPtr& pBadResponse)
{
    if (Initialize () == BAD) {

        HandleBadReponse (SQL_HANDLE_NOT_INITIALIZE, pBadResponse);

        return BAD;
    }

    if (ConnectSqlServer (pServer, pUserName, pPassword, pBadResponse) == BAD) {

        return BAD;
    }

    if (AddForeignKey (pDataBaseName, pTableName, pForeignKeyName, pColumnName, pReferenceTableName, pBadResponse) == BAD) {

        return BAD;
    }
    return GOOD;
}

eGoodBad TSqlServer::SqlDropForeignKey (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                        AStrPtr pForeignKeyName, StrPtr& pBadResponse)
{
    if (Initialize () == BAD) {

        HandleBadReponse (SQL_HANDLE_NOT_INITIALIZE, pBadResponse);

        return BAD;
    }

    if (ConnectSqlServer (pServer, pUserName, pPassword, pBadResponse) == BAD) {

        return BAD;
    }

    if (DropForeignKey (pDataBaseName, pTableName, pForeignKeyName, pBadResponse) == BAD) {

        return BAD;
    }
    return GOOD;
}

eGoodBad TSqlServer::SqlShowForeignKeyData (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName,
                                            AStrPtr pTableName, AStrPtr& pResultString, StrPtr& pBadResponse)
{
    if (Initialize () == BAD) {

        HandleBadReponse (SQL_HANDLE_NOT_INITIALIZE, pBadResponse);

        return BAD;
    }

    if (ConnectSqlServer (pServer, pUserName, pPassword, pBadResponse) == BAD) {

        return BAD;
    }

    if (ShowForeignKey (pArgc, pDataBaseName, pTableName, pResultString, pBadResponse) == BAD) {

        return BAD;
    }
    return GOOD;
}

eGoodBad TSqlServer::SqlCreateTrigger (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTriggerName, AStrPtr pTableName,
                                       AStrPtr pActivationTime, AStrPtr pTriggerEvent, AStrPtr pTriggerCondition, StrPtr& pBadResponse)
{
    if (Initialize () == BAD) {

        HandleBadReponse (SQL_HANDLE_NOT_INITIALIZE, pBadResponse);

        return BAD;
    }

    if (ConnectSqlServer (pServer, pUserName, pPassword, pBadResponse) == BAD) {

        return BAD;
    }

    if (CreateTrigger (pArgc, pDataBaseName, pTriggerName, pTableName, pActivationTime, pTriggerEvent, pTriggerCondition, pBadResponse) == BAD) {

        return BAD;
    }
    return GOOD;
}

eGoodBad TSqlServer::SqlDropTrigger (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTriggerName, StrPtr& pBadResponse)
{
    if (Initialize () == BAD) {

        HandleBadReponse (SQL_HANDLE_NOT_INITIALIZE, pBadResponse);

        return BAD;
    }

    if (ConnectSqlServer (pServer, pUserName, pPassword, pBadResponse) == BAD) {

        return BAD;
    }

    if (DropTrigger (pDataBaseName, pTriggerName, pBadResponse) == BAD) {

        return BAD;
    }
    return GOOD;
}

eGoodBad TSqlServer::SqlSetGeneralLog (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eActionType pLogAction, StrPtr pDllPath, ULong pDllPathLen, StrPtr& pBadResponse)
{
        AStrPtr    dll_path = nullptr;

    if (Initialize () == BAD) {

        HandleBadReponse (SQL_HANDLE_NOT_INITIALIZE, pBadResponse);

        return BAD;
    }

    if (ConnectSqlServer (pServer, pUserName, pPassword, pBadResponse) == BAD) {

        return BAD;
    }

    dll_path = (AStrPtr) malloc ((pDllPathLen + 1) * sizeof(AChar));
    UTF16ToAscii (dll_path, pDllPath, pDllPathLen);

    if (SetGeneralLog (pDataBaseName, pLogAction, dll_path, pDllPathLen, pBadResponse) == BAD) {

        free (dll_path);
        return BAD;
    }
    free (dll_path);
    return GOOD;
}

eGoodBad TSqlServer::PerformSqlJoin (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eJoinType pJoinType, AStrPtr pSelectCondition,
                                     AStrPtr pSetOrFromCondtion, AStrPtr* pTableNameArray, ULong pTableNameArraySize, AStrPtr* pOnConditionArray,
                                     ULong pOnConditionArraySize, AStrPtr pWhereCondition, AStrPtr pOrderByCondition, AStrPtr& pResultString, StrPtr& pBadResponse)
{
    if (Initialize() == BAD) {

        HandleBadReponse (SQL_HANDLE_NOT_INITIALIZE, pBadResponse);

        return BAD;
    }

    if (ConnectSqlServer (pServer, pUserName, pPassword, pBadResponse) == BAD) {

        return BAD;
    }

    if (SqlJoin (pDataBaseName, pJoinType, pSelectCondition, pSetOrFromCondtion, pTableNameArray, pTableNameArraySize, pOnConditionArray, pOnConditionArraySize, pWhereCondition,
                 pOrderByCondition, pResultString, pBadResponse) == BAD) {

        return BAD;
    }
    return GOOD;
}

eGoodBad TSqlServer::Initialize ()
{
    // Allocate the environment handle
    if (SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &vEnvHandle) != SQL_SUCCESS) {
        return BAD;
    }

    // Set the ODBC version environment attribute
    if (SQLSetEnvAttr (vEnvHandle, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0) != SQL_SUCCESS) {
        return BAD;
    }

    // Allocate the connection handle
    if (SQLAllocHandle (SQL_HANDLE_DBC, vEnvHandle, &vConnHandle) != SQL_SUCCESS) {
        return BAD;
    }

    return GOOD;
}

eGoodBad TSqlServer::ConnectSqlServer (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, StrPtr& pBadResponse)
{
        SQLCHAR       conn_str_out [1024];
        AStrPtr       conn_str               = nullptr;
        SQLRETURN     ret_code;
        ULong         conn_str_len;

    if (!pServer || !*pServer) {

        HandleBadReponse (INCORRECT_SERVER_NAME, pBadResponse);
        return BAD;
    }

    if (*pUserName && *pPassword) {

        conn_str_len = (ULong) (strlen (SQL_SQL_SERVER_AUTHENTICATION) + strlen (pServer) + strlen (pUserName) + strlen (pPassword) + 1);
        conn_str     = (AStrPtr) malloc ((conn_str_len + 1) * sizeof (AChar));

        sprintf (conn_str, SQL_SQL_SERVER_AUTHENTICATION, pServer, pUserName, pPassword);

    } else {

        conn_str_len = (ULong) (strlen (SQL_WINDOWS_AUTHENTICATION) + strlen (pServer) + 1);
        conn_str     = (AStrPtr) malloc ((conn_str_len + 1) * sizeof (AChar));

        sprintf (conn_str, SQL_WINDOWS_AUTHENTICATION, pServer);
    }

    ret_code = SQLDriverConnectA (vConnHandle, nullptr, (SQLCHAR*)conn_str, SQL_NTS, conn_str_out, 1024, nullptr, SQL_DRIVER_NOPROMPT);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        free (conn_str);
        return BAD;
    }

    free (conn_str);
    return GOOD;
}

eGoodBad TSqlServer::CreateDatabase (AStrPtr pDataBaseName, eBool pCreateDb, StrPtr& pBadResponse)
{
        SQLRETURN     ret_code;
        AStrPtr       query              = nullptr;
        ULong         query_len;
        eGoodBad      rc                 = BAD;
        SQLINTEGER    db_exists_count    = 0;

    // Query to check if the database exists
    query_len = (ULong) (strlen (CHECK_DATABASE_EXISTAENCE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, CHECK_DATABASE_EXISTAENCE_QUERY, pDataBaseName);

    if (ExecuteCountQuery (query, db_exists_count, pBadResponse) != SQL_SUCCESS) {
        goto end;
    }

    free (query);
    query = nullptr;

    if (pCreateDb) {

        if (db_exists_count > 0) {

            HandleBadReponse (DATABASE_ALREADY_EXIST, pBadResponse);
            return rc;

        } else {

            query_len = (ULong) (strlen (CREATE_SQL_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
            query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

            sprintf (query, CREATE_SQL_DATABASE_QUERY, pDataBaseName);

            ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);

            if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

                HandleSqlError (ret_code, pBadResponse);
                goto end;
            }
        }
    } else {

        if (db_exists_count == 0) {

            HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
            return rc;

        } else {

            query_len = (ULong) (strlen (DROP_SQL_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
            query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

            sprintf (query, DROP_SQL_DATABASE_QUERY, pDataBaseName);
            ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);

            if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

                HandleSqlError (ret_code, pBadResponse);
                goto end;
            }
        }

    }
    rc = GOOD;
end:
    free (query);
    return rc;
}

eGoodBad TSqlServer::CreateLocalTable (AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnNameAndDataType, StrPtr& pBadResponse) 
{
        SQLRETURN     ret_code;
        AStrPtr       query                  = nullptr;
        ULong         query_len;
        eGoodBad      rc                     = BAD;
        SQLINTEGER    schema_exists_count    = 0;
        SQLINTEGER    table_exists_count     = 0;

    //Check if the schema (database) exists
    query_len = (ULong) (strlen (CHECK_DATABASE_EXISTAENCE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof(AChar));

    sprintf (query, CHECK_DATABASE_EXISTAENCE_QUERY, pDataBaseName);

    if (ExecuteCountQuery (query, schema_exists_count, pBadResponse) != SQL_SUCCESS) {
        
        goto end;
    }

    free (query);
    query = nullptr;

    if (schema_exists_count == 0) {

        HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
        return rc;
    }

    //Use the specified database
    query_len = (ULong) (strlen (USE_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, USE_DATABASE_QUERY, pDataBaseName);
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        return rc;
    }

    free (query);
    query = nullptr;

    //Check if the table exists in the schema
    query_len = (ULong) (strlen (CHECK_TABLE_EXISTAENCE_QUERY) + strlen (pTableName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, CHECK_TABLE_EXISTAENCE_QUERY, pTableName);

    if (ExecuteCountQuery (query, table_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    //If the table exists, return an error message
    if (table_exists_count > 0) {

        HandleBadReponse (TABLE_ALREADY_EXIST, pBadResponse);
        return rc;
    }

    //Create the table with the provided column names and data types
    query_len = (ULong) (strlen (CREATE_SQL_TABLE_QUERY) + strlen (pTableName) + strlen (pColumnNameAndDataType) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof(AChar));

    sprintf (query, CREATE_SQL_TABLE_QUERY, pTableName, pColumnNameAndDataType);
    ret_code = SQLExecDirectA (GetStatementHandle (), (SQLCHAR*) query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        goto end;
    }

    rc = GOOD;
end:
    free (query);
    return rc;
}

eGoodBad TSqlServer::DeleteLocalTable (AStrPtr pDataBaseName, AStrPtr pTableName, StrPtr& pBadResponse)
{
        SQLRETURN     ret_code;
        AStrPtr       query                  = nullptr;
        ULong         query_len;
        eGoodBad      rc                     = BAD;
        SQLINTEGER    schema_exists_count    = 0;
        SQLINTEGER    table_exists_count     = 0;

    //Check if the schema (database) exists
    query_len = (ULong) (strlen (CHECK_DATABASE_EXISTAENCE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, CHECK_DATABASE_EXISTAENCE_QUERY, pDataBaseName);

    if (ExecuteCountQuery (query, schema_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (schema_exists_count == 0) {

        HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
        return rc;
    }

    //Use the specified database
    query_len = (ULong) (strlen (USE_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, USE_DATABASE_QUERY, pDataBaseName);
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        return rc;
    }

    free (query);
    query = nullptr;

    //Check if the table exists in the schema
    query_len = (ULong) (strlen (CHECK_TABLE_EXISTAENCE_QUERY) + strlen (pTableName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof(AChar));

    sprintf (query, CHECK_TABLE_EXISTAENCE_QUERY, pTableName);

    if (ExecuteCountQuery (query, table_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    //If the table exists, delete table
    if (table_exists_count > 0) {

        //delete the table 
        query_len = (ULong) (strlen (DROP_SQL_TABLE_QUERY) + strlen (pTableName) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

        sprintf (query, DROP_SQL_TABLE_QUERY, pTableName);
        ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);

        if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

            HandleSqlError (ret_code, pBadResponse);
            goto end;
        }
    } else {

        HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);
        return rc;
    }

    rc = GOOD;
end:
    free (query);
    return rc;
}

eGoodBad TSqlServer::AlterLocalTable (AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName, AStrPtr pColumnDataType, StrPtr& pBadResponse)
{
        SQLRETURN     ret_code;
        AStrPtr       query                  = nullptr;
        ULong         query_len;
        eGoodBad      rc                     = BAD;
        SQLINTEGER    schema_exists_count    = 0;
        SQLINTEGER    table_exists_count     = 0;
        SQLINTEGER    column_exists_count    = 0;

    //Check if the schema (database) exists
    query_len = (ULong) (strlen (CHECK_DATABASE_EXISTAENCE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, CHECK_DATABASE_EXISTAENCE_QUERY, pDataBaseName);

    if (ExecuteCountQuery (query, schema_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (schema_exists_count == 0) {

        HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
        return rc;
    }

    //Use the specified database
    query_len = (ULong) (strlen (USE_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, USE_DATABASE_QUERY, pDataBaseName);
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        return rc;
    }

    free (query);
    query = nullptr;

    //Check if the table exists in the schema
    query_len = (ULong) (strlen (CHECK_TABLE_EXISTAENCE_QUERY) + strlen (pTableName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof(AChar));

    sprintf (query, CHECK_TABLE_EXISTAENCE_QUERY, pTableName);

    if (ExecuteCountQuery (query, table_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (table_exists_count == 0) {

        HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);
        return rc;
    }

    //Check if the column already exists
    query_len = (ULong) (strlen (CHECK_COLUMN_EXISTAENCE_QUERY) + strlen (pTableName) + strlen (pColumnName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, CHECK_COLUMN_EXISTAENCE_QUERY, pTableName, pColumnName);

    if (ExecuteCountQuery (query, column_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (column_exists_count > 0) {

        HandleBadReponse (COLUMN_ALREADY_EXIST, pBadResponse);
        return rc;

    } else {

        //Alter the table to add the new column
        query_len = (ULong) (strlen (ALTER_SQL_TABLE_QUERY) + strlen (pTableName) + strlen (pColumnName) + strlen (pColumnDataType) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

        sprintf (query, ALTER_SQL_TABLE_QUERY, pTableName, pColumnName, pColumnDataType);
        ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);

        if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

            HandleSqlError (ret_code, pBadResponse);
            goto end;
        }
    }

    rc = GOOD;
end:
    free (query);
    return rc;
}

eGoodBad TSqlServer::InsertDataIntoTable (AStrPtr pDataBaseName, AStrPtr* pTableNameArray, AStrPtr* pColumnNamesArray, AStrPtr* pValuesArray, ULong pArraySize, StrPtr& pBadResponse)
{
        SQLRETURN     ret_code;
        AStrPtr       query                  = nullptr;
        ULong         query_len;
        eGoodBad      rc                     = BAD;
        SQLINTEGER    schema_exists_count    = 0;
        SQLINTEGER    table_exists_count     = 0;

    // Check if ArraySize is 0
    if (pArraySize == 0) {

        HandleBadReponse (EMPTY_DATA, pBadResponse);
        return BAD;
    }
    //Check if the schema (database) exists
    query_len = (ULong) (strlen (CHECK_DATABASE_EXISTAENCE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof(AChar));

    sprintf (query, CHECK_DATABASE_EXISTAENCE_QUERY, pDataBaseName);

    if (ExecuteCountQuery (query, schema_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (schema_exists_count == 0) {

        HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
        return rc;
    }
    //Use the specified database
    query_len = (ULong) (strlen (USE_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, USE_DATABASE_QUERY, pDataBaseName);
    ret_code = SQLExecDirectA (GetStatementHandle (), (SQLCHAR*) query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        return rc;
    }

    free (query);
    query = nullptr;

    // Begin the transaction
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*)"BEGIN TRANSACTION", SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        return rc;
    }

    for (ULong i = 0; i < pArraySize; i++) {

        //Check if the table exists in the schema
        query_len = (ULong) (strlen (CHECK_TABLE_EXISTAENCE_QUERY) + strlen (pTableNameArray[i]) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

        sprintf (query, CHECK_TABLE_EXISTAENCE_QUERY, pTableNameArray [i]);

        if (ExecuteCountQuery (query, table_exists_count, pBadResponse) != SQL_SUCCESS) {
            
            ExecuteRollBackQuery (pBadResponse);
            goto end;
        }

        free (query);
        query = nullptr;

        if (table_exists_count == 0) {

            HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);
            ExecuteRollBackQuery (pBadResponse);
            return rc;
        }
        // Construct the SQL query to insert data into the table
        query_len = (ULong) (strlen (INSERT_SQL_TABLE_DATA_QUERY) + strlen (pTableNameArray[i]) + strlen (pColumnNamesArray[i]) + strlen (pValuesArray[i]) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

        sprintf (query, INSERT_SQL_TABLE_DATA_QUERY, pTableNameArray[i], pColumnNamesArray[i], pValuesArray[i]);
        ret_code = SQLExecDirectA (GetStatementHandle (), (SQLCHAR*) query, SQL_NTS);

        if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

            HandleSqlError (ret_code, pBadResponse);
            ExecuteRollBackQuery (pBadResponse);
            goto end;
        }
    }
    // Commit the transaction if all operations are successful
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) "COMMIT", SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        return rc;
    }
    rc = GOOD;
end:
    free (query);
    return rc;
}

eGoodBad TSqlServer::DeleteDataIntoTable (Word pArgc, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pCondition, StrPtr& pBadResponse)
{        
        SQLRETURN     ret_code;
        AStrPtr       query                  = nullptr;
        ULong         query_len;
        eGoodBad      rc                     = BAD;
        SQLINTEGER    schema_exists_count    = 0;
        SQLINTEGER    table_exists_count     = 0;

    //Check if the schema (database) exists
    query_len = (ULong) (strlen (CHECK_DATABASE_EXISTAENCE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, CHECK_DATABASE_EXISTAENCE_QUERY, pDataBaseName);

    if (ExecuteCountQuery (query, schema_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (schema_exists_count == 0) {

        HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
        return rc;
    }

    //Use the specified database
    query_len = (ULong) (strlen (USE_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, USE_DATABASE_QUERY, pDataBaseName);
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        goto end;
    }

    free (query);
    query = nullptr;

    //Check if the table exists in the schema
    query_len = (ULong) (strlen (CHECK_TABLE_EXISTAENCE_QUERY) + strlen (pTableName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof(AChar));

    sprintf (query, CHECK_TABLE_EXISTAENCE_QUERY, pTableName);

    if (ExecuteCountQuery (query, table_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (table_exists_count > 0) {

        // Delete specific data from the table
        if (pArgc == 7) {

            query_len = (ULong) (strlen (DELETE_SPECIFIC_SQL_TABLE_DATA_QUERY) + strlen (pTableName) + strlen (pCondition) + 1);
            query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

            sprintf (query, DELETE_SPECIFIC_SQL_TABLE_DATA_QUERY, pTableName, pCondition);

        } else {
            // Delete all data from the table
            query_len = (ULong) (strlen (DELETE_ALL_SQL_TABLE_DATA_QUERY) + strlen (pTableName) + 1);
            query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

            sprintf (query, DELETE_ALL_SQL_TABLE_DATA_QUERY, pTableName);
        }
        ret_code = SQLExecDirectA (GetStatementHandle (), (SQLCHAR*) query, SQL_NTS);

        if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

            HandleSqlError (ret_code, pBadResponse);
            goto end;
        }

    } else {

        HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);
        return rc;
    }

    rc = GOOD;
end:
    free (query);
    return rc;
}

eGoodBad TSqlServer::ShowTableColumnData (Word pArgc, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName, AStrPtr pDllPath, AStrPtr& pResultString, StrPtr& pBadResponse)
{
        SQLRETURN      ret_code;
        AStrPtr        query                  = nullptr;
        ULong          query_len;
        ULong          result_string_len;
        SQLSMALLINT    column_count;
        SQLINTEGER     schema_exists_count    = 0;
        SQLINTEGER     table_exists_count     = 0;
        eBool          is_general_log         = FALSE;


    if (strcmp (pTableName, "sql.general_log") == 0) {

            is_general_log = TRUE;
    }

    //Check if the schema (database) exists
    query_len = (ULong) (strlen (CHECK_DATABASE_EXISTAENCE_QUERY) + strlen (pDataBaseName) + 1);
    query = (AStrPtr) malloc ((query_len + 1) * sizeof(AChar));

    sprintf(query, CHECK_DATABASE_EXISTAENCE_QUERY, pDataBaseName);

    if (ExecuteCountQuery (query, schema_exists_count, pBadResponse) != SQL_SUCCESS) {

        free(query);
        return BAD;
    }

    free (query);
    query = nullptr;

    if (schema_exists_count == 0) {

        HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
        return BAD;
    }

    //Use the specified database
    query_len = (ULong) (strlen (USE_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof(AChar));

    sprintf (query, USE_DATABASE_QUERY, pDataBaseName);
    ret_code = SQLExecDirectA(GetStatementHandle (), (SQLCHAR*) query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        free (query);
        return BAD;
    }

    free (query);
    query = nullptr;

    if (!is_general_log) {

        //Check if the table exists in the schema
        query_len = (ULong) (strlen (CHECK_TABLE_EXISTAENCE_QUERY) + strlen (pTableName) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

        sprintf (query, CHECK_TABLE_EXISTAENCE_QUERY, pTableName);

        if (ExecuteCountQuery (query, table_exists_count, pBadResponse) != SQL_SUCCESS) {

            free (query);
            return BAD;
        }

        free (query);
        query = nullptr;

        if (table_exists_count == 0) {

            HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);
            return BAD;
        }
    }

    // Prepare the query
    if (is_general_log) {

        query_len = (ULong) (strlen (INSERT_GENERAL_LOG_DATA_QUERY) + strlen (pDllPath) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));
        sprintf (query, INSERT_GENERAL_LOG_DATA_QUERY, pDllPath);

        ret_code = SQLExecDirectA(GetStatementHandle(), (SQLCHAR*)query, SQL_NTS);
        if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

            HandleSqlError (ret_code, pBadResponse);
            free (query);
            return BAD;
        }
        free (query);
        query = nullptr;

        query_len = (ULong) (strlen (SHOW_GENERAL_LOG_DATA_QUERY) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));
        sprintf (query, SHOW_GENERAL_LOG_DATA_QUERY);

    } else if (pArgc == 7) {

        query_len = (ULong) (strlen (SHOW_COLUMN1_SQL_TABLE_DATA_QUERY) + strlen (pColumnName) + strlen (pTableName) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));
        sprintf (query, SHOW_COLUMN1_SQL_TABLE_DATA_QUERY, pColumnName, pTableName);

    } else {

        query_len = (ULong) (strlen (SHOW_ALL_SQL_TABLE_DATA_QUERY) + strlen (pTableName) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));
        sprintf (query, SHOW_ALL_SQL_TABLE_DATA_QUERY, pTableName);
    }

    // Execute the query
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);
    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        free (query);
        return BAD;
    }
    free (query);
    query = nullptr;

    // Process the result set
    SQLNumResultCols (GetStatementHandle (), &column_count);

    rapidjson::Document json_document;
    json_document.SetObject ();

    // Array for columns
    rapidjson::Value columns_array (rapidjson::kArrayType);
    vector<string> column_names;

    for (SQLSMALLINT i = 1; i <= column_count; ++i) {

            AStrPtr     column_name = nullptr;
            SQLSMALLINT data_type;
            SQLSMALLINT name_length;
            SQLSMALLINT column_name_length;

        SQLDescribeColA (GetStatementHandle (), i, nullptr, 0, &column_name_length, nullptr, nullptr, nullptr, nullptr);
        column_name = (AStrPtr) malloc ((column_name_length + 1) * sizeof(AChar));
        SQLDescribeColA (GetStatementHandle (), i, (SQLCHAR*) column_name, (column_name_length + 1) * sizeof (AChar), &name_length, &data_type, nullptr, nullptr, nullptr);

        if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

            HandleSqlError (ret_code, pBadResponse);
            free (query);
            return BAD;
        }

        // Create a JSON object for the column
        rapidjson::Value column_object(rapidjson::kObjectType);
        column_object.AddMember ("Name", rapidjson::Value (column_name, json_document.GetAllocator ()), json_document.GetAllocator ());
        column_object.AddMember ("Type", rapidjson::Value (GetDataTypeName (data_type), json_document.GetAllocator ()), json_document.GetAllocator ());
        columns_array.PushBack (column_object, json_document.GetAllocator ());
        column_names.push_back (column_name);
        free (column_name);
    }

    json_document.AddMember ("ColumnsData", columns_array, json_document.GetAllocator ());

    // Array for rows
    rapidjson::Value data_array (rapidjson::kArrayType);

    while (SQLFetch(GetStatementHandle ()) != SQL_NO_DATA) {

        rapidjson::Value row_object (rapidjson::kObjectType);
        if (column_count == 0) {
            break;
        }
        for (SQLSMALLINT j = 1; j <= column_count; ++j) {

                AStrPtr column_value = nullptr;
                SQLLEN indicator;
                SQLLEN column_length;

            SQLColAttribute(GetStatementHandle (), j, SQL_DESC_LENGTH, nullptr, 0, nullptr, &column_length);
            column_value = (AStrPtr) malloc ((column_length + 1) * sizeof(AChar));
            SQLGetData (GetStatementHandle(), j, SQL_C_CHAR, column_value, (column_length + 1) * sizeof(AChar), &indicator);

            if (indicator == SQL_NULL_DATA) {

                strcpy (column_value, "NULL");
            }

            // Add column name and value to row
            row_object.AddMember(
                rapidjson::Value (column_names [j - 1].c_str (), json_document.GetAllocator ()),  // Column name
                rapidjson::Value (column_value, json_document.GetAllocator ()), // Column value
                json_document.GetAllocator ());

            free (column_value);
        }
        data_array.PushBack (row_object, json_document.GetAllocator ());
    }

    json_document.AddMember ("RowsData", data_array, json_document.GetAllocator ());

    // Write response
    // Convert the JSON document to a string
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer (buffer);
    json_document.Accept (writer);

    pResultString = (AStrPtr) malloc (buffer.GetSize () + 1);
    strcpy (pResultString, buffer.GetString());

    return GOOD;
}

eGoodBad TSqlServer::UpdateColumnData (AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnDataValue, AStrPtr pConditionData, StrPtr& pBadResponse)
{
        SQLRETURN     ret_code;
        AStrPtr       query                  = nullptr;
        ULong         query_len;
        eGoodBad      rc                     = BAD;
        SQLINTEGER    schema_exists_count    = 0;
        SQLINTEGER    table_exists_count     = 0;

        //Check if the schema (database) exists
    query_len = (ULong) (strlen (CHECK_DATABASE_EXISTAENCE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, CHECK_DATABASE_EXISTAENCE_QUERY, pDataBaseName);

    if (ExecuteCountQuery (query, schema_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (schema_exists_count == 0) {

        HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
        return rc;
    }

    //Use the specified database
    query_len = (ULong) (strlen (USE_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, USE_DATABASE_QUERY, pDataBaseName);
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        return rc;
    }

    free (query);
    query = nullptr;

    //Check if the table exists in the schema
    query_len = (ULong) (strlen (CHECK_TABLE_EXISTAENCE_QUERY) + strlen (pTableName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof(AChar));

    sprintf (query, CHECK_TABLE_EXISTAENCE_QUERY, pTableName);

    if (ExecuteCountQuery (query, table_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (table_exists_count == 0) {

        HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);
        return rc;

    } else {
        //Alter the table to add the new column
        query_len = (ULong) (strlen (UPDATE_SQL_TABLE_DATA_QUERY) + strlen (pTableName) + strlen (pColumnDataValue) + strlen (pConditionData) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

        sprintf (query, UPDATE_SQL_TABLE_DATA_QUERY, pTableName, pColumnDataValue, pConditionData);
        ret_code = SQLExecDirectA (GetStatementHandle (), (SQLCHAR*) query, SQL_NTS);

        if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

            HandleSqlError (ret_code, pBadResponse);
            goto end;
        }
    }
    rc = GOOD;
end:
    free (query);
    return rc;
}

eGoodBad TSqlServer::AddForeignKey (AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pForeignKeyName, AStrPtr pColumnName, AStrPtr pReferenceTableName, StrPtr& pBadResponse)
{
        SQLRETURN     ret_code;
        AStrPtr       query                           = nullptr;
        ULong         query_len;
        eGoodBad      rc                              = BAD;
        SQLINTEGER    schema_exists_count             = 0;
        SQLINTEGER    table_exists_count              = 0;
        SQLINTEGER    reference_table_exists_count    = 0;

    //Check if the schema (database) exists
    query_len = (ULong) (strlen (CHECK_DATABASE_EXISTAENCE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, CHECK_DATABASE_EXISTAENCE_QUERY, pDataBaseName);

    if (ExecuteCountQuery (query, schema_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (schema_exists_count == 0) {

        HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
        return rc;
    }

    //Use the specified database
    query_len = (ULong) (strlen (USE_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, USE_DATABASE_QUERY, pDataBaseName);
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        return rc;
    }

    free (query);
    query = nullptr;

    //Check if the table exists in the schema
    query_len = (ULong) (strlen (CHECK_TABLE_EXISTAENCE_QUERY) + strlen (pTableName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof(AChar));

    sprintf (query, CHECK_TABLE_EXISTAENCE_QUERY, pTableName);

    if (ExecuteCountQuery (query, table_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (table_exists_count == 0) {

        HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);
        return rc;

    }

    //Check if the reference table exists in the schema
    query_len = (ULong) (strlen (CHECK_TABLE_EXISTAENCE_QUERY) + strlen (pReferenceTableName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof(AChar));

    sprintf (query, CHECK_TABLE_EXISTAENCE_QUERY, pReferenceTableName);

    if (ExecuteCountQuery (query, reference_table_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (reference_table_exists_count == 0) {

        HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);
        return rc;

    } else {

        // Execute the ALTER TABLE query to add foreign key constraint
        query_len = (ULong) (strlen (ADD_SQL_FOREIGN_KEY_QUERY) + strlen (pTableName) + strlen (pForeignKeyName) + strlen (pColumnName) + strlen(pReferenceTableName) + strlen(pColumnName) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

        sprintf (query, ADD_SQL_FOREIGN_KEY_QUERY, pTableName, pForeignKeyName, pColumnName, pReferenceTableName, pColumnName);
        ret_code = SQLExecDirectA (GetStatementHandle (), (SQLCHAR*) query, SQL_NTS);

        if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

            HandleSqlError (ret_code, pBadResponse);
            goto end;
        }
    }
    rc = GOOD;
end:
    free (query);
    return rc;
}

eGoodBad TSqlServer::DropForeignKey (AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pForeignKeyName, StrPtr& pBadResponse)
{
        SQLRETURN     ret_code;
        AStrPtr       query                           = nullptr;
        ULong         query_len;
        eGoodBad      rc                              = BAD;
        SQLINTEGER    schema_exists_count             = 0;
        SQLINTEGER    table_exists_count              = 0;
        SQLINTEGER    foreign_key_exists_count        = 0;

    //Check if the schema (database) exists
    query_len = (ULong) (strlen (CHECK_DATABASE_EXISTAENCE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, CHECK_DATABASE_EXISTAENCE_QUERY, pDataBaseName);

    if (ExecuteCountQuery (query, schema_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (schema_exists_count == 0) {

        HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
        return rc;
    }

    //Use the specified database
    query_len = (ULong) (strlen (USE_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, USE_DATABASE_QUERY, pDataBaseName);
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        return rc;
    }

    free (query);
    query = nullptr;

    //Check if the table exists in the schema
    query_len = (ULong) (strlen (CHECK_TABLE_EXISTAENCE_QUERY) + strlen (pTableName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof(AChar));

    sprintf (query, CHECK_TABLE_EXISTAENCE_QUERY, pTableName);

    if (ExecuteCountQuery (query, table_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (table_exists_count == 0) {

        HandleBadReponse (TABLE_NOT_EXIST, pBadResponse);
        return rc;

    }

    // Check if the foreign key constraint exists
    query_len = (ULong) (strlen (CHECK_FOREIGN_KEY_CONSTRAINT_QUERY) + strlen (pTableName) + strlen (pForeignKeyName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof(AChar));

    sprintf (query, CHECK_FOREIGN_KEY_CONSTRAINT_QUERY, pTableName, pForeignKeyName);

    if (ExecuteCountQuery (query, foreign_key_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (foreign_key_exists_count == 0) {

        HandleBadReponse (FOREIGN_KEY_CONSTRAINT_NOT_EXIST, pBadResponse);
        return rc;

    } else {

        // Execute the ALTER TABLE query to add foreign key constraint
        query_len = (ULong) (strlen (DROP_SQL_FOREIGN_KEY_QUERY) + strlen (pTableName) + strlen (pForeignKeyName) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

        sprintf (query, DROP_SQL_FOREIGN_KEY_QUERY, pTableName, pForeignKeyName);
        ret_code = SQLExecDirectA (GetStatementHandle (), (SQLCHAR*) query, SQL_NTS);

        if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

            HandleSqlError (ret_code, pBadResponse);
            goto end;
        }
    }
    rc = GOOD;
end:
    free (query);
    return rc;
}

eGoodBad TSqlServer::ShowForeignKey (Word pArgc, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr& pResultString, StrPtr& pBadResponse)
{
        SQLRETURN      ret_code;
        AStrPtr        query         = nullptr;
        SQLSMALLINT    column_count;
        ULong          query_len;
        SQLINTEGER     schema_exists_count    = 0;
        SQLINTEGER     table_exists_count     = 0;

    //Check if the schema (database) exists
    query_len = (ULong) (strlen (CHECK_DATABASE_EXISTAENCE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, CHECK_DATABASE_EXISTAENCE_QUERY, pDataBaseName);

    if (ExecuteCountQuery (query, schema_exists_count, pBadResponse) != SQL_SUCCESS) {

        free (query);
        return BAD;
    }

    free (query);
    query = nullptr;

    if (schema_exists_count == 0) {

        HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
        return BAD;
    }

    //Use the specified database
    query_len = (ULong) (strlen (USE_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, USE_DATABASE_QUERY, pDataBaseName);
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        free (query);
        return BAD;
    }

    free (query);
    query = nullptr;

    if (pArgc == 6) {

        //Check if the table exists in the schema
        query_len = (ULong) (strlen (CHECK_TABLE_EXISTAENCE_QUERY) + strlen (pTableName) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

        sprintf(query, CHECK_TABLE_EXISTAENCE_QUERY, pTableName);

        if (ExecuteCountQuery (query, table_exists_count, pBadResponse) != SQL_SUCCESS) {

            free (query);
            return BAD;
        }

        free (query);
        query = nullptr;

        if (table_exists_count == 0) {

            HandleBadReponse(TABLE_NOT_EXIST, pBadResponse);
            return BAD;
        }
    }

    if (pArgc == 6) {

        query_len = (ULong) (strlen ("SELECT tp.name AS TABLE_NAME, fk.name AS CONSTRAINT_NAME, cp.name AS COLUMN_NAME, tr.name AS REFERENCED_TABLE_NAME, cr.name AS REFERENCED_COLUMN_NAME FROM sys.foreign_keys AS fk INNER JOIN sys.foreign_key_columns AS fkc ON fk.object_id = fkc.constraint_object_id INNER JOIN sys.tables AS tp ON fkc.parent_object_id = tp.object_id INNER JOIN sys.columns AS cp ON fkc.parent_object_id = cp.object_id AND fkc.parent_column_id = cp.column_id INNER JOIN sys.tables AS tr ON fkc.referenced_object_id = tr.object_id INNER JOIN sys.columns AS cr ON fkc.referenced_object_id = cr.object_id AND fkc.referenced_column_id = cr.column_id WHERE tp.name = '%s' ORDER BY fk.name;") + strlen(pTableName) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));
        sprintf (query, "SELECT tp.name AS TABLE_NAME, fk.name AS CONSTRAINT_NAME, cp.name AS COLUMN_NAME, tr.name AS REFERENCED_TABLE_NAME, cr.name AS REFERENCED_COLUMN_NAME FROM sys.foreign_keys AS fk INNER JOIN sys.foreign_key_columns AS fkc ON fk.object_id = fkc.constraint_object_id INNER JOIN sys.tables AS tp ON fkc.parent_object_id = tp.object_id INNER JOIN sys.columns AS cp ON fkc.parent_object_id = cp.object_id AND fkc.parent_column_id = cp.column_id INNER JOIN sys.tables AS tr ON fkc.referenced_object_id = tr.object_id INNER JOIN sys.columns AS cr ON fkc.referenced_object_id = cr.object_id AND fkc.referenced_column_id = cr.column_id WHERE tp.name = '%s' ORDER BY fk.name;", pTableName);

    } else {

        query_len = (ULong) (strlen ("SELECT tp.name AS TABLE_NAME, fk.name AS CONSTRAINT_NAME, cp.name AS COLUMN_NAME, tr.name AS REFERENCED_TABLE_NAME, cr.name AS REFERENCED_COLUMN_NAME FROM sys.foreign_keys AS fk INNER JOIN sys.foreign_key_columns AS fkc ON fk.object_id = fkc.constraint_object_id INNER JOIN  sys.tables AS tp ON fkc.parent_object_id = tp.object_id INNER JOIN sys.columns AS cp ON fkc.parent_object_id = cp.object_id AND fkc.parent_column_id = cp.column_id INNER JOIN sys.tables AS tr ON fkc.referenced_object_id = tr.object_id INNER JOIN sys.columns AS cr ON fkc.referenced_object_id = cr.object_id AND fkc.referenced_column_id = cr.column_id ORDER BY tp.name, fk.name;") + 1);
        query     = (AStrPtr) malloc((query_len + 1) * sizeof(AChar));
        sprintf(query, "SELECT tp.name AS TABLE_NAME, fk.name AS CONSTRAINT_NAME, cp.name AS COLUMN_NAME, tr.name AS REFERENCED_TABLE_NAME, cr.name AS REFERENCED_COLUMN_NAME FROM sys.foreign_keys AS fk INNER JOIN sys.foreign_key_columns AS fkc ON fk.object_id = fkc.constraint_object_id INNER JOIN  sys.tables AS tp ON fkc.parent_object_id = tp.object_id INNER JOIN sys.columns AS cp ON fkc.parent_object_id = cp.object_id AND fkc.parent_column_id = cp.column_id INNER JOIN sys.tables AS tr ON fkc.referenced_object_id = tr.object_id INNER JOIN sys.columns AS cr ON fkc.referenced_object_id = cr.object_id AND fkc.referenced_column_id = cr.column_id ORDER BY tp.name, fk.name;");
    }

    // Execute the query
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*)query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        free (query);
        return BAD;
    }
    free (query);
    query = nullptr;
    // Prepare JSON document for the results
    // Process the result set
    SQLNumResultCols (GetStatementHandle (), &column_count);

    rapidjson::Document json_document;
    json_document.SetObject ();
    vector<string> column_names;

    for (SQLSMALLINT i = 1; i <= column_count; ++i) {

        AStrPtr     column_name = nullptr;
        SQLSMALLINT column_name_length;

        SQLDescribeColA (GetStatementHandle (), i, nullptr, 0, &column_name_length, nullptr, nullptr, nullptr, nullptr);
        column_name = (AStrPtr) malloc ((column_name_length + 1) * sizeof(AChar));
        SQLDescribeColA (GetStatementHandle (), i, (SQLCHAR*) column_name, (column_name_length + 1) * sizeof (AChar), 0, 0, nullptr, nullptr, nullptr);

        if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

            HandleSqlError (ret_code, pBadResponse);
            free (query);
            return BAD;
        }
        column_names.push_back (column_name);
        free (column_name);
        column_name = nullptr;
    }

    // Array for Foreign Key
    rapidjson::Value data_array (rapidjson::kArrayType);

    while (SQLFetch (GetStatementHandle ()) != SQL_NO_DATA) {

        rapidjson::Value row_object (rapidjson::kObjectType);

        for (SQLSMALLINT j = 1; j <= column_count; ++j) {

            AStrPtr column_value     = nullptr;
            SQLLEN  indicator;
            SQLLEN  column_length;

            SQLColAttribute (GetStatementHandle (), j, SQL_DESC_LENGTH, nullptr, 0, nullptr, &column_length);
            column_value = (AStrPtr) malloc ((column_length + 1) * sizeof(AChar));
            SQLGetData(GetStatementHandle (), j, SQL_C_CHAR, column_value, (column_length + 1) * sizeof (AChar), &indicator);

            if (indicator == SQL_NULL_DATA) {

                strcpy (column_value, "NULL");
            }

            // Add column name and value to row
            row_object.AddMember(
                rapidjson::Value (column_names[j - 1].c_str (), json_document.GetAllocator ()),  // Column name
                rapidjson::Value (column_value, json_document.GetAllocator ()), // Column value
                json_document.GetAllocator ());
            free(column_value);
            column_value = nullptr;
        }
        data_array.PushBack (row_object, json_document.GetAllocator ());
    }

    json_document.AddMember ("ForeignKeyTable", data_array, json_document.GetAllocator ());

    // Convert JSON document to string
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    json_document.Accept (writer);
    pResultString = (AStrPtr) malloc (buffer.GetSize() + 1);
    strcpy (pResultString, buffer.GetString ());

    return GOOD;
}

eGoodBad TSqlServer::CreateTrigger (Word pArgc, AStrPtr pDataBaseName, AStrPtr pTriggerName, AStrPtr pTableName,
                                    AStrPtr pActivationTime, AStrPtr pTriggerEvent, AStrPtr pTriggerCondition, StrPtr& pBadResponse)
{
        SQLRETURN     ret_code;
        AStrPtr       query                           = nullptr;
        CAStrPtr      activation_time                 = nullptr;
        ULong         query_len;
        eGoodBad      rc                              = BAD;
        SQLINTEGER    schema_exists_count             = 0;
        SQLINTEGER    trigger_exists_count            = 0;

    //Check if the schema (database) exists
    query_len = (ULong) (strlen (CHECK_DATABASE_EXISTAENCE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, CHECK_DATABASE_EXISTAENCE_QUERY, pDataBaseName);

    if (ExecuteCountQuery (query, schema_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (schema_exists_count == 0) {

        HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
        return rc;
    }

    //Use the specified database
    query_len = (ULong) (strlen (USE_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, USE_DATABASE_QUERY, pDataBaseName);
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        return rc;
    }

    free (query);
    query = nullptr;

    //Check if the trigger exists in the schema
    query_len = (ULong) (strlen (CHECK_TRIGGER_EXISTENCE_QUERY) + strlen (pTriggerName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, CHECK_TRIGGER_EXISTENCE_QUERY, pTriggerName);

    if (ExecuteCountQuery (query, trigger_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (trigger_exists_count > 0) {

        HandleBadReponse (TRIGGER_ALREADY_EXIST, pBadResponse);
        return rc;
    }

    activation_time = (_stricmp (pActivationTime, "BEFORE") == 0) ? "INSTEAD OF" : pActivationTime;

    // Create trigger query
    if (pArgc == 9) {

        query_len = (ULong) (strlen (CREATE_SQL_TRIGGER_QUERY) + strlen (pTriggerName) + strlen (pTableName) + strlen (activation_time) + strlen (pTriggerEvent) + strlen (pTableName) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

        sprintf (query, CREATE_SQL_TRIGGER_QUERY, pTriggerName, pTableName, activation_time, pTriggerEvent, pTableName);

    }
    else {

        query_len = (ULong) (strlen (CREATE_SQL_TRIGGER_CONDITION_QUERY) + strlen (pTriggerName) + strlen (pTableName) + strlen (activation_time) + strlen (pTriggerEvent) + strlen (pTriggerCondition) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

        sprintf (query, CREATE_SQL_TRIGGER_CONDITION_QUERY, pTriggerName, pTableName, activation_time, pTriggerEvent, pTriggerCondition);
    }
    ret_code = SQLExecDirectA(GetStatementHandle (), (SQLCHAR*) query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        goto end;
    }

    rc = GOOD;
end:
    free (query);
    return rc;
}

eGoodBad TSqlServer::DropTrigger (AStrPtr pDataBaseName, AStrPtr pTriggerName, StrPtr& pBadResponse)
{
        SQLRETURN     ret_code;
        AStrPtr       query                           = nullptr;
        CAStrPtr      activation_time                 = nullptr;
        ULong         query_len;
        eGoodBad      rc                              = BAD;
        SQLINTEGER    schema_exists_count             = 0;
        SQLINTEGER    trigger_exists_count            = 0;

    //Check if the schema (database) exists
    query_len = (ULong) (strlen (CHECK_DATABASE_EXISTAENCE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, CHECK_DATABASE_EXISTAENCE_QUERY, pDataBaseName);

    if (ExecuteCountQuery (query, schema_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (schema_exists_count == 0) {

        HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
        return rc;
    }

    //Use the specified database
    query_len = (ULong) (strlen (USE_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, USE_DATABASE_QUERY, pDataBaseName);
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        return rc;
    }

    free (query);
    query = nullptr;

    //Check if the trigger exists in the schema
    query_len = (ULong) (strlen (CHECK_TRIGGER_EXISTENCE_QUERY) + strlen (pTriggerName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, CHECK_TRIGGER_EXISTENCE_QUERY, pTriggerName);

    if (ExecuteCountQuery (query, trigger_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (trigger_exists_count == 0) {

        HandleBadReponse (TRIGGER_NOT_EXIST, pBadResponse);
        return rc;

    } else {
        // Drop the trigger
        query_len = (ULong) (strlen (DROP_SQL_TRIGGER_QUERY) + strlen (pTriggerName) + 1);
        query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

        sprintf (query, DROP_SQL_TRIGGER_QUERY, pTriggerName);
        ret_code = SQLExecDirectA (GetStatementHandle (), (SQLCHAR*) query, SQL_NTS);

        if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

            HandleSqlError (ret_code, pBadResponse);
            goto end;
        }
    }
    rc = GOOD;
end:
    free(query);
    return rc;
}

eGoodBad TSqlServer::SetGeneralLog (AStrPtr pDataBaseName, eActionType pLogAction, AStrPtr pDllPath, ULong pDllPathLen, StrPtr& pBadResponse)
{
        SQLRETURN     ret_code;
        AStrPtr       query                 = nullptr;
        ULong         query_len;
        SQLINTEGER    table_exists_count    = 0;
        SQLINTEGER    schema_exists_count   = 0;
        eGoodBad      rc                    = BAD;

    //Check if the schema (database) exists
    query_len = (ULong) (strlen (CHECK_DATABASE_EXISTAENCE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, CHECK_DATABASE_EXISTAENCE_QUERY, pDataBaseName);

    if (ExecuteCountQuery (query, schema_exists_count, pBadResponse) != SQL_SUCCESS) {

        goto end;
    }

    free (query);
    query = nullptr;

    if (schema_exists_count == 0) {

        HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
        return rc;
    }

    //Use the specified database
    query_len = (ULong) (strlen (USE_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
    query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query, USE_DATABASE_QUERY, pDataBaseName);
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) query, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        return rc;
    }

    free (query);
    query = nullptr;

    switch (pLogAction) {

        case ACTION_TYPE_ENABLE: {
            
            query_len = (ULong) (strlen (CREATE_START_GENERAL_LOG_QUERY) + strlen (pDllPath) + 1);
            query     = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

            sprintf (query, CREATE_START_GENERAL_LOG_QUERY, pDllPath);
            ret_code = SQLExecDirectA (GetStatementHandle (), (SQLCHAR*) query, SQL_NTS);

            if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

                HandleSqlError (ret_code, pBadResponse);
                goto end;
            }

            free (query);
            query = nullptr;

            //Check if the table exists in the schema
            query_len = (ULong) (strlen (CHECK_TABLE_EXISTAENCE_QUERY) + strlen (SQL_GENERAL_LOG_TABLE_NAME) + 1);
            query = (AStrPtr) malloc ((query_len + 1) * sizeof(AChar));

            sprintf (query, CHECK_TABLE_EXISTAENCE_QUERY, SQL_GENERAL_LOG_TABLE_NAME);
            FreeStatementHandle ();
            if (ExecuteCountQuery (query, table_exists_count, pBadResponse) != SQL_SUCCESS) {

                goto end;
            }

            free (query);
            query = nullptr;

            if (table_exists_count == 0) {

                ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) CREATE_GENERAL_LOG_TABLE_QUERY, SQL_NTS);

                if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

                    HandleSqlError (ret_code, pBadResponse);
                    return rc;
                }
            }
        }
        break;
        case ACTION_TYPE_DISABLE: {

            ret_code = SQLExecDirectA (GetStatementHandle (), (SQLCHAR*) STOP_DROP_GENERAL_LOG_QUERY, SQL_NTS);

            if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

                HandleSqlError (ret_code, pBadResponse);
                return rc;
            }

        }
        break;
        case ACTION_TYPE_DELETE: {

            if (DeleteFiles(pDllPath, "*.xel") == BAD) {

                HandleBadReponse(SQL_DELETE_GENERAL_LOG_FILE_FAILED, pBadResponse);
                return rc;
            }

            ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*) DROP_GENERAL_LOG_TABLE_QUERY, SQL_NTS);

            if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

                HandleSqlError (ret_code, pBadResponse);
                return rc;
            }
        }
        break;

    default:
        // Invalid action type
        HandleBadReponse (TDL_ERROR_INCORRECT_ACTION_TYPE, pBadResponse);
        return BAD;
    }

    rc = GOOD;
end:
    free (query);
    return rc;
}

eGoodBad TSqlServer::DeleteFiles (AStrPtr pDllPath, CAStrPtr pFileExtension)
{
        WIN32_FIND_DATAA find_file_data;
        HANDLE           hfind;
        char             dir_to_walk [MAX_PATH];

    snprintf (dir_to_walk, sizeof (dir_to_walk), "%s%s", pDllPath, pFileExtension);

    hfind = FindFirstFileA (dir_to_walk, &find_file_data);

    if (hfind == INVALID_HANDLE_VALUE) {

        return BAD;
    }

    do {
        // Construct the full path to the file
        char full_path [MAX_PATH];
        snprintf (full_path, sizeof(full_path), "%s%s", pDllPath, find_file_data.cFileName);

        // Attempt to delete the file
        if (remove (full_path) != 0) {

            FindClose (hfind);
            return BAD;
        }
    } while (FindNextFileA (hfind, &find_file_data) != 0);

    // Close the handle
    FindClose (hfind);
    return GOOD;
}

eGoodBad TSqlServer::SqlJoin (AStrPtr pDataBaseName, eJoinType pJoinType, AStrPtr pSelectCondition, AStrPtr pSetOrFromCondtion, AStrPtr* pTableNameArray, 
                              ULong pTableNameArraySize, AStrPtr* pOnConditionArray, ULong pOnConditionArraySize, AStrPtr pWhereCondition, AStrPtr pOrderByCondition, 
                              AStrPtr& pResultString, StrPtr& pBadResponse)
{
        SQLRETURN     ret_code;
        AStrPtr       query_str       = nullptr;
        string        query;
        SQLSMALLINT   column_count;
        ULong         query_len;
        SQLINTEGER    schema_exists_count    = 0;

    //Check if the schema (database) exists
    query_len = (ULong) (strlen (CHECK_DATABASE_EXISTAENCE_QUERY) + strlen (pDataBaseName) + 1);
    query_str = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query_str, CHECK_DATABASE_EXISTAENCE_QUERY, pDataBaseName);

    if (ExecuteCountQuery (query_str, schema_exists_count, pBadResponse) != SQL_SUCCESS) {

        free (query_str);
        return BAD;
    }

    free (query_str);
    query_str = nullptr;

    if (schema_exists_count == 0) {

        HandleBadReponse (DATABASE_NOT_EXIST, pBadResponse);
        return BAD;
    }

    //Use the specified database
    query_len = (ULong) (strlen (USE_DATABASE_QUERY) + strlen (pDataBaseName) + 1);
    query_str = (AStrPtr) malloc ((query_len + 1) * sizeof (AChar));

    sprintf (query_str, USE_DATABASE_QUERY, pDataBaseName);
    ret_code = SQLExecDirectA (GetStatementHandle(), (SQLCHAR*)query_str, SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        free (query_str);
        return BAD;
    }

    free (query_str);
    query_str = nullptr;

    switch (pJoinType) {

    case INNER_JOIN_TYPE:
    case LEFT_JOIN_TYPE:
    case RIGHT_JOIN_TYPE:
    case CROSS_JOIN_TYPE:
    case EQUI_JOIN_TYPE:

        query = "SELECT " + string(pSelectCondition) + " FROM " + string(pSetOrFromCondtion);
        for (ULong i = 0; i < pTableNameArraySize; ++i) {

            switch (pJoinType) {

            case INNER_JOIN_TYPE:

                query += " INNER JOIN " + string(pTableNameArray[i]) + " ON " + string(pOnConditionArray[i]);
                break;

            case LEFT_JOIN_TYPE:

                query += " LEFT JOIN " + string(pTableNameArray[i]) + " ON " + string(pOnConditionArray[i]);
                break;

            case RIGHT_JOIN_TYPE:

                query += " RIGHT JOIN " + string(pTableNameArray[i]) + " ON " + string(pOnConditionArray[i]);
                break;

            case CROSS_JOIN_TYPE:

                query += " CROSS JOIN " + string(pTableNameArray[i]);
                break;
            }
        }
        break;

    default:

        // Invalid Join type
        HandleBadReponse (TDL_ERROR_INCORRECT_MYSQL_JOIN_TYPE, pBadResponse);
        return BAD;
    }

    if (pWhereCondition && *pWhereCondition) {

        query += " WHERE " + string (pWhereCondition);
    }

    if (pOrderByCondition && *pOrderByCondition) {

        query += " ORDER BY " + string (pOrderByCondition);
    }
    query += ";";

    ret_code = SQLExecDirectA (GetStatementHandle (), (SQLCHAR*)query.c_str(), SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
        return BAD;

    } else {

        rapidjson::Document json_document;
        json_document.SetObject ();
        SQLNumResultCols (GetStatementHandle(), &column_count);

        //Take Column Name
        vector<string> column_names_array;

        for (SQLSMALLINT i = 1; i <= column_count; ++i) {

            AStrPtr     column_name = nullptr;
            SQLSMALLINT column_name_length;

            SQLDescribeColA(GetStatementHandle (), i, nullptr, 0, &column_name_length, nullptr, nullptr, nullptr, nullptr);
            column_name = (AStrPtr) malloc ((column_name_length + 1) * sizeof (AChar));
            SQLDescribeColA (GetStatementHandle (), i, (SQLCHAR*)column_name, (column_name_length + 1) * sizeof (AChar), 0, 0, nullptr, nullptr, nullptr);

            if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

                HandleSqlError (ret_code, pBadResponse);
                return BAD;
            }
            column_names_array.push_back (column_name);
            free (column_name);
            column_name = nullptr;
        }
        // Array for Foreign Key
        rapidjson::Value data_array (rapidjson::kArrayType);

        while (SQLFetch(GetStatementHandle ()) != SQL_NO_DATA) {

            rapidjson::Value row_object (rapidjson::kObjectType);

            if (column_count == 0) {
                break;
            }

            for (SQLSMALLINT j = 1; j <= column_count; ++j) {

                AStrPtr column_value = nullptr;
                SQLLEN  indicator;
                SQLLEN  column_length;

                SQLColAttribute (GetStatementHandle (), j, SQL_DESC_LENGTH, nullptr, 0, nullptr, &column_length);
                column_value = (AStrPtr) malloc ((column_length + 2) * sizeof (AChar));
                SQLGetData (GetStatementHandle (), j, SQL_C_CHAR, column_value, (column_length + 2) * sizeof (AChar), &indicator);

                if (indicator != SQL_NULL_DATA) {

                    // Add column name and value to row
                    row_object.AddMember(
                        rapidjson::Value(column_names_array[j - 1].c_str(), json_document.GetAllocator()),  // Column name
                        rapidjson::Value(column_value, json_document.GetAllocator()), // Column value
                        json_document.GetAllocator());
                }
                free (column_value);
                column_value = nullptr;
            }
            data_array.PushBack (row_object, json_document.GetAllocator());
        }

        json_document.AddMember ("Join Data", data_array, json_document.GetAllocator ());
        // Convert JSON document to string
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        json_document.Accept (writer);
        pResultString = (AStrPtr) malloc (buffer.GetSize () + 1);
        strcpy (pResultString, buffer.GetString ());
    }
    return GOOD;
}

SQLRETURN TSqlServer::ExecuteCountQuery (AStrPtr pQuery, SQLINTEGER& pCount, StrPtr& pBadResponse) 
{
    SQLRETURN ret_code = SQLExecDirectA(GetStatementHandle(), (SQLCHAR*)pQuery, SQL_NTS);

    if (ret_code == SQL_SUCCESS || ret_code == SQL_SUCCESS_WITH_INFO) {

        // Fetch the result and use SQLGetData to retrieve the count
        ret_code = SQLFetch(GetStatementHandle());

        if (ret_code == SQL_SUCCESS || ret_code == SQL_SUCCESS_WITH_INFO) {

            // Fetch the count (assuming it's in the first column)
            SQLGetData(GetStatementHandle (), 1, SQL_C_LONG, &pCount, sizeof (pCount), nullptr);
        }

        // Free the statement handle after fetching data
        FreeStatementHandle ();

    } else {

        HandleSqlError (ret_code, pBadResponse);
    }

    return ret_code;
}

SQLRETURN TSqlServer::ExecuteRollBackQuery (StrPtr& pBadResponse)
{
    // Rollback the transaction in case of an error
    SQLRETURN ret_code = SQLExecDirectA(GetStatementHandle(), (SQLCHAR*) "ROLLBACK", SQL_NTS);

    if (ret_code != SQL_SUCCESS && ret_code != SQL_SUCCESS_WITH_INFO) {

        HandleSqlError (ret_code, pBadResponse);
    }
    return ret_code;
}

SQLHANDLE TSqlServer::GetStatementHandle ()
{
    if (vStmtHandle == nullptr) {

        SQLAllocHandle (SQL_HANDLE_STMT, vConnHandle, &vStmtHandle);
    }
    return vStmtHandle;
}

void TSqlServer::FreeStatementHandle ()
{
    if (vStmtHandle != nullptr) {

        SQLFreeStmt (vStmtHandle, SQL_CLOSE);
    }
}

void TSqlServer::HandleSqlError (RETCODE pRetCode, StrPtr& pBadResponse) 
{
        SQLCHAR        message [1024];
        SQLHANDLE      handle           = nullptr;
        AStrPtr        bad_resp;
        string         all_errors; // For accumulating error messages
        ULong          bad_resp_len;
        SQLCHAR        sql_state [6];
        SQLINTEGER     native_error;
        SQLSMALLINT    handle_type;
        SQLSMALLINT    i                = 0;// Record number

    // Handle specific cases based on pRetCode
    if (pRetCode == SQL_NO_DATA) {
        // SQL_NO_DATA (100) means no more data, not an error
        HandleBadReponse (SQL_RETCODE_100_NO_DATA_AVAILABLE, pBadResponse);
        return;
    }
    // Determine the correct handle type and handle
    if (pRetCode == SQL_ERROR || pRetCode == SQL_NEED_DATA || pRetCode == SQL_INVALID_HANDLE) {

        // If the error is related to statement execution, use the statement handle.
        // Otherwise, use the connection handle.
        if (vStmtHandle != nullptr) {

            handle      = vStmtHandle;
            handle_type = SQL_HANDLE_STMT;

        } else {
            handle      = vConnHandle;
            handle_type = SQL_HANDLE_DBC;
        }

    } else if (pRetCode == SQL_STILL_EXECUTING) {

        // For SQL_STILL_EXECUTING, it's likely a statement handle, so we use it.
        handle      = vStmtHandle;
        handle_type = SQL_HANDLE_STMT;

    } else {
        // If we don’t handle these codes, return early
        return;
    }

    // Retrieve error message using SQLGetDiagRec
    while (SQLGetDiagRecA (handle_type, handle, ++i, sql_state, &native_error, message, sizeof(message), nullptr) == SQL_SUCCESS) {
        // Format the error message
        string error_msg = string ((AStrPtr) message) + " (SQL State: " + (char *) sql_state + ")";
        all_errors += error_msg + "\n"; // Append to all_errors
    }

    // If there are errors, handle them
    if (!all_errors.empty ()) {

        HandleBadReponse (all_errors.c_str (), pBadResponse); // Pass the concatenated error messages
    }
}

CAStrPtr TSqlServer::GetDataTypeName (SQLSMALLINT pDataType) 
{
    switch (pDataType) {

        case SQL_CHAR:                         return "CHAR";
        case SQL_VARCHAR:                      return "VARCHAR";
        case SQL_INTEGER:                      return "INTEGER";
        case SQL_SMALLINT:                     return "SMALLINT";
        case SQL_FLOAT:                        return "FLOAT";
        case SQL_REAL:                         return "REAL";
        case SQL_DOUBLE:                       return "DOUBLE";
        case SQL_NUMERIC:                      return "NUMERIC";
        case SQL_DECIMAL:                      return "DECIMAL";
        case SQL_DATE:                         return "DATE";
        case SQL_TIME:                         return "TIME";
        case SQL_TIMESTAMP:                    return "TIMESTAMP";
        case SQL_BINARY:                       return "BINARY";
        case SQL_VARBINARY:                    return "VARBINARY";
        case SQL_LONGVARBINARY:                return "LONGVARBINARY";
        case SQL_BIGINT:                       return "BIGINT";
        case SQL_TINYINT:                      return "TINYINT";
        case SQL_BIT:                          return "BIT";
        case SQL_WCHAR:                        return "WCHAR";
        case SQL_WVARCHAR:                     return "WVARCHAR";
        case SQL_WLONGVARCHAR:                 return "WLONGVARCHAR";
        case SQL_GUID:                         return "GUID";
        case SQL_LONGVARCHAR:                  return "LONGVARCHAR";
        case SQL_TYPE_DATE:                    return "TYPE_DATE";
        case SQL_TYPE_TIME:                    return "TYPE_TIME";
        case SQL_TYPE_TIMESTAMP:               return "TYPE_TIMESTAMP";
        case SQL_INTERVAL_YEAR:                return "INTERVAL_YEAR";
        case SQL_INTERVAL_MONTH:               return "INTERVAL_MONTH";
        case SQL_INTERVAL_DAY:                 return "INTERVAL_DAY";
        case SQL_INTERVAL_HOUR:                return "INTERVAL_HOUR";
        case SQL_INTERVAL_MINUTE:              return "INTERVAL_MINUTE";
        case SQL_INTERVAL_SECOND:              return "INTERVAL_SECOND";
        case SQL_INTERVAL_YEAR_TO_MONTH:       return "INTERVAL_YEAR_TO_MONTH";
        case SQL_INTERVAL_DAY_TO_HOUR:         return "INTERVAL_DAY_TO_HOUR";
        case SQL_INTERVAL_DAY_TO_MINUTE:       return "INTERVAL_DAY_TO_MINUTE";
        case SQL_INTERVAL_DAY_TO_SECOND:       return "INTERVAL_DAY_TO_SECOND";
        case SQL_INTERVAL_HOUR_TO_MINUTE:      return "INTERVAL_HOUR_TO_MINUTE";
        case SQL_INTERVAL_HOUR_TO_SECOND:      return "INTERVAL_HOUR_TO_SECOND";
        case SQL_INTERVAL_MINUTE_TO_SECOND:    return "INTERVAL_MINUTE_TO_SECOND";
        default:                               return "UNKNOWN";
    }
}

