#ifndef YASAV_H
#define YASAV_H

#include <QWidget>
#include <QString>
#include <QTimer>

#include "array/arraymodel.h"
#include "array/arrayviewer.h"

#include "sort/sorter.h"
#include "sort/selection.h"
#include "sort/bubble.h"

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
    sorter *s;
    QTimer ticker;
    void connectSorter();

private slots:
    void updateArraySizeLabel(int newSize);
    void updateArrayFill(int newIndex);
    void updateSorter(int newIndex);
    void updateTicker(int newMs);
    void toggleGoStop();
    void stop();
};

#endif // YASAV_H
