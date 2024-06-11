#ifndef LOCALDB_H
#define LOCALDB_H

#include "common.hpp"

extern "C" {

	HRESULT    CreateDB         (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize);
	HRESULT    DeleteDB         (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize);
	HRESULT    CreateTable      (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize);
	HRESULT    DeleteTable      (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize);
	HRESULT    AlterTable       (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize);
	HRESULT    InsertData       (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize);
	HRESULT    DeleteAllData    (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize);
	HRESULT    ShowTableData    (Word pArgc, WStrPtr* pArgv, WStrPtr* pResult, Long* pResultSize);
}

#endif