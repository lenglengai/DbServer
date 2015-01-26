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
	${commons}/classid.cpp
	${commons}/versionid.cpp
	${commons}/default.cpp)

SET( COMMON_H
	${commons}/definc.h
	${commons}/typeinc.h
	${commons}/error_.h
	${commons}/stdinc.h
	${commons}/libinc.h
	${commons}/default.h
	${commons}/singleton.h
	${commons}/noncopyable.h
	${commons}/convert.h
	${commons}/classid.h
	${commons}/versionid.h)
##############################################################

add_subdirectory(Common COM_SRC)
add_subdirectory(DbService DB_SRC)
add_subdirectory(Packet PKT_SRC)
aux_source_directory(. MAIN_SRC)
add_executable(${PROJECT_NAME} ${MAIN_SRC})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} libmariadb)
