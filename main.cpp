#include "main.hpp"

using namespace std;


void print(vector<int> &v, int n, mutex &mtx)
{
    lock_guard<mutex> guard(mtx);
    for (size_t i = 0; i < v.size(); ++i)
        v.at(i) = n;
    for (auto elem : v) {
            cout << elem << " ";
        }
    cout << endl;
}

/* stack listing 3.3*/
template<typename T, typename Container = deque<T> >
class stack
{
public:
    explicit stack (const Container&);
    explicit stack (Container&& = Container());
    template <class Alloc> explicit stack (const Alloc&);
    template <class Alloc> stack (const Container&, const Alloc&);
    template <class Alloc> stack (const Container&&, const Alloc&);
    template <class Alloc> stack (stack&&, const Alloc&);
    bool empty() const;
    size_t size() const;
    T& top();
    T const& top() const;
    void push (T const&);
    void push (T&&);
    void pop();
    void swap(stack&&);
};


int main ()
{
      setlocale(0, "");
      srand(time(0));
      srand(rand());
      ostream_iterator<int> out(cout, "\n");
      const size_t size = 25;
      boost::chrono::milliseconds start(clock());
//----------------------------------------------------------------

      vector<int> vec(size);
      mutex mtx;


      thread thr1([&vec, &mtx](){ print(vec, 7, mtx);
              auto pd = getpid();
              cout << pd << endl;
          });
      thread thr2([&vec, &mtx](){ print(vec, 9, mtx);
              auto pd = getpid();
              cout << pd << endl;
          });

      auto ppd = getppid();

      thr1.join();
      thr2.join();


      for (auto elem : vec)
          cout << elem << " ";
      cout <<  endl;


      cout << ppd << endl;
      */
//---------------------------------------------------------------
      boost::chrono::milliseconds end(clock());
      using ms = boost::chrono::milliseconds;
      ms dur = boost::chrono::duration_cast<ms>(end - start);
      double dd = dur.count() / 1000.0;
      cout << fixed << dd / 1000.0 << " sec. = " << (end - start) / 1000.0 << endl;

    return 0;
}











