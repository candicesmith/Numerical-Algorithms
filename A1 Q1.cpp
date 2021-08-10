#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <limits>
#include <vector>
#include <fstream>
#include "half.hpp"

using namespace std;
using half_float::half;
using half_float::half_cast;

// third derivative
half df3(half x) {
    return half_cast<half>((half(1.2) * pow(x, half(2.0))) - (half(0.9) * x) - half(1.0));
}

// first derivative
half df(half x) {
    return half_cast<half>((half(-0.4) * pow(x, half(3.0))) - (half(0.45) * pow(x, half(2.0))) - x - half(0.15));
}

// function
half f(half x) {
    return half_cast<half>((half(-0.1) * pow(x, half(4.0))) - (half(0.15) * pow(x, half(3.0))) - (half(0.5) * pow(x, half(2.0))) - (half(0.15) * (x)) + half(1.2));
}

// centered difference approximation
half cda(half h, half x, half(*f)(half)) {
    half forward, backward;
    forward = f(x + h);
    backward = f(x - h);

    return half_cast<half>((forward - backward) / (2 * h));
}

// third derivative
float df3(float x) {
    return ((1.2 * pow(x, 2.0)) - (0.9 * x) - 1.0);
}

// first derivative
float df(float x) {
    return ((-0.4 * pow(x, 3.0)) - (0.45 * pow(x, 2.0)) - x - 0.15);
}

// function
float f(float x) {
    return (-0.1 * pow(x, 4.0)) - (0.15 * pow(x, 3.0)) - (0.5 * pow(x, 2.0)) - (0.15 * (x)) + 1.2;
}

// centered difference approximation
float cda(float h, float x, float(*f)(float)) {
    float forward, backward;
    forward = f(x + h);
    backward = f(x - h);

    return (forward - backward) / (2 * h);
}

// third derivative
double df3(double x) {
    return ((1.2 * pow(x, 2.0)) - (0.9 * x) - 1.0);
}

// first derivative
double df(double x) {
    return ((-0.4 * pow(x, 3.0)) - (0.45 * pow(x, 2.0)) - x - 0.15);
}

// function
double f(double x) {
    return (-0.1 * pow(x, 4.0)) - (0.15 * pow(x, 3.0)) - (0.5 * pow(x, 2.0)) - (0.15 * (x)) + 1.2;
}

// centered difference approximation
double cda(double h, double x, double(*f)(double)) {
    double forward, backward;
    forward = f(x + h);
    backward = f(x - h);

    return (forward - backward) / (2 * h);
}

int main() {
    const half eps16 = numeric_limits<half>::epsilon();
    const float eps32 = numeric_limits<float>::epsilon();
    const double eps64 = numeric_limits<double>::epsilon();
    vector<half> CDAh;
    vector<float> CDAf;
    vector<double> CDAd;
    vector<half> errh;
    vector<float> errf;
    vector<double> errd;
    vector<half> trunch;
    vector<float> truncf;
    vector<double> truncd;

    ofstream outfile16err;
    ofstream outfile32err;
    ofstream outfile64err;

    outfile16err.open("outputfile16err.txt", ios_base::app);
    outfile32err.open("outputfile32err.txt", ios_base::app);
    outfile64err.open("outputfile64err.txt", ios_base::app);

    cout << "eps16: " << eps16 << endl;
    cout << "eps32: " << eps32 << endl;
    cout << "eps64: " << eps64 << endl;

    half xh = half(0.5);
    float xf = 0.5;
    double xd = 0.5;

    half hrealVal = df(xh);
    float frealVal = df(xf);
    double drealVal = df(xd);

    cout << "hreal: " << hrealVal << endl;
    cout << "freal: " << frealVal << endl;
    cout << "dreal: " << drealVal << endl;

    half h(1.0);
    for (int i = 0; i < 2000; i++) {
        half res = cda(h, xh, &f);
        half err = fabs(((hrealVal - res) / hrealVal) * half(100.0));
        half truncErr = (df3(eps16) / half(6.0)) * h * h;
        CDAh.push_back(res);
        errh.push_back(err);
        trunch.push_back(truncErr);
        h -= 0.001;
    }
    h = half(1.0);

    for (int i = 0; i < 2000 - 1; i++) {
        if (i == 0)
            continue;
        half err = (errh[i - 1] - errh[i + 1]) / half(2.0) * h;
        half trueVal = CDAh[i] + err - trunch[i];
        outfile16err << fixed << h << " " << trueVal << " " << err << endl;
        h -= 0.001;
    }

    half hOpt = cbrt((half(3.0) * eps16) / df3(eps16));
    cout << "16-bit hOpt: " << hOpt << endl;

    float hf = 1.0;
    for (int i = 0; i < 2000; i++) {
        float res = cda(hf, xf, &f);
        float err = fabs(((frealVal - res) / frealVal) * 100.0);
        float truncErr = (df3(eps32) / 6.0) * h * h;
        CDAf.push_back(res);
        errf.push_back(err);
        truncf.push_back(truncErr);
        hf -= 0.001;
    }
    hf = 1.0;
    for (int i = 0; i < 2000 - 1; i++) {
        if (i == 0) 
            continue;
        float err = (errf[i - 1] - errf[i + 1]) / float(2.0) * hf;
        float trueVal = CDAf[i] + err - truncf[i];
        outfile32err << fixed << hf << " " << trueVal << " " << err << endl;
        hf -= 0.001;
    }
    float hOptf = cbrt((3.0 * eps32) / df3(eps32));
    cout << "32-bit hOpt: " << hOptf << endl;

    double hd = 1.0;
    for (int i = 0; i < 2000; i++) {
        double res = cda(hd, xd, &f);
        double err = fabs(((drealVal - res) / drealVal) * 100.0);
        double truncErr = (df3(eps64) / 6.0) * h * h;
        CDAd.push_back(res);
        errd.push_back(err);
        truncd.push_back(truncErr);
        hd -= 0.001;
    }

    hd = 1.0;
    for (int i = 0; i < 2000 - 1; i++) {
        if (i == 0)
            continue;
        double err = (errd[i - 1] - errd[i + 1]) / 2.0 * hd;
        double trueVal = CDAd[i] + err - truncd[i];
        outfile64err << fixed << hd << " " << trueVal << " " << err << endl;
        hd -= 0.001;
    }

    double hOptd = cbrt((3.0 * eps64) / df3(eps64));
    for (int i = 0; i < 2000 - 1; i++) {
        if (i == 0)
            continue;
        double err = (errd[i - 1] - errd[i + 1]) / 2.0 * hOptd;
        double trueVal = CDAd[i] + err - truncd[i];
    }
    cout << "64-bit hOpt: " << hOptd << endl;
}
