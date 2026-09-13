#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <windows.h>

using namespace std;

double calculateDet(const vector<vector<double>>& A){
    int n = A.size();
    if (n == 0) return 0.0;

    double det = 1.0;

    // копіюєм матрицю для подальших розрахунків і змін
    vector<vector<double>> V = A;

    for (int k = 0; k < n; ++k) {
        //шукаєм найбільший елемент в матриці як головний по всій підматриці
        // k початковий елемент (0;0)
        double max_value = abs(V[k][k]);
        int h = k;
        int w = k;
        //рухаємось по л рядку по горизонталі
        for (int l = k; l < n; ++l) {
            //рухаємось по к рядку по вертикалі
            for (int f = k; f < n; ++f) {
                if (max_value < abs(V[l][f])) {
                max_value = abs(V[l][f]);
                h = l;
                w = f;
                }
            }
        }
        // переконуємось чи наша матриця не вироджена, детермінант не дорівнює нулю
        if (max_value < 1e-12) { // < 0.000000000001
            return 0.0;
        }
        // якшо максимальне число не знаходиться в верхній горизонталі
        if (h != k){
            for (int d = 0; d < n; ++d){
                double value = V[k][d];
                V[k][d] = V[h][d];
                V[h][d] = value;
            }
        }    
        // якшо максимальне число не знаходиться в лівій вертикалі
        if (w != k){
            for (int d = 0; d < n; ++d){
                double value = V[d][k];
                V[d][k] = V[d][w];
                V[d][w] = value;
            }
        }
        //зміна знаку головного елементу після перестановок
        if ((w + h) % 2 != 0) {
            det = -det;
        }

        det = det * V[k][k];

        // виключення елементів (прямий  хід)
        for (int i = k + 1; i < n; ++i){
            double C_n = V[i][k]/V[k][k]; //знаходимо множник
            for (int j = k + 1; j < n; ++j){
                V[i][j] = V[i][j] - V[k][j] * C_n;
            }
        }
    }
    return det;


}

int main(){
    SetConsoleOutputCP(CP_UTF8);

    //double k = 8;
    //double s = 0.02 * k;

    vector<vector<double>> matrix = {
        {2.0, 4.0, 1.0},
        {-1.0, 1.0, 2.0},
        {3.0, -2.0, -1.0}
    };

    cout << fixed << setprecision(4);
    cout << "Визначник матриці: " << calculateDet(matrix) << endl;

    return 0;

}
