#include "show_board.hpp"
#include "tictactoe.hpp"
#include "types.hpp"
#include <map>
int main()
{
  typedef fas::for_<
    fas::type_list< 
      fas::tuple< 
        fas::empty_type, 
        e,
        board
      > 
    >, 
    fas::and_<
      fas::not_<
        fas::same_type<
          fas::int_<-1>, 
          fas::first< last< fas::_1> >
        >
      >, 
      fas::same_type<
        e, 
        fas::second< last< fas::_1> >
      > 
    >, 
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
