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

template <typename Type>
void gen(Type &v, size_t _size)
{
    my_boost_int_Rnd rnd;
    for (size_t i = 0; i < _size; ++i)
        v.push_back(rnd.int_boost_rnd());
}




/*mutex some_mutex;

void add(list<int> &add_to_list ,int new_value)
{
    lock_guard<mutex> guard(some_mutex);
    add_to_list.push_back(new_value);
}

bool list_contains(list<int> some_list, int value_to_find)
{
    lock_guard<mutex> guard(some_mutex);
    return *find(some_list.begin(), some_list.end(), value_to_find) == value_to_find;
}
*/


void print(vector<int> &v)
{
    mutex test_mutex;
    test_mutex.lock();
    //lock_guard<mutex> guard(test_mutex);
    for (auto elem : v) {
            cout << elem << " ";
        }
    cout << endl;
    test_mutex.unlock();
}

/*
void f1(int &n, mutex &mtx)
{
    while (1) {
            mtx.lock();
            cout << "f1 " << n << endl;
            n += 2;
            mtx.unlock();
            usleep(95000);
        }
}

void f2(int &n, mutex &mtx)
{
    while (1) {
            mtx.lock();
            cout << "f2 " << n << endl;
            n -= 2;
            mtx.unlock();
            usleep(95000);
        }
}
*/


int main ()
{
      setlocale(0, "");
      srand(time(0));
      srand(rand());
      ostream_iterator<int> out(cout, "\n");
      const size_t size = 100000;
      boost::chrono::milliseconds start(clock());
//----------------------------------------------------------------

      int n = 10;
      mutex mtx;

      thread thr1([&n, &mtx](){ f1(n, mtx); });
      thread thr2([&n, &mtx](){ f2(n, mtx); });

      thr1.join();
      thr2.join();

     /* vector<int> vec(size);

      thread thr([&vec](){ print(vec); });

      for (size_t i = size / 2; i < size; ++i)
          vec.at(i) = i;

      thr.join();*/


      /*list<int> lst{1,2,3,4,5,6,7,8,9,10};
       //gen(lst, 10);

       add(lst, 88);

       bool b = list_contains(lst, 89);

       if (b)
           cout << "true" << endl;
       else
           cout << "false" << endl;

       for (auto a : lst)
           cout << a << endl;*/
//---------------------------------------------------------------
      boost::chrono::milliseconds end(clock());
      using ms = boost::chrono::milliseconds;
      ms dur = boost::chrono::duration_cast<ms>(end - start);
      double dd = dur.count() / 1000.0;
      cout << fixed << dd / 1000.0 << " sec. = " << (end - start) / 1000.0 << endl;

    return 0;
}











