#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "chartwidget.h"
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QRandomGenerator>
#include <QString>
#include "stoogesort.h"
#include "radixsort.h"
#include "sortalghoritm.h"
#include "mergesort.h"
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *dataBar = new QHBoxLayout();

    QLabel* countNumbersLabel = new QLabel("Элементов");
    QSpinBox* countNumbersSpin = new QSpinBox(this);
    QLabel* minValueLabel = new QLabel("Мин");
    QSpinBox* minValueSpin = new QSpinBox(this);
    QLabel* maxValuesLabel = new QLabel("Макс");
    QSpinBox* maxValueSpin = new QSpinBox(this);

    countNumbersSpin->setRange(0, 1000);
    countNumbersSpin->setValue(countNumbers);

    minValueSpin->setRange(0, 1000);
    minValueSpin->setValue(0);

    maxValueSpin->setRange(0, 1000);
    maxValueSpin->setValue(100);

    QPushButton *genData = new QPushButton("Генерировать данные");

    dataBar->addWidget(countNumbersLabel);
    dataBar->addWidget(countNumbersSpin);
    dataBar->addWidget(minValueLabel);
    dataBar->addWidget(minValueSpin);
    dataBar->addWidget(maxValuesLabel);
    dataBar->addWidget(maxValueSpin);
    dataBar->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    dataBar->addWidget(genData);

    chart = new chartWidget(numbers,minValue,maxValue);

    speedLabel->setText(QString("Обновление каждые %1 мс").arg(timerDelay));
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 200);
    slider->setValue(0);

    QHBoxLayout *buttonBar = new QHBoxLayout();
    buttonBar->addWidget(mergeButton);
    buttonBar->addWidget(stoogeButton);
    buttonBar->addWidget(radixButton);


    mainLayout->addLayout(dataBar);
    mainLayout->addWidget(chart);
    mainLayout->addWidget(speedLabel);
    mainLayout->addWidget(slider);
    mainLayout->addLayout(buttonBar);

    this->setCentralWidget(centralWidget);

    connect(genData,&QPushButton::clicked,this,&MainWindow::GenerateNumbers);
    connect(slider,&QSlider::sliderMoved,this,&MainWindow::setTimerDelay);
    connect(mergeButton, &QPushButton::clicked, this, &MainWindow::mergeClick);
    connect(stoogeButton, &QPushButton::clicked, this, &MainWindow::stoogeClick);
    connect(radixButton, &QPushButton::clicked, this, &MainWindow::radixClick);
    connect(&timer,&QTimer::timeout,this,&MainWindow::timerTick);
}

void MainWindow::GenerateNumbers() {
    QRandomGenerator *generator = QRandomGenerator::global();
    numbers.clear();
    for (int i = 0; i < countNumbers; ++i) {
        numbers.append(generator->bounded(minValue,maxValue+1));
    }
    chart->update();
}

void MainWindow::timerTick(){
    if(!sortAlgh->isFinished()){
        timer.stop();
        timer.start(timerDelay);
        sortAlgh->step();
        chart->update();
        // qDebug() << "таймер" << timerDelay;
    }
    else{
        // qDebug() << "таймер стоп";
        this->FinishTimer();
    }

}

void MainWindow::FinishTimer(){
    timer.stop();
    mergeButton->setEnabled(true);
    stoogeButton->setEnabled(true);
    radixButton->setEnabled(true);
}

void MainWindow::startSort(sortAlghoritm *alg) {
    sortAlgh = alg;
    timer.start(timerDelay);
    mergeButton->setEnabled(false);
    stoogeButton->setEnabled(false);
    radixButton->setEnabled(false);
}

void MainWindow::mergeClick() {
    startSort(new mergeSort(numbers, *chart));
}
void MainWindow::stoogeClick(){
    startSort(new stoogeSort(numbers, *chart));
}
void MainWindow::radixClick() {
    startSort(new radixSort(numbers, *chart));
}

void MainWindow::setTimerDelay(int value){
    timerDelay = 200 - value;
    speedLabel->setText(QString("Обновление каждые %1 мс").arg(timerDelay));
}


MainWindow::~MainWindow() {
    delete chart;
}
