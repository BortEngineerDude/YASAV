#ifndef ARRAYMODEL_H
#define ARRAYMODEL_H

#define MAX_MDL_SIZE 300
#include <QVector>
#include <QObject>
#include <QString>
#include <algorithm>
#include <math.h>
#include <random>
#include "range.h"

enum class FILL_TYPE{ LINEAR, CUBIC, ONE_ODD, LINEAR_INVERSE };

class arraymodel: public QObject
{
    friend class arrayviewer;

    Q_OBJECT

    QVector<int> m_vect;
    int m_idxA;
    int m_idxB;
    FILL_TYPE m_fill;
    unsigned int m_swaps;
    unsigned int m_comparisons;

public:
    range<int> m_complete;
    bool m_highlight;
    //arraymodel();
    arraymodel( int size = 50, FILL_TYPE fill = FILL_TYPE::LINEAR );

    void swap();
    bool compare();
    void setA(int A);
    void setB(int B);

    void refill();

    unsigned int comparisons() const;
    unsigned int swaps() const;
    FILL_TYPE fillType() const;
    int size() const;
    int max() const;
    int min() const;
    int top() const;
    int A() const;
    int B() const;

    int element(int idx) const;

    ~arraymodel() = default;

public slots:
    void shuffle();
    void setFillType( FILL_TYPE newFillType );
    void setSize( int newSize );
    void resetStats();

signals:
    void changed();
};

#endif // ARRAYMODEL_H
