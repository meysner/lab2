#include "chartwidget.h"
#include <QPainter>

void chartWidget::highlightRect(int i, QColor color){
    highlights.append({i, color});
    this->update();
}

void chartWidget::reset(){
    highlights.clear();
}

chartWidget::chartWidget(QList<int>& numbers, int minValue,int maxValue) : numbers(numbers), maxValue(maxValue) {
    this->setMinimumSize(200, 200);
    this->setMaximumSize(20000, 20000);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void chartWidget::paintEvent(QPaintEvent *event) {

    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);


    int countNumbers = numbers.count();

    if (countNumbers == 0)
        return;
    //относительное отображение
    int min = numbers[0];
    int max = numbers[0];
    for (int val : numbers) {
        if (val > max) max = val;
        if (val < min) min = val;
    }
    float range = max - min;
    if (range == 0) range = 1;

    float squareWidth = this->width()/float(countNumbers);
    max = max + 20;

    for (int i = 0; i < countNumbers; i++) {
        if (i >= numbers.size()) continue;

        float x = squareWidth * i;

        float y_end = this->height();
        float y_height = numbers[i] / float(max) * this->height();
        float y = y_end - y_height;

        bool isHighlighted = false;
        QColor highlightColor = Qt::yellow;

        for (const auto& selection : highlights) {
            if (selection.i == i) {
                isHighlighted = true;
                highlightColor = selection.color;
                break;
            }
        }

        painter.fillRect(x, y, squareWidth, y_end, highlightColor);

        QString valueText = QString::number(numbers[i]);
        float textWidth = painter.fontMetrics().horizontalAdvance(valueText);
        float textHeight = painter.fontMetrics().height();

        painter.setPen(Qt::white);
        painter.drawText(x + (squareWidth - textWidth) / 2, y - textHeight, valueText);
    }


}
