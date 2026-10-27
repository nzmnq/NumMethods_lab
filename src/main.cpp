#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

const int n = 2; // розмір

// обчислюєм рівнняня ф-ції
vector<double> calcF(const vector<double>& x) {
    return {
        x[0] * x[0] - x[1] * x[1] + 0.1 - x[0],
        2.0 * x[0] * x[1] + 0.1 - x[1]
    };
}

// матриця якобі
vector<vector<double>> calcJ(const vector<double>& x) {
    return {
        { 2.0 * x[0] - 1.0, -2.0 * x[1] },
        { 2.0 * x[1], 2.0 * x[0] - 1.0 }
    };
}

// обернення матриці методом гауса з головним елементом по всій матриці
vector<vector<double>> gauss(vector<vector<double>> V) {
    // одинична матриця
    vector<vector<double>> E(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) E[i][i] = 1.0;

    // масив для відстеження перестановок стовпців
    vector<int> col_index(n);
    for (int i = 0; i < n; ++i) col_index[i] = i;

    // прямий хід
    for (int k = 0; k < n; ++k) {
        // шукаєм найбільший елемент в матриці як головний по всій підматриці
        double max_value = abs(V[k][k]);
        int h = k;
        int w = k;

        // рухаємось по л рядку по горизонталі
        for (int l = k; l < n; ++l) {
            // рухаємось по ф рядку по вертикалі
            for (int f = k; f < n; ++f) {
                if (max_value < abs(V[l][f])) {
                    max_value = abs(V[l][f]);
                    h = l;
                    w = f;
                }
            }
        }

        // переконуємось чи наша матриця не вироджена
        if (max_value < 1e-12) return {};

        // якшо максимальне число не знаходиться в верхній горизонталі
        if (h != k) {
            for (int d = 0; d < n; ++d) {
                swap(V[k][d], V[h][d]);
                swap(E[k][d], E[h][d]);
            }
        }

        // якшо максимальне число не знаходиться в лівій вертикалі
        if (w != k) {
            for (int d = 0; d < n; ++d) {
                swap(V[d][k], V[d][w]);
            }
            swap(col_index[k], col_index[w]);
        }

        // виключення елементів (прямий хід)
        for (int i = k + 1; i < n; ++i) {
            double C_n = V[i][k] / V[k][k]; // знаходимо множник
            for (int j = k + 1; j < n; ++j) {
                V[i][j] -= V[k][j] * C_n;
            }
            for (int j = 0; j < n; ++j) {
                E[i][j] -= E[k][j] * C_n;
            }
        }
    }

    // зворотний хід
    vector<vector<double>> inv(n, vector<double>(n));
    for (int c = 0; c < n; ++c) {
        vector<double> X_temp(n);
        for (int i = n - 1; i >= 0; --i) {
            double sum = 0.0;
            for (int j = i + 1; j < n; ++j) {
                sum += V[i][j] * X_temp[j];
            }
            X_temp[i] = (E[i][c] - sum) / V[i][i];
        }
        // відновлення початкового порядку
        for (int i = 0; i < n; ++i) {
            inv[col_index[i]][c] = X_temp[i];
        }
    }

    return inv;
}

int main() {
    vector<double> x = { 0.1, 0.1 };
    vector<double> x_OLD = { 0.1, 0.1 };
    double eps = 1e-5; // відносна похибка у відсотках

    // обчислюєм якобі і обертаєм методом гауса один раз (спрощений ньютон)
    vector<vector<double>> J = calcJ(x);
    vector<vector<double>> INVERS = gauss(J);

    cout << "Обернена матриця Якобі:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << INVERS[i][j] << " ";
        }
        cout << "\n";
    }

    // ітераційний процес спрощеного методу ньютона
    int iteration = 0;
    bool converged = false;

    do {
        iteration++;

        // обчислення ф-ції ф
        vector<double> f = calcF(x_OLD);

        // очислення наближення х
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                sum += INVERS[i][j] * f[j];
            }
            x[i] = x_OLD[i] - sum;
        }

        // перевірка умови збіжності
        converged = true;
        for (int i = 0; i < n; i++) {
            double rel_error = fabs((x[i] - x_OLD[i]) / x[i]) * 100.0;
            if (rel_error >= eps) {
                converged = false;
            }
            x_OLD[i] = x[i];
        }

    } while (!converged && iteration < 10000);

    cout << fixed << setprecision(10);
    cout << "\nКількість ітерацій: " << iteration << "\n";
    cout << "Знайдений вектор X:\n";
    for (int i = 0; i < n; i++) {
        cout << "x[" << i + 1 << "] = " << x[i] << "\n";
    }

    vector<double> check = calcF(x);
    cout << scientific << setprecision(6);
    cout << "\nПеревірка (значення функцій F(X)):\n";
    for (int i = 0; i < n; i++) {
        cout << "f[" << i + 1 << "] = " << check[i] << "\n";
    }

    return 0;
}