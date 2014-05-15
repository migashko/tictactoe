#ifndef TICCTACTOE_TYPES_HPP
#define TICCTACTOE_TYPES_HPP

#include <fas/integral.hpp>
#include <fas/type_list.hpp>

struct $ {};
struct x {};
struct o {};

typedef fas::int_< 
  #include "rand.inl" 
> initial_rand;

typedef fas::int_<
  #include "level.inl" 
> level;

typedef fas::type_list_n<
  #include "board.inl" 
>::type board;


typedef fas::type_list_n<
    $, $, $, 
    $, $, $, 
    $, $, $
>::type empty_board;

#endif
