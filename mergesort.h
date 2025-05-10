#ifndef MERGESORT_H
#define MERGESORT_H

#include "sortalghoritm.h"
#include <QList>
#include <QVector>

class mergeSort : public sortAlghoritm
{
    QList<int>& numbers;
    QVector<int> buffer;
    int n;

    // параметры текущего прохода
    int width;          // текущий размер объединяемых блоков
    int leftStart;      // начало блока
    int mid, rightEnd;  // границы блоков

    // индексы для слияния
    int i, j, k;

    enum Phase { PREPARE, MERGING } phase;

public:
    mergeSort(QList<int>& numbers, chartWidget& chart);
    void step() override;
};

#endif // MERGESORT_H
