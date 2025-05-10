#include "mergesort.h"
#include <algorithm>

mergeSort::mergeSort(QList<int>& numbers, chartWidget& chart)
    : sortAlghoritm(chart)
    , numbers(numbers)
    , buffer(numbers.size())
    , n(numbers.size())
    , width(1)
    , leftStart(0)
    , phase(PREPARE)
{}

void mergeSort::step(){
    if (finished) return;

    chart.reset();
    QColor compareColor = Qt::blue;
    QColor moveColor    = Qt::red;

    // Подготовка к очередному слиянию блока
    if (phase == PREPARE) {
        if (width >= n) {
            // Всё отсортировано
            finished = true;
            return;
        }
        // Вычисляем границы текущих двух блоков
        mid = std::min(leftStart + width, n);
        rightEnd = std::min(leftStart + 2*width, n);
        // Копируем в буфер
        for (int idx = leftStart; idx < rightEnd; ++idx) {
            buffer[idx] = numbers[idx];
        }
        // Инициализируем индексы слияния
        i = leftStart;
        j = mid;
        k = leftStart;
        phase = MERGING;
    }
    else {
        // Выполняем единичный шаг слияния
        if (i < mid && j < rightEnd) {
            // сравнение
            chart.highlightRect(i, compareColor);
            chart.highlightRect(j, compareColor);
            // выбираем меньший элемент
            if (buffer[i] <= buffer[j]) {
                chart.highlightRect(k, moveColor);
                numbers[k++] = buffer[i++];
            } else {
                chart.highlightRect(k, moveColor);
                numbers[k++] = buffer[j++];
            }
        }
        else if (i < mid) {
            // оставшиеся из левого блока
            chart.highlightRect(i, compareColor);
            chart.highlightRect(k, moveColor);
            numbers[k++] = buffer[i++];
        }
        else if (j < rightEnd) {
            // оставшиеся из правого блока
            chart.highlightRect(j, compareColor);
            chart.highlightRect(k, moveColor);
            numbers[k++] = buffer[j++];
        }
        else {
            // закончился один блок — переходим к следующему
            leftStart += 2*width;
            phase = PREPARE;
            // если все блоки пройдены, удваиваем размер блока
            if (leftStart >= n) {
                width *= 2;
                leftStart = 0;
            }
        }
    }
}
