#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>

using namespace std;

/* QUESTION 4 */

double mat(vector<pair<int, double>>& data, double h, int a, int b) {
	double area = data.at(a).second + data.at(b).second;

	for (int i = 1; i < data.size() / h; i++) {
		area += 2.0 * data.at(i * h).second;
	}
	area *= h;

	return area;
}

double rombergIntegration(vector<pair<int, double>>& data) {
	int n = 7;
	double h = 8.0;
	int a = 0, b = data.size() - 1;
	double** I = new double* [n];
	double area = 0.0, acc = 1.0;


	I[0] = new double[1];
	I[0][0] = mat(data, 1, a, b);

	for (int i = 1; i < n; i++) {
		I[i] = new double[i + 1];
		// estimate using trapezoidal rule
		for (int j = 1; j <= i; j++) {
			if (j == 1) {
				I[i][j] = mat(data, h, a, b);
				// h = step size which is halved each iteration
				// this is what improves accuracy
				h /= 2.0;
			}
			// extrapolate using romberg intergration
			else {
				I[i][j] = I[i][j - 1] + (I[i][j - 1] - I[i - 1][j - 1]) / (pow(4, j - 1) - 1);

				// letting it run until current value equals previous value
				// this results in real answer (as calculated by hand)
				/*if (I[i][j] == I[i][j - 1]) {
					cout << i << endl;
					area = I[i][j];
					for (int k = 1; k < i; k++) {
						for (int l = 1; l <= k; l++) {
							cout << fixed << " | " << I[k][l] << "\t";
						}
						cout << " |" << endl;
					}
					return area;
				}*/

				// if target accuracy of 1.0 has been reached return the estimated area
				if ((fabs(I[i][j] - I[i][j - 1]) / I[i][j]) * 100 < acc) {
					area = I[i][j];
					// prints table
					for (int k = 1; k <= i ; k++) {
						for (int l = 1; l <= k; l++) {
							cout << fixed << " | " << I[k][l] << "\t";
						}
						cout << " |" << endl;
					}
					return area;
				}
			}
			area = I[i][j];
		}
	}
	return area;
}

void setData(vector<pair<int, double>>& data, vector<int>& x, vector<double>& H) {
	for (int i = 0; i < x.size(); i++) {
		data.push_back(make_pair(x[i], H[i]));
	}
}

int main() {
	vector<int> x = { 0, 2, 4, 6, 8, 10, 12, 14, 16 };
	vector<double> H = { 0.0, 1.9, 2.0, 2.0, 2.4, 2.6, 2.25, 1.12, 0.0 };
	vector<pair<int, double>> data;

	setData(data, x, H);

	cout << "\nIntegral: " << rombergIntegration(data) << endl;
}