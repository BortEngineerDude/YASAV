#ifndef BUBBLE_H
#define BUBBLE_H
#include "array/arraymodel.h"

enum bubble_step {BS_COMPARE,BS_SWAP};

class bubble : public QObject
{
    Q_OBJECT

    arraymodel * model;
    bubble_step step;
    int idx;
    int top;
    bool compareState;
    bool hasSwaps;

public:
    bubble();
    void setModel(arraymodel * newModel);

public slots:
    void advance();
    void updateModel();
    void reset();

signals:

    void finished();
};

#endif // BUBBLE_H
