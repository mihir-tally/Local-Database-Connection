#ifndef LOCALDB_HXX
#define LOCALDB_HXX

TLocalDataBase::TLocalDataBase (StrPtr* pResult, Long* pResultSize)
{
    vResult     = pResult;
    vResultSize = pResultSize;
    vDllPath    = nullptr;
    vDllPathLen = 0;

    vActionType = ACTION_TYPE_UNKNOWN;
    vJoinType   = UNKNOWN_JOIN_TYPE;
    vServerType = UNKNOWN_SERVER_TYPE;

    vSqlServer   = nullptr;
    vMySqlServer = nullptr;

    GetDllPath ();
}

TLocalDataBase::~TLocalDataBase ()
{
    if (vDllPath) {

        free (vDllPath);
        vDllPath = nullptr;
    }

    if (vServerType == MYSQL_SERVER_TYPE) {

        delete vMySqlServer;

    } else if (vServerType == SQL_SERVER_TYPE) {

        delete vSqlServer;
    }
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

    AsciiToUTF16 (*vResult, pVal, *vResultSize - 1);
}

#endif //LOCALDB_HXX
