#ifndef TICTACTOE_SHOW_BOARD_HPP
#define TICTACTOE_SHOW_BOARD_HPP

#include "tictactoe.hpp"
#include <fas/type_list.hpp>
#include <fas/typemanip.hpp>
#include <iostream>

namespace std
{
  std::ostream& operator<<(std::ostream& s,  e) 
  {
    s << "-";
    return s;
  }

  std::ostream& operator<<(std::ostream& s,  o) 
  {
    s << "O";
    return s;
  }

  std::ostream& operator<<(std::ostream& s,  x) 
  {
    s << "X";
    return s;
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
    return s;
  }

  
  std::ostream& operator<<(std::ostream& s, fas::empty_list) 
  {
    return s;
  }

  /*
   * [ pos, fig, board ] - победный ход компилятора
   * [ pos, e,   board ] - очередной ход
   * [ pos, e,   board ] - очередной ход
   * [ -1,  fig, empty_list ] - исходная доска с победителем Fig
   * [ -1 , e,   empty_list ] - исходная доска с нечей
*/

  template<typename Pos, typename Fig, typename Board>
  std::ostream& operator<< ( std::ostream& s, fas::tuple< Pos, Fig, Board> ) 
  { 
    s << Board();
    
    enum {
      nopos   = fas::same_type< Pos, fas::int_<-1> >::value, 
      nofig   = fas::same_type< e, Fig>::value
    };
    
    if ( nopos )
    {
      if (nofig)
        s << "Draw" << std::endl;
      else
        s << Fig() << " winner (you)" << std::endl;
    }
    else if ( !nofig )
    {
      s << Fig() << " winner (compiler)" << std::endl;
    }
    return s;
  }

  template<typename Pos, typename Fig, typename Board, typename Tail>
  std::ostream& operator<<(std::ostream& s,  fas::type_list<fas::tuple< Pos, Fig, Board>, Tail>) 
  {
    s << fas::tuple<Pos, Fig, Board>() << std::endl;
    s << Tail();
    return s;
  }
}

#endif
