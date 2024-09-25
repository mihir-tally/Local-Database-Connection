#include <winsock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <malloc.h>
#include <tchar.h>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <iostream>
#include <sql.h>
#include <sqlext.h>
#include <vector>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

#include "rapidschema.h"
#include <stringbuffer.h>
#include <writer.h>
#include <prettywriter.h>
#include <error/en.h>

#include "defines.h"
#include "enum.h"
#include "helper.hpp"
#include "LocalDB.h"
#include "LocalDB.hpp"
#include "sqlserver.hpp"
#include "mysqlserver.hpp"