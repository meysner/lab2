// radixsort.cpp
#include "radixsort.h"
#include <QtGlobal>    // для qPow()

radixSort::radixSort(QList<int>& numbers, chartWidget& chart)
    : sortAlghoritm(chart)
    , numbers(numbers)
    , currentDigit(0)
    , index(0)
    , distribution(true)
    , collectBucket(0)
    , collectIndex(0)
{
    // находим максимальное число, чтобы определить количество разрядов
    int maxVal = 0;
    for (int v : numbers) {
        if (v > maxVal) maxVal = v;
    }
    // кол-во цифр в maxVal (хотя бы 1)
    maxDigits = (maxVal > 0) ? int( std::floor(std::log10(maxVal)) + 1 ) : 1;

    buckets.resize(10);
}

void radixSort::step()
{
    if (finished) return;

    chart.reset();
    QColor compareColor = Qt::blue;
    QColor moveColor    = Qt::red;

    if (distribution) {
        // фаза распределения по корзинам
        if (index < numbers.size()) {
            chart.highlightRect(index, compareColor);

            int digit = (numbers[index] / int(qPow(10, currentDigit))) % 10;
            chart.highlightRect(index, moveColor);

            buckets[digit].append(numbers[index]);
            index++;
        }
        if (index >= numbers.size()) {
            // переход к сборке
            distribution   = false;
            collectBucket  = 0;
            collectIndex   = 0;
            index          = 0;
        }
    } else {
        // фаза сборки обратно в numbers
        // ищем следующую непустую корзину
        while (collectBucket < 10 &&
               collectIndex >= buckets[collectBucket].size())
        {
            collectBucket++;
            collectIndex = 0;
        }

        if (collectBucket < 10) {
            chart.highlightRect(index, compareColor);
            chart.highlightRect(index, moveColor);

            numbers[index] = buckets[collectBucket][collectIndex];
            collectIndex++;
            index++;
        } else {
            // завершили сборку текущего разряда
            currentDigit++;
            if (currentDigit >= maxDigits) {
                finished = true;
            } else {
                // готовимся к следующему проходу
                for (auto &b : buckets) b.clear();
                distribution = true;
                index        = 0;
            }
        }
    }
}
