
#include "show_board.hpp"

#include "tictactoe.hpp"
#include "types.hpp"

#include <fas/type_list.hpp>
#include <fas/integral.hpp>
#include <fas/typemanip.hpp>
#include <fas/algorithm.hpp>
#include <fas/mp.hpp>
#include <fas/static_check.hpp>
#include <iostream>
//#include<tuple>

// [ 3, $] ход

int main()
{
    // [-1, $] - ничья
    // [-1, x] - есть победитель
    // [ 3, x] - компилятор победил
    // [ 3, $] ход
    
  typedef fas::for_<
    fas::type_list< 
      fas::tuple< 
        fas::int_<-2>, 
        $, 
        board
      > 
    >, 
    fas::and_<
      fas::and_<
        fas::not_<
          fas::same_type<
            fas::int_<-1>, 
            fas::first< last< fas::_1> >
          > 
        >, 
        fas::same_type<
          $, 
          fas::second< last< fas::_1> >
        > 
      >,
      fas::not_< 
        fas::f<is_full<
          fas::third< 
            last< fas::_1>
          >
        > >
      >
    >
    /*fas::and_<*/
      /*fas::same_type<
        $, 
        fas::second< last< fas::_1> >
      >*/
      /*
      fas::same_type<
        fas::int_<-1>, 
        fas::first< last< fas::_1> >
      >, 
      fas::less<
        fas::length< fas::_1 >, 
        fas::int_<10> 
      > 
    >*/, 
    fas::push_back< 
      game< 
        initial_rand, 
        level, 
        fas::third< last< fas::_1> > 
      >, 
      fas::_1 
    >
  >::type result_list;

  typedef fas::tail<result_list>::type game_list;

  std::cout << board() << std::endl;
  std::cout << game_list() << std::endl;
  
  return 0;
}
