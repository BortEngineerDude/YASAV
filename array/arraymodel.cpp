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

    m_top = -1;
    m_vect = QVector<int>(size,0);

    refill();
}
void arraymodel::swap()
{
    int tmp = m_vect.at(m_idxA);
    m_vect[m_idxA] = m_vect.at(m_idxB);
    m_vect[m_idxB] = tmp;
    emit changed();
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
void arraymodel::setTop(int top)
{
    m_top = top;
}
void arraymodel::shuffle()
{
    std::mt19937 randomizer;
    std::shuffle(m_vect.begin(), m_vect.end(), randomizer);
    m_top = m_vect.size();
    emit changed();
}
void arraymodel::refill()
{
    int size = m_vect.size();
    switch(m_fill)
    {
        case FILL_TYPE::LINEAR:
            for(int i = 0; i < size; ++i)
            {
                m_vect[i] = i+1;
            }
        break;
        case FILL_TYPE::CUBIC:
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

int arraymodel::top() const
{
    return m_top;
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
    return m_vect.at(m_idxA);
}
int arraymodel::elementB() const
{
    return m_vect.at(m_idxB);
}
