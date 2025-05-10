#ifndef SORTALGHORITM_H
#define SORTALGHORITM_H

#include "chartwidget.h"
class sortAlghoritm
{
public:
    virtual void step() = 0;
    bool isFinished();

    sortAlghoritm(chartWidget& chart);

protected:
    bool finished = false;
    chartWidget& chart;
};

#endif
