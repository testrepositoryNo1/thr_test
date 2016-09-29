#include "stdfx.h"

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

class Btask
{
  string st1;
public:
  Btask(string s) { st1 = s; }
  void operator ()() const  {}

  int rnd_str()
  {
       default_random_engine dre(clock());
       uniform_int_distribution<int> di(97, 122);
       char ch;
       size_t count = 0;
       string str, rand_word = st1;
       size_t size = 0;

       while (str != rand_word) {
           str = "";
           size = rand_word.size();
           while (size){
               ch  = static_cast<char>(di(dre));
               str.push_back(ch);
               --size;
             }
           ++count;
         }

       return count;
  }


};



int main ()
{
    setlocale(0, "");
    srand(time(0));
    srand(rand());
    ostream_iterator<int> out(cout, "\n");
//    const size_t c = 10000;
    clock_t start = clock();
//----------------------------------------------------------------

    vector <int> vec_t(10);

    Btask obj1("test");
    Btask obj2("test");

    thread th(obj1);
    th.join();


    cout << obj1.rnd_str() << endl;
    cout << obj2.rnd_str() << endl;

//----------------------------------------------------------------
    clock_t finish = clock();
    double result = (finish - start) * 1.0 / CLOCKS_PER_SEC;
    cout << fixed << result << endl;
    return 0;
}





