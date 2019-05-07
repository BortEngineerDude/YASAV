#include "arraymodel.h"

arraymodel::arraymodel(int size, FILL_TYPE fillType)
{
    m_idxA = -1;
    m_idxB = -1;
    m_fill = fillType;

    if(size > MAX_MDL_SIZE)
    {
        size = MAX_MDL_SIZE;
    }

    m_vect = QVector<int>(size,0);
    m_complete = range<int>(0, size);

    refill();
}
void arraymodel::swap()
{
    int tmp = m_vect.at(m_idxA);
    m_vect[m_idxA] = m_vect.at(m_idxB);
    m_vect[m_idxB] = tmp;
    //emit changed();
}
void arraymodel::setA(int A)
{
    if(A >= -1 && A <= m_vect.size())
    {
        m_idxA = A;
    }
}
void arraymodel::setB(int B)
{
    if(B >= -1 && B <= m_vect.size())
    {
        m_idxB = B;
    }
}
void arraymodel::shuffle()
{
    std::mt19937 randomizer;
    std::shuffle(m_vect.begin(), m_vect.end(), randomizer);
    m_complete.setPoint(-1);
    emit changed();
}
void arraymodel::refill()
{
    int size = m_vect.size();
    switch(m_fill)
    {
    case FILL_TYPE::LINEAR:
    {
        for(int i = 0; i < size; ++i)
        {
            m_vect[i] = i+1;
        }
        break;
    }
    case FILL_TYPE::CUBIC:
    {
        int zeroOffset = size / 2;
        int min = 0;
        for(int i = 0; i < size; ++i)
        {
            int val = i - zeroOffset;
            m_vect[i] = pow(val,3);
            if(!i)
            {
                min = m_vect[0];
            }
            m_vect[i] -= min;
        }
        int max = m_vect.last()/size;
        for(int &val : m_vect)
        {
            val = val/max;
        }
        break;
    }
    case FILL_TYPE::ONE_ODD:
    {
        for(int &val : m_vect)
        {
            val = 1;
        }
        m_vect.last() = 2;
        break;
    }
    case FILL_TYPE::LINEAR_INVERSE:
    {
        for(int i = size - 1; i >= 0; --i)
        {
            m_vect[i] = size - i;
        }
        m_complete.setPoint(-1);
        emit changed();
        return;//special case
    }
    }

    m_complete.setRange(0,size);
    emit changed();
}
void arraymodel::setFillType(FILL_TYPE newFillType)
{
    if(newFillType != m_fill)
    {
        m_fill = newFillType;
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

    if(m_vect.size() != newSize)
    {
        m_vect.resize(newSize);
        refill();
    }
}
FILL_TYPE arraymodel::fillType() const
{
    return m_fill;
}
bool arraymodel::compare() const
{
    return m_vect.at(m_idxA) > m_vect.at(m_idxB);
}
int arraymodel::size() const
{
    return m_vect.size();
}
int arraymodel::max() const
{
    int max = m_vect.at(0);
    for( int val : m_vect )
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
    int min = m_vect.at(0);
    for( int val : m_vect )
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
    return m_idxA;
}
int arraymodel::B() const
{
    return m_idxB;
}
int arraymodel::elementA() const
{
    if(m_idxA >= 0 && m_idxA <= m_vect.size())
    {
        return m_vect.at(m_idxA); //QVector does NOT use exceptions!
    }
    return -1;
}
int arraymodel::elementB() const
{
    if(m_idxB >= 0 && m_idxB <= m_vect.size())
    {
        return m_vect.at(m_idxB);
    }
    return -1;
}
