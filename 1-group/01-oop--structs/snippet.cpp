#include <iostream>
const int PERIOD = 60;

struct ComplexNumber {
    double a = 0;
    double b = 0;
};

struct Size1 { // What is the size here?
    bool a;
    double b;
    int c;
};


struct Size2 { // What is the size here?
    bool a;
    int c;
    double b;
};

void printComplexNumber(const ComplexNumber& num) {
    std::cout << num.a << " + " << num.b << " * i" << std::endl;
}

struct Distance {
    int foot = 0;
    int inc = 0;
};

void print(const Distance& p) {
    std::cout << p.foot << "`" << p.inc << "``" << std::endl;
}

Distance sumD(const Distance& first, const Distance& second) {
    // Can we move somewhere else this magic number 12?
    Distance res{first.foot+second.foot, first.inc+second.inc};
    res.foot += res.inc / 12;
    res.inc %= 12;
    return res;
}

struct TimePeriod {
    int hour = 0;
    int min = 0;
    int sec = 0;
};

TimePeriod distance (const TimePeriod& from,const TimePeriod& to) {
    // Sometimes it`s much easier to translate the object to another type...
    // If it`s possible,this is part of this course
    int first = from.hour * PERIOD * PERIOD + from.min * PERIOD + from.sec;
    int sec = to.hour * PERIOD * PERIOD + to.min * PERIOD + to.sec;
    int res = std::abs(first-sec);
    TimePeriod result;
    result.sec = res % PERIOD; res /= PERIOD;
    result.min = res % PERIOD; res /= PERIOD;
    result.hour = res;
    return result;
}

void print(const TimePeriod& time) {
    std::cout << time.hour << ":" << time.min << ":" <<time.sec << std::endl;
}

int main() {
    ComplexNumber a{2,5};
    printComplexNumber(a);

    TimePeriod first{12,25,45};
    TimePeriod second{21,48,31};
    TimePeriod distanceResult = distance(first, second);
    print(distanceResult);

    Distance f{1,9};
    Distance s{1,8};
    Distance r = sumD(f,s);
    print(r);
}
