#include <iostream>
#include <utility>
#include <iomanip>

using namespace std;

/* QUESTION 6 */

double f(double x) { return exp(-x) - x; }
double df(double x) { return -exp(-x) - 1; }

void bisection(double a, double b) {
	double u = f(a);
	double v = f(b);

	cout << " _______________________________" << endl;
	cout << " i\tRoot \t\tError " << endl;
	cout << " _______________________________" << endl;

	for (int i = 0; i < 20; i++) {
		double c = (a + b) / 2;
		double fc = f(c);

		if (u * fc < 0) {
			b = c;
			v = fc;
		}
		else {
			a = c;
			u = fc;
		}
		cout << " " << i << "\t" << fixed << c << "\t" << fabs(fc) << endl;
	}
}

void newtonRaphson(double a) {
	double z, fz;
	int loop = 0;

	cout << " _______________________________" << endl;
	cout << " i\tRoot \t\tError " << endl;
	cout << " _______________________________" << endl;

	do {
		z = a - (f(a) / df(a));
		fz = f(z);
		cout << " " << loop++ << "\t" << z << "\t" << fz << endl;
		a = z;
	} while (fabs(fz) > 0.00001);
}

void secant(double xi, double xi_p) {
	int count = 0;
	double x2 = 0.0, fxi = f(xi), fxi_p = f(xi_p);
	cout << " _______________________________" << endl;
	cout << " i\tRoot \t\tError " << endl;
	cout << " _______________________________" << endl;
	while (fabs(xi_p - xi) >= 0.00001) {
		x2 = (fxi_p * xi - fxi * xi_p) / (fxi_p - fxi);
		xi = xi_p;
		fxi = fxi_p;
		xi_p = x2;
		fxi_p = f(xi_p);
		count++;
		cout << " " << count << "\t" << x2 << "\t" << fabs(fxi_p) << endl; 
	}
	
}

int main() {
	double a = 0.0, b = 1.0;
	cout << "\n Bisection method:\n";
	bisection(a, b);
	cout << "\n\n Newton-Raphson method:\n";
	newtonRaphson(a);
	cout << "\n\n Secant method: \n";
	secant(a, b);
}