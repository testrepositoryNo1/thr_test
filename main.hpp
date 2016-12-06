#ifndef MAIN_HPP
#define MAIN_HPP
#include "stdfx.h"

class my_boost_int_Rnd
{
public:

  int64_t int_boost_rnd()
  {
    boost::random::mt19937 temp_gen(clock() * time(0) / rand());       /* seed */
    boost::random::uniform_int_distribution<>temp_di;
    boost::random::mt19937 gen(temp_di(temp_gen));
    boost::random::uniform_int_distribution<> dist;
    return dist(gen);
  }


  int64_t int_boost_rnd(int a, int b)
  {
    boost::random::mt19937 temp_gen(clock() * time(0) / rand());       /* seed is clock*/
    boost::random::uniform_int_distribution<>temp_di;
    boost::random::mt19937 gen(temp_di(temp_gen));
    boost::random::uniform_int_distribution<> dist(a, b);
    return dist(gen);
  }

  long double double_boost_rnd()
  {
    my_boost_int_Rnd ob;

    double r =  ob.int_boost_rnd() / 1.0;
    double x = r / ob.int_boost_rnd() * ob.int_boost_rnd(1, 100);
    return x;
  }
};

template <typename Type>
void gen(Type &v, size_t _size)
{
    my_boost_int_Rnd rnd;
    for (size_t i = 0; i < _size; ++i)
        v.push_back(rnd.int_boost_rnd());
}


#endif // MAIN_HPP
