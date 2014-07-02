cmake_minimum_required(VERSION 2.6)

project(tictactoy CXX)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

if(UNIX)
#   if ( NOT ${gcc_version_number} LESS 4008 )
#       SET(CMAKE_CXX_STANDARD    "${CMAKE_CXX_STANDARD} -ftemplate-backtrace-limit=0")
#endif()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_STANDARD} -W -Wall -pedantic -fno-rtti")

  message(STATUS "CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-O2 -g -DNDEBUG")
  set(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g -fno-inline")
elseif(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /wd4503 /wd4307 /EHsc /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS")
  set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
  set(CMAKE_CXX_FLAGS_DEBUG  "/Od /D_DEBUG")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/Yd /O2 /DNDEBUG")
else(UNIX)

endif(UNIX)


add_subdirectory(faslib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/faslib)

add_executable(tictactoe_iter tictactoe_iter.cpp)
add_executable(tictactoe_its tictactoe_its.cpp)
add_executable(tictactoe tictactoe.cpp)

set( level_sh "${CMAKE_CURRENT_SOURCE_DIR}/level.sh")
set( board_sh "${CMAKE_CURRENT_SOURCE_DIR}/board.sh")
set( rand_sh "${CMAKE_CURRENT_SOURCE_DIR}/rand.sh")

if (WIN32)
 set( level_sh "${CMAKE_CURRENT_SOURCE_DIR}/level.cmd")
 set( board_sh "${CMAKE_CURRENT_SOURCE_DIR}/board.cmd")
 set( rand_sh "${CMAKE_CURRENT_SOURCE_DIR}/rand.cmd")
endif()

add_custom_target(
    rand
    COMMAND
      ${rand_sh}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
  board 
  COMMAND
    ${board_sh}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
  level 
  COMMAND
    ${level_sh}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)


add_dependencies(tictactoe rand level board)
add_dependencies(tictactoe_its rand level board)
