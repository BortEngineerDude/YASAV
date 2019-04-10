#ifndef YASAV_H
#define YASAV_H

#include <QWidget>
#include <QString>
#include "array/arraymodel.h"
#include "array/arrayviewer.h"

namespace Ui {
class yasav;
}

class yasav : public QWidget
{
    Q_OBJECT

public:
    explicit yasav(QWidget *parent = 0);
    ~yasav();

private:
    Ui::yasav *ui;
    arraymodel m;

public slots:
    void updateArraySizeLabel(int newSize);
    void updateArrayFill(int newIndex);
};

#endif // YASAV_H
