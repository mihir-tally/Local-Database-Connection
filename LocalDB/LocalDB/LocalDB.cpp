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

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

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

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

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

HRESULT ShowTableData (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
        TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->ShowTableData (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

HRESULT UpdateTableData (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
        TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->UpdateTableData (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

HRESULT ForeignKey (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
        TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->ForeignKey (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

HRESULT ShowForeignKey (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
        TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->ShowForeignKey (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

HRESULT Triggers (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
        TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->Triggers (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

HRESULT GeneralLog (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
        TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->GeneralLog (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

HRESULT MysqlJoin (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize)
{
        TLocalDataBase * localdatabase;

    localdatabase = ALLOC_TLocalDataBase (pResult, pResultSize);

    localdatabase->MysqlJoin (pArgc, pArgv);

    delete localdatabase;
    return S_OK;
}

eGoodBad TLocalDataBase::SelectServerAndAlloc (CStrPtr pSqlServerName)
{
    if (_tcsicmp (pSqlServerName, MYSQL_SERVER_NAME) == 0) {

        vServerType = MYSQL_SERVER_TYPE;
        vMySqlServer = ALLOC_TMySqlServer ();

    } else if (_tcsicmp (pSqlServerName, SQL_SERVER_NAME) == 0) {

        vServerType = SQL_SERVER_TYPE;
        vSqlServer  = ALLOC_TSqlServer ();

    } else {

        return BAD;
    }

    return GOOD;
}

void TLocalDataBase::RemoveSpacesAroundComma (AStrPtr pStr)
{
        Long  i;
        Long  j;
        Long  str_len;
        Long  space_count;

    i = 0;
    j = 0;
    space_count = 0;

    if (!pStr || !*pStr) {

        return;
    }

    str_len = (Long) strlen (pStr);

    for (ULong i = 0; i < str_len; i++) {

        if (pStr[i] == ' ' && (pStr[i + 1] == ',' || pStr[i + 1] == ' ')) {

            continue;
        }

        pStr[j++] = pStr[i];

        if (pStr[i] == ',' && pStr[i + 1] == ' ') {

            space_count = 1;

            while (pStr[i + space_count] == ' ') {

                space_count++;
            }

            i += space_count - 1;
        }
    }

    pStr[j] = '\0';
}

Long TLocalDataBase::CountCommaOccurrence (AStrPtr pStr)
{
        Long comma_count;

    comma_count = 0;

    if (!*pStr || !pStr) {

        return -1;
    }

    while (*pStr != '\0') {

        if (*pStr == ',') {

            comma_count++;
        }

        pStr++;
    }

    return comma_count;
}

Long TLocalDataBase::CountBraces (AStrPtr pStr)
{
        ULong braces_count;
        ULong in_braces; // Flag to check if inside {}
        ULong i;

    braces_count = 0;
    in_braces    = 0;
    i            = 0;

    if (!pStr || !*pStr) {

        return -1;  // Invalid input
    }

    while (pStr[i] != '\0') {

        if (pStr[i] == '{') {

            in_braces = 1;

        }
        else if (pStr[i] == '}') {

            if (in_braces) {

                braces_count++;
                in_braces = 0;
            }
        }
        i++;
    }
    return braces_count;
}

Long TLocalDataBase::CountCommaBetweenBraces (AStrPtr pStr)
{
        Long comma_operator_count;

    comma_operator_count = 0;

    if (!pStr || !*pStr) {

        return -1;  // Invalid input
    }

    while (*pStr && *(pStr + 1)) {

        if (*pStr == '}' && *(pStr + 1) == ',' && *(pStr + 2) == '{') {

            comma_operator_count++;
            pStr++;  // Move to the next character after '}'
        }
        pStr++;  // Move to the next character
    }

    return comma_operator_count;
}

void TLocalDataBase::ExtractDetailsFromCSV (AStrPtr * pArray, ULong pArraySize, AStrPtr pData, ULong* pDataCount)
{
        AStrPtr    str            = nullptr;
        AStrPtr    context        = nullptr;
        ULong      num_of_data;

    *pDataCount = 0;

    if (!pData || !*pData || !pArray) {

        return;
    }

    str         = strtok_s( pData, ",", &context);
    num_of_data = 0;

    while (str != nullptr && num_of_data < pArraySize) {

        pArray[num_of_data] = (AStrPtr) malloc (strlen(str) + 1);

        if (pArray[num_of_data] != nullptr) {

            strcpy_s (pArray[num_of_data], strlen (str) + 1, str); // Copy the string
            num_of_data++;
            (*pDataCount)++;
        }
        else {
            
            break;
        }
        str = strtok_s (nullptr, ",", &context);
    }
}

void TLocalDataBase::ExtractDataBetweenBraces (AStrPtr * pArray, ULong pArraySize, AStrPtr pData, ULong * pDataCount)
{
        CAStrPtr    start    = nullptr;
        CAStrPtr    end      = nullptr;
        AStrPtr     data     = nullptr;

    if (!pArray || pArraySize == 0 || !pData || !*pData) {

        return;
    }

    start       = pData;
    *pDataCount = 0;

    while ((start = strchr (start, '{')) != nullptr && *pDataCount < pArraySize) {

        end = strchr (start, '}');

        if (end == nullptr) {

            break; // No closing brace found
        }

        // Move the pointers to the actual data
        start++;
        size_t len = end - start;

        
        data = (AStrPtr) malloc (len + 1);

        if (data == nullptr) {

            return;
        }
        
        // Copy the data between the braces
        strncpy(data, start, len);
        data[len] = '\0';

        // Store the extracted data in the pArray array
        pArray[*pDataCount] = data;
        (*pDataCount)++;

        // Move past this closing brace
        start = end + 1;
    }
}

void TLocalDataBase::FreeArrayDataAndArray (AStrPtr * pArray, ULong pArraySize)
{

    if (!pArray || pArraySize == 0) {

        return;
    }

    for (ULong i = 0; i < pArraySize; i++) {

        free (pArray[i]);
    }
    free (pArray);
}

eGoodBad TLocalDataBase::GetDllPath ()
{
        HMODULE  module_handle;
        Char     dll_path [MAX_PATH_LENGTH];

    module_handle = GetModuleHandle (DLL_FILE_NAME);

    if (module_handle != NULL) {

        if (GetModuleFileName (module_handle, dll_path, MAX_PATH_LENGTH) > 0) {

            StrPtr last_slash = _tcsrchr (dll_path, '\\');

            if (last_slash != nullptr) {

                *(last_slash + 1) = '\0';

                vDllPathLen = (ULong)_tcslen(dll_path) + 1;
                vDllPath = (StrPtr) malloc ((vDllPathLen) * sizeof(Char));

                _tcscpy_s (vDllPath, vDllPathLen, dll_path);

                return GOOD;
            }
        }
    }
    return BAD;
}

eGoodBad TLocalDataBase::WriteResponeFile (AStrPtr pResponseData, CStrPtr pFileName)
{
        HANDLE     file;
        CStrPtr    file_name                   = nullptr;
        StrPtr     dll_path                    = nullptr;
        ULong      num_bytes_written;
        ULong      dll_path_len;

    if (!vDllPath || !*vDllPath || vDllPathLen == 0) {

        return BAD;
    }

    if (!pResponseData || !*pResponseData) {

        return BAD;

    }
    file_name = pFileName ? pFileName : DATABASE_TABLE_DATA_FILE_NAME;

    dll_path_len = vDllPathLen + (ULong)_tcslen(file_name);
    dll_path     = (StrPtr) malloc ((dll_path_len) * sizeof (Char));

    _tcscpy_s (dll_path, vDllPathLen, vDllPath);
    _tcscat_s (dll_path, (vDllPathLen + (ULong)_tcslen (file_name)), file_name);

    file = CreateFile (dll_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (file == INVALID_HANDLE_VALUE)
        return BAD;

    WriteFile (file, pResponseData, (ULong) strlen (pResponseData), &num_bytes_written, NULL);

    CloseHandle (file);
    free (dll_path);
    return GOOD;
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

    if (pArgc != 5) {

        SetResult (INSUFFICIENT_PARAMS_CREATEDB);
        return rc;
    }

    if (SelectServerAndAlloc (pArgv[0]) == BAD) {

        SetResult (INCORRECT_SERVER_NAME_SELECT);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[1]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[1], server_len);

    username_len = (ULong) _tcslen (pArgv[2]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[2], username_len);

    password_len = (ULong) _tcslen (pArgv[3]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[3], password_len);

    databasename_len = (ULong) _tcslen (pArgv[4]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[4], databasename_len);

    if (vServerType == MYSQL_SERVER_TYPE) {

        if (vMySqlServer->MySqlDataBase (server, username, password, databasename, pCreateDB, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
    } else if (vServerType == SQL_SERVER_TYPE) {

        if (vSqlServer->SqlDataBase (server, username, password, databasename, pCreateDB, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
    }

    if (pCreateDB) {

        SetResult (DATABASE_CREATED);

    } else {

        SetResult (DATABASE_DELETED);
    }

    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    if (bad_response) free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::CreateTable (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server                          = nullptr;
        AStrPtr    username                        = nullptr;
        AStrPtr    password                        = nullptr;
        AStrPtr    databasename                    = nullptr;
        AStrPtr    table_name                      = nullptr;
        AStrPtr    column_name_and_datatype        = nullptr;
        StrPtr     bad_response                    = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        ULong      column_name_and_datatype_len;
        eGoodBad   rc                               = BAD;

    if (pArgc != 7) {

        SetResult (INSUFFICIENT_PARAMS_CREATE_TABLE);
        return rc;
    }

    if (SelectServerAndAlloc (pArgv[0]) == BAD) {

        SetResult (INCORRECT_SERVER_NAME_SELECT);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[1]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[1], server_len);

    username_len = (ULong) _tcslen (pArgv[2]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[2], username_len);

    password_len = (ULong) _tcslen (pArgv[3]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[3], password_len);

    databasename_len = (ULong) _tcslen (pArgv[4]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[4], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[5]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[5], table_name_len);

    column_name_and_datatype_len = (ULong) _tcslen (pArgv[6]);
    column_name_and_datatype = (AStrPtr) malloc ((column_name_and_datatype_len + 1) * sizeof (AChar));
    UTF16ToAscii (column_name_and_datatype, pArgv[6], column_name_and_datatype_len);

    if (vServerType == MYSQL_SERVER_TYPE) {

        if (vMySqlServer->MySqlCreateLocalTable (server, username, password, databasename, table_name, column_name_and_datatype, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
    } else if (vServerType == SQL_SERVER_TYPE) {

        if (vSqlServer->SqlCreateLocalTable (server, username, password, databasename, table_name, column_name_and_datatype, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
    }

    SetResult (TABLE_CREATED);
    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    free (column_name_and_datatype);
    if (bad_response) free (bad_response);

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

    if (pArgc != 6) {

        SetResult (INSUFFICIENT_PARAMS_DELETE_TABLE);
        return rc;
    }

    if (SelectServerAndAlloc (pArgv[0]) == BAD) {

        SetResult (INCORRECT_SERVER_NAME_SELECT);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[1]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[1], server_len);

    username_len = (ULong) _tcslen (pArgv[2]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[2], username_len);

    password_len = (ULong) _tcslen (pArgv[3]);
    password     = (AStrPtr)malloc((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[3], password_len);

    databasename_len = (ULong) _tcslen (pArgv[4]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[4], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[5]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[5], table_name_len);

    if (vServerType == MYSQL_SERVER_TYPE) {

        if (vMySqlServer->MySqlDeleteLocalTable (server, username, password, databasename, table_name, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }

    } else if (vServerType == SQL_SERVER_TYPE) {

        if (vSqlServer->SqlDeleteLocalTable (server, username, password, databasename, table_name, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }

    }

    SetResult (TABLE_DELETED);

    rc = GOOD;
end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    if (bad_response) free (bad_response);

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

    if (pArgc != 8) {

        SetResult (INSUFFICIENT_PARAMS_ALTER_TABLE);
        return rc;
    }

    if (SelectServerAndAlloc (pArgv[0]) == BAD) {

        SetResult (INCORRECT_SERVER_NAME_SELECT);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[1]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[1], server_len);

    username_len = (ULong) _tcslen (pArgv[2]);
    username     = (AStrPtr)malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[2], username_len);

    password_len = (ULong) _tcslen (pArgv[3]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[3], password_len);

    databasename_len = (ULong) _tcslen (pArgv[4]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[4], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[5]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[5], table_name_len);

    column_name_len = (ULong) _tcslen (pArgv[6]);
    column_name     = (AStrPtr) malloc ((column_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (column_name, pArgv[6], column_name_len);

    column_datatype_len = (ULong) _tcslen (pArgv[7]);
    column_datatype     = (AStrPtr) malloc ((column_datatype_len + 1) * sizeof (AChar));
    UTF16ToAscii (column_datatype, pArgv[7], column_datatype_len);

    if (vServerType == MYSQL_SERVER_TYPE) {

        if (vMySqlServer->MySqlAlterLocalTable (server, username, password, databasename, table_name, column_name, column_datatype, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
    } else if (vServerType == SQL_SERVER_TYPE) {

        if (vSqlServer->SqlAlterLocalTable (server, username, password, databasename, table_name, column_name, column_datatype, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
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
    if (bad_response) free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::InsertData (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr      server                 = nullptr;
        AStrPtr      username               = nullptr;
        AStrPtr      password               = nullptr;
        AStrPtr      databasename           = nullptr;
        AStrPtr      table_name             = nullptr;
        AStrPtr      column_names           = nullptr;
        AStrPtr      values                 = nullptr;
        AStrPtr *    table_names_array      = nullptr;
        AStrPtr *    column_names_array     = nullptr;
        AStrPtr *    column_values_array    = nullptr;
        StrPtr       bad_response           = nullptr;
        ULong        server_len;
        ULong        username_len;
        ULong        password_len;
        ULong        databasename_len;
        ULong        table_name_len;
        ULong        column_names_len;
        ULong        values_len;
        ULong        table_count;
        ULong        column_count_braces;
        ULong        values_count_braces;
        ULong        column_count_comma;
        ULong        values_count_comma;
        ULong        table_names_data_count;
        ULong        column_names_data_count;
        ULong        values_data_count;
        eGoodBad     rc                    = BAD;

    table_names_data_count  = 0;
    column_names_data_count = 0;
    values_data_count       = 0;

    if (pArgc != 8) {

        SetResult (INSUFFICIENT_PARAMS_INSERT_DATA);
        return rc;
    }

    if (SelectServerAndAlloc (pArgv[0]) == BAD) {

        SetResult (INCORRECT_SERVER_NAME_SELECT);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[1]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[1], server_len);

    username_len = (ULong) _tcslen (pArgv[2]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[2], username_len);

    password_len = (ULong) _tcslen (pArgv[3]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii( password, pArgv[3], password_len);

    databasename_len = (ULong) _tcslen (pArgv[4]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[4], databasename_len);

    if (!*pArgv[5] || !*pArgv[6] || !*pArgv[7]) {

        goto end;
    }

    table_name_len = (ULong) _tcslen (pArgv[5]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[5], table_name_len);

    column_names_len = (ULong) _tcslen (pArgv[6]);
    column_names     = (AStrPtr) malloc ((column_names_len + 1) * sizeof (AChar));
    UTF16ToAscii (column_names, pArgv[6], column_names_len);

    values_len = (ULong) _tcslen (pArgv[7]);
    values     = (AStrPtr) malloc ((values_len + 1) * sizeof (AChar));
    UTF16ToAscii (values, pArgv[7], values_len);

    RemoveSpacesAroundComma (table_name);
    RemoveSpacesAroundComma (column_names);
    RemoveSpacesAroundComma (values);

    table_count         = CountCommaOccurrence (table_name);
    column_count_braces = CountBraces (column_names);
    values_count_braces = CountBraces (values);
    column_count_comma  = CountCommaBetweenBraces (column_names);
    values_count_comma  = CountCommaBetweenBraces (values);

    // here + 1 in table count because if user give one data then CountCommaOccurrence will give 0
    // here + 1 in column_count_comma and values_count_comma because if user give one data then CountCommaBetweenBraces will give 0
    if (column_count_braces == 0 || values_count_braces == 0 || column_count_braces != column_count_comma + 1
        || values_count_braces != values_count_comma + 1 || table_count + 1 != column_count_braces
        || column_count_braces != values_count_braces) {

        SetResult (INCORRECT_NUM_OF_DATA_PROVIDED);
        goto end;
    }
    //here + 1 because if user give one data then CountBraces will give 0
    table_names_array = (AStrPtr *) malloc ((table_count + 1) * sizeof (AStrPtr));
    ExtractDetailsFromCSV (table_names_array, table_count + 1, table_name, &table_names_data_count);

    column_names_array = (AStrPtr *) malloc ((column_count_braces) * sizeof (AStrPtr));
    ExtractDataBetweenBraces (column_names_array, column_count_braces, column_names, &column_names_data_count);

    column_values_array = (AStrPtr *) malloc ((values_count_braces) * sizeof (AStrPtr));
    ExtractDataBetweenBraces (column_values_array, values_count_braces, values, &values_data_count);


    if (vServerType == MYSQL_SERVER_TYPE) {

        if (vMySqlServer->MySqlInsertDataIntoTable (server, username, password, databasename, table_names_array, column_names_array, column_values_array, table_count + 1, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
    } else if (vServerType == SQL_SERVER_TYPE) {

        if (vSqlServer->SqlInsertDataIntoTable (server, username, password, databasename, table_names_array, column_names_array, column_values_array, table_count + 1, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
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
    FreeArrayDataAndArray (table_names_array, table_names_data_count);
    FreeArrayDataAndArray (column_names_array, column_names_data_count);
    FreeArrayDataAndArray (column_values_array, values_data_count);
    if (bad_response) free (bad_response);

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

    if (pArgc != 6 && pArgc != 7) {

        SetResult (INSUFFICIENT_PARAMS_DELETE_DATA);
        return rc;
    }

    if (SelectServerAndAlloc (pArgv[0]) == BAD) {

        SetResult (INCORRECT_SERVER_NAME_SELECT);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[1]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[1], server_len);

    username_len = (ULong) _tcslen (pArgv[2]);
    username     = (AStrPtr)malloc((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[2], username_len);

    password_len = (ULong) _tcslen (pArgv[3]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[3], password_len);

    databasename_len = (ULong) _tcslen (pArgv[4]);
    databasename     = (AStrPtr)malloc((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[4], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[5]);
    table_name     = (AStrPtr )malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[5], table_name_len);

    if (pArgc == 7) {

        condition_len = (ULong) _tcslen (pArgv[6]);
        condition     = (AStrPtr) malloc ((condition_len + 1) * sizeof (AChar));
        UTF16ToAscii (condition, pArgv[6], condition_len);
    }

    if (vServerType == MYSQL_SERVER_TYPE) {

        if (vMySqlServer->MySqlDeleteDataFromTable (pArgc, server, username, password, databasename, table_name, condition, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
    } else if (vServerType == SQL_SERVER_TYPE) {

        if (vSqlServer->SqlDeleteDataFromTable (pArgc, server, username, password, databasename, table_name, condition, bad_response) == BAD) {

            SetResult(bad_response);
            goto end;
        }
    }
    SetResult (DATA_DELETED);

    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    free (condition);
    if (bad_response) free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::ShowTableData (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server               = nullptr;
        AStrPtr    username             = nullptr;
        AStrPtr    password             = nullptr;
        AStrPtr    databasename         = nullptr;
        AStrPtr    table_name           = nullptr;
        AStrPtr    column_name          = nullptr;
        AStrPtr    result_string        = nullptr;
        StrPtr     bad_response         = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        ULong      column_name_len;
        eGoodBad   rc                   = BAD;

    if (pArgc != 6 && pArgc != 7) {

        SetResult (INSUFFICIENT_PARAMS_SHOW_DATA);
        return rc;
    }

    if (SelectServerAndAlloc (pArgv[0]) == BAD) {

        SetResult (INCORRECT_SERVER_NAME_SELECT);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[1]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[1], server_len);

    username_len = (ULong) _tcslen (pArgv[2]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[2], username_len);

    password_len = (ULong) _tcslen (pArgv[3]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[3], password_len);

    databasename_len = (ULong) _tcslen (pArgv[4]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[4], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[5]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[5], table_name_len);

    if (pArgc == 7) {

        column_name_len = (ULong) _tcslen (pArgv[6]);
        column_name     = (AStrPtr) malloc ((column_name_len + 1) * sizeof (AChar));
        UTF16ToAscii (column_name, pArgv[6], column_name_len);

    }

    if (vServerType == MYSQL_SERVER_TYPE) {

        if (vMySqlServer->MyShowTableColumnData (pArgc, server, username, password, databasename, table_name, column_name, result_string, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }

    } else if (vServerType == SQL_SERVER_TYPE) {

        if (vSqlServer->SqlShowTableColumnData (pArgc, server, username, password, databasename, table_name, column_name, vDllPath, vDllPathLen, result_string, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
    }
    if (WriteResponeFile (result_string) == BAD) {

        SetResult (FAILED_TO_WRITE_FILE);
        goto end;
    }

    SetResult (SHOW_TABLE_COLUMN_DATA);
    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    free(column_name);
    if (result_string) free (result_string);
    if (bad_response) free (bad_response);

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

    if (pArgc != 8) {

        SetResult (INSUFFICIENT_PARAMS_UPDATE_COLUMN_DATA);
        return rc;
    }

    if (SelectServerAndAlloc (pArgv[0]) == BAD) {

        SetResult (INCORRECT_SERVER_NAME_SELECT);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[1]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[1], server_len);

    username_len = (ULong) _tcslen (pArgv[2]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[2], username_len);

    password_len = (ULong) _tcslen (pArgv[3]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[3], password_len);

    databasename_len = (ULong) _tcslen (pArgv[4]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[4], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[5]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[5], table_name_len);

    column_name_value_len = (ULong) _tcslen (pArgv[6]);
    column_name_value     = (AStrPtr) malloc ((column_name_value_len + 1) * sizeof (AChar));
    UTF16ToAscii (column_name_value, pArgv[6], column_name_value_len);

    condition_data_len = (ULong) _tcslen (pArgv[7]);
    condition_data     = (AStrPtr) malloc ((condition_data_len + 1) * sizeof (AChar));
    UTF16ToAscii (condition_data, pArgv[7], condition_data_len);

    if (vServerType == MYSQL_SERVER_TYPE) {

        if (vMySqlServer->MySqlUpdateColumnData (server, username, password, databasename, table_name, column_name_value, condition_data, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
    } else if (vServerType == SQL_SERVER_TYPE) {

        if (vSqlServer->SqlUpdateColumnData (server, username, password, databasename, table_name, column_name_value, condition_data, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
    }

    SetResult (TABLE_COLUMN_DATA_UPDATED);
    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    free (column_name_value);
    free (condition_data);
    if (bad_response) free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::ForeignKey (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server                  = nullptr;
        AStrPtr    username                = nullptr;
        AStrPtr    password                = nullptr;
        AStrPtr    databasename            = nullptr;
        AStrPtr    table_name              = nullptr;
        AStrPtr    foreign_key_name        = nullptr;
        AStrPtr    reference_table_name    = nullptr;
        AStrPtr    column_name             = nullptr;
        StrPtr     bad_response            = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        ULong      foreign_key_name_len;
        ULong      reference_table_name_len;
        ULong      column_name_len;
        eGoodBad   rc                      = BAD;

    if (pArgc != 7 && pArgc != 9) {

        SetResult (INSUFFICIENT_PARAMS_ADD_FOREIGN_KEY);
        return rc;
    }

    if (SelectServerAndAlloc (pArgv[0]) == BAD) {

        SetResult (INCORRECT_SERVER_NAME_SELECT);
        return rc;
    }
    server_len = (ULong) _tcslen (pArgv[1]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[1], server_len);

    username_len = (ULong) _tcslen (pArgv[2]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[2], username_len);

    password_len = (ULong) _tcslen (pArgv[3]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[3], password_len);

    databasename_len = (ULong) _tcslen (pArgv[4]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[4], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[5]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[5], table_name_len);

    foreign_key_name_len = (ULong) _tcslen (pArgv[6]);
    foreign_key_name    = (AStrPtr) malloc ((foreign_key_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (foreign_key_name, pArgv[6], foreign_key_name_len);

    if (pArgc == 9) {

        column_name_len = (ULong) _tcslen (pArgv[7]);
        column_name     = (AStrPtr) malloc ((column_name_len + 1) * sizeof (AChar));
        UTF16ToAscii (column_name, pArgv[7], column_name_len);

        reference_table_name_len = (ULong) _tcslen (pArgv[8]);
        reference_table_name     = (AStrPtr) malloc ((reference_table_name_len + 1) * sizeof (AChar));
        UTF16ToAscii (reference_table_name, pArgv[8], reference_table_name_len);

        HandleForeignKeyOperation (TRUE, server, username, password, databasename, table_name, foreign_key_name, column_name, reference_table_name, bad_response);

    } else {
        // DROP FOREIGN KEY
        HandleForeignKeyOperation (FALSE, server, username, password, databasename, table_name, foreign_key_name, nullptr, nullptr , bad_response);
    }
    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    free (foreign_key_name);

    if (column_name)          free (column_name);
    if (reference_table_name) free (reference_table_name);
    if (bad_response)         free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::ShowForeignKey (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server              = nullptr;
        AStrPtr    username            = nullptr;
        AStrPtr    password            = nullptr;
        AStrPtr    databasename        = nullptr;
        AStrPtr    table_name          = nullptr;
        AStrPtr    result_string       = nullptr;
        StrPtr     bad_response        = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        eGoodBad   rc                  = BAD;

    if (pArgc != 5 && pArgc != 6) {

        SetResult (INSUFFICIENT_PARAMS_SHOW_FOREIGN_KEY);
        return rc;
    }

    if (SelectServerAndAlloc (pArgv[0]) == BAD) {

        SetResult (INCORRECT_SERVER_NAME_SELECT);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[1]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[1], server_len);

    username_len = (ULong) _tcslen (pArgv[2]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[2], username_len);

    password_len = (ULong) _tcslen (pArgv[3]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[3], password_len);

    databasename_len = (ULong) _tcslen (pArgv[4]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[4], databasename_len);
    
    if (pArgc == 6) {

        table_name_len = (ULong) _tcslen (pArgv[5]);
        table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
        UTF16ToAscii (table_name, pArgv[5], table_name_len);
    }
    if (vServerType == MYSQL_SERVER_TYPE) {

        if (vMySqlServer->MySqlShowForeignKeyData (pArgc, server, username, password, databasename, table_name, result_string, bad_response) == BAD) {

            SetResult(bad_response);
            goto end;
        }

    } else if (vServerType == SQL_SERVER_TYPE) {

        if (vSqlServer->SqlShowForeignKeyData (pArgc, server, username, password, databasename, table_name, result_string, bad_response) == BAD) {

            SetResult(bad_response);
            goto end;
        }
    }

    if (WriteResponeFile (result_string) == BAD) {

        SetResult (FAILED_TO_WRITE_FILE);
        goto end;
    }

    SetResult (SHOW_FOREIGN_KEY);

    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    if (table_name) free (table_name);
    if (result_string) free(result_string);
    if (bad_response) free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::Triggers (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server               = nullptr;
        AStrPtr    username             = nullptr;
        AStrPtr    password             = nullptr;
        AStrPtr    databasename         = nullptr;
        AStrPtr    table_name           = nullptr;
        AStrPtr    trigger_name         = nullptr;
        AStrPtr    activation_time      = nullptr;
        AStrPtr    trigger_event        = nullptr;
        AStrPtr    trigger_condition    = nullptr;
        StrPtr     bad_response         = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        ULong      trigger_name_len;
        ULong      activation_time_len;
        ULong      trigger_event_len;
        ULong      trigger_condition_len;
        eGoodBad   rc                   = BAD;

    if (pArgc != 6 && pArgc != 9 && pArgc != 10) {

        SetResult (INSUFFICIENT_PARAMS_TRIGGERS);
        return rc;
    }

    if (SelectServerAndAlloc (pArgv[0]) == BAD) {

        SetResult (INCORRECT_SERVER_NAME_SELECT);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[1]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[1], server_len);

    username_len = (ULong) _tcslen (pArgv[2]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[2], username_len);

    password_len = (ULong) _tcslen (pArgv[3]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[3], password_len);

    databasename_len = (ULong) _tcslen (pArgv[4]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[4], databasename_len);

    trigger_name_len = (ULong)_tcslen (pArgv[5]);
    trigger_name     = (AStrPtr) malloc ((trigger_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (trigger_name, pArgv[5], trigger_name_len);

    if (pArgc == 6) {

        // DROP TRIGGER
        HandleTriggerOperation (FALSE, pArgc, server, username, password, databasename, trigger_name, nullptr, nullptr, nullptr, nullptr, bad_response);

    } else if (pArgc == 9 || pArgc == 10) {

        table_name_len = (ULong) _tcslen (pArgv[6]);
        table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
        UTF16ToAscii (table_name, pArgv[6], table_name_len);

        activation_time_len = (ULong) _tcslen (pArgv[7]);
        activation_time     = (AStrPtr) malloc ((activation_time_len + 1) * sizeof (AChar));
        UTF16ToAscii (activation_time, pArgv[7], activation_time_len);

        trigger_event_len = (ULong) _tcslen (pArgv[8]);
        trigger_event     = (AStrPtr) malloc ((trigger_event_len + 1) * sizeof (AChar));
        UTF16ToAscii (trigger_event, pArgv[8], trigger_event_len);

        if (pArgc == 10) {

            trigger_condition_len = (ULong) _tcslen (pArgv[9]);
            trigger_condition     = (AStrPtr) malloc ((trigger_condition_len + 1) * sizeof (AChar));
            UTF16ToAscii (trigger_condition, pArgv[9], trigger_condition_len);
        }
        // CREATE TRIGGER
        HandleTriggerOperation (TRUE, pArgc, server, username, password, databasename, trigger_name, table_name, activation_time, trigger_event, trigger_condition, bad_response);
    }

    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (trigger_name);
    if (table_name)        free (table_name);
    if (activation_time)   free (activation_time);
    if (trigger_event)     free (trigger_event);
    if (trigger_condition) free (trigger_condition);
    if (bad_response)      free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::GeneralLog (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server                   = nullptr;
        AStrPtr    username                 = nullptr;
        AStrPtr    password                 = nullptr;
        AStrPtr    databasename             = nullptr;
        AStrPtr    action_type              = nullptr;
        AStrPtr    enable_log_query         = nullptr;
        CAStrPtr   successful_message       = nullptr;
        StrPtr     bad_response             = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      action_type_len;
        ULong      successful_message_len;
        eGoodBad   rc                       = BAD;

    if (pArgc != 6) {

        SetResult (INSUFFICIENT_PARAMS_GENERAL_LOG);
        return rc;
    }

    if (SelectServerAndAlloc (pArgv[0]) == BAD) {

        SetResult (INCORRECT_SERVER_NAME_SELECT);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[1]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[1], server_len);

    username_len = (ULong) _tcslen (pArgv[2]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[2], username_len);

    password_len = (ULong) _tcslen (pArgv[3]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[3], password_len);

    databasename_len = (ULong) _tcslen (pArgv[4]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[4], databasename_len);

    action_type_len = (ULong) _tcslen (pArgv[5]);
    action_type     = (AStrPtr) malloc ((action_type_len + 1) * sizeof (AChar));
    UTF16ToAscii (action_type, pArgv[5], action_type_len);

    if (_stricmp (action_type, "Enable") == 0) {

        vActionType        = ACTION_TYPE_ENABLE;
        successful_message = GENERAL_LOG_ENABLE;

    }
    else if (_stricmp (action_type, "Disable") == 0) {

        vActionType        = ACTION_TYPE_DISABLE;
        successful_message = GENERAL_LOG_DISABLE;

    }
    else if (_stricmp (action_type, "Delete") == 0) {

        vActionType        = ACTION_TYPE_DELETE;
        successful_message = GENERAL_LOG_DELETE_LOG_DATA;

    } else {

        SetResult (TDL_ERROR_INCORRECT_ACTION_TYPE);
        goto end;
    }
    if (vServerType == MYSQL_SERVER_TYPE) {

        if (vMySqlServer->MySqlSetGeneralLog (server, username, password, databasename, vActionType, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
    } else if (vServerType == SQL_SERVER_TYPE) {

        if (vSqlServer->SqlSetGeneralLog (server, username, password, databasename, vActionType, vDllPath, vDllPathLen, bad_response) == BAD) {

            SetResult(bad_response);
            goto end;
        }
    }

    SetResult (successful_message);

    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (action_type);
    if (bad_response) free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::MysqlJoin (Word pArgc, WStrPtr* pArgv)
{
        AStrPtr    server                     = nullptr;
        AStrPtr    username                   = nullptr;
        AStrPtr    password                   = nullptr;
        AStrPtr    databasename               = nullptr;
        AStrPtr    join_type                  = nullptr;
        AStrPtr    select_condition           = nullptr;
        AStrPtr    set_or_from_condition      = nullptr;
        AStrPtr    table_name                 = nullptr;
        AStrPtr    on_condition               = nullptr;
        AStrPtr    where_condition            = nullptr;
        AStrPtr    order_by_condition         = nullptr;
        AStrPtr    result_string              = nullptr;
        AStrPtr *  table_names_array          = nullptr;
        AStrPtr *  on_condition_array         = nullptr;
        CAStrPtr   successful_message         = nullptr;
        StrPtr     bad_response               = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      join_type_len;
        ULong      select_condition_len;
        ULong      set_or_from_condition_len;
        ULong      table_name_len;
        ULong      table_count;
        ULong      table_names_data_count;
        ULong      on_condition_len;
        ULong      on_condition_count;
        ULong      on_condition_data_count;
        ULong      where_condition_len;
        ULong      order_by_condition_len;
        ULong      successful_message_len;
        eGoodBad   rc                         = BAD;

    if (pArgc != 10 && pArgc != 11 && pArgc != 12) {

        SetResult (INSUFFICIENT_PARAMS_MYSQL_JOIN);
        return rc;
    }

    if (SelectServerAndAlloc (pArgv[0]) == BAD) {

        SetResult (INCORRECT_SERVER_NAME_SELECT);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[1]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[1], server_len);

    username_len = (ULong) _tcslen (pArgv[2]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii(username, pArgv[2], username_len);

    password_len = (ULong) _tcslen (pArgv[3]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[3], password_len);

    databasename_len = (ULong) _tcslen (pArgv[4]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[4], databasename_len);

    join_type_len = (ULong) _tcslen (pArgv[5]);
    join_type = (AStrPtr) malloc ((join_type_len + 1) * sizeof (AChar));
    UTF16ToAscii (join_type, pArgv[5], join_type_len);

    if (_stricmp (join_type, "Inner") == 0) {

        vJoinType          = INNER_JOIN_TYPE;
        successful_message = INNER_JOIN_EXECUTED;

    } else if (_stricmp (join_type, "Left") == 0) {

        vJoinType          = LEFT_JOIN_TYPE;
        successful_message = LEFT_JOIN_EXECUTED;

    } else if (_stricmp (join_type, "Right") == 0) {

        vJoinType          = RIGHT_JOIN_TYPE;
        successful_message = RIGHT_JOIN_EXECUTED;

    } else if (_stricmp (join_type, "Cross") == 0) {

        vJoinType          = CROSS_JOIN_TYPE;
        successful_message = CROSS_JOIN_EXECUTED;

    } else if (_stricmp (join_type, "Delete") == 0) {

        vJoinType          = DELETE_JOIN_TYPE;
        successful_message = DELETE_JOIN_EXECUTED;

    } else if (_stricmp (join_type, "Equi") == 0) {

        vJoinType          = EQUI_JOIN_TYPE;
        successful_message = EQUI_JOIN_EXECUTED;

    } else if (_stricmp (join_type, "Natural") == 0) {

        vJoinType          = NATURAL_JOIN_TYPE;
        successful_message = NATURAL_JOIN_EXECUTED;

    } else if (_stricmp (join_type, "Update") == 0) {

        vJoinType          = UPDATE_JOIN_TYPE;
        successful_message = UPDATE_JOIN_EXECUTED;

    } else {

        SetResult (TDL_ERROR_INCORRECT_MYSQL_JOIN_TYPE);
        goto end;
    }

    select_condition_len = (ULong) _tcslen (pArgv[6]);
    select_condition     = (AStrPtr) malloc ((select_condition_len + 1) * sizeof (AChar));
    UTF16ToAscii (select_condition, pArgv[6], select_condition_len);

    set_or_from_condition_len = (ULong) _tcslen (pArgv[7]);
    set_or_from_condition     = (AStrPtr) malloc ((set_or_from_condition_len + 1) * sizeof (AChar));
    UTF16ToAscii (set_or_from_condition, pArgv[7], set_or_from_condition_len);

    table_name_len = (ULong) _tcslen (pArgv[8]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[8], table_name_len);

    on_condition_len = (ULong) _tcslen (pArgv[9]);
    on_condition     = (AStrPtr) malloc ((on_condition_len + 1) * sizeof (AChar));
    UTF16ToAscii (on_condition, pArgv[9], on_condition_len);

    if (pArgc == 11) {

        where_condition_len = (ULong) _tcslen (pArgv[10]);
        where_condition     = (AStrPtr) malloc ((where_condition_len + 1) * sizeof (AChar));
        UTF16ToAscii (where_condition, pArgv[10], where_condition_len);

    } else if (pArgc == 12) {

        where_condition_len = (ULong) _tcslen (pArgv[10]);
        where_condition     = (AStrPtr) malloc ((where_condition_len + 1) * sizeof (AChar));
        UTF16ToAscii (where_condition, pArgv[10], where_condition_len);

        order_by_condition_len = (ULong) _tcslen (pArgv[11]);
        order_by_condition     = (AStrPtr) malloc ((order_by_condition_len + 1) * sizeof (AChar));
        UTF16ToAscii (order_by_condition, pArgv[11], order_by_condition_len);
    }

    RemoveSpacesAroundComma (table_name);
    RemoveSpacesAroundComma (on_condition);

    table_count        = CountCommaOccurrence (table_name);
    on_condition_count = CountCommaOccurrence (on_condition);

    // here + 1 in table count because if user give one data then CountCommaOccurrence will give 0
    table_names_array = (AStrPtr *) malloc ((table_count + 1) * sizeof(AStrPtr));
    ExtractDetailsFromCSV (table_names_array, table_count + 1, table_name, &table_names_data_count);

    // here + 1 in on condition count because if user give one data then CountCommaOccurrence will give 0
    on_condition_array = (AStrPtr *) malloc ((on_condition_count + 1) * sizeof (AStrPtr));
    ExtractDetailsFromCSV (on_condition_array, on_condition_count + 1, on_condition, &on_condition_data_count);

    if (table_count + 1 == table_names_data_count && on_condition_count + 1 == on_condition_data_count) {
        if (vServerType == MYSQL_SERVER_TYPE) {

            if (vMySqlServer->PerformMysqlJoin (server, username, password, databasename, vJoinType, select_condition, set_or_from_condition, table_names_array, table_count + 1, on_condition_array, on_condition_count + 1, where_condition, order_by_condition, result_string, bad_response) == BAD) {

                SetResult (bad_response);
                goto end;
            }
        }
        else if (vServerType == SQL_SERVER_TYPE) {

            if (vSqlServer->PerformSqlJoin (server, username, password, databasename, vJoinType, select_condition, set_or_from_condition, table_names_array, table_count + 1, on_condition_array, on_condition_count + 1, where_condition, order_by_condition, result_string, bad_response) == BAD) {

                SetResult (bad_response);
                goto end;
            }
        }
    }
    if (WriteResponeFile (result_string) == BAD) {

        SetResult (FAILED_TO_WRITE_FILE);
        goto end;
    }

    SetResult (successful_message);

    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (join_type);
    free (select_condition);
    free (set_or_from_condition);
    free (table_name);
    free (on_condition);
    free (where_condition);
    free (order_by_condition);
    FreeArrayDataAndArray (table_names_array, table_names_data_count);
    FreeArrayDataAndArray (on_condition_array, on_condition_data_count);
    if (result_string) free (result_string);
    if (bad_response) free (bad_response);

    return rc;
}

void TLocalDataBase::HandleForeignKeyOperation (eBool pIsAddOperation, AStrPtr pServer, AStrPtr pUsername, AStrPtr pPassword,
                                                AStrPtr pDatabasename, AStrPtr pTableName, AStrPtr pForeignKeyName, AStrPtr pColumnName, AStrPtr pReferenceTableName, StrPtr& pBadResponse) {
        int result;
        
    result = 0;

    if (vServerType == MYSQL_SERVER_TYPE) {

        result = pIsAddOperation
            ? vMySqlServer->MySqlAddForeignKey (pServer, pUsername, pPassword, pDatabasename, pTableName, pForeignKeyName, pColumnName, pReferenceTableName, pBadResponse)
            : vMySqlServer->MySqlDropForeignKey (pServer, pUsername, pPassword, pDatabasename, pTableName, pForeignKeyName, pBadResponse);
    }
    else if (vServerType == SQL_SERVER_TYPE) {

        result = pIsAddOperation
            ? vSqlServer->SqlAddForeignKey (pServer, pUsername, pPassword, pDatabasename, pTableName, pForeignKeyName, pColumnName, pReferenceTableName, pBadResponse)
            : vSqlServer->SqlDropForeignKey (pServer, pUsername, pPassword, pDatabasename, pTableName, pForeignKeyName, pBadResponse);
    }

    if (result == BAD) {

        SetResult (pBadResponse);
        return;
    }

    SetResult (pIsAddOperation ? ADD_FOREIGN_KEY : DROP_FOREIGN_KEY);
}

void TLocalDataBase::HandleTriggerOperation (eBool pIsAddOperation, Word pArgc, AStrPtr pServer, AStrPtr pUsername, AStrPtr pPassword, AStrPtr pDatabasename, AStrPtr pTriggerName, AStrPtr pTableName,
                                             AStrPtr pActivationTime, AStrPtr pTriggerEvent, AStrPtr pTriggerCondition, StrPtr& pBadResponse)
{
        int result;

    result = 0;

    if (vServerType == MYSQL_SERVER_TYPE) {

        result = pIsAddOperation
            ? vMySqlServer->MySqlCreateTrigger (pArgc, pServer, pUsername, pPassword, pDatabasename, pTriggerName, pTableName, pActivationTime, pTriggerEvent, pTriggerCondition, pBadResponse)
            : vMySqlServer->MySqlDropTrigger (pServer, pUsername, pPassword, pDatabasename, pTriggerName, pBadResponse);
    }
    else if (vServerType == SQL_SERVER_TYPE) {

        result = pIsAddOperation
            ? vSqlServer->SqlCreateTrigger (pArgc, pServer, pUsername, pPassword, pDatabasename, pTriggerName, pTableName, pActivationTime, pTriggerEvent, pTriggerCondition, pBadResponse)
            : vSqlServer->SqlDropTrigger (pServer, pUsername, pPassword, pDatabasename, pTriggerName, pBadResponse);
    }

    if (result == BAD) {

        SetResult (pBadResponse);
        return;
    }

    SetResult(pIsAddOperation ? CREATE_TRIGGER : DROP_TRIGGER);
}