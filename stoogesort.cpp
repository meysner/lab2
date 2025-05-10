#include "stoogesort.h"
#include <algorithm>
#include <QtGlobal>
#include <QColor>

stoogeSort::stoogeSort(QList<int>& numbers, chartWidget& chart)
    : sortAlghoritm(chart), numbers(numbers)
{
    // Инициализируем стек одной задачей на весь диапазон
    stack.push_back({0, numbers.size() - 1, 0, 0});
}

void stoogeSort::step() {
    if (finished || stack.empty()) {
        finished = true;
        return;
    }

    // Готовим цвета подсветки
    chart.reset();
    QColor compareColor = Qt::blue;
    QColor moveColor    = Qt::red;

    Task &t = stack.back();
    qsizetype l = t.l, r = t.r;

    // Фаза 0: сравнить и, если нужно, обменять концовые элементы
    if (t.phase == 0) {
        chart.highlightRect(static_cast<int>(l),   compareColor);
        chart.highlightRect(static_cast<int>(r),   compareColor);
        if (numbers[static_cast<int>(l)] > numbers[static_cast<int>(r)]) {
            chart.highlightRect(static_cast<int>(r), moveColor);
            std::swap(numbers[static_cast<int>(l)], numbers[static_cast<int>(r)]);
        }
        // Переходим к рекурсивным фазам, если размер > 2
        qsizetype len = r - l + 1;
        if (len > 2) {
            t.k     = len / 3;
            t.phase = 1;
            // Сортируем первые 2/3
            stack.push_back({l, r - t.k, 0, 0});
        } else {
            // Никаких рекурсий, задача завершена
            stack.pop_back();
        }
        return;
    }

    // Фаза 1: после первой 2/3 — запускаем сортировку последних 2/3
    if (t.phase == 1) {
        t.phase = 2;
        stack.push_back({l + t.k, r, 0, 0});
        return;
    }

    // Фаза 2: после второй 2/3 — снова первые 2/3
    if (t.phase == 2) {
        t.phase = 3;
        stack.push_back({l, r - t.k, 0, 0});
        return;
    }

    // Фаза 3: всё для этого сегмента сделано
    if (t.phase == 3) {
        stack.pop_back();
        return;
    }
}
