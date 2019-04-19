#include "arraymodel.h"

arraymodel::arraymodel(int size, FILL_TYPE fillType)
{
    idxA = -1;
    idxB = -1;

    fill = fillType;
    if(size > MAX_MDL_SIZE)
    {
        size = MAX_MDL_SIZE;
    }
    vect = QVector<int>(size,0);

    refill();
}
void arraymodel::swap()
{
    try
    {
        int tmp = vect.at(idxA);
        vect[idxA] = vect.at(idxB);
        vect[idxB] = tmp;
    }
    catch(...)
    {
        return;
    }
    emit changed();
}
void arraymodel::setA(int A)
{
    if(A >= -1 && A <= vect.size())
    {
        idxA = A;
    }
}
void arraymodel::setB(int B)
{
    if(B >= -1 && B <= vect.size())
    {
        idxB = B;
    }
}
void arraymodel::shuffle()
{
    std::mt19937 g;
    std::shuffle(vect.begin(), vect.end(), g);
    emit changed();
}
void arraymodel::refill()
{
    int size = vect.size();
    switch(fill)
    {
        case FILL_TYPE::UNIQUE:
            for(int i = 0; i < size; ++i)
            {
                vect[i] = i+1;
            }
        break;
        case FILL_TYPE::CUBIC:
            int zeroOffset = size / 2;
            int min = 0;
            for(int i = 0; i < size; ++i)
            {
                int val = i - zeroOffset;
                vect[i] = val*val*val;
                if(!i)
                {
                    min = vect[0];
                }
                vect[i] -= min;
            }
        break;
    }
    emit changed();
}
void arraymodel::setFillType(FILL_TYPE newFillType)
{
    if(newFillType != fill)
    {
        fill = newFillType;
        refill();
    }
}
void arraymodel::setSize(int newSize)
{
    if(newSize > MAX_MDL_SIZE)
    {
        newSize = MAX_MDL_SIZE;
    }
    else if(newSize < 0)
    {
        newSize = 0;
    }

    if(vect.size() != newSize)
    {
        vect.resize(newSize);
        refill();
    }
}
FILL_TYPE arraymodel::fillType() const
{
    return fill;
}
int arraymodel::size() const
{
    return vect.size();
}
int arraymodel::max() const
{
    int max = vect.at(0);
    for( int val : vect )
    {
        if(val > max)
        {
            max = val;
        }
    }
    return max;
}
int arraymodel::min() const
{
    int min = vect.at(0);
    for( int val : vect )
    {
        if(val < min)
        {
            min = val;
        }
    }
    return min;
}
int arraymodel::A() const
{
    return idxA;
}
int arraymodel::B() const
{
    return idxB;
}
int arraymodel::elementA() const
{
    int val = 0;
    try
    {
        val = vect.at(idxA);
    }
    catch(...)
    {
        return 0;
    }
    return val;
}
int arraymodel::elementB() const
{
    int val = 0;
    try
    {
        val = vect.at(idxB);
    }
    catch(...)
    {
        return 0;
    }
    return val;
}
int arraymodel::element(int idx) const
{
    int val = 0;
    try
    {
        val = vect.at(idx);
    }
    catch(...)
    {
        return 0;
    }
    return val;
}
