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

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

#include "LocalDB.h"
#include "LocalDB.hpp"
#include "defines.h"
#include "enum.h"

#include "rapidschema.h"
#include <stringbuffer.h>
#include <writer.h>
#include <prettywriter.h>
#include <error/en.h>

using namespace std;