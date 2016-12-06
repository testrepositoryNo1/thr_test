#include "main.hpp"

using namespace std;


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


void print(vector<int> v, mutex &mtx)
{
    //mtx.lock();
    lock_guard<mutex> guard(mtx);

    /*for (size_t i = 0; i < v.size(); ++i)
        v.at(i) = 1;*/

    for (auto elem : v) {
            cout << elem << " ";
        }
    cout << endl;
    //mtx.unlock();
}


void foo(vector<int> &v, mutex &mtx)
{
    //mtx.lock();
    lock_guard<mutex> guard(mtx);
    for (size_t i = v.size() / 2; i < v.size(); ++i)
        v.at(i) = i;
    //mtx.unlock();
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

      vector<int> vec(size);
      mutex mtx;

      thread th1([vec, &mtx](){ print(vec, mtx); });
      thread th2([&vec, &mtx](){ foo(vec, mtx); });

      th1.join();
      th2.join();

      for (size_t i = size - 20; i < size; ++i)
              cout << vec.at(i) << endl;


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











