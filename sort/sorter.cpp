#include "sorter.h"

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
