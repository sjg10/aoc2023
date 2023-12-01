#include <iostream>
#include <string>
#include <numeric>
#include "Day01.h"


std::vector<std::string> Day01::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto ret = getCalibrationSum(input);
    out.push_back(std::to_string(ret.first));
    out.push_back(std::to_string(ret.second));
    return out;
}

const std::vector<std::string> numbers = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};

std::pair<unsigned int, unsigned int> Day01::getCalibrationSum(std::istream &input) {
    unsigned int sum1 = 0;
    unsigned int sum2 = 0;
    for(std::string x; std::getline(input, x);) {
        int a = -1;
        int aloc = -1;
        int a2 = -1;
        int aloc2 = -1;
        int b = -1;
        int bloc = -1;
        int b2 = -1;
        int bloc2 = -1;
        // find digit locations
        for (unsigned int i = 0; i < x.size(); i++) {
            char c = x[i];
            if ( c >= '0' && c <= '9') {
                if (a== -1) {
                    a = (c - '0');
                    aloc = i;
                }
                else {
                    b = (c - '0');
                    bloc = i;
                }
            }
        }
        // find text number locations
        for(int j = 0; j < 10; j++) {
            size_t first = x.find(numbers[j]);
            size_t last = x.rfind(numbers[j]);
            if(first != std::string::npos) {
                if (aloc2 == -1 || (int)first < aloc2) {
                    aloc2 = first;
                    a2 = j;
                }
                if (bloc2 == -1 || (int)last > bloc2) {
                    bloc2 = last;
                    b2 = j;
                }
            }
        }
        // tot up sums
        unsigned int e1 = 0;
        unsigned int e2 = 0;
        // skip sum1 if missing digits
        if (!(b == -1 && a == -1 )){
            if (b == -1) {
                b = a;
                bloc = aloc;
            }
            e1 += (a*10);
            e1 += (b);
        }
        if (b2 == -1) {
            b2 = a2;
            bloc2 = aloc2;
        }
        if (aloc2 == -1 || (aloc != -1 && aloc < aloc2)) {
            e2 += (a*10);
        }
        else {
            e2 += (a2*10);
        }
        if (bloc2 == -1 || bloc > bloc2) {
            e2 += (b);
        }
        else {
            e2 += (b2);
        }
        sum1 += e1;
        sum2 += e2;
    }
    return {sum1, sum2};
}
