#include "sorter.h"

QString sorter::generateStats()
{
    QString stats;
    QTextStream s(&stats);
    s << '\n' << QObject::tr("Swaps") << ": " << model->swaps()
      << '\n' << QObject::tr("Comparisons") << ": " << model->comparisons()
      << '\n' << QObject::tr("Steps") << ": " << steps;
    return stats;
}

sorter::sorter() : stateStream(&state)
{}

sorter::sorter(arraymodel * newModel) : stateStream(&state)
{
    model = newModel;
    model->setA(-1);
    model->setB(-1);
}
void sorter::setModel(arraymodel * newModel)
{
    model = newModel;
    model->setA(-1);
    model->setB(-1);
}

const QString &sorter::getState() const
{
    return state;
}
