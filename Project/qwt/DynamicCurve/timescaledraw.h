#ifndef TIMESCALEDRAW_H
#define TIMESCALEDRAW_H

#include <qwt_scale_draw.h>
#include <QDateTime>
#include <QTime>

class TimeScaleDraw : public QwtScaleDraw
{
public:
    TimeScaleDraw();
    ~TimeScaleDraw();

    virtual QwtText label(double v) const;
};

#endif // TIMESCALEDRAW_H
