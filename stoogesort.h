#ifndef STOOGESORT_H
#define STOOGESORT_H

#include "sortalghoritm.h"
#include <vector>
#include <QList>

class stoogeSort : public sortAlghoritm {
    struct Task {
        qsizetype l;
        qsizetype r;
        qsizetype k;
        int phase; // 0 = compare&swap, 1 = first 2/3, 2 = last 2/3, 3 = final 2/3
    };

    QList<int>& numbers;
    std::vector<Task> stack;

public:
    stoogeSort(QList<int>& numbers, chartWidget& chart);
    void step() override;
};

#endif // STOOGESORT_H
