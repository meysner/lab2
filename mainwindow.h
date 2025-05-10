#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "chartwidget.h"
#include "sortalghoritm.h"
#include <QTimer>
#include <QLabel>
#include "QPushButton"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    sortAlghoritm* sortAlgh = nullptr;
    int countNumbers = 100;
    int minValue = 9;
    int maxValue = 100;
    QList<int> numbers;
    chartWidget *chart;

    QLabel *speedLabel = new QLabel("Скорость: 0");
    QPushButton *mergeButton = new QPushButton("Слиянием");
    QPushButton *stoogeButton = new QPushButton("Stooge Sort");
    QPushButton *radixButton = new QPushButton("Поразрядная");


    QTimer timer;
    int timerDelay = 200;

    void setTimerDelay(int value);
    void mergeClick();
    void stoogeClick();
    void radixClick();
    void timerTick();
    void startSort(sortAlghoritm* alg);
    void FinishTimer();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void GenerateNumbers();
};
#endif // MAINWINDOW_H
