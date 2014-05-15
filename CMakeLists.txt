cmake_minimum_required(VERSION 2.6)

project(tictactoy CXX)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -ftemplate-backtrace-limit=0")

include_directories(../faslib)
#add_executable(tictactoe tictactoe.cpp)
#add_executable(tictactoe2 tictactoe2.cpp)
#add_executable(tictactoe3 tictactoe3.cpp)
add_executable(tictactoe_its tictactoe_its.cpp)
add_executable(tictactoe tictactoe.cpp)
#add_executable(test test.cpp)

string(TIMESTAMP ts "%M%S")
message(STATUS " ------------- ${ts} ------------------- ")
string(RANDOM LENGTH 4 ALPHABET 0123456789 RANDOM_SEED ${ts} initial_rand)

add_custom_target(
    rand
    COMMAND
      ./rand.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
  board 
  COMMAND
    ./board.sh
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
  level 
  COMMAND
    ./level.sh
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)


add_dependencies(tictactoe rand level board)
add_dependencies(tictactoe_its rand level board)
