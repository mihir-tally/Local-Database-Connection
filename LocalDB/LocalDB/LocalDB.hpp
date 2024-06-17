#ifndef LOCALDB_HPP
#define LOCALDB_HPP
#include "common.hpp"

using namespace std;
using namespace sql;

#define DATABASE_CREATED                       "Database Created Successfully"
#define DATABASE_DELETED                       "Database Deleted Successfully"
#define TABLE_CREATED                          "Table Created Successfully"
#define TABLE_DELETED                          "Table Deleted Successfully"
#define TABLE_ALTERED                          "Table Altered Successfully"
#define DATA_INSERTED                          "Data Inserted Successfully"
#define DATA_DELETED                           "Data Delete Successfully"
#define TABLE_COLUMN_DATA_UPDATED              "Table Column Data is Successfully Updated"
#define ADD_FOREIGN_KEY                        "Foreign key is added successfully"

#define INSUFFICIENT_PARAMS_CREATEDB           "Insufficient TDL Parameters. Expected parameters are '<Server>:<User Name>:<Password>:<DataBase Name>'"
#define INSUFFICIENT_PARAMS_CREATE_TABLE       "Insufficient TDL Parameters. Expected parameters for CreateTable are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Column Name>:<Column Data Type>'"
#define INSUFFICIENT_PARAMS_DELETE_TABLE       "Insufficient TDL Parameters. Expected parameters for DeleteTable are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>'"
#define INSUFFICIENT_PARAMS_ALTER_TABLE        "Insufficient TDL Parameters. Expected parameters for AlterTable are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Column Name>:<Column Data Type>'"
#define INSUFFICIENT_PARAMS_INSERT_DATA        "Insufficient TDL Parameters. Expected parameters for InsertData are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>':<Column Name>:<Column Value>"
#define INSUFFICIENT_PARAMS_DELETE_DATA        "Insufficient TDL Parameters. Expected parameters for DeleteAllData are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>'"
#define INSUFFICIENT_PARAMS_SHOW_DATA          "Insufficient TDL Parameters. Expected parameters for ShowTableData are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Column Name 1(Optional)>:<Column Name 2(Optional)>'"
#define INSUFFICIENT_PARAMS_UPDATE_COLUMN_DATA "Insufficient TDL Parameters. Expected parameters for UpdateTableData are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Column Name With Values>:<Condition>'"
#define INSUFFICIENT_PARAMS_ADD_FOREIGN_KEY    "Insufficient TDL Parameters. Expected parameters for AddForeignKey are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Reference Table Name>:<Column Name>'"


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
        eGoodBad    AddForeignKey               (Word pArgc, WStrPtr* pArgv);
    private:

        eGoodBad    DataBase                   (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eBool pCreateDb, StrPtr& pBadResponse);
        eGoodBad    CreateLocalTable           (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName, 
                                                AStrPtr pColumnDataType, StrPtr& pBadResponse);

        eGoodBad    AlterLocalTable            (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName, 
                                                AStrPtr pColumnDataType, StrPtr& pBadResponse);

        eGoodBad    DeleteLocalTable           (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, StrPtr& pBadResponse);
        eGoodBad    InsertDataIntoTable        (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnNames, 
                                                AStrPtr pValues, StrPtr& pBadResponse);

        eGoodBad    DeleteDataFromTable        (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pCondition, StrPtr& pBadResponse);
        eGoodBad    ShowTableColumnData        (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName1, 
                                                AStrPtr pColumnName2, StrPtr& pResult, StrPtr& pBadResponse);

        eGoodBad    UpdateColumnData           (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnDataValue, 
                                                AStrPtr pConditionData, StrPtr& pBadResponse);

        eGoodBad    AddForeignKey              (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                                AStrPtr pReferenceTableName, AStrPtr pColumnName, StrPtr& pBadResponse);

        void        SetResult                  (CWStrPtr pVal);
        void        SetResult                  (CAStrPtr pVal);
        void        UTF8ToUTF16                (WStrPtr pDestination, CAStrPtr pSource, UInt32 pLength);
        void        UTF16ToAscii               (AStrPtr pDest, CWStrPtr pSrc, Long pSrcLen);
        void        AsciiToUTF16               (WStrPtr pDestination, CAStrPtr pSource, UInt32 pLength);

        StrPtr *    vResult;
        Long *      vResultSize;
};
#endif //LOCALDB_HPP