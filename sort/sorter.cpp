#include "sorter.h"

sorter::sorter()
{

}
sorter::sorter(arraymodel * newModel)
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
