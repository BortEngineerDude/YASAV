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

#define COLOR_A       0x4f, 0x61, 0xc5
#define COLOR_B       0xfb, 0x9c, 0x10
#define COLOR_DONE    0x4c, 0x8c, 0x4a
#define COLOR_UNKNOWN 0x45, 0x5A, 0x64
#define COLOR_BACKGR  0xc0, 0xc0, 0xc0

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
