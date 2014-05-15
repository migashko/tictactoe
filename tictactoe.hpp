#ifndef TICTACTOE_TICTACTOE_HPP
#define TICTACTOE_TICTACTOE_HPP

#include <fas/type_list.hpp>
#include <fas/typemanip.hpp>
#include <fas/algorithm.hpp>
#include <fas/integral.hpp>

#include "types.hpp"

/// ///////////////////////////////////////////
/// ///////////////////////////////////////////
/// ///////////////////////////////////////////

template<typename L>
struct last
{
  typedef typename fas::type_at_c<
    fas::length< L >::value-1, 
    L
  >::type type;
};

template<int Pos, typename V, typename L>
struct set_at_c
{
  typedef fas::split_c<Pos, L> splitter;
  typedef typename splitter::left_list left_list;
  typedef typename splitter::right_list right_list;
  typedef typename fas::tail< right_list >::type headless;
  typedef fas::type_list< V, headless > pollywog;
  typedef typename fas::merge< left_list, pollywog >::type type;
};

template<typename Pos, typename V, typename L>
struct set_at
  : set_at_c< Pos::value, V, L>
{
};

/// ///////////////////////////////////////////
/// ///////////////////////////////////////////
/// ///////////////////////////////////////////

template<typename Board>
struct is_full
{
  enum {
    value = fas::type_count< $, Board >::value == 0
  };
  typedef fas::int_<value> type;
};

template<typename Fig, typename PairList>
struct is_win_line
{
  enum {
    value = fas::count_if< PairList , fas::same_type< Fig, fas::second<fas::_1> > >::value == 3
  };
};


template<typename Fig, typename PairList>
struct has_win_pos
{
  enum {
    value = 
         fas::count_if< PairList , fas::same_type< $,   fas::second<fas::_1> > >::value == 1
      && fas::count_if< PairList , fas::same_type< Fig, fas::second<fas::_1> > >::value == 2
  };
};

/// /////////////////////////////////////////

template<typename Fig, typename PairList>
struct win_helper
{
  typedef typename fas::if_c<
    has_win_pos< Fig, PairList >::value, 
    typename fas::select< PairList, fas::same_type< fas::second<fas::_1>, $> >::type, 
    fas::empty_list
  >::type type;
};


template<typename Fig, typename PairList>
struct winning_move
{
  typedef typename fas::transform<
    typename win_helper< Fig, PairList >::type, 
    fas::pair< fas::first<fas::_1>, Fig > 
  >::type type;
};

template<typename Fig, typename PairList>
struct blocking_move
{
  typedef typename fas::if_<
    fas::same_type<Fig, x>, 
    o, 
    x
  >::type rev_fig;

  typedef typename win_helper< rev_fig, PairList >::type type;
};

template<typename, typename PairList>
struct winner_line
{
  typedef typename fas::switch_<
    fas::case_c< is_win_line<x, PairList>::value, fas::pair< fas::int_<-1>, x> >, 
    fas::case_c< is_win_line<o, PairList>::value, fas::pair< fas::int_<-1>, o> >,
    fas::default_< fas::empty_list >
  >::type type;
};

/// ////////////////////////////////////////////////

template<
  template<typename, typename> class Move, 
  typename Fig, 
  typename Board, 
  int P0, int P1, int P2
>
struct move_t
{
  typedef typename fas::type_list_n<
    fas::pair< fas::int_<P0>, typename fas::type_at_c<P0, Board>::type >, 
    fas::pair< fas::int_<P1>, typename fas::type_at_c<P1, Board>::type >, 
    fas::pair< fas::int_<P2>, typename fas::type_at_c<P2, Board>::type >
  >::type pos_list;

  typedef typename Move<Fig, pos_list>::type type;
};

template<
  template<typename, typename> class Move, 
  typename Fig, 
  typename Board
>
struct moves_list_t
{
  typedef typename fas::type_list_n <
    typename move_t< Move, Fig, Board, 0, 1, 2 >::type,
    typename move_t< Move, Fig, Board, 3, 4, 5 >::type, 
    typename move_t< Move, Fig, Board, 6, 7, 8 >::type, 
 
    typename move_t< Move, Fig, Board, 0, 3, 6 >::type,
    typename move_t< Move, Fig, Board, 1, 4, 7 >::type, 
    typename move_t< Move, Fig, Board, 2, 5, 8 >::type, 

    typename move_t< Move, Fig, Board, 0, 4, 8 >::type, 
    typename move_t< Move, Fig, Board, 2, 4, 6 >::type

  >::type type;
};

/// ////////////////////////////////////////////////

template<typename Board>
struct draw_list
{
  typedef typename fas::if_c<
    is_full< Board >::value, 
    fas::pair< fas::int_<-1>, $ >, 
    fas::empty_list
  >::type type;
};

template<typename Fig, typename Board>
struct winner_list
  : moves_list_t< winner_line,  Fig, Board>
{};


template<typename Fig, typename Board>
struct winning_moves
  : moves_list_t< winning_move,  Fig, Board>
{};

template<typename Fig, typename Board>
struct blocking_moves
  : moves_list_t< blocking_move,  Fig, Board>
{};

/// ////////////////////////////////////////////////

template<typename R, typename Level>
struct priority_positions
{
  typedef fas::int_<4> center;
  typedef fas::type_list_n< fas::int_<0>, fas::int_<2>, fas::int_<6>, fas::int_<8> >::type corner_list;
  typedef fas::type_list_n< fas::int_<1>, fas::int_<3>, fas::int_<5>, fas::int_<7> >::type side_list;
  
  typedef typename fas::merge<
    center, 
    typename fas::merge<
      typename fas::random_shuffle< R, corner_list>::type, 
      typename fas::random_shuffle< R, side_list>::type
    >::type
  >::type level2_list;

  typedef typename fas::merge<
    center, 
    typename fas::random_shuffle< 
      R, 
      typename fas::merge<
        corner_list, 
        side_list
      >::type
    >::type
  >::type level1_list;

  typedef typename fas::random_shuffle< 
      R, 
      level2_list
  >::type level0_list;

  typedef typename fas::switch_<
    fas::case_< fas::same_type< Level, fas::int_<0> >, level0_list >, 
    fas::case_< fas::same_type< Level, fas::int_<1> >, level1_list >, 
    fas::default_< level2_list >
  >::type type;
};


template<typename R, typename Level, typename Board>
struct free_moves
{
  typedef typename fas::transform  <
    typename priority_positions< R, Level >::type,
    fas::pair<
      fas::_1, 
      fas::type_at< fas::_1, Board>
    >
  >::type pair_list;

  typedef typename fas::select<
    pair_list, 
    fas::same_type< 
      $, 
      fas::second<fas::_1>
    >
  >::type type;
};

/// //////////////////////////////////


template<
  typename R,
  typename Level,
  typename Fig, 
  typename Board
>
struct available_moves
{
  typedef typename fas::type_list_n<
    typename draw_list< Board >::type, 
    typename winner_list< Fig, Board >::type, 
    typename winning_moves< Fig, Board >::type, 
    typename blocking_moves< Fig, Board >::type, 
    typename free_moves<R, Level, Board >::type
  >::type type;
};

template<typename Board>
struct figure
{
  typedef typename fas::if_c<
    fas::type_count< $, Board>::value % 2 == 1, 
    x, 
    o
  >::type type;
  
};

template<typename Pos, typename Fig,  typename Board>
struct do_move
{
  typedef typename fas::for_<
    fas::pair< Pos, Board>, 
    fas::not_equal_to< 
      fas::first<fas::_1>, 
      fas::int_<-1> 
    >, 
    fas::pair<
      fas::int_<-1>, 
      set_at< Pos, Fig, fas::second<fas::_1> >
    >
  >::type result;

  typedef typename fas::second<result>::type type;
};

template<typename R, typename Level, typename Board>
struct game
{
  typedef typename figure<Board>::type fig;
  typedef typename available_moves<R, Level, fig, Board>::type moves;
  typedef typename fas::head<moves>::type result_move;
  typedef typename fas::first<result_move>::type position;
  typedef typename fas::second<result_move>::type win_fig;
  typedef typename do_move<position, fig, Board>::type board;

  typedef fas::tuple< position, win_fig, board > type;
};

#endif
