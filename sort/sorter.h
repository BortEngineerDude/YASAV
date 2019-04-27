#ifndef SORTER_H
#define SORTER_H
#include "array/arraymodel.h"

enum class SORT_TYPE{BUBBLE,SELECTION};

class sorter : public QObject
{
    Q_OBJECT

protected:
    arraymodel * model;

public:
    sorter() = default;
    sorter(arraymodel * model);
    void setModel(arraymodel * newModel);
    virtual SORT_TYPE sortType() const = 0;
    virtual ~sorter() = default;

public slots:
    virtual void advance() = 0;
    virtual void resetState() = 0;

signals:
    void stepDone();
    void iterationDone();
    void finished();
};

#endif // SORT_BASE_H
