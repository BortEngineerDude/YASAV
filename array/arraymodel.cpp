#include "arraymodel.h"

arraymodel::arraymodel(FILL_TYPE fillType, int size)
{
    fill = fillType;
    if(size > MAX_MDL_SIZE)
    {
        size = MAX_MDL_SIZE;
    }
    vect = QVector<int>(size,0);

    refill();
}
void arraymodel::swap(int idxA, int idxB)
{
    int tmp = vect.at(idxA);
    vect[idxA] = vect.at(idxB);
    vect[idxB] = tmp;
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
}
void arraymodel::setFillType(FILL_TYPE newFillType)
{
    if(newFillType != fill)
    {
        fill = newFillType;
        refill();
        emit changed();
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
        emit changed();
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
int arraymodel::getElement(int element) const
{
    return vect.at(element);
}
