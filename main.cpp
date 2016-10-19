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
      fout << currentDateTime() << endl;
      sleep(1);
    }
  fout.close();
}


int main ()
{
    setlocale(0, "");
    srand(time(0));
    srand(rand());
    ostream_iterator<int> out(cout, "\n");
    const size_t c = 30;
    clock_t start = clock();
//----------------------------------------------------------------

    ofstream fout;
    fout.open("test.txt", ios::app);

    thread th(foo);
    th.detach();
    sleep(10); /* поток завершается когда основной процесс заканчивается,
                  т.е. если основной процесс (из которого был запущен поток) заканчивается до того
                  как отсоединенный поток завершит свои "дела", этот поток тоже будет остановлен...
                  (вывод ) сделан  на осове тестов...
               */
    fout << " - " << currentDateTime() << endl;
    fout.close();

//----------------------------------------------------------------
    clock_t finish = clock();
    double result = (finish - start) * 1.0 / CLOCKS_PER_SEC;
    cout << fixed << result << endl;
    return 0;
}





