#ifndef ARRAYVIEWER_H
#define ARRAYVIEWER_H

#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QRect>
#include <QLine>
#include <QPaintEvent>
#include "arraymodel.h"

#ifdef DEBUG
#include <QDebug>
#endif

class arrayviewer : public QWidget
{
    Q_OBJECT
    const arraymodel * model;

public:
    explicit arrayviewer(QWidget *parent = 0);
    void setModel(const arraymodel * newModel);

protected:
    virtual void paintEvent(QPaintEvent *event);
};

#endif // ARRAYVIEWER_H
