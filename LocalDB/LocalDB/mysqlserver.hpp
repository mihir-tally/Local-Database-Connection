#ifndef MYSQLSERVER_HPP
#define MYSQLSERVER_HPP

using namespace std;
using namespace sql;
using namespace rapidjson;

#define ALLOC_TMySqlServer     new TMySqlServer

class TMySqlServer {

    public:
                    TMySqlServer             (void) {};
                    ~TMySqlServer            (void) {};
	    eGoodBad    MySqlDataBase            (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eBool pCreateDb, StrPtr& pBadResponse);
        eGoodBad    MySqlCreateLocalTable    (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnNameAndDataType,
                                              StrPtr& pBadResponse);

        eGoodBad    MySqlDeleteLocalTable    (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, StrPtr& pBadResponse);
        eGoodBad    MySqlAlterLocalTable     (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName,
                                              AStrPtr pColumnDataType, StrPtr& pBadResponse);

        eGoodBad    MySqlInsertDataIntoTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr* pTableNameArray, AStrPtr* pColumnNamesArray,
                                              AStrPtr* pValuesArray, ULong pArraySize, StrPtr& pBadResponse);

        eGoodBad    MySqlDeleteDataFromTable (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pCondition, 
                                              StrPtr& pBadResponse);

        eGoodBad    MySqlUpdateColumnData    (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnDataValue,
                                              AStrPtr pConditionData, StrPtr& pBadResponse);

        eGoodBad    MySqlAddForeignKey       (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pForeignKeyName,
                                              AStrPtr pColumnName, AStrPtr pReferenceTableName, StrPtr& pBadResponse);

        eGoodBad    MySqlDropForeignKey      (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                              AStrPtr pForeignKeyName, StrPtr& pBadResponse);

        eGoodBad    MySqlCreateTrigger       (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTriggerName, AStrPtr pTableName,
                                              AStrPtr pActivationTime, AStrPtr pTriggerEvent, AStrPtr pTriggerCondition, StrPtr& pBadResponse);

        eGoodBad    MySqlDropTrigger         (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTriggerName, StrPtr& pBadResponse);

        eGoodBad    MyShowTableColumnData    (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName,
                                              AStrPtr& pResultString, StrPtr& pBadResponse);

        eGoodBad    MySqlShowForeignKeyData  (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr& pResultString, 
                                              StrPtr& pBadResponse);

        eGoodBad    PerformMysqlJoin         (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eJoinType pJoinType, AStrPtr pSelectCondition,
                                              AStrPtr pSetOrFromCondtion, AStrPtr* pTableNameArray, ULong pTableNameArraySize, AStrPtr* pOnConditionArray, ULong pOnConditionArraySize,
                                              AStrPtr pWhereCondition, AStrPtr pOrderByCondition, AStrPtr& pResultString, StrPtr& pBadResponse);

        eGoodBad    MySqlSetGeneralLog       (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eActionType pLogAction, StrPtr& pBadResponse);
        void        Recursion                (int pItr, int pMainCount, string& pTableName, ResultSetMetaData* meta_data, ResultSet* res, Value& pRowObject, Document::AllocatorType& pAllocator);
};

#endif //MYSQLSERVER_HPP