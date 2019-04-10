//This class is basicly vector wrapper with some additional controls

#ifndef ARRAYMODEL_H
#define ARRAYMODEL_H

#define MAX_MDL_SIZE 1024
#include <QVector>
#include <QObject>
#include <algorithm>
#include <random>

enum class FILL_TYPE{UNIQUE,CUBIC};

class arraymodel: public QObject
{
    Q_OBJECT

    QVector<int> vect;
    FILL_TYPE fill;

public:
    //arraymodel();
    arraymodel(FILL_TYPE fill = FILL_TYPE::UNIQUE, int size = 100);

    void swap(int idxA, int idxB);
    void refill();

    FILL_TYPE fillType() const;
    int size() const;
    int max() const;
    int min() const;

    int getElement(int element) const;

    ~arraymodel() = default;

public slots:
    void shuffle();
    void setFillType(FILL_TYPE newFillType);
    void setSize(int newSize);

signals:
    void changed();
};

#endif // ARRAYMODEL_H
