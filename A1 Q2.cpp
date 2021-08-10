#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>

using namespace std;

/* QUESTION 2 */

struct Data {
    double time, bearing, dist;
};

void calcCoords(vector<Data> data, vector<pair<double, double>>& coords) {
    double x, y;
    pair<double, double> coord;

    for (int i = 0; i < data.size(); i++) {
        x = data[i].dist * cos(data[i].bearing);
        y = data[i].dist * sin(data[i].bearing);
        coord = make_pair(x, y);
        coords.push_back(coord);
    }
}

pair<double, double> firstOrderDeriv(pair<double, double> iMinus, pair<double, double> iPlus, double h) {
    double dx = fabs((iPlus.first -  iMinus.first) / (2 * h));
    double dy = fabs((iPlus.second - iMinus.second) / (2 * h));
    pair<double, double> xyPrime = make_pair(dx, dy);

    return xyPrime;
}

pair<double, double> secondOrderDeriv(pair<double, double> iMinus, pair<double, double> i, pair<double, double> iPlus, double h) {
    double dx = (iPlus.first - 2 * i.first + iMinus.first) / (h * h);
    double dy = (iPlus.second - 2 * i.second + iMinus.second) / (h * h);
    pair<double, double> xyPrime = make_pair(dx, dy);

    return xyPrime;
}

void calcVelocity(vector<Data>& data, vector<pair<double, double>>& coords, vector<pair<double, double>>& velocities) {
    pair<double, double> velocity;
    pair<double, double> iCoords;
    pair<double, double> iCoordsPlus;
    pair<double, double> iCoordsMinus;
    double h;

    for (int i = 1; i < data.size() - 1; i++) {
        iCoords = coords[i];
        iCoordsPlus = coords[i + 1];
        iCoordsMinus = coords[i - 1];
        h = data[i].time - data[i + 1].time;
        velocity = firstOrderDeriv(iCoordsMinus, iCoordsPlus, h);
        velocities.push_back(velocity);
    }
}

void calcAcceleration(vector<Data>& data, vector<pair<double, double>>& coords, vector<pair<double, double>>& accelerations) {
    pair<double, double> acceleration;
    pair<double, double> iCoords;
    pair<double, double> iCoordsPlus;
    pair<double, double> iCoordsMinus;
    double h;


    for (int i = 1; i < data.size() - 1; i++) {
        iCoords = coords[i];
        iCoordsPlus = coords[i + 1];
        iCoordsMinus = coords[i - 1];
        h = data[i].time - data[i + 1].time;
        acceleration = secondOrderDeriv(iCoordsMinus, iCoords, iCoordsPlus, h);
        accelerations.push_back(acceleration);
    }
}

void setData(vector<Data>& data, vector<double>& time, vector<double>& bearing, vector<double>& dist) {
    Data d;

    for (int i = 0; i < time.size(); i++) {
        d = { time[i], bearing[i], dist[i] };
        data.push_back(d);
    }
}


int main() {
    vector<double> time = { 200, 202, 204, 206, 208, 210 };
    vector<double> bearing = { 0.75, 0.72, 0.70, 0.68, 0.67, 0.66 };
    vector<double> dist = { 5120, 5370, 5560, 5800, 6030, 6240 };
    vector<Data> data;
    vector<pair<double, double>> coords;
    vector<pair<double, double>> velocities;
    vector<pair<double, double>> accelerations;

    setData(data, time, bearing, dist);

    calcCoords(data, coords);

    calcVelocity(data, coords, velocities);

    calcAcceleration(data, coords, accelerations);

    cout << "time: " << data[0].time;
    cout << "\tx: " << coords[0].first << "\ty: " << coords[0].second << endl;

    for (int i = 0; i < accelerations.size(); i++) {
        cout << "time: " << data[i + 1].time;
        cout << "\tx: " << coords[i + 1].first << "\ty: " << coords[i + 1].second;
        cout << setprecision(8) << "\tvx: " << velocities[i].first << "\tvy: " << velocities[i].second;
        cout << setprecision(8) << "\tax: " << accelerations[i].first << "\tay: " << accelerations[i].second << endl;
    }

    cout << "time: " << data[data.size() - 1].time;
    cout << "\tx: " << coords[coords.size() - 1].first << "\ty: " << coords[coords.size() - 1].second << endl;
}