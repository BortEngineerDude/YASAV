#ifndef ARRAYVIEWER_H
#define ARRAYVIEWER_H

#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QRect>
#include <QLine>
#include <QPaintEvent>
#include <QColor>
#include <QFont>
#include <QTextStream>
#include "arraymodel.h"

#define COLOR_A       0x3f, 0x51, 0xb5
#define COLOR_B       0xfb, 0x8c, 0
#define COLOR_DONE    0x4c, 0x8c, 0x4a
#define COLOR_UNKNOWN 0xc0, 0xc0, 0xc0
#define COLOR_BACKGR  0x26, 0x32, 0x38

#ifdef DEBUG
#include <QDebug>
#endif

class arrayviewer : public QWidget
{
    Q_OBJECT
    const arraymodel * model;
    QColor colorA;
    QColor colorB;
    QColor colorDone;
    QColor colorUnknown;
    QColor colorBackground;

public:
    explicit arrayviewer(QWidget *parent = 0);
    void setModel(const arraymodel * newModel);

protected:
    virtual void paintEvent(QPaintEvent *event);
};

#endif // ARRAYVIEWER_H
