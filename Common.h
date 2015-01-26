#pragma once

#ifdef APIEXPORT
#define __funapi __declspec(dllexport)
#else
#define __funapi
#endif

#if defined(_WIN32) ||  defined(_WIN64)
#define __WINDOW__
#endif

#ifdef __WINDOW__
#define __FUN__ __FUNCTION__
#else
#define __FUN__ __PRETTY_FUNCTION__
#endif

#define STARTYEAR 2015
#define STARTMONTH 1
#define STARTDAY 1

#define ENDYEAR 2015
#define ENDMONTH 6
#define ENDDAY 1

#define INITYEAR 2015
#define INITMONTH 1
#define INITDAY 1

#define VERNAME "release"

typedef char __i8;
typedef short __i16;
typedef long __i32;
#ifdef __WINDOW__
typedef __int64 __i64;
#else
typedef long long __i64;
#endif

#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <deque>
#include <memory>
#include <functional>
#include <mutex>
#include <atomic>
#include <chrono>
#include <thread>
#include <random>
#include <typeinfo>
#include <iostream>
#include <sstream>

#ifdef __WINDOW__
#pragma warning( push )
#pragma warning( disable : 4819 )
#endif
#include <boost/format.hpp>
#ifdef __WINDOW__
#pragma warning( pop )
#endif

#include <errmsg.h>
#include <mysql.h>

#include "Common/noncopyable.h"
#include "Common/singleton.h"
#include "Common/default.h"
#include "Common/convert.h"
#include "Common/LogService.h"
#include "Common/TimeService.h"
#include "DbError_.h"
#include "DbService/BufWriter.h"
#include "Message/D2SCommand.h"
#include "Message/D2SQuery.h"
#include "DbService/DbParam.h"
#include "Message/S2DStatement.h"
#include "Message/D2SStatement.h"
#include "Message/S2DPreCommand.h"
#include "Message/D2SPreCommand.h"
#include "Message/S2DPreQuery.h"
#include "Message/D2SPreQuery.h"
#include "DbService/DbResult.h"
#include "DbService/DbPreResult.h"
#include "DbService/DbStatement.h"
#include "DbService/DbConnection.h"
#include "DbService/DataBase.h"
#include "DbService/DbService.h"
