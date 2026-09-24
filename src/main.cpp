#include <iostream>
#include <cmath>
#include <iomanip>
#include <windows.h>

using namespace std;

//запишем нашу ф-цію

double f(double x){
    return exp(x)+ x;
}
int main(){
SetConsoleOutputCP(CP_UTF8);
// за умовою проміжок [-2 , 3], берем за х0 -1 а за х1 0
double x_old = -1.0;
double x = 1;
double epsilon = 0.1; // відносна похибка

double x_older, fx_older, fx, error;
int iter = 0;

do{
    iter++;
    x_older = x_old;
    x_old = x;

    //проганяєм через нашу ф-цію
    fx_older = f(x_older);
    fx = f(x_old);

    //ітер. формула методу січних
    x = x_old - fx/((fx_older - fx)/(x_older - x_old));

    error = abs((x-x_old)/x) * 100.0;

    cout << "ітерація: " << iter << '\n';
    cout << "x = " << setprecision(6) << x << '\n';
    cout << "похибка: " << error << '\n';
}while(error >= epsilon);

cout << "кінцеве зн корення: " << x << '\n';
cout << "f(x) мусить бути близьким до нуля: " << setprecision(3) << f(x);

return 0;
}