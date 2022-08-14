//
// Created by MooZV on 2021/4/23.
//

#ifndef ALGORITHM_TICTOC_H
#define ALGORITHM_TICTOC_H
#include <ctime>
#include <iostream>

class TicToc {
public:
    static double sum, min;

    TicToc() = default;

    ~TicToc() = default;

    void tic() {
        start = clock();
    }

    void toc() {
        end = clock();
        double during = double(end - start) / CLOCKS_PER_SEC;
        if (during < min )
            min = during;
        sum += during;
    }

private:
    clock_t start, end;
};
double TicToc::sum = 0;
double TicToc::min = INT8_MAX;

#endif //ALGORITHM_TICTOC_H
