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

    if (pArgc != 4) {

        SetResult (INSUFFICIENT_PARAMS_CREATEDB);
        return rc;
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
        AStrPtr    server               = nullptr;
        AStrPtr    username             = nullptr;
        AStrPtr    password             = nullptr;
        AStrPtr    databasename         = nullptr;
        AStrPtr    table_name           = nullptr;
        AStrPtr    column_name          = nullptr;
        AStrPtr    column_datatype      = nullptr;
        StrPtr     bad_response         = nullptr;
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
        return rc;
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
    column_name     = (AStrPtr) malloc ((column_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (column_name, pArgv[5], column_name_len);

    column_datatype_len = (ULong) _tcslen (pArgv[6]);
    column_datatype     = (AStrPtr) malloc ((column_datatype_len + 1) * sizeof (AChar));
    UTF16ToAscii (column_datatype, pArgv[6], column_datatype_len);

    if (CreateLocalTable (server, username, password, databasename, table_name, column_name, column_datatype, bad_response) == BAD) {

        SetResult (bad_response);
        goto end;
    }

    SetResult (TABLE_CREATED);
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

    if (pArgc != 5) {

        SetResult (INSUFFICIENT_PARAMS_DELETE_TABLE);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[0]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[0], server_len);

    username_len = (ULong) _tcslen (pArgv[1]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[1], username_len);

    password_len = (ULong) _tcslen (pArgv[2]);
    password     = (AStrPtr)malloc((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[2], password_len);

    databasename_len = (ULong) _tcslen (pArgv[3]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[3], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[4]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[4], table_name_len);

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

    if (pArgc != 7) {

        SetResult (INSUFFICIENT_PARAMS_ALTER_TABLE);
        return rc;
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

    if (pArgc != 7) {

        SetResult (INSUFFICIENT_PARAMS_INSERT_DATA);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[0]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[0], server_len);

    username_len = (ULong) _tcslen (pArgv[1]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii (username, pArgv[1], username_len);

    password_len = (ULong) _tcslen (pArgv[2]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii( password, pArgv[2], password_len);

    databasename_len = (ULong) _tcslen (pArgv[3]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[3], databasename_len);

    if (!*pArgv[4] || !*pArgv[5] || !*pArgv[6]) {

        goto end;
    }

    table_name_len = (ULong) _tcslen (pArgv[4]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[4], table_name_len);

    column_names_len = (ULong) _tcslen (pArgv[5]);
    column_names     = (AStrPtr) malloc ((column_names_len + 1) * sizeof (AChar));
    UTF16ToAscii (column_names, pArgv[5], column_names_len);

    values_len = (ULong) _tcslen (pArgv[6]);
    values     = (AStrPtr) malloc ((values_len + 1) * sizeof (AChar));
    UTF16ToAscii (values, pArgv[6], values_len);

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

    if (InsertDataIntoTable (server, username, password, databasename, table_names_array, column_names_array, column_values_array, table_count + 1, bad_response) == BAD) {

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

    if (pArgc != 5 && pArgc != 6) {

        SetResult (INSUFFICIENT_PARAMS_DELETE_DATA);
        return rc;
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
    databasename     = (AStrPtr)malloc((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[3], databasename_len);

    table_name_len = (ULong) _tcslen (pArgv[4]);
    table_name     = (AStrPtr )malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[4], table_name_len);

    if (pArgc == 6) {

        condition_len = (ULong) _tcslen (pArgv[5]);
        condition     = (AStrPtr) malloc ((condition_len + 1) * sizeof (AChar));
        UTF16ToAscii (condition, pArgv[5], condition_len);
    }
    if (DeleteDataFromTable (pArgc, server, username, password, databasename, table_name, condition, bad_response) == BAD) {

        SetResult (bad_response);
        goto end;
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
        AStrPtr    column_name_1        = nullptr;
        AStrPtr    column_name_2        = nullptr;
        StrPtr     bad_response         = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        ULong      column_name_1_len;
        ULong      column_name_2_len;
        eGoodBad   rc                   = BAD;

    if (pArgc != 5 && pArgc != 6 && pArgc != 7) {

        SetResult (INSUFFICIENT_PARAMS_SHOW_DATA);
        return rc;

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

    if (pArgc == 6) {

        column_name_1_len = (ULong) _tcslen (pArgv[5]);
        column_name_1     = (AStrPtr) malloc ((column_name_1_len + 1) * sizeof (AChar));
        UTF16ToAscii (column_name_1, pArgv[5], column_name_1_len);

    } else if (pArgc == 7) {

        column_name_1_len = (ULong) _tcslen (pArgv[5]);
        column_name_1     = (AStrPtr) malloc ((column_name_1_len + 1) * sizeof (AChar));
        UTF16ToAscii (column_name_1, pArgv[5], column_name_1_len);

        column_name_2_len = (ULong) _tcslen (pArgv[6]);
        column_name_2     = (AStrPtr) malloc ((column_name_2_len + 1) * sizeof (AChar));
        UTF16ToAscii (column_name_2, pArgv[6], column_name_2_len);
    }

    if (ShowTableColumnData (pArgc ,server, username, password, databasename, table_name, column_name_1, column_name_2, bad_response) == BAD) {

        SetResult (bad_response);
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
    free (column_name_1);
    free (column_name_2);
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

    if (pArgc != 7) {

        SetResult (INSUFFICIENT_PARAMS_UPDATE_COLUMN_DATA);
        return rc;
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

    column_name_value_len = (ULong) _tcslen (pArgv[5]);
    column_name_value     = (AStrPtr) malloc ((column_name_value_len + 1) * sizeof (AChar));
    UTF16ToAscii (column_name_value, pArgv[5], column_name_value_len);

    condition_data_len = (ULong) _tcslen (pArgv[6]);
    condition_data     = (AStrPtr) malloc ((condition_data_len + 1) * sizeof (AChar));
    UTF16ToAscii (condition_data, pArgv[6], condition_data_len);

    if (UpdateColumnData (server, username, password, databasename, table_name, column_name_value, condition_data, bad_response) == BAD) {

        SetResult (bad_response);
        goto end;
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

    if (pArgc != 6 && pArgc != 8) {

        SetResult (INSUFFICIENT_PARAMS_ADD_FOREIGN_KEY);
        return rc;
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

    foreign_key_name_len = (ULong) _tcslen (pArgv[5]);
    foreign_key_name    = (AStrPtr) malloc ((foreign_key_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (foreign_key_name, pArgv[5], foreign_key_name_len);

    if (pArgc == 8) {

        column_name_len = (ULong) _tcslen (pArgv[6]);
        column_name     = (AStrPtr) malloc ((column_name_len + 1) * sizeof (AChar));
        UTF16ToAscii (column_name, pArgv[6], column_name_len);

        reference_table_name_len = (ULong) _tcslen (pArgv[7]);
        reference_table_name     = (AStrPtr) malloc ((reference_table_name_len + 1) * sizeof (AChar));
        UTF16ToAscii (reference_table_name, pArgv[7], reference_table_name_len);

        if (AddForeignKey (server, username, password, databasename, table_name, foreign_key_name, column_name, reference_table_name, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
        SetResult (ADD_FOREIGN_KEY);

    } else {

        if (DropForeignKey (server, username, password, databasename, table_name, foreign_key_name, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }
        SetResult (DROP_FOREIGN_KEY);
    }

    rc = GOOD;

end:
    free (server);
    free (username);
    free (password);
    free (databasename);
    free (table_name);
    free (column_name);

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
        StrPtr     bad_response        = nullptr;
        ULong      server_len;
        ULong      username_len;
        ULong      password_len;
        ULong      databasename_len;
        ULong      table_name_len;
        eGoodBad   rc                  = BAD;

    if (pArgc != 4 && pArgc != 5) {

        SetResult (INSUFFICIENT_PARAMS_SHOW_FOREIGN_KEY);
        return rc;
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
    
    if (pArgc == 5) {

        table_name_len = (ULong) _tcslen (pArgv[4]);
        table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
        UTF16ToAscii (table_name, pArgv[4], table_name_len);
    }

    if (ShowForeignKeyData (pArgc, server, username, password, databasename, table_name, bad_response) == BAD) {

        SetResult (bad_response);
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
    if (bad_response) free(bad_response);

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

    if (pArgc != 5 && pArgc != 8 && pArgc != 9) {

        SetResult (INSUFFICIENT_PARAMS_TRIGGERS);
        return rc;
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

    trigger_name_len = (ULong)_tcslen(pArgv[4]);
    trigger_name     = (AStrPtr) malloc ((trigger_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (trigger_name, pArgv[4], trigger_name_len);

    if (pArgc == 5) {

        if (DropTrigger (server, username, password, databasename, trigger_name, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }

        SetResult (DROP_TRIGGER);

    } else if (pArgc == 8 || pArgc == 9) {

        table_name_len = (ULong) _tcslen (pArgv[5]);
        table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
        UTF16ToAscii (table_name, pArgv[5], table_name_len);

        activation_time_len = (ULong) _tcslen (pArgv[6]);
        activation_time     = (AStrPtr) malloc ((activation_time_len + 1) * sizeof (AChar));
        UTF16ToAscii (activation_time, pArgv[6], activation_time_len);

        trigger_event_len = (ULong) _tcslen (pArgv[7]);
        trigger_event     = (AStrPtr) malloc ((trigger_event_len + 1) * sizeof (AChar));
        UTF16ToAscii (trigger_event, pArgv[7], trigger_event_len);

        if (pArgc == 9) {

            trigger_condition_len = (ULong) _tcslen (pArgv[8]);
            trigger_condition     = (AStrPtr) malloc ((trigger_condition_len + 1) * sizeof (AChar));
            UTF16ToAscii (trigger_condition, pArgv[8], trigger_condition_len);
        }

        if (CreateTrigger (pArgc, server, username, password, databasename, trigger_name, table_name, activation_time, trigger_event, trigger_condition, bad_response) == BAD) {

            SetResult (bad_response);
            goto end;
        }

        SetResult (CREATE_TRIGGER);
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

    if (pArgc != 5) {

        SetResult (INSUFFICIENT_PARAMS_GENERAL_LOG);
        return rc;
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

    action_type_len = (ULong) _tcslen (pArgv[4]);
    action_type     = (AStrPtr) malloc ((action_type_len + 1) * sizeof (AChar));
    UTF16ToAscii (action_type, pArgv[4], action_type_len);

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

    if (SetGeneralLog (server, username, password, databasename, vActionType, bad_response) == BAD) {

        SetResult (bad_response);
        goto end;
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
        AStrPtr    enable_log_query           = nullptr;
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
        ULong      successful_message_len;
        eGoodBad   rc                         = BAD;

    if (pArgc != 10) {

        SetResult (INSUFFICIENT_PARAMS_MYSQL_JOIN);
        return rc;
    }

    server_len = (ULong) _tcslen (pArgv[0]);
    server     = (AStrPtr) malloc ((server_len + 1) * sizeof (AChar));
    UTF16ToAscii (server, pArgv[0], server_len);

    username_len = (ULong) _tcslen (pArgv[1]);
    username     = (AStrPtr) malloc ((username_len + 1) * sizeof (AChar));
    UTF16ToAscii(username, pArgv[1], username_len);

    password_len = (ULong) _tcslen (pArgv[2]);
    password     = (AStrPtr) malloc ((password_len + 1) * sizeof (AChar));
    UTF16ToAscii (password, pArgv[2], password_len);

    databasename_len = (ULong) _tcslen (pArgv[3]);
    databasename     = (AStrPtr) malloc ((databasename_len + 1) * sizeof (AChar));
    UTF16ToAscii (databasename, pArgv[3], databasename_len);

    join_type_len = (ULong) _tcslen (pArgv[4]);
    join_type = (AStrPtr) malloc ((join_type_len + 1) * sizeof (AChar));
    UTF16ToAscii (join_type, pArgv[4], join_type_len);

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

    select_condition_len = (ULong) _tcslen (pArgv[5]);
    select_condition     = (AStrPtr) malloc ((select_condition_len + 1) * sizeof (AChar));
    UTF16ToAscii (select_condition, pArgv[5], select_condition_len);

    set_or_from_condition_len = (ULong) _tcslen (pArgv[6]);
    set_or_from_condition     = (AStrPtr) malloc ((set_or_from_condition_len + 1) * sizeof (AChar));
    UTF16ToAscii (set_or_from_condition, pArgv[6], set_or_from_condition_len);

    table_name_len = (ULong) _tcslen (pArgv[7]);
    table_name     = (AStrPtr) malloc ((table_name_len + 1) * sizeof (AChar));
    UTF16ToAscii (table_name, pArgv[7], table_name_len);

    on_condition_len = (ULong) _tcslen (pArgv[8]);
    on_condition     = (AStrPtr) malloc ((on_condition_len + 1) * sizeof (AChar));
    UTF16ToAscii (on_condition, pArgv[8], on_condition_len);

    where_condition_len = (ULong) _tcslen (pArgv[9]);
    where_condition     = (AStrPtr) malloc ((where_condition_len + 1) * sizeof (AChar));
    UTF16ToAscii (where_condition, pArgv[9], where_condition_len);

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

        if (PerformMysqlJoin (server, username, password, databasename, vJoinType, select_condition, set_or_from_condition, table_names_array, table_count + 1, on_condition_array, on_condition_count + 1, where_condition, bad_response) == BAD) {

            SetResult (bad_response);
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
    free (join_type);
    free (select_condition);
    free (set_or_from_condition);
    free (table_name);
    free (on_condition);
    free (where_condition);
    FreeArrayDataAndArray (table_names_array, table_names_data_count);
    FreeArrayDataAndArray (on_condition_array, on_condition_data_count);
    if (bad_response) free (bad_response);

    return rc;
}

eGoodBad TLocalDataBase::DataBase (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName,
                                   eBool pCreateDb, StrPtr& pBadResponse)
{
        Driver *              driver;
        Connection *          con         = nullptr;
        Statement *           stmt        = nullptr;
        PreparedStatement *   pstmt       = nullptr;
        ResultSet *           res         = nullptr;
        CAStrPtr              bad_resp    = nullptr;
        ULong                 len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);
        return BAD;
    }

    try {

        stmt = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        bool db_exists = res->next ();

        if (pCreateDb) {

            if (db_exists) {

                bad_resp     = "Database already exists";
                len          = (ULong) strlen (bad_resp);
                pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

                UTF8ToUTF16 (pBadResponse, bad_resp, len);

                delete res;
                delete pstmt;
                delete stmt;
                delete con;
                return BAD;

            } else {

                stmt->execute ("CREATE DATABASE " + string(pDataBaseName));
                con->setSchema (pDataBaseName);
            }
        } else {
            
            if (!db_exists) {

                bad_resp     = DATABASE_NOT_EXIST;
                len          = (ULong) strlen (bad_resp);
                pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

                UTF8ToUTF16 (pBadResponse, bad_resp, len);

                delete res;
                delete pstmt;
                delete stmt;
                delete con;
                return BAD;

            } else {

                stmt->execute ("DROP DATABASE " + string (pDataBaseName));
            }
        }

        delete res;
        delete pstmt;
        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete res;
        delete pstmt;
        delete stmt;
        delete con;

        return BAD;
    }

    return GOOD;
}

eGoodBad TLocalDataBase::CreateLocalTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, 
                                           AStrPtr pColumnName, AStrPtr pColumnDataType, StrPtr& pBadResponse)
{
        Driver *              driver;
        Connection *          con         = nullptr;
        Statement *           stmt        = nullptr;
        PreparedStatement *   pstmt       = nullptr;
        ResultSet *           res         = nullptr;
        CAStrPtr              bad_resp    = nullptr;
        ULong                 len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        stmt  = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = DATABASE_NOT_EXIST;
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

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
        stmt = con->createStatement ();

        // Check if the table already exists
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res = pstmt->executeQuery ();

        if (res->next()) {

            // Table already exists
            bad_resp     = "Table already exists";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        stmt->execute ("CREATE TABLE " + string (pTableName) + " (" + string (pColumnName) + " " + string (pColumnDataType) + ");");

        delete res;
        delete pstmt;
        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete res;
        delete pstmt;
        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::DeleteLocalTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, StrPtr& pBadResponse)
{
        Driver *              driver;
        Connection *          con         = nullptr;
        Statement *           stmt        = nullptr;
        PreparedStatement *   pstmt       = nullptr;
        ResultSet *           res         = nullptr;
        CAStrPtr              bad_resp    = nullptr;
        ULong                 len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        stmt  = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = DATABASE_NOT_EXIST;
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

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

        res   = nullptr;
        pstmt = nullptr;
        stmt  = nullptr;

        stmt  = con->createStatement ();

        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");

        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);

        res = pstmt->executeQuery ();

        if (res->next ()) {

            stmt->execute ("DROP TABLE " + string(pTableName));

        }
        else {

            bad_resp     = "Table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

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

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete res;
        delete pstmt;
        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::AlterLocalTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                          AStrPtr pColumnName, AStrPtr pColumnDataType, StrPtr& pBadResponse)
{
        Driver *              driver;
        Connection *          con         = nullptr;
        Statement *           stmt        = nullptr;
        PreparedStatement *   pstmt       = nullptr;
        ResultSet *           res         = nullptr;
        CAStrPtr              bad_resp    = nullptr;
        ULong                 len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);
        return BAD;
    }

    try {

        stmt  = con->createStatement ();

        // Check if the database exists
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = DATABASE_NOT_EXIST;
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

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

        res   = nullptr;
        pstmt = nullptr;
        stmt  = nullptr;

        stmt = con->createStatement ();

        // Check if the table exists
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = "Table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Check if the column exists
        pstmt = con->prepareStatement ("SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ? AND COLUMN_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        pstmt->setString (3, pColumnName);
        res = pstmt->executeQuery ();

        if (res->next ()) {

            bad_resp     = "Column already exists";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete stmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        stmt = con->createStatement ();

        stmt->execute ("ALTER TABLE " + string (pTableName) + " ADD COLUMN " + string (pColumnName) + " " + string (pColumnDataType) + ";");

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete res;
        delete pstmt;
        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::InsertDataIntoTable (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr * pTableNameArray, AStrPtr * pColumnNamesArray, AStrPtr * pValuesArray, ULong ArraySize, StrPtr& pBadResponse)
{
        Driver *              driver      = nullptr;
        Connection *          con         = nullptr;
        Statement *           stmt        = nullptr;
        PreparedStatement *   pstmt       = nullptr;
        ResultSet *           res         = nullptr;
        string                query;
        CAStrPtr              bad_resp    = nullptr;
        ULong                 len;

    // Check if ArraySize is 0
    if (ArraySize == 0) {
            
        bad_resp     = "No Data to Insert";   
        len          = (ULong) strlen (bad_resp);      
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));       
        UTF8ToUTF16 (pBadResponse, bad_resp, len);
        return BAD;    
    }
    try {
        
        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);
        con->setAutoCommit (false); // Set auto-commit to false

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        // Check if the database exists
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            // Database does not exist
            bad_resp     = DATABASE_NOT_EXIST;
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);
            con->setAutoCommit (true); // Enable auto-commit after commit

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema (pDataBaseName);

        for (ULong i = 0; i < ArraySize; i++) {

            pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
            pstmt->setString (1, pDataBaseName);
            pstmt->setString (2, pTableNameArray[i]);
            res = pstmt->executeQuery ();

            if (!res->next ()) {

                // Table does not exist
                bad_resp     = "Table does not exist";
                len          = (ULong) strlen (bad_resp);
                pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

                UTF8ToUTF16 (pBadResponse, bad_resp, len);

                con->rollback (); // Rollback the transaction in case of an error
                con->setAutoCommit (true); // Enable auto-commit after commit

                delete res;
                delete pstmt;
                delete con;
                return BAD;
            }

            delete res;
            delete pstmt;

            res   = nullptr;
            pstmt = nullptr;

            stmt = con->createStatement ();

            // Construct the SQL query to insert data into the table
            query = "INSERT INTO " + string (pTableNameArray[i]) + " " + string (pColumnNamesArray[i]) + " VALUES " + string (pValuesArray[i]) + ";";

            // Execute the query
            stmt->execute (query);

            delete stmt;
        }
        con->commit (); // Commit the transaction
        con->setAutoCommit (true); // Enable auto-commit after commit
        delete con;
        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        if (con != nullptr) {

            con->rollback (); // Rollback the transaction in case of an error
            con->setAutoCommit (true); // Enable auto-commit after commit
        }

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::DeleteDataFromTable (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pCondition,StrPtr& pBadResponse)
{
        Driver *               driver      = nullptr;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        string                 query;
        CAStrPtr               bad_resp    = nullptr;
        ULong                  len;

    try {
        
        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {
        
        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = DATABASE_NOT_EXIST;
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            // Table does not exist
            bad_resp     = "Table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        
        res   = nullptr;
        pstmt = nullptr;

        // Delete all data from the table
        stmt = con->createStatement ();

        if (pArgc == 6) {

            query = "DELETE FROM " + string (pTableName) + " WHERE " + string (pCondition) + ";";

        } else {

            query = "DELETE FROM " + string (pTableName) + ";";
        }


        // Execute the query
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp = e.what ();
        len = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::ShowTableColumnData (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, AStrPtr pColumn1, AStrPtr pColumn2, StrPtr& pBadResponse)
{
        Driver *               driver            = nullptr;
        Connection *           con               = nullptr;
        Statement *            stmt              = nullptr;
        PreparedStatement *    pstmt             = nullptr;
        ResultSet *            res               = nullptr;
        ResultSetMetaData *    meta_data         = nullptr;
        AStrPtr                result_string;
        string                 query;
        CAStrPtr               bad_resp          = nullptr;
        ULong                  len;
        int                    column_count;
        eBool                  is_general_log    = FALSE;

    try {

        driver = get_driver_instance ();
        con = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        if (strcmp (pTableName, "mysql.general_log") == 0) {

            is_general_log = TRUE;
        }

        if (!is_general_log) {

            pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
            pstmt->setString (1, pDataBaseName);
            res = pstmt->executeQuery ();

            if (!res->next ()) {

                bad_resp     = DATABASE_NOT_EXIST;
                len          = (ULong) strlen (bad_resp);
                pBadResponse = (StrPtr) malloc ((len + 1) * sizeof(Char));
                UTF8ToUTF16 (pBadResponse, bad_resp, len);

                delete res;
                delete pstmt;
                delete con;
                return BAD;
            }

            delete res;
            delete pstmt;

            res   = nullptr;
            pstmt = nullptr;

            con->setSchema (pDataBaseName);
            pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
            pstmt->setString (1, pDataBaseName);
            pstmt->setString (2, pTableName);
            res = pstmt->executeQuery ();

            if (!res->next ()) {

                bad_resp     = "Table does not exist";
                len          = (ULong) strlen (bad_resp);
                pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
                UTF8ToUTF16 (pBadResponse, bad_resp, len);

                delete res;
                delete pstmt;
                delete con;
                return BAD;
            }

            delete res;
            delete pstmt;

            res   = nullptr;
            pstmt = nullptr;
        }

        stmt = con->createStatement ();

        if (is_general_log) {

            query = "SELECT * FROM " + string (pTableName);

        } else if (pArgc == 6) {

            query = "SELECT " + string (pColumn1) + " FROM " + string (pTableName);

        } else if (pArgc == 7) {

            query = "SELECT " + string (pColumn1) + ", " + string (pColumn2) + " FROM " + string (pTableName);

        } else {

            query = "SELECT * FROM " + string (pTableName);
        }

        res          = stmt->executeQuery (query);
        meta_data    = res->getMetaData ();
        column_count = meta_data->getColumnCount ();

        rapidjson::Document json_document;
        json_document.SetObject ();

        // Array for columns
        rapidjson::Value columns_array (rapidjson::kArrayType);

        for (int i = 1; i <= column_count; ++i) {

            rapidjson::Value column_object (rapidjson::kObjectType);
            rapidjson::Value column_name;
            rapidjson::Value column_type;

            column_name.SetString (meta_data->getColumnName (i).c_str (), json_document.GetAllocator ());
            column_type.SetString (meta_data->getColumnTypeName (i).c_str (), json_document.GetAllocator ());

            column_object.AddMember ("Name", column_name, json_document.GetAllocator ());
            column_object.AddMember ("Type", column_type, json_document.GetAllocator ());

            columns_array.PushBack (column_object, json_document.GetAllocator ());
        }
        json_document.AddMember ("ColumnsData", columns_array, json_document.GetAllocator ());

        // Array for rows
        rapidjson::Value data_array (rapidjson::kArrayType);

        while (res->next ()) {

            rapidjson::Value row_object (rapidjson::kObjectType);

            for (int j = 1; j <= column_count; ++j) {

                rapidjson::Value column_name;
                rapidjson::Value column_value;

                column_name.SetString (meta_data->getColumnName (j).c_str (), json_document.GetAllocator ());
                column_value.SetString (res->getString (j).c_str (), json_document.GetAllocator ());

                row_object.AddMember (column_name, column_value, json_document.GetAllocator ());
            }
            data_array.PushBack (row_object, json_document.GetAllocator ());
        }
        json_document.AddMember ("RowsData", data_array, json_document.GetAllocator ());

        // Convert JSON document to string
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer (buffer);
        json_document.Accept (writer);

        result_string = (AStrPtr)buffer.GetString ();

        if (WriteResponeFile (result_string) == BAD) {

            bad_resp     = "Failed to write data in file";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete stmt;
            delete con;
            delete res;
            return BAD;
        }

        delete stmt;
        delete con;
        delete res;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::UpdateColumnData (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName, 
                                           AStrPtr pColumnDataValue, AStrPtr pConditionData, StrPtr& pBadResponse)
{
        Driver *               driver    = nullptr;
        Connection *           con       = nullptr;
        Statement *            stmt      = nullptr;
        PreparedStatement *    pstmt     = nullptr;
        ResultSet *            res       = nullptr;
        string                 query;
        CAStrPtr               bad_resp  = nullptr;
        ULong                  len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = DATABASE_NOT_EXIST;
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res   = pstmt->executeQuery ();

        if (!res->next()) {

            // Table does not exist
            bad_resp     = "Table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Delete all data from the table
        stmt  = con->createStatement ();
        query = "UPDATE " + string (pTableName) + " SET " + string (pColumnDataValue) + " WHERE " + string (pConditionData) + ";";

        // Execute the query
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::AddForeignKey (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                        AStrPtr pForeignKeyName, AStrPtr pColumnName, AStrPtr pReferenceTableName, StrPtr& pBadResponse)
{
        Driver *               driver      = nullptr;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        string                 query;
        CAStrPtr               bad_resp    = nullptr;
        ULong                  len;

    try {

        driver = get_driver_instance ();
        con = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {
        // Check if the database exists
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = DATABASE_NOT_EXIST;
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Check if the main table exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = "Table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;


        // Check if the reference table exists
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pReferenceTableName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = "Reference table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);
            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Execute the ALTER TABLE query to add foreign key constraint
        stmt  = con->createStatement ();
        string query = "ALTER TABLE " + string (pTableName) + " ADD CONSTRAINT " + string (pForeignKeyName) + " FOREIGN KEY (" + string (pColumnName) + ") REFERENCES " + string (pReferenceTableName) + "(" + string (pColumnName) + ") ON DELETE CASCADE ON UPDATE CASCADE;";
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::DropForeignKey (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTableName,
                                         AStrPtr pForeignKeyName, StrPtr& pBadResponse)
{
        Driver *               driver      = nullptr;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        string                 query;
        CAStrPtr               bad_resp    = nullptr;
        ULong                  len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);
        return BAD;
    }

    try {
        // Check if the database exists
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = DATABASE_NOT_EXIST;
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);
            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Check if the table exists
        con->setSchema(pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        res  = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = "Table does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);
            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Check if the foreign key constraint exists
        pstmt = con->prepareStatement ("SELECT CONSTRAINT_NAME FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ? AND CONSTRAINT_NAME = ? AND CONSTRAINT_TYPE = 'FOREIGN KEY'");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTableName);
        pstmt->setString (3, pForeignKeyName);
        res  = pstmt->executeQuery ();

        if (!res->next()) {

            bad_resp     = "Foreign key constraint does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16(pBadResponse, bad_resp, len);
            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Execute the ALTER TABLE query to drop the foreign key constraint
        stmt  = con->createStatement ();
        query = "ALTER TABLE " + string (pTableName) + " DROP FOREIGN KEY " + string (pForeignKeyName) + ";";
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    }
    catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;

        return BAD;
    }
}

eGoodBad TLocalDataBase::ShowForeignKeyData (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, 
                                             AStrPtr pTableName, StrPtr& pBadResponse) 
{
        Driver *               driver            = nullptr;
        Connection *           con               = nullptr;
        Statement *            stmt              = nullptr;
        PreparedStatement *    pstmt             = nullptr;
        ResultSet *            res               = nullptr;
        ResultSetMetaData *    meta_data         = nullptr;
        AStrPtr                result_string;
        string                 query;
        CAStrPtr               bad_resp          = nullptr;
        ULong                  len;
        int                    column_count;

    try {

        driver = get_driver_instance();
        con    = driver->connect(pServer, pUserName, pPassword);

    }catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);
        return BAD;
    }

    try {
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = DATABASE_NOT_EXIST;
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        con->setSchema (pDataBaseName);

        if (pArgc == 5) {

            pstmt = con->prepareStatement ("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
            pstmt->setString (1, pDataBaseName);
            pstmt->setString (2, pTableName);
            res  = pstmt->executeQuery ();

            if (!res->next ()) {

                bad_resp     = "Table does not exist";
                len          = (ULong) strlen (bad_resp);
                pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
                UTF8ToUTF16 (pBadResponse, bad_resp, len);

                delete res;
                delete pstmt;
                delete con;

                return BAD;
            }

            delete res;
            delete pstmt;

            res   = nullptr;
            pstmt = nullptr;
        }

        stmt = con->createStatement ();

        if (pArgc == 5) {

            query = "SELECT table_name, constraint_name, column_name, referenced_table_name, referenced_column_name FROM information_schema.key_column_usage WHERE table_schema = '" + string(pDataBaseName) + "' AND table_name = '" + string(pTableName) + "' AND referenced_table_name IS NOT NULL;";
        
        } else {

            query = "SELECT table_name, constraint_name, column_name, referenced_table_name, referenced_column_name FROM information_schema.key_column_usage WHERE table_schema = '" + string(pDataBaseName) + "' AND referenced_table_name IS NOT NULL;";
        }

        res          = stmt->executeQuery (query);
        meta_data    = res->getMetaData ();
        column_count = meta_data->getColumnCount ();

        rapidjson::Document json_document;
        json_document.SetObject ();

        rapidjson::Value data_array (rapidjson::kArrayType);

        while (res->next ()) {

            rapidjson::Value row_object (rapidjson::kObjectType);

            for (int j = 1; j <= column_count; ++j) {

                rapidjson::Value column_name;
                rapidjson::Value column_value;

                column_name.SetString (meta_data->getColumnName (j).c_str (), json_document.GetAllocator ());
                column_value.SetString (res->getString (j).c_str (), json_document.GetAllocator ());
                row_object.AddMember (column_name, column_value, json_document.GetAllocator ());
            }
            data_array.PushBack (row_object, json_document.GetAllocator ());
        }

        json_document.AddMember ("ForeignKeyTable", data_array, json_document.GetAllocator ());

        // Convert JSON document to string
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer (buffer);
        json_document.Accept (writer);

        result_string = (AStrPtr) buffer.GetString ();

        if (WriteResponeFile (result_string) == BAD) {

            bad_resp     = "Failed to write data in file";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete stmt;
            delete con;
            delete res;
            return BAD;
        }

        delete stmt;
        delete con;
        delete res;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen( bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;

        return BAD;
    }
}

eGoodBad TLocalDataBase::CreateTrigger (Word pArgc, AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTriggerName,
                                        AStrPtr pTableName, AStrPtr pActivationTime, AStrPtr pTriggerEvent, AStrPtr pTriggerCondition, StrPtr& pBadResponse)
{
        Driver *               driver      = nullptr;
        Connection *           con         = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        Statement *            stmt        = nullptr;
        ResultSet *            res         = nullptr;
        string                 query;
        CAStrPtr               bad_resp    = nullptr;
        ULong                  len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));

        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {
        // Check if database exists
        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res  = pstmt->executeQuery ();

        if (!res->next()) {

            bad_resp     = DATABASE_NOT_EXIST;
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Check if trigger exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TRIGGER_NAME FROM INFORMATION_SCHEMA.TRIGGERS WHERE TRIGGER_SCHEMA = ? AND TRIGGER_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTriggerName);
        res  = pstmt->executeQuery ();

        if (res->next ()) {
            // Trigger already exists
            bad_resp     = "Trigger already exists";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Create trigger query
        stmt = con->createStatement ();

        if (pArgc == 8) {

            query = "CREATE TRIGGER " + string (pTriggerName) + " " + string (pActivationTime) + " " +string (pTriggerEvent) + " ON " +string (pTableName) +" FOR EACH ROW " + " SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = '" + 
                     string (pTableName) + " does not support creation/deletion/updation of data';";

        } else {

            query = "CREATE TRIGGER " + string (pTriggerName) + " " + string (pActivationTime) + " " + string (pTriggerEvent) + " ON " + string (pTableName) + " FOR EACH ROW " + string (pTriggerCondition) + ";";
        }

        // Execute the query
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete pstmt;
        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::DropTrigger (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, AStrPtr pTriggerName, StrPtr& pBadResponse)
{
        Driver *               driver      = nullptr;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        string                 query;
        CAStrPtr               bad_resp    = nullptr;
        ULong                  len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof(Char));
        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        return BAD;
    }

    try {

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res  = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = DATABASE_NOT_EXIST;
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Check if the trigger exists
        con->setSchema (pDataBaseName);
        pstmt = con->prepareStatement ("SELECT TRIGGER_NAME FROM INFORMATION_SCHEMA.TRIGGERS WHERE TRIGGER_SCHEMA = ? AND TRIGGER_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        pstmt->setString (2, pTriggerName);
        res  = pstmt->executeQuery ();

        if (!res->next()) {
            // Trigger does not exist
            bad_resp     = "Trigger does not exist";
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16(pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Drop the trigger
        stmt  = con->createStatement ();
        query = "DROP TRIGGER " + string (pTriggerName) + ";";

        // Execute the query
        stmt->execute (query);

        delete stmt;
        delete con;

        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::SetGeneralLog (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eActionType pLogAction,
                                        StrPtr& pBadResponse) 
{
        Driver *               driver      = nullptr;
        Connection *           con         = nullptr;
        Statement *            stmt        = nullptr;
        PreparedStatement *    pstmt       = nullptr;
        ResultSet *            res         = nullptr;
        string                 query;
        CAStrPtr               bad_resp    = nullptr;
        ULong                  len;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
        UTF8ToUTF16 (pBadResponse, bad_resp, len);
        return BAD;
    }

    try {

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res = pstmt->executeQuery ();

        if (!res->next ()) {

            bad_resp     = DATABASE_NOT_EXIST;
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Set the schema
        con->setSchema (pDataBaseName);

        stmt = con->createStatement ();

        switch (pLogAction) {

            case ACTION_TYPE_ENABLE:

                // Enable general log and set log output to table
                stmt->execute ("SET global general_log = 1;");
                stmt->execute ("SET global log_output = 'table';");
                break;

            case ACTION_TYPE_DISABLE:

                stmt->execute ("SET global general_log = 0;");
                break;

            case ACTION_TYPE_DELETE:
                // Delete general log data
                stmt->execute ("truncate table mysql.general_log;");
                break;

            default:
                // Invalid action type
                bad_resp     = TDL_ERROR_INCORRECT_ACTION_TYPE;
                len          = (ULong) strlen (bad_resp);
                pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
                UTF8ToUTF16 (pBadResponse, bad_resp, len);
                delete stmt;
                delete con;
                return BAD;
        }

        delete stmt;
        delete con;
        return GOOD;

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;
        return BAD;
    }
}

eGoodBad TLocalDataBase::PerformMysqlJoin (AStrPtr pServer, AStrPtr pUserName, AStrPtr pPassword, AStrPtr pDataBaseName, eJoinType pJoinType, AStrPtr pSelectCondition, AStrPtr pSetOrFromCondtion, AStrPtr * pTableNameArray, 
                                           ULong pTableNameArraySize, AStrPtr * pOnConditionArray, ULong pOnConditionArraySize, AStrPtr pWhereCondition, StrPtr& pBadResponse)
{
        Driver *               driver             = nullptr;
        Connection *           con                = nullptr;
        Statement *            stmt               = nullptr;
        PreparedStatement *    pstmt              = nullptr;
        ResultSet *            res                = nullptr;
        ResultSetMetaData *    meta_data          = nullptr;
        AStrPtr                result_string;
        string                 query;
        CAStrPtr               bad_resp           = nullptr;
        ULong                  len;
        bool                   is_select_query    = false;
        int                    column_count;

    try {

        driver = get_driver_instance ();
        con    = driver->connect (pServer, pUserName, pPassword);

    } catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
        UTF8ToUTF16 (pBadResponse, bad_resp, len);
        return BAD;
    }

    try {

        pstmt = con->prepareStatement ("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = ?");
        pstmt->setString (1, pDataBaseName);
        res   = pstmt->executeQuery ();

        if (!res->next()) {

            bad_resp     = DATABASE_NOT_EXIST;
            len          = (ULong) strlen (bad_resp);
            pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
            UTF8ToUTF16 (pBadResponse, bad_resp, len);

            delete res;
            delete pstmt;
            delete con;
            return BAD;
        }

        delete res;
        delete pstmt;

        res   = nullptr;
        pstmt = nullptr;

        // Set the schema
        con->setSchema (pDataBaseName);

        stmt = con->createStatement ();

        switch (pJoinType) {

            case INNER_JOIN_TYPE:
            case LEFT_JOIN_TYPE:
            case RIGHT_JOIN_TYPE:
            case CROSS_JOIN_TYPE:
            case NATURAL_JOIN_TYPE:
            case EQUI_JOIN_TYPE:
                is_select_query = true;

                query = "SELECT " + string (pSelectCondition) + " FROM " + string (pSetOrFromCondtion);
                for (ULong i = 0; i < pTableNameArraySize; ++i) {

                    switch (pJoinType) {

                        case INNER_JOIN_TYPE:

                            query += " INNER JOIN " + string(pTableNameArray[i]) + " ON " + string (pOnConditionArray[i]);
                            break;

                        case LEFT_JOIN_TYPE:

                            query += " LEFT JOIN " + string (pTableNameArray[i]) + " ON " + string (pOnConditionArray[i]);
                            break;

                        case RIGHT_JOIN_TYPE:
                        
                            query += " RIGHT JOIN " + string (pTableNameArray[i]) + " ON " + string (pOnConditionArray[i]);
                            break;

                        case CROSS_JOIN_TYPE:
                            
                            query += " CROSS JOIN " + string (pTableNameArray[i]);
                            break;

                        case NATURAL_JOIN_TYPE:
                             
                            query += " NATURAL JOIN " + string (pTableNameArray[i]);
                            break;

                        default:
                            break;
                    }
                }
                break;

            case DELETE_JOIN_TYPE:

                query = "DELETE " + string (pSelectCondition) + " FROM " + string (pSetOrFromCondtion);

                for (ULong i = 0; i < pTableNameArraySize; ++i) {

                    query += " JOIN " + string (pTableNameArray[i]) + " ON " + string (pOnConditionArray[i]);
                }
                break;

            case UPDATE_JOIN_TYPE:

                query = "UPDATE " + string (pSelectCondition);

                for (ULong i = 0; i < pTableNameArraySize; ++i) {

                    query += " JOIN " + string (pTableNameArray[i]) + " ON " + string (pOnConditionArray[i]);
                }
                query += " SET " + string (pSetOrFromCondtion);
                break;
        
            default:
             
                // Invalid Join type
                bad_resp     = TDL_ERROR_INCORRECT_MYSQL_JOIN_TYPE;
                len          = (ULong) strlen (bad_resp);
                pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
                UTF8ToUTF16 (pBadResponse, bad_resp, len);
                delete stmt;
                delete con;
                return BAD;
        }

        if (pWhereCondition && *pWhereCondition) {

            query += " WHERE " + string (pWhereCondition);
        }

        query += ";";

        if (is_select_query) {

            res          = stmt->executeQuery (query);
            meta_data    = res->getMetaData ();
            column_count = meta_data->getColumnCount ();

            rapidjson::Document json_document;
            json_document.SetObject ();

            rapidjson::Value data_array (rapidjson::kArrayType);

            while (res->next ()) {

                rapidjson::Value row_object (rapidjson::kObjectType);

                for (int j = 1; j <= column_count; ++j) {

                    rapidjson::Value column_name;
                    rapidjson::Value column_value;

                    column_name.SetString (meta_data->getColumnName (j).c_str (), json_document.GetAllocator ());
                    column_value.SetString (res->getString (j).c_str (), json_document.GetAllocator ());
                    row_object.AddMember (column_name, column_value, json_document.GetAllocator ());
                }
                data_array.PushBack (row_object, json_document.GetAllocator ());
            }

            json_document.AddMember ("Join Data", data_array, json_document.GetAllocator ());

            // Convert JSON document to string
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer (buffer);
            json_document.Accept (writer);

            result_string = (AStrPtr) buffer.GetString ();

            if (WriteResponeFile (result_string) == BAD) {

                bad_resp     = "Failed to write data in file";
                len          = (ULong) strlen (bad_resp);
                pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
                UTF8ToUTF16 (pBadResponse, bad_resp, len);

                delete res;
                delete stmt;
                delete con;
                return BAD;
            }
            delete res;
            res = nullptr;

        } else {

            stmt->executeUpdate (query);
        }

        delete stmt;
        delete con;
        return GOOD;

    }
    catch (SQLException& e) {

        bad_resp     = e.what ();
        len          = (ULong) strlen (bad_resp);
        pBadResponse = (StrPtr) malloc ((len + 1) * sizeof (Char));
        UTF8ToUTF16 (pBadResponse, bad_resp, len);

        delete stmt;
        delete con;
        return BAD;
    }
}