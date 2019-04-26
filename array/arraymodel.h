//This class is basicly vector wrapper with some additional controls

#ifndef ARRAYMODEL_H
#define ARRAYMODEL_H

#define MAX_MDL_SIZE 1024
#include <QVector>
#include <QObject>
#include <QString>
#include <algorithm>
#include <math.h>
#include <random>

enum class FILL_TYPE{LINEAR,CUBIC};

class arraymodel: public QObject
{
    friend class arrayviewer;

    Q_OBJECT

    QVector<int> m_vect;
    FILL_TYPE m_fill;

    int m_idxA;
    int m_idxB;
    int m_top;

public:
    //arraymodel();
    arraymodel(int size = 50, FILL_TYPE fill = FILL_TYPE::LINEAR);

    void swap();
    void setA(int A);
    void setB(int B);
    void setTop(int top);
    void refill();

    FILL_TYPE fillType() const;
    int size() const;
    int max() const;
    int min() const;
    int top() const;
    int A() const;
    int B() const;

    int elementA() const;
    int elementB() const;
    //int element(int idx) const;

    ~arraymodel() = default;

public slots:
    void shuffle();
    void setFillType(FILL_TYPE newFillType);
    void setSize(int newSize);

signals:
    void changed();
    void failed(QString failure);
};

#endif // ARRAYMODEL_H
