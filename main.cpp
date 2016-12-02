#include "main.hpp"

using namespace std;
using namespace chrono;


template <typename T>
void show(vector<T> v)
{
    for (auto a : v)
        cout << a << endl;
}

template <typename T>
void func (vector<T> &v)
{
     generate(v.begin(), v.end(), rand);
}


const string currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}


void foo()
{
  ofstream fout;
  fout.open("test.txt", ios::app);

  for (size_t i = 0; i < 10; ++i) {
      fout << " + " << currentDateTime() << endl;
      sleep(1);
    }
  fout.close();
}


void gen(vector<int> &v, size_t _size)
{
    my_boost_int_Rnd rnd;
    for (size_t i = 0; i < _size; ++i)
        v.push_back(rnd.int_boost_rnd());
}


int main ()
{
      setlocale(0, "");
      srand(time(0));
      srand(rand());
      ostream_iterator<int> out(cout, "\n");
      const size_t size = 1000000;
      boost::chrono::milliseconds start(clock());
//----------------------------------------------------------------

      size_t sum = 0, sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;

      vector<int> vec;
      gen(vec, size);

      thread thr1([vec, &sum1]()
      {
              auto iter = vec.begin();
              for (size_t i = 0; i < vec.size() / 4; ++i, ++iter)
                  sum1 += *iter;
              return sum1;
          });


      thread thr2([vec, &sum2]()
      {
              auto iter = vec.begin() + vec.size() / 4;
              for (size_t i = vec.size() / 4; i < vec.size() / 2; ++i, ++iter)
                  sum2 += *iter;
              return sum2;
          });


      thread thr3([vec, &sum3]()
      {
              size_t sz = vec.size() * 3 / 4;
              auto iter = vec.begin() + vec.size() / 2;
              for (size_t i = vec.size() / 2; i < sz ; ++i, ++iter)
                  sum3 += *iter;
              return sum3;
          });


      size_t sz = vec.size();
      auto iter = vec.begin() + vec.size() * 3 / 4;
      for (size_t i = vec.size() * 3 / 4; i < sz ; ++i, ++iter)
          sum4 += *iter;

      thr1.join();
      thr2.join();
      thr3.join();

      sum = sum1 + sum2 + sum3 + sum4;
      cout << sum << endl;


//---------------------------------------------------------------
      boost::chrono::milliseconds end(clock());
      using ms = boost::chrono::milliseconds;
      ms dur = boost::chrono::duration_cast<ms>(end - start);
      double dd = dur.count() / 1000.0;
      cout << fixed << dd / 1000.0 << " sec. = " << (end - start) / 1000.0 << endl;

    return 0;
}











