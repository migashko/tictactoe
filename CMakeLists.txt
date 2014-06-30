cmake_minimum_required(VERSION 2.6)

project(tictactoy CXX)

add_subdirectory(faslib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/faslib)

add_executable(tictactoe_its tictactoe_its.cpp)
add_executable(tictactoe tictactoe.cpp)

set( level_sh "${CMAKE_CURRENT_SOURCE_DIR}/level.sh")
set( board_sh "${CMAKE_CURRENT_SOURCE_DIR}/board.sh")
set( rand_sh "${CMAKE_CURRENT_SOURCE_DIR}/rand.sh")

if (WIN32)
 set( level_sh "${CMAKE_CURRENT_SOURCE_DIR}\level.cmd")
 set( board_sh "${CMAKE_CURRENT_SOURCE_DIR}\board.cmd")
 set( rand_sh "${CMAKE_CURRENT_SOURCE_DIR}\rand.cmd")
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
