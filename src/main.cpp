#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x){
    return sqrt((1.0 + x) / (1.0 - x));
}

double F(double x) {
    return -sqrt(1.0 - x * x) + asin(x);
}

double trapMethod(double a, double b, int n){
    double h = (b - a) / n;
    double fa = f(a);
    double fb = f(b);
    double sum = 0.0;

    for(int i = 1; i < n; i++){
        double x = a +i * h;
        sum += f(x);
    }

    return h * ((fa + fb) / 2.0 + sum);
}


int main(){

    const double a = 0.0;
    const double b = 0.5;
    const int n = 30;
    
    double intg_trap = trapMethod(a, b, n);

    //за нютона лейбніца ф(б) - ф(а)
    double intg_exact = F(b) - F(a);

    double abs_error = abs(intg_trap - intg_exact);
    double rel_error = (abs_error / abs(intg_exact)) * 100.0;


    cout << fixed << setprecision(6);
    cout << "Наближене значення (трапеції): " << intg_trap << '\n';
    cout << "Точне значення:               " << intg_exact << '\n';
    cout << "Абсолютна похибка:            " << abs_error << '\n';
    cout << "Відносна похибка:             " << rel_error << '\n';

    return 0;
}