#ifndef SQLSERVER_HPP
#define SQLSERVER_HPP

#define SQL_WINDOWS_AUTHENTICATION                                 "DRIVER={SQL Server};SERVER=%s;Trusted_Connection=yes;"
#define SQL_SQL_SERVER_AUTHENTICATION                              "DRIVER={SQL Server};SERVER=%s;UID=%s;PWD=%s;Trusted_Connection=no;"
#define SQL_ERROR_FORMAT                                           "SQL Driver Message: %s \nSQL State: %s."

#define SQL_GENERAL_LOG_TABLE_NAME                                 "GeneralQueryLogHistory"

#define INCORRECT_SERVER_NAME                                      "Incorrect Server Name Provided"

#define SQL_HANDLE_NOT_INITIALIZE                                  "Failed to initialize SQL handles"
#define SQL_CONNECTION_FAILED                                      "Failed to connect to SQL Server"
#define SQL_RETCODE_100_NO_DATA_AVAILABLE                          "No Data Available"
#define CREATE_SQL_DATABASE_QUERY                                  "CREATE DATABASE [%s];"
#define CREATE_SQL_TABLE_QUERY                                     "CREATE TABLE [%s] (%s);"
#define DROP_SQL_TABLE_QUERY                                       "DROP TABLE [%s];"
#define DROP_SQL_DATABASE_QUERY                                    "DROP DATABASE [%s];"
#define ALTER_SQL_TABLE_QUERY                                      "ALTER TABLE [%s] ADD [%s] %s;"
#define INSERT_SQL_TABLE_DATA_QUERY                                "INSERT INTO %s %s VALUES %s;"
#define SHOW_ALL_SQL_TABLE_DATA_QUERY                              "SELECT * FROM %s;"
#define SHOW_COLUMN1_SQL_TABLE_DATA_QUERY                          "SELECT %s FROM %s;"
#define SHOW_COLUMN2_SQL_TABLE_DATA_QUERY                          "SELECT %s, %s FROM %s;"
#define DELETE_SPECIFIC_SQL_TABLE_DATA_QUERY                       "DELETE FROM %s WHERE %s;"
#define DELETE_ALL_SQL_TABLE_DATA_QUERY                            "DELETE FROM %s;"
#define UPDATE_SQL_TABLE_DATA_QUERY                                "UPDATE %s SET %s WHERE %s;"
#define ADD_SQL_FOREIGN_KEY_QUERY                                  "ALTER TABLE %s ADD CONSTRAINT %s FOREIGN KEY (%s) REFERENCES %s (%s) ON DELETE CASCADE ON UPDATE CASCADE;"
#define DROP_SQL_FOREIGN_KEY_QUERY                                 "ALTER TABLE %s DROP CONSTRAINT %s;"
#define CREATE_SQL_TRIGGER_QUERY                                   "CREATE TRIGGER %s ON %s %s %s AS BEGIN RAISERROR ('%s does not support creation/deletion/updation of data.', 16, 1); END;"
#define CREATE_SQL_TRIGGER_CONDITION_QUERY                         "CREATE TRIGGER %s ON %s %s %s AS BEGIN %s END;"
#define DROP_SQL_TRIGGER_QUERY                                     "DROP TRIGGER %s;"
#define USE_DATABASE_QUERY                                         "USE [%s];"
#define CHECK_DATABASE_EXISTAENCE_QUERY                            "SELECT COUNT(*) FROM sys.databases WHERE name = '%s';"
#define CHECK_TABLE_EXISTAENCE_QUERY                               "SELECT COUNT(*) FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = '%s';"
#define CHECK_COLUMN_EXISTAENCE_QUERY                              "SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = '%s' AND COLUMN_NAME = '%s';"
#define CHECK_FOREIGN_KEY_CONSTRAINT_QUERY                         "SELECT COUNT(*) FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS WHERE TABLE_NAME = '%s' AND CONSTRAINT_NAME = '%s' AND CONSTRAINT_TYPE = 'FOREIGN KEY';"
#define CHECK_TRIGGER_EXISTENCE_QUERY                              "SELECT COUNT(*) FROM sys.triggers WHERE name = '%s'; "
#define CREATE_START_GENERAL_LOG_QUERY                             "CREATE EVENT SESSION [GeneralQueryLog] ON SERVER ADD EVENT sqlserver.sql_statement_completed (ACTION (sqlserver.client_hostname, sqlserver.client_app_name, sqlserver.username, sqlserver.database_name))ADD TARGET package0.event_file (SET filename = N'%sGeneralQueryLog.xel', max_rollover_files = (1)) WITH (STARTUP_STATE = ON); \n ALTER EVENT SESSION [GeneralQueryLog] ON SERVER STATE = START;"
#define CREATE_GENERAL_LOG_TABLE_QUERY                             "CREATE TABLE GeneralQueryLogHistory (client_hostname NVARCHAR(256), client_app_name NVARCHAR(256), username NVARCHAR(256), database_name NVARCHAR(256), statement NVARCHAR(MAX), duration BIGINT, log_time DATETIME DEFAULT GETDATE());"
#define STOP_DROP_GENERAL_LOG_QUERY                                "ALTER EVENT SESSION [GeneralQueryLog] ON SERVER STATE = STOP; DROP EVENT SESSION [GeneralQueryLog] ON SERVER;"
#define DROP_GENERAL_LOG_TABLE_QUERY                               "DROP TABLE GeneralQueryLogHistory"
#define SQL_DELETE_GENERAL_LOG_FILE_FAILED                         "Failed to delete GeneralQueryLog.xel file"
#define INSERT_GENERAL_LOG_DATA_QUERY                              "INSERT INTO GeneralQueryLogHistory (client_hostname, client_app_name, username, database_name, statement, duration) SELECT CAST(event_data AS XML).value('(event/action[@name=\"client_hostname\"]/value)[1]', 'NVARCHAR(256)') AS client_hostname, CAST(event_data AS XML).value('(event/action[@name=\"client_app_name\"]/value)[1]', 'NVARCHAR(256)') AS client_app_name, CAST(event_data AS XML).value('(event/action[@name=\"username\"]/value)[1]', 'NVARCHAR(256)') AS username, CAST(event_data AS XML).value('(event/action[@name=\"database_name\"]/value)[1]', 'NVARCHAR(256)') AS database_name, CAST(event_data AS XML).value('(event/data[@name=\"statement\"]/value)[1]', 'NVARCHAR(MAX)') AS statement, CAST(event_data AS XML).value('(event/data[@name=\"duration\"]/value)[1]', 'BIGINT') AS duration FROM sys.fn_xe_file_target_read_file('%sGeneralQueryLog*.xel', NULL, NULL, NULL) AS logs;"
#define SHOW_GENERAL_LOG_DATA_QUERY                                "select * from GeneralQueryLogHistory;"

#define ALLOC_TSqlServer     new TSqlServer

class TSqlServer {

    public:

                        TSqlServer             (void);
                        ~TSqlServer            (void);

        eGoodBad       SqlDataBase             (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eBool pCreateDb, StrPtr& pBadResponse);
        eGoodBad       SqlCreateLocalTable     (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnNameAndDataType,
                                                StrPtr& pBadResponse);

        eGoodBad       SqlDeleteLocalTable     (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, StrPtr& pBadResponse);
        eGoodBad       SqlAlterLocalTable      (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName,
                                                AStrPtr pColumnDataType, StrPtr& pBadResponse);

        eGoodBad       SqlInsertDataIntoTable  (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr* pTableNameArray,
                                                AStrPtr* pColumnNamesArray, AStrPtr* pValuesArray, ULong ArraySize, StrPtr& pBadResponse);

        eGoodBad       SqlDeleteDataFromTable  (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName,
                                                AStrPtr pTableName, AStrPtr pCondition, StrPtr& pBadResponse);

        eGoodBad       SqlShowTableColumnData  (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,AStrPtr pColumnName, StrPtr pDllPath,
                                                ULong pDllPathLen, AStrPtr& pResultString, StrPtr& pBadResponse);

        eGoodBad       SqlUpdateColumnData     (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                                AStrPtr pColumnDataValue, AStrPtr pConditionData, StrPtr& pBadResponse);

        eGoodBad       SqlAddForeignKey        (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                                AStrPtr pForeignKeyName, AStrPtr pColumnName, AStrPtr pReferenceTableName, StrPtr& pBadResponse);

        eGoodBad       SqlDropForeignKey       (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                                AStrPtr pForeignKeyName, StrPtr& pBadResponse);

        eGoodBad       SqlShowForeignKeyData   (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName,
                                                AStrPtr pTableName, AStrPtr& pResultString, StrPtr& pBadResponse);

        eGoodBad       SqlCreateTrigger        (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTriggerName, AStrPtr pTableName,
                                                AStrPtr pActivationTime, AStrPtr pTriggerEvent, AStrPtr pTriggerCondition, StrPtr& pBadResponse);

        eGoodBad       SqlDropTrigger          (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTriggerName, StrPtr& pBadResponse);
        eGoodBad       SqlSetGeneralLog        (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eActionType pLogAction, StrPtr pDllPath, ULong pDllPathLen, StrPtr& pBadResponse);

        eGoodBad       PerformSqlJoin          (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eJoinType pJoinType, AStrPtr pSelectCondition,
                                                AStrPtr pSetOrFromCondtion, AStrPtr* pTableNameArray, ULong pTableNameArraySize, AStrPtr* pOnConditionArray,
                                                ULong pOnConditionArraySize, AStrPtr pWhereCondition, AStrPtr pOrderByCondition, AStrPtr& pResultString, StrPtr& pBadResponse);

    private:

        eGoodBad        Initialize             ();
        eGoodBad        ConnectSqlServer       (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, StrPtr& pBadResponse);
        eGoodBad        CreateDatabase         (AStrPtr pDataBaseName, eBool pCreateDb, StrPtr& pBadResponse);
        eGoodBad        CreateLocalTable       (AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnNameAndDataType, StrPtr& pBadResponse);
        eGoodBad        DeleteLocalTable       (AStrPtr pDataBaseName, AStrPtr pTableName, StrPtr& pBadResponse);
        eGoodBad        AlterLocalTable        (AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName, AStrPtr pColumnDataType, StrPtr& pBadResponse);
        eGoodBad        InsertDataIntoTable    (AStrPtr pDataBaseName, AStrPtr* pTableNameArray, AStrPtr* pColumnNamesArray, AStrPtr* pValuesArray, ULong ArraySize, StrPtr& pBadResponse);
        eGoodBad        DeleteDataIntoTable    (Word pArgc, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pCondition, StrPtr& pBadResponse);
        eGoodBad        ShowTableColumnData    (Word pArgc, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName,AStrPtr pDllPath, AStrPtr& pResultString, StrPtr& pBadResponse);
        eGoodBad        UpdateColumnData       (AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnDataValue, AStrPtr pConditionData, StrPtr& pBadResponse);
        eGoodBad        AddForeignKey          (AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pForeignKeyName, AStrPtr pColumnName, AStrPtr pReferenceTableName, StrPtr& pBadResponse);
        eGoodBad        DropForeignKey         (AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pForeignKeyName, StrPtr& pBadResponse);
        eGoodBad        ShowForeignKey         (Word pArgc, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr& pResultString, StrPtr& pBadResponse);
        eGoodBad        CreateTrigger          (Word pArgc, AStrPtr pDataBaseName, AStrPtr pTriggerName, AStrPtr pTableName, AStrPtr pActivationTime, AStrPtr pTriggerEvent, 
                                                AStrPtr pTriggerCondition, StrPtr& pBadResponse);

        eGoodBad        DropTrigger            (AStrPtr pDataBaseName, AStrPtr pTriggerName, StrPtr& pBadResponse);
        eGoodBad        SetGeneralLog          (AStrPtr pDataBaseName, eActionType pLogAction, AStrPtr pDllPath, ULong pDllPathLen, StrPtr& pBadResponse);
        eGoodBad        SqlJoin                (AStrPtr pDataBaseName, eJoinType pJoinType, AStrPtr pSelectCondition,
                                                AStrPtr pSetOrFromCondtion, AStrPtr* pTableNameArray, ULong pTableNameArraySize, AStrPtr* pOnConditionArray,
                                                ULong pOnConditionArraySize, AStrPtr pWhereCondition, AStrPtr pOrderByCondition, AStrPtr& pResultString, StrPtr& pBadResponse);
        void            HandleSqlError         (RETCODE pRetCode, StrPtr& pBadResponse);

        SQLRETURN       ExecuteCountQuery      (AStrPtr pQuery, SQLINTEGER& pCount, StrPtr& pBadResponse);
        SQLRETURN       ExecuteRollBackQuery   (StrPtr& pBadResponse);

        SQLHANDLE       GetStatementHandle     ();
        void            FreeStatementHandle    ();
        CAStrPtr        GetDataTypeName        (SQLSMALLINT pDataType);
        eGoodBad        DeleteFiles            (AStrPtr pDllPath, CAStrPtr pFileExtension);
        SQLHANDLE       vEnvHandle;
        SQLHANDLE       vConnHandle;
        SQLHANDLE       vStmtHandle;

};
#endif //SQLSERVER_HPP