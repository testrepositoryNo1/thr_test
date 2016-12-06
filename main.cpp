#include "main.hpp"

using namespace std;


class Read_and_fill
{

private:
    double sum;
    double mtpl;
    double sum_of_sq;
    deque<double> deq;
    mutex mtx; /* думаю ы этом приложении этот мютекс роли особо не играет */

public:
    Read_and_fill() { sum = 0.0; mtpl = 1; sum_of_sq = 0.0; }
    void    fill_files();
    double  addition (deque<double> deq);
    double  multiplication (deque<double> deq);
    double  sum_of_squares (deque<double> deq);
    double  read_file(int _number, mutex &mtx);
    void    threads();
    void    show_in_terminal();
};


void Read_and_fill::fill_files()
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
    threads();
}

/*
   сложение
*/
double Read_and_fill::addition (deque<double> deq)
{
    double sum = 0.0;

    for (auto elem : deq)
        sum += elem;

    return sum;
}

/*
   умножение
*/
double Read_and_fill::multiplication (deque<double> deq)
{
    double mtpl = 1.0;

    for (auto elem : deq)
        mtpl *= elem;

    return mtpl;
}

/*
   сумма квадратов
*/
double Read_and_fill::sum_of_squares (deque<double> deq)
{
    double sum = 0.0;

    for (auto elem : deq)
        sum += (elem * elem);

    return sum;
}

double Read_and_fill::read_file(int _number, mutex &mtx)
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


    switch (instruction) {
        case 1: sum       = addition(deq); return sum;
        case 2: mtpl      = multiplication(deq); return mtpl;
        case 3: sum_of_sq = sum_of_squares(deq); return sum_of_sq;
        }
    return  -1;
}

void Read_and_fill::threads()
{
   ofstream fout("out.dat", ios::out);

   thread thr1([&fout, this]()
   {
           sum = read_file(1, mtx);
           fout << "just sum: " << sum << "\n";
       });
   thread thr2([&fout, this]()
   {
           mtpl = read_file(2, mtx);
           fout << fixed << "multiplication: " << mtpl << "\n"; });

   thread thr3([&fout, this]()
   {
           sum_of_sq = read_file(3, mtx);
           fout << "sum_of_squares: " << sum_of_sq << "\n";
       });

   thr1.join();
   thr2.join();
   thr3.join();


}

void  Read_and_fill::show_in_terminal()
{
    cout << "just sum" << setw(8) << " : " << sum << "\n"
         << fixed << "multiplication: " << mtpl << "\n"
         << "sum_of_squares: " << sum_of_sq << endl;
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


      Read_and_fill  raf;

      raf.fill_files();
      raf.show_in_terminal();

//---------------------------------------------------------------
      boost::chrono::milliseconds end(clock());
      using ms = boost::chrono::milliseconds;
      ms dur = boost::chrono::duration_cast<ms>(end - start);
      double dd = dur.count() / 1000.0;
      cout << fixed << dd / 1000.0 << " sec. = " << (end - start) / 1000.0 << endl;

    return 0;
}











