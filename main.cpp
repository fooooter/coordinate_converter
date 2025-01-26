#include <iostream>
#include <cmath>
#include <csignal>
#include <stack>

using namespace std;

#define PI 3.1415

typedef struct cartesian {
    float   x;
    float   y;
};

typedef struct polar {
    float   r;
    float   angle;
};

void int_handler(int signum) {
    cout << endl << "Exitting..." << endl;
    exit(signum);
}

inline float radians_to_degrees(const float& radian) {
    return radian * (180 / PI);
}

inline float degrees_to_radians(const float& degree) {
    return (degree * PI) / 180;
}

cartesian polar_to_cartesian(const polar &_polar) {
    cartesian _cartesian;
    if (_polar.angle == 0 && _polar.r != 0) {
        _cartesian.x = _polar.r; _cartesian.y = 0;
    } else if (_polar.angle != 0 && _polar.r == 0) {
        _cartesian.x = 0; _cartesian.y = 0;
    } else if (_polar.angle != 0 && _polar.r != 0) {
        _cartesian.x = _polar.r * cosf(_polar.angle);
        _cartesian.y = _polar.r * sinf(_polar.angle);
    } else {
        _cartesian.x = 0; _cartesian.y = 0;
    }

    return _cartesian;
}
polar cartesian_to_polar(const cartesian &_cartesian) {
    polar _polar;
    if (_cartesian.x > 0 && _cartesian.y > 0) {
        _polar.angle = atanf(_cartesian.y / _cartesian.x);
        _polar.r = sqrt(pow(_cartesian.x, 2) + pow(_cartesian.y, 2));
    } else if (_cartesian.x < 0 && _cartesian.y != 0) {
        _polar.angle = atanf(_cartesian.y / _cartesian.x) + PI;
        _polar.r = sqrt(pow(_cartesian.x, 2) + pow(_cartesian.y, 2));
    } else if (_cartesian.x > 0 && _cartesian.y < 0) {
        _polar.angle = atanf(_cartesian.y / _cartesian.x) + 2 * PI;
        _polar.r = sqrt(pow(_cartesian.x, 2) + pow(_cartesian.y, 2));
    } else if (_cartesian.x == 0 && _cartesian.y > 0) {
        _polar.angle = PI / 2;
        _polar.r = _cartesian.y;
    } else if (_cartesian.x == 0 && _cartesian.y < 0) {
        _polar.angle = 3 * PI / 2;
        _polar.r = _cartesian.y;
    } else {
        _polar.angle = 0;
        _polar.r = _cartesian.x;
    }
    return _polar;
}

int main() {
    signal(SIGINT, int_handler);
    unsigned short int selection;
    cout << "\t     ---COORDINATE SYSTEM CONVERTER---" << endl;
    repeat:
        cout << "Please specify the conversion type." << endl <<
                "0 - from cartesian coordinate system to polar coordinate system" << endl <<
                "1 - from polar coordinate system to cartesian coordinate system" << endl <<
                "Your selection: ";
        cin >> selection;
        if (selection > 1) {
            cout << endl << "Invalid number." << endl << endl;
            goto repeat;
        }
        if (!selection) {
            cartesian cart;
            cout << "Enter x coordinate: ";
            cin >> cart.x;
            cout << "Enter y coordinate: ";
            cin >> cart.y;
            polar pol = cartesian_to_polar(cart);
            cout << "Polar coordinates: " << "(" << pol.r << "," << radians_to_degrees(pol.angle) << "°" << ")" << endl;
        } else {
            polar pol;
            cout << "Enter radial coordinate (r): ";
            cin >> pol.r;
            cout << "Enter angular coordinate (in degrees): ";
            cin >> pol.angle;
            pol.angle = degrees_to_radians(pol.angle);
            cartesian cart = polar_to_cartesian(pol);
            cout << "Cartesian coordinates: " << "(" << cart.x << "," << cart.y << ")" << endl;
        }
    return 0;
}
