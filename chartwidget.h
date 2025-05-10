#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QList>
#include <QWidget>
#include <QPainter>

class chartWidget : public QWidget
{
    Q_OBJECT
    QList<int>& numbers;

    struct Highlight{
        int i;
        QColor color;
    };
    QList<Highlight> highlights;
    int minValue;
    int maxValue;

public:
    void highlightRect(int i, QColor color);
    void reset();
    chartWidget(QList<int>& numbers, int minValue,int maxValue);


protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // CHARTWIDGET_H
