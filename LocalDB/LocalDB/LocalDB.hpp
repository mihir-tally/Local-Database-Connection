#ifndef LOCALDB_HPP
#define LOCALDB_HPP
#include "common.hpp"

using sql::Driver;
using sql::Connection;
using sql::Statement;
using sql::PreparedStatement;
using sql::SQLException;
using sql::ResultSet;

#define DATABASE_CREATED                       "Database Created Successfully"
#define DATABASE_DELETED                       "Database Deleted Successfully"
#define TABLE_CREATED                          "Table Created Successfully"
#define TABLE_DELETED                          "Table Deleted Successfully"
#define TABLE_ALTERED                          "Table Altered Successfully"
#define DATA_INSERTED                          "Data Inserted Successfully"
#define ALL_DATA_DELETED                       "All Data Delete Successfully"

#define INSUFFICIENT_PARAMS_CREATEDB           "Insufficient TDL Parameters. Expected parameters are '<Server>:<User Name>:<Password>:<DataBase Name>'"
#define INSUFFICIENT_PARAMS_CREATE_TABLE       "Insufficient TDL Parameters. Expected parameters for CreateTable are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Column Name>:<Column Data Type>'"
#define INSUFFICIENT_PARAMS_DELETE_TABLE       "Insufficient TDL Parameters. Expected parameters for DeleteTable are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>'"
#define INSUFFICIENT_PARAMS_ALTER_TABLE        "Insufficient TDL Parameters. Expected parameters for AlterTable are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>:<Column Name>:<Column Data Type>'"
#define INSUFFICIENT_PARAMS_INSERT_DATA        "Insufficient TDL Parameters. Expected parameters for InsertData are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>':<Column Name>:<Column Value>"
#define INSUFFICIENT_PARAMS_DELETE_ALL_DATA    "Insufficient TDL Parameters. Expected parameters for DeleteAllData are '<Server>:<User Name>:<Password>:<DataBase Name>:<Table Name>'"

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
        eGoodBad    DeleteAllData              (Word pArgc, WStrPtr* pArgv);

    private:

        eGoodBad    DataBase                   (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eBool pCreateDb, CAStrPtr& pBadResponse);
        eGoodBad    CreateLocalTable           (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName, AStrPtr pColumnDataType, CAStrPtr& pBadResponse);
        eGoodBad    AlterLocalTable            (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnName, AStrPtr pColumnDataType, CAStrPtr& pBadResponse);
        eGoodBad    DeleteLocalTable           (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, CAStrPtr& pBadResponse);
        eGoodBad    InsertDataIntoTable        (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumnNames, AStrPtr pValues, CAStrPtr& pBadResponse);
        eGoodBad    DeleteAllDataFromTable     (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, CAStrPtr& pBadResponse);

        void        SetResult                  (CWStrPtr pVal);
        void        SetResult                  (CAStrPtr pVal);
        void        UTF16ToAscii               (AStrPtr pDest, CWStrPtr pSrc, Long pSrcLen);
        void        AsciiToUTF16               (WStrPtr pDestination, CAStrPtr pSource, UInt32 pLength);

        StrPtr *    vResult;
        Long *      vResultSize;
};
#endif //LOCALDB_HPP