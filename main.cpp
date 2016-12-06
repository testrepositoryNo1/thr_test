#include "main.hpp"

using namespace std;

/* files generator */
void fill_files()
{
    ofstream fout;
    string str;
    my_boost_int_Rnd rnd;

    for(size_t i = 1; i <= 3; ++i) {
            str = "file_no_" + to_string(i) + ".txt";
            fout.open(str, ios::out);
            fout << i << "\n";
            for(size_t i = 0; i < 10; ++i) {
                    fout << rnd.double_boost_rnd() << " ";
                }
            fout.close();
        }
}


/*
   сложение
*/
double addition (deque<double> deq)
{
    double sum = 0.0;

    for (auto elem : deq)
        sum += elem;

    return sum;
}

/*
   умножение
*/
double multiplication (deque<double> deq)
{
    double mtpl = 1.0;

    for (auto elem : deq)
        mtpl *= elem;

    return mtpl;
}

/*
   сумма квадратов
*/
double sum_of_squares (deque<double> deq)
{
    double sum = 0.0;

    for (auto elem : deq)
        sum += (elem * elem);

    return sum;
}

struct temp {
    double sum{0.0};
    double mtpl{0.0};
    double sum_of_sq{0.0};
};

double read_file(int _number, mutex &mtx)
{
    lock_guard<mutex> guard(mtx);
    string str = "file_no_" + to_string(_number) + ".txt";
    ifstream fin(str, ios::out);

    deque<double> deq;
    double var = 0.0;

    while (fin) {
           fin >> var;
           deq.push_back(var);
        }
    int instruction = deq.front();
    deq.pop_front();

    temp obj;

    switch (instruction) {
        case 1: obj.sum       = addition(deq); return obj.sum;
        case 2: obj.mtpl      = multiplication(deq); return obj.mtpl;
        case 3: obj.sum_of_sq = sum_of_squares(deq); return obj.sum_of_sq;
        }
    return  -1;
}

int main ()
{
      setlocale(0, "");
      srand(time(0));
      srand(rand());
      //ostream_iterator<int> out(cout, "\n");
      //const size_t size = 25;
      boost::chrono::milliseconds start(clock());
//----------------------------------------------------------------


      fill_files();


      ofstream fout("out.dat", ios::out);
      mutex mtx;
      temp tmp;



      thread thr1([&fout, &mtx, &tmp]()
      {
              tmp.sum = read_file(1, mtx);
              fout << "just sum: " << tmp.sum << "\n";
          });
      thread thr2([&fout, &mtx, &tmp]()
      {
              tmp.mtpl = read_file(2, mtx);
              fout << fixed << "multiplication: " << tmp.mtpl << "\n"; });

      thread thr3([&fout, &mtx, &tmp]()
      {
              tmp.sum_of_sq = read_file(3, mtx);
               fout << "sum_of_squares: " << tmp.sum_of_sq << "\n";
          });

      thr1.join();
      thr2.join();
      thr3.join();

      cout << tmp.sum << "\n" << tmp.mtpl << "\n" << tmp.sum_of_sq << endl;

//---------------------------------------------------------------
      boost::chrono::milliseconds end(clock());
      using ms = boost::chrono::milliseconds;
      ms dur = boost::chrono::duration_cast<ms>(end - start);
      double dd = dur.count() / 1000.0;
      cout << fixed << dd / 1000.0 << " sec. = " << (end - start) / 1000.0 << endl;

    return 0;
}











