#ifndef RANGE_H
#define RANGE_H

template <typename T> class range
{
    T m_begin{};
    T m_end{};
public:
    range() = default;
    range(const T& begin, const T& end)
    {
        if(begin <= end)
        {
            m_begin = begin;
            m_end = end;
        }
        else
        {
            m_begin = end;
            m_end = begin;
        }
    }
    void setRange(const T& begin, const T& end)
    {
        if(begin <= end)
        {
            m_begin = begin;
            m_end = end;
        }
        else
        {
            m_begin = end;
            m_end = begin;
        }
    }
    const T& begin() const
    {
        return m_begin;
    }
    const T& middle() const
    {
        return (m_end - m_begin) / 2;
    }
    const T& end() const
    {
        return m_end;
    }
    void setBegin(const T& begin)
    {
        if(begin < m_end)
        {
            m_begin = begin;
        }
        else
        {
            m_begin = m_end;
        }
    }
    void setEnd(const T& end)
    {
        if(end > m_begin)
        {
            m_end = end;
        }
        else
        {
            m_end = m_begin;
        }
    }
    void setPoint(const T& point)
    {
        m_end = m_begin = point;
    }
    bool inRange(const T& val) const
    {
        return (val >= m_begin) && (val <= m_end);
    }
    bool outOfRange(const T& val) const
    {
        return (val < m_begin) || (val > m_end);
    }
};

#endif // RANGE_H
