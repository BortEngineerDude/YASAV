#include "sorter.h"

const QString sorter::generateStats()
{
    QString stats;
    QTextStream s(&stats);
    s << '\n' << QObject::tr("Steps") << ": " << m_steps
      << '\n' << QObject::tr("Comparisons") << ": " << m_model->comparisons()
      << '\n' << QObject::tr("Swaps") << ": " << m_model->swaps();
    return stats;
}
sorter::sorter() : m_stateStream(&m_state), m_steps(0)
{}
sorter::sorter(arraymodel * newModel) : m_stateStream(&m_state), m_steps(0)
{
    m_model = newModel;
    m_model->setA(-1);
    m_model->setB(-1);
}
void sorter::setModel(arraymodel * newModel)
{
    m_model = newModel;
    m_model->setA(-1);
    m_model->setB(-1);
}
const QString &sorter::state() const
{
    return m_state;
}
int sorter::steps() const
{
    return m_steps;
}
