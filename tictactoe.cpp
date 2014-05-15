
#include "tictactoe.hpp"
#include "types.hpp"
#include "show_board.hpp"

//#include "board.hpp"

//#include <fas/type_list.hpp>
//#include <fas/integral.hpp>
//#include <fas/typemanip.hpp>
//#include <fas/algorithm.hpp>
//#include <fas/static_check.hpp>
#include <iostream>
//#include<tuple>

int main()
{
  typedef game< initial_rand, level, board >::type result;
  std::cout << result() ;
  
  return 0;
}
