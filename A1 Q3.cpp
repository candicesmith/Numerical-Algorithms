#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>

using namespace std;
constexpr auto N = 5;

/* QUESTION 3 */

double f(double x) {
    return (-0.1 * x * x * x * x) - (0.15 * x * x * x) - (0.5 * x * x) - (0.25 * x) + 1.2;
}

double trueValue(double x) {
    return (-0.4 * x * x * x) - (0.45 * x * x) - x - 0.25;
}

double centralDifference(double x, double h) {
    return (f(x + h) - f(x - h)) / (2 * h);
}

void richardsonExtrapolation(double x, double h, double trueVal) {
    double RE[N][N];
    double error, h2 = h;

    for (int i = 0; i < N; i++) {
        RE[i][0] = (f(x + h) - f(x - h)) / (2 * h);
        for (int j = 1; j <= i; j++) {
            RE[i][j] = RE[i][j - 1] + (RE[i][j - 1] - RE[i - 1][j - 1]) / (pow(4, j) - 1);
        }
        h /= 2.0;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            h2 /= 2.0;
            error = fabs((trueVal - RE[i][j]) * 100 / trueVal);
            cout << fixed << "h: " << h2 << "\tRE: " << RE[i][j] << "\tError: " << error << "%" << endl;
        }
    }
    cout << endl;
}

int main() {
    double x = 0.5;
    double h = 0.5;
    double centralDiff, richExtrap, trueVal, cdaError, reError;

    trueVal = trueValue(x);
    cout << "Real value: " << trueVal << endl << endl;

    while (h > 0.01) {
        centralDiff = centralDifference(x, h);
        cdaError = fabs((trueVal - centralDiff) * 100 / trueVal);
        cout << fixed << "h: " << h << "\tCDA: " << centralDiff << "\tError: " << cdaError << "%" << endl;
        h -= 0.01;
    }
    cout << endl;

    richardsonExtrapolation(x, h, trueVal);
}