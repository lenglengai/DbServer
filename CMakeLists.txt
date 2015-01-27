cmake_minimum_required(VERSION 3.0)
project(dbServer)

if(WIN32)
  add_definitions("-D_WIN32_WINNT=0x0601")
  set(CMAKE_C_FLAGS_DEBUG   "/MDd /Zi /Od /Ob0 /RTC1")
  set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Od /Ob0 /RTC1")
  set(CMAKE_C_FLAGS_RELEASE   "/MT /O2 /Ob2 /DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "/MT /O2 /Ob2 /DNDEBUG")
  set(CMAKE_EXE_LINKER_FLAGS "/MANIFEST:NO")
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
else()
  set(CMAKE_CXX_FLAGS "-std=c++11")
endif()

include_directories($ENV{BOOST_ROOT})
link_directories($ENV{BOOST_ROOT}/stage/lib)
set(Boost_USE_STATIC_LIBS TRUE)
find_package(Boost COMPONENTS system date_time regex chrono thread filesystem log log_setup REQUIRED)

include_directories($ENV{MYSQL_ROOT}/include)
link_directories($ENV{MYSQL_ROOT}/lib)

##############################################################
set( MAIN_SRC
	${CMAKE_SOURCE_DIR}/Main.cpp )
	
set( MAIN_H  
	${CMAKE_SOURCE_DIR}/Common.h 
	${CMAKE_SOURCE_DIR}/DbError_.h )
##############################################################
set( commons ${CMAKE_SOURCE_DIR}/Common )

set( COMMON_SRC
	${commons}/LogService.cpp
	${commons}/TimeService.cpp
	${commons}/default.cpp 
	${commons}/version.cpp)

SET( COMMON_H
	${commons}/version.h
	${commons}/default.h
	${commons}/singleton.h
	${commons}/noncopyable.h
	${commons}/convert.h
	${commons}/LogService.h
	${commons}/TimeService.h)
##############################################################
set( dbServices ${CMAKE_SOURCE_DIR}/DbService )

set( DB_SRC
	${dbServices}/BufWriter.cpp
	${dbServices}/DataBase.cpp
	${dbServices}/DbConnection.cpp 
	${dbServices}/DbParam.cpp 
	${dbServices}/DbPreResult.cpp 
	${dbServices}/DbResult.cpp 
	${dbServices}/DbService.cpp 
	${dbServices}/DbStatement.cpp )

SET( DB_H
	${dbServices}/BufWriter.h
	${dbServices}/DataBase.h
	${dbServices}/DbConnection.h
	${dbServices}/DbParam.h
	${dbServices}/DbPreResult.h
	${dbServices}/DbResult.h
	${dbServices}/DbService.h
	${dbServices}/DbStatement.h )
##############################################################
set( packets ${CMAKE_SOURCE_DIR}/Packet )

set( PKT_SRC
	${packets}/D2SCommand.cpp
	${packets}/D2SPreCommand.cpp
	${packets}/D2SPreQuery.cpp 
	${packets}/D2SQuery.cpp 
	${packets}/D2SStatement.cpp 
	${packets}/S2DPreCommand.cpp 
	${packets}/S2DPreQuery.cpp 
	${packets}/S2DStatement.cpp )

SET( PKT_H
	${packets}/D2SCommand.h
	${packets}/D2SPreCommand.h
	${packets}/D2SPreQuery.h
	${packets}/D2SQuery.h
	${packets}/D2SStatement.h
	${packets}/S2DPreCommand.h
	${packets}/S2DPreQuery.h
	${packets}/S2DStatement.h )
##############################################################
set( sessions ${CMAKE_SOURCE_DIR}/Session )

set( SES_SRC
	${sessions}/ReadBlock.cpp
	${sessions}/WriteBlock.cpp
	${sessions}/IoService.cpp 
	${sessions}/D2SQuery.cpp 
	${sessions}/D2SStatement.cpp 
	${sessions}/S2DPreCommand.cpp 
	${sessions}/S2DPreQuery.cpp 
	${sessions}/S2DStatement.cpp )

SET( SES_H
	${sessions}/IBlock.h
	${sessions}/ReadBlock.h
	${sessions}/WriteBlock.h
	${sessions}/IoService.h
	${sessions}/D2SStatement.h
	${sessions}/S2DPreCommand.h
	${sessions}/S2DPreQuery.h
	${sessions}/S2DStatement.h )
##############################################################

add_executable( ${PROJECT_NAME}
	${MAIN_SRC} ${MAIN_H}
	${COMMON_SRC} ${COMMON_H}
	${DB_SRC} ${DB_H}
	${PKT_SRC} ${PKT_H}
	${SES_SRC} ${SES_H}	)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} libmariadb)
