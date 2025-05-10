#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QList>
#include <QWidget>

class chartWidget : public QWidget
{
    Q_OBJECT

    int elCount;
    QList<int> selectedPair;
    QList<int>* values;

public:
    chartWidget();
    void update();
};

#endif // CHARTWIDGET_H
