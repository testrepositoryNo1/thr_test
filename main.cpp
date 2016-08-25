#include <iostream>
#include <iomanip>
#include <stdio.h>

//#include <ctime>
//#include <time.h>
#include <chrono>

#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <string>
#include <utility>
#include <list>
#include <set>

#include <memory>

#include <fstream>

#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string.h>

#include <thread>



using namespace std;
using namespace chrono;


template <typename T>
void func (vector<T> &v)
{
    generate(v.begin(), v.end(), rand);
}


class background_task
{

public:
    background_task(){}
    background_task(vector<int> &v) { generate(v.begin(), v.end(), rand);}
    ~background_task(){}

    void operator()() const{}


};


template <typename T>
void show(vector<T> v)
{
    for (auto a : v)
        cout << a << endl;
}

void print()
{
    int x = 0;
    while(x < 100){
        ++x;
        cout << x << endl;
        system("clear");
    }
}


template <typename T>
void foutfunc (vector<T> v)
{
    fstream fout;
    fout.open("/home/smasuryan/zeromq_projects/thr_test/test.txt", ios_base::app);
    int x = 0;
    for (auto a : v){
        fout << a << endl;
        fout.flush();
        ++x;
    }
    fout <<  "x = " << x << endl;
    fout.close();
}


class Task
{
    int x;
    vector<int> vec;
public:
    Task() { x = 0; }
    Task(int i) { x = i; }
    Task(vector<int> &v) {  func(v);  }

    ~Task() {}

    void some_func() {
        int x = 90000000;
            while(x)
                --x;
            cout << x << endl;
            }



    template <typename T>
    void func (vector<T> &v)
    {
        generate(v.begin(), v.end(), rand);
    }

    void operator () () { some_func(); }
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

    vector <int> vec_t(10, 1);

    Task t(vec_t);
    Task t1;

    thread th(t), th1(t1);
    th.join();

    copy(vec_t.begin(), vec_t.end(), out);

    th1.join();




/*    vector<int> vec(c), vec1(c);

    background_task f(vec);
    thread th1(f);
    th1.join();
    thread th( [=](){ foutfunc(vec); } );
    th.join();

*/

/*
    background_task f(vec);
    thread th(f), th1( [](){ print(); } );
    th1.detach();
    th.join();

    cout << "heare" << endl;
    func(vec1);
*/

//----------------------------------------------------------------
    clock_t finish = clock();
    double result = (finish - start) * 1.0 / CLOCKS_PER_SEC;
    cout << fixed << result << endl;
    return 0;
}





