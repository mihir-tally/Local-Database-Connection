#ifndef LOCALDB_HPP
#define LOCALDB_HPP

using namespace std;
using namespace sql;

#define MAX_PATH_LENGTH                                     1024

#define DATABASE_TABLE_DATA_FILE_NAME                       _TEXT ("tallyprime_sql_data.json")
#define DLL_FILE_NAME                                       _TEXT ("LocalDB.dll")

#define DATABASE_NOT_EXIST                                  "Database does not exist"
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

#define TDL_ERROR_INCORRECT_ACTION_TYPE                     "Incorrect Action Type Provided"
#define TDL_ERROR_INCORRECT_MYSQL_JOIN_TYPE                 "Incorrect Mysql Join Type Provided"
#define INCORRECT_NUM_OF_DATA_PROVIDED                      "Incorrect Number of Table Name/Column Name/Column Data provided"

#define INSUFFICIENT_PARAMS_CREATEDB                        "Insufficient TDL Parameters. Expected parameters are '<Server>:<User Name>:<Password>:<DataBase Name>'"
#define INSUFFICIENT_PARAMS_CREATE_TABLE                    "Insufficient TDL Parameters. Expected parameters for CreateTable are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Column Name>:<Column Data Type>'"
#define INSUFFICIENT_PARAMS_DELETE_TABLE                    "Insufficient TDL Parameters. Expected parameters for DeleteTable are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>'"
#define INSUFFICIENT_PARAMS_ALTER_TABLE                     "Insufficient TDL Parameters. Expected parameters for AlterTable are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Column Name>:<Column Data Type>'"
#define INSUFFICIENT_PARAMS_INSERT_DATA                     "Insufficient TDL Parameters. Expected parameters for InsertData are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>':<Column Name>:<Column Value>"
#define INSUFFICIENT_PARAMS_DELETE_DATA                     "Insufficient TDL Parameters. Expected parameters for DeleteAllData are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>'"
#define INSUFFICIENT_PARAMS_SHOW_DATA                       "Insufficient TDL Parameters. Expected parameters for ShowTableData are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Column Name 1(Optional)>:<Column Name 2(Optional)>'"
#define INSUFFICIENT_PARAMS_UPDATE_COLUMN_DATA              "Insufficient TDL Parameters. Expected parameters for UpdateTableData are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Column Name With Values>:<Condition>'"
#define INSUFFICIENT_PARAMS_ADD_FOREIGN_KEY                 "Insufficient TDL Parameters. Expected parameters for AddForeignKey are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Foreign Key Name>:<Reference Table Name>:<Column Name>'"
#define INSUFFICIENT_PARAMS_SHOW_FOREIGN_KEY                "Insufficient TDL Parameters. Expected parameters for ShowForeignKey are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>'"
#define INSUFFICIENT_PARAMS_TRIGGERS                        "Insufficient TDL Parameters. Expected parameters for TRIGGERS are '<Server>:<User Name>:<Password>:<DataBase Name>:<Trigger Name>:<Table Name>':<BEFORE/AFTER>:<INSERT/DELETE/UPDATE>:<Condition> (Optional)"
#define INSUFFICIENT_PARAMS_GENERAL_LOG                     "Insufficient TDL Parameters. Expected parameters for GeneralLog are '<Server>:<User Name>:<Password>:<DataBase Name>:<Enable/Disable/Delete>"
#define INSUFFICIENT_PARAMS_MYSQL_JOIN                      "Insufficient TDL Parameters. Expected parameters for MysqlJoin are '<Server>:<User Name>:<Password>:<DataBase Name>:<Select Condition>:<From/Set Condition>:<Table Name>:<On Condition>:<Where Condition>"

enum eActionType {

    ACTION_TYPE_UNKNOWN = 0,
    ACTION_TYPE_ENABLE,
    ACTION_TYPE_DISABLE,
    ACTION_TYPE_DELETE,
};

enum eJoinType {

    UNKNOWN_JOIN_TYPE = 0,
    INNER_JOIN_TYPE,
    LEFT_JOIN_TYPE,
    RIGHT_JOIN_TYPE,
    CROSS_JOIN_TYPE,
    DELETE_JOIN_TYPE,
    EQUI_JOIN_TYPE,
    NATURAL_JOIN_TYPE,
    UPDATE_JOIN_TYPE,
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

        eGoodBad    DataBase                   (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eBool pCreateDb, StrPtr& pBadResponse);
        eGoodBad    CreateLocalTable           (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName, 
                                                AStrPtr pColumnDataType, StrPtr& pBadResponse);

        eGoodBad    AlterLocalTable            (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName, 
                                                AStrPtr pColumnDataType, StrPtr& pBadResponse);

        eGoodBad    DeleteLocalTable           (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, StrPtr& pBadResponse);
        eGoodBad    InsertDataIntoTable        (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr * pTableNameArray, AStrPtr * pColumnNamesArray, 
                                                AStrPtr * pValuesArray, ULong ArraySize, StrPtr& pBadResponse);

        eGoodBad    DeleteDataFromTable        (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pCondition, StrPtr& pBadResponse);
        eGoodBad    ShowTableColumnData        (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName1, 
                                                AStrPtr pColumnName2, StrPtr& pBadResponse);

        eGoodBad    UpdateColumnData           (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnDataValue, 
                                                AStrPtr pConditionData, StrPtr& pBadResponse);

        eGoodBad    AddForeignKey              (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pForeignKeyName,
                                                AStrPtr pColumnName, AStrPtr pReferenceTableName, StrPtr& pBadResponse);

        eGoodBad   DropForeignKey              (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                                AStrPtr pForeignKeyName, StrPtr& pBadResponse);

        eGoodBad   ShowForeignKeyData          (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, StrPtr& pBadResponse);
        eGoodBad   CreateTrigger               (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTriggerName, AStrPtr pTableName,
                                                AStrPtr pActivationTime, AStrPtr pTriggerEvent, AStrPtr pTriggerCondition, StrPtr& pBadResponse);

        eGoodBad   DropTrigger                 (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTriggerName, StrPtr& pBadResponse);
        eGoodBad   SetGeneralLog               (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eActionType pLogAction, StrPtr& pBadResponse);
        eGoodBad   PerformMysqlJoin            (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eJoinType pJoinType, AStrPtr pSelectCondition, AStrPtr pSetOrFromCondtion, AStrPtr* pTableNameArray,
                                                ULong pTableNameArraySize, AStrPtr* pOnConditionArray, ULong pOnConditionArraySize, AStrPtr pWhereCondition, StrPtr& pBadResponse);

        void       RemoveSpacesAroundComma     (AStrPtr pStr);
        Long       CountCommaOccurrence        (AStrPtr pStr);
        Long       CountBraces                 (AStrPtr pStr);
        Long       CountCommaBetweenBraces     (AStrPtr pStr);
        void       ExtractDetailsFromCSV       (AStrPtr* pArray, ULong pArraySize, AStrPtr pData, ULong* pDataCount);
        void       ExtractDataBetweenBraces    (AStrPtr* pArray, ULong pArraySize, AStrPtr pData, ULong* pDataCount);
        void       FreeArrayDataAndArray       (AStrPtr* pArray, ULong pArraySize);
        eGoodBad   GetDllPath                  ();
        eGoodBad   WriteResponeFile            (AStrPtr pResponseData, CStrPtr pFileName = nullptr);

inline  void        SetResult                  (CWStrPtr pVal);
inline  void        SetResult                  (CAStrPtr pVal);

        StrPtr *    vResult;
        Long *      vResultSize;

        StrPtr      vDllPath;
        ULong       vDllPathLen;

        eActionType vActionType;
        eJoinType   vJoinType;
};

#include "LocalDB.hxx"

#endif //LOCALDB_HPP