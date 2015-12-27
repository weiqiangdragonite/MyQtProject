#include "timescaledraw.h"

TimeScaleDraw::TimeScaleDraw()
{

}

TimeScaleDraw::~TimeScaleDraw()
{

}

QwtText TimeScaleDraw::label(double v) const
{
    //QDateTime datetime;
    QString time;
    time = QTime::currentTime().toString("h:m:s");
    return QwtText(time);
}

