#include "tictactoe.hpp"
#include "types.hpp"
#include "show_board.hpp"
#include <iostream>

int main()
{
  typedef game< initial_rand, level, board >::type result;
  std::cout << result() ;
  return 0;
}
