// radixsort.h
#ifndef RADIXSORT_H
#define RADIXSORT_H

#include "sortalghoritm.h"
#include <QVector>

class radixSort : public sortAlghoritm
{
    QList<int>& numbers;
    // Вспомогательный буфер не нужен, т.к. мы собираем сразу в numbers при сборке
    int maxDigits;            // число проходов (максимальная длина числа)
    int currentDigit;         // текущий номер разряда (0 – младший)
    int index;                // индекс текущего элемента при распределении или сборке
    bool distribution;        // фаза: true – распределяем по buckets, false – собираем обратно
    QVector<QList<int>> buckets; // 10 корзин для цифр 0–9
    int collectBucket;        // номер корзины при сборке
    int collectIndex;         // индекс внутри текущей корзины при сборке

public:
    radixSort(QList<int>& numbers, chartWidget& chart);
    void step() override;
};

#endif // RADIXSORT_H
