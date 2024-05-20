#include<algorithm>
#include "calc.h"
using namespace std;

string inTwo(unsigned long long int n) {
    string number;
    while (n / 2 != 0) {
        number = (char((n % 2) + '0')) + number;
        n = n / 2;
    }
    number = (char((n % 2) + '0')) + number;
    reverse(number.begin(), number.end());
    return number;
}

string inEight(unsigned long long int n) {
    string number;
    while (n / 8 != 0) {
        number = (char((n % 8) + '0')) + number;
        n = n / 8;
    }
    number = (char((n % 8) + '0')) + number;
    return number;
}

string inSixteen(unsigned long long int n) {
    string number;
    while (n / 16 != 0) {
        if ((n % 16) > 9) {
            number = (char((n % 16) + '7')) + number;
        } else {
            number = (char((n % 16) + '0')) + number;
        }
        n = n / 16;
    }
    if ((n % 16) > 9) {
        number = (char((n % 16) + '7')) + number;
    } else {
        number = (char((n % 16) + '0')) + number;
    }
    return number;
}