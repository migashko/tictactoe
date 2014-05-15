#ifndef TICTACTOE_SHOW_BOARD_HPP
#define TICTACTOE_SHOW_BOARD_HPP

#include "tictactoe.hpp"
#include <fas/type_list.hpp>
#include <fas/typemanip.hpp>
#include <iostream>

namespace std
{
  std::ostream& operator<<(std::ostream& s,  $) 
  {
    s << "-";
  }

  std::ostream& operator<<(std::ostream& s,  o) 
  {
    s << "O";
  }

  std::ostream& operator<<(std::ostream& s,  x) 
  {
    s << "X";
  }
  
  template<typename L, typename R>
  std::ostream& operator<<(std::ostream& s,  fas::type_list<L, R>) 
  {
    s << L();
    int len = fas::length<R>::value;
    if ( len%3 == 0 )
      s <<  std::endl;
    else if (len != 0)
      s <<  " ";
    s << R();
  }

  
  std::ostream& operator<<(std::ostream& s, fas::empty_list) 
  {
  }


  template<typename Pos, typename Fig, typename Board>
  std::ostream& operator<<(std::ostream& s,  fas::tuple< Pos, Fig, Board>) 
  { 
    //std::cout <<  Fig() << Pos::value << std::endl;
    s << Board();
    
    // [-1, $] - ничья
    // [-1, x] - есть победитель
    // [ 3, x] - компилятор победил
    // [ 3, $] ход
    if ( is_full<Board>::value )
    {
      s << "Draw" << std::endl;
    }
    else if ( !fas::same_type< $, Fig>::value && !fas::same_type< fas::int_<-1>, Pos >::value )
    {
      s << Fig() << " winner (compiler)" << std::endl;
    }
    else if ( !fas::same_type< $, Fig>::value && fas::same_type< fas::int_<-1>, Pos >::value )
    {
      s << Fig() << " winner (you)" << std::endl;
    }
  }

  template<typename Pos, typename F, typename S, typename Tail>
  std::ostream& operator<<(std::ostream& s,  fas::type_list<fas::tuple< Pos, F, S>, Tail>) 
  {
    s << fas::tuple<Pos, F, S>() << std::endl;
    s << Tail();
  }
  
}


#endif
