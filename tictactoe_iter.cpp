#include "tictactoe.hpp"
#include "types.hpp"
#include "show_board.hpp"
#include <iostream>
#include <cstdio>

template<int I, typename Fig>
void input_pos(fas::empty_list);


template<int I, typename Fig, typename Board>
void input_pos(Board);

template<int I, typename Fig, typename Board>
void next_game()
{
  typedef typename game< initial_rand, fas::int_<I>, Board >::type result;
  std::cout << result() ;
  input_pos<I, Fig>(typename fas::third<result>::type());
}

template<int I, typename Fig, typename Board>
void set_fig( fas::int_<8>, int )
{
  typedef typename set_at_c<8, Fig, Board>::type board;
  next_game<I, Fig, board>();
}

template<int I, typename Fig, typename Board, int Pos>
void set_fig( fas::int_<Pos>, int pos)
{
  if (pos == Pos)
  {
    typedef typename set_at_c<Pos, Fig, Board>::type board;
    next_game<I, Fig, board>();
  }
  else
    set_fig<I, Fig, Board>( fas::int_<Pos+1>(), pos);
}



template<int I, typename Fig>
void input_pos(fas::empty_list)
{
  //std::cout << "Done" << std::endl;
  printf("Done\n");

}

template<int I, typename Fig, typename Board>
void input_pos(Board)
{
  int pos = 0;
  /*std::cout << "Pos [0..8]: ";
  std::cin >> pos;*/
  printf("Pos [0..8]: ");
  scanf("%d", &pos);

  set_fig<I, Fig, Board>(fas::int_<0>(), pos);
}

template<int I>
void start_game( o )
{
  typedef typename game< initial_rand, fas::int_<I>, empty_board >::type result;
  std::cout << result() ;
  input_pos<I, o>(typename fas::third<result>::type());
}

template<int I>
void start_game( x )
{
  std::cout << empty_board() <<  std::endl;  
  input_pos<I, x>(empty_board());
}

template<int I>
void select_fig( )
{
  char fig = 'x';
  // std::cout << "Fig [x, o]: ";
  //std::cin >> fig;
  printf("Fig [x, o]: ");
  scanf("%c", &fig);

  if (fig=='o')
    start_game<I>(o());
  else
    start_game<I>(x());
}

void select_level( fas::int_<0>, int )
{
  select_fig<0>();
}

template<int I>
void select_level( fas::int_<I>, int level)
{
  if (level == I)
    select_fig<I>();
  else
    select_level( fas::int_<I+1>(), level);
}



int main()
{
  int level = 0;
  printf("Level [0,1,2]: ");
  scanf("%d", &level);
  /*
  std::cout << "Level [0,1,2]: ";
  std::cin >> level;
  */
  select_level( fas::int_<0>(), level);
  /*
  typedef game< initial_rand, level, board >::type result;
  std::cout << result() ;
  */
  return 0;
}
