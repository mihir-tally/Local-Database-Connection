#ifndef LOCALDB_HPP
#define LOCALDB_HPP
#include "sqlserver.hpp"
#include "mysqlserver.hpp"

using namespace std;
using namespace sql;

#define MAX_PATH_LENGTH                                     1024

#define DATABASE_TABLE_DATA_FILE_NAME                       _TEXT ("tallyprime_sql_data.json")
#define DLL_FILE_NAME                                       _TEXT ("LocalDB.dll")

#define SQL_SERVER_NAME                                     _TEXT ("SqlServer")
#define MYSQL_SERVER_NAME                                   _TEXT ("MySqlServer")

#define DATABASE_CREATED                                    "Database Created Successfully"
#define DATABASE_DELETED                                    "Database Deleted Successfully"
#define TABLE_CREATED                                       "Table Created Successfully"
#define TABLE_DELETED                                       "Table Deleted Successfully"
#define TABLE_ALTERED                                       "Table Altered Successfully"
#define DATA_INSERTED                                       "Data Inserted Successfully"
#define DATA_DELETED                                        "Data Delete Successfully"
#define SHOW_TABLE_COLUMN_DATA                              "Table Column Data fetched Successfully"
#define TABLE_COLUMN_DATA_UPDATED                           "Table Column Data is Successfully Updated"
#define ADD_FOREIGN_KEY                                     "Foreign key is added successfully"
#define DROP_FOREIGN_KEY                                    "Foreign key dropped successfully"
#define SHOW_FOREIGN_KEY                                    "Foreign Key and fetched Successfully"
#define CREATE_TRIGGER                                      "Trigger Created Successfully"
#define DROP_TRIGGER                                        "Trigger dropped Successfully"
#define GENERAL_LOG_ENABLE                                  "General Log Enable Successfully"
#define GENERAL_LOG_DISABLE                                 "General Log Disable Successfully"
#define GENERAL_LOG_DELETE_LOG_DATA                         "General Log Data is Successfully Deleted"
#define INNER_JOIN_EXECUTED                                 "Inner Join Query Executed Successfully"
#define LEFT_JOIN_EXECUTED                                  "Left Join Query Executed Successfully"
#define RIGHT_JOIN_EXECUTED                                 "Right Join Query Executed Successfully"
#define CROSS_JOIN_EXECUTED                                 "Cross Join Query Executed Successfully"
#define DELETE_JOIN_EXECUTED                                "Delete Join Query Executed Successfully"
#define EQUI_JOIN_EXECUTED                                  "Equi Join Query Executed Successfully"
#define NATURAL_JOIN_EXECUTED                               "Natural Join Query Executed Successfully"
#define UPDATE_JOIN_EXECUTED                                "Update Join Query Executed Successfully"

#define DATABASE_NOT_EXIST                                  "Database does not exist"
#define TABLE_NOT_EXIST                                     "Table does not exist"
#define REFERENCE_TABLE_NOT_EXIST                           "Reference table does not exist"
#define FOREIGN_KEY_CONSTRAINT_NOT_EXIST                    "Foreign key constraint does not exist"
#define TRIGGER_NOT_EXIST                                   "Trigger does not exist"
#define DATABASE_ALREADY_EXIST                              "Database already exists"
#define TABLE_ALREADY_EXIST                                 "Table already exists"
#define COLUMN_ALREADY_EXIST                                "Column already exists"
#define TRIGGER_ALREADY_EXIST                               "Trigger already exists"
#define EMPTY_DATA                                          "No Data to Insert"
#define FAILED_TO_WRITE_FILE                                "Failed to write data in file"

#define TDL_ERROR_INCORRECT_ACTION_TYPE                     "Incorrect Action Type Provided"
#define TDL_ERROR_INCORRECT_MYSQL_JOIN_TYPE                 "Incorrect Mysql Join Type Provided"
#define INCORRECT_NUM_OF_DATA_PROVIDED                      "Incorrect Number of Table Name/Column Name/Column Data provided"
#define INCORRECT_SERVER_NAME_SELECT                        "Incorrect Server Name is Provided (MySqlServer or SqlServer)"

#define INSUFFICIENT_PARAMS_CREATEDB                        "Insufficient TDL Parameters. Expected parameters are '<MySqlServer or SqlServer>:<Server>:<User Name>:<Password>:<DataBase Name>'"
#define INSUFFICIENT_PARAMS_CREATE_TABLE                    "Insufficient TDL Parameters. Expected parameters for CreateTable are '<MySqlServer or SqlServer>:<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Column Name and Column Data Type>'"
#define INSUFFICIENT_PARAMS_DELETE_TABLE                    "Insufficient TDL Parameters. Expected parameters for DeleteTable are '<MySqlServer or SqlServer>:<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>'"
#define INSUFFICIENT_PARAMS_ALTER_TABLE                     "Insufficient TDL Parameters. Expected parameters for AlterTable are '<MySqlServer or SqlServer>:<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Column Name>:<Column Data Type>'"
#define INSUFFICIENT_PARAMS_INSERT_DATA                     "Insufficient TDL Parameters. Expected parameters for InsertData are '<MySqlServer or SqlServer>:<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>':<Column Name>:<Column Value>"
#define INSUFFICIENT_PARAMS_DELETE_DATA                     "Insufficient TDL Parameters. Expected parameters for DeleteAllData are '<MySqlServer or SqlServer>:<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>'"
#define INSUFFICIENT_PARAMS_SHOW_DATA                       "Insufficient TDL Parameters. Expected parameters for ShowTableData are '<MySqlServer or SqlServer>:<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Column Name (Optional)>'"
#define INSUFFICIENT_PARAMS_UPDATE_COLUMN_DATA              "Insufficient TDL Parameters. Expected parameters for UpdateTableData are '<MySqlServer or SqlServer>:<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Column Name With Values>:<Condition>'"
#define INSUFFICIENT_PARAMS_ADD_FOREIGN_KEY                 "Insufficient TDL Parameters. Expected parameters for AddForeignKey are '<MySqlServer or SqlServer>:<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Foreign Key Name>:<Reference Table Name>:<Column Name>'"
#define INSUFFICIENT_PARAMS_SHOW_FOREIGN_KEY                "Insufficient TDL Parameters. Expected parameters for ShowForeignKey are '<MySqlServer or SqlServer>:<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>'"
#define INSUFFICIENT_PARAMS_TRIGGERS                        "Insufficient TDL Parameters. Expected parameters for TRIGGERS are '<MySqlServer or SqlServer>:<Server>:<User Name>:<Password>:<DataBase Name>:<Trigger Name>:<Table Name>':<BEFORE/AFTER>:<INSERT/DELETE/UPDATE>:<Condition> (Optional)"
#define INSUFFICIENT_PARAMS_GENERAL_LOG                     "Insufficient TDL Parameters. Expected parameters for GeneralLog are '<MySqlServer or SqlServer>:<Server>:<User Name>:<Password>:<DataBase Name>:<Enable/Disable/Delete>"
#define INSUFFICIENT_PARAMS_MYSQL_JOIN                      "Insufficient TDL Parameters. Expected parameters for MysqlJoin are '<MySqlServer or SqlServer>:<Server>:<User Name>:<Password>:<DataBase Name>:<Select Condition>:<From/Set Condition>:<Table Name>:<On Condition>:<Where Condition> (Optional):<Order By> (Optional)"

enum eServerType {

    UNKNOWN_SERVER_TYPE = 0,
    MYSQL_SERVER_TYPE,
    SQL_SERVER_TYPE,
};

#define ALLOC_TLocalDataBase      new TLocalDataBase

class TLocalDataBase {

    public:

inline              TLocalDataBase             (StrPtr* pResult, Long* pResultSize);
inline              ~TLocalDataBase            ();

        eGoodBad    CreateandDeleteDataBase    (Word pArgc, WStrPtr* pArgv, eBool pCreateDb = TRUE);
        eGoodBad    CreateTable                (Word pArgc, WStrPtr* pArgv);
        eGoodBad    DeleteTable                (Word pArgc, WStrPtr* pArgv);
        eGoodBad    AlterTable                 (Word pArgc, WStrPtr* pArgv);
        eGoodBad    InsertData                 (Word pArgc, WStrPtr* pArgv);
        eGoodBad    DeleteData                 (Word pArgc, WStrPtr* pArgv);
        eGoodBad    ShowTableData              (Word pArgc, WStrPtr* pArgv);
        eGoodBad    UpdateTableData            (Word pArgc, WStrPtr* pArgv);
        eGoodBad    ForeignKey                 (Word pArgc, WStrPtr* pArgv);
        eGoodBad    ShowForeignKey             (Word pArgc, WStrPtr* pArgv);
        eGoodBad    Triggers                   (Word pArgc, WStrPtr* pArgv);
        eGoodBad    GeneralLog                 (Word pArgc, WStrPtr* pArgv);
        eGoodBad    MysqlJoin                  (Word pArgc, WStrPtr* pArgv);

    private:

        void        HandleForeignKeyOperation  (eBool pIsAddOperation, AStrPtr pServer, AStrPtr pUsername, AStrPtr pPassword, AStrPtr pDatabasename, AStrPtr pTableName, AStrPtr pForeignKeyName,
                                                AStrPtr pColumnName, AStrPtr pReferenceTableName, StrPtr& pBadResponse);

        void        HandleTriggerOperation     (eBool pIsAddOperation, Word pArgc, AStrPtr pServer, AStrPtr pUsername, AStrPtr pPassword, AStrPtr pDatabasename, AStrPtr pTriggerName, AStrPtr pTableName,
                                                AStrPtr pActivationTime, AStrPtr pTriggerEvent, AStrPtr pTriggerCondition,StrPtr& pBadResponse);

        eGoodBad    SelectServerAndAlloc       (CStrPtr pSqlServerName);

        void        RemoveSpacesAroundComma    (AStrPtr pStr);
        Long        CountCommaOccurrence       (AStrPtr pStr);
        Long        CountBraces                (AStrPtr pStr);
        Long        CountCommaBetweenBraces    (AStrPtr pStr);
        void        ExtractDetailsFromCSV      (AStrPtr* pArray, ULong pArraySize, AStrPtr pData, ULong* pDataCount);
        void        ExtractDataBetweenBraces   (AStrPtr* pArray, ULong pArraySize, AStrPtr pData, ULong* pDataCount);
        void        FreeArrayDataAndArray      (AStrPtr* pArray, ULong pArraySize);
        eGoodBad    GetDllPath                 ();
        eGoodBad    WriteResponeFile           (AStrPtr pResponseData, CStrPtr pFileName = nullptr);

inline  void        SetResult                  (CWStrPtr pVal);
inline  void        SetResult                  (CAStrPtr pVal);

        StrPtr *       vResult;
        Long *         vResultSize;

        StrPtr         vDllPath;
        ULong          vDllPathLen;

        eActionType    vActionType;
        eJoinType      vJoinType;
        eServerType    vServerType;

        TSqlServer *   vSqlServer;
        TMySqlServer * vMySqlServer;
};

#include "LocalDB.hxx"

#endif //LOCALDB_HPP