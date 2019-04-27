#include "selection.h"

selection::selection()
{
    step = SS_COMPARE;
    minAddr = -1;
    minVal = -1;
}
SORT_TYPE selection::sortType() const
{
    return SORT_TYPE::SELECTION;
}
void selection::advance()
{
    if(model->A() == -1)
    {
        model->m_complete.setPoint(0);
        model->setA(0);
        model->setB(1);
        minVal = model->elementA();
        minAddr = -1;
    }

    switch(step)
    {
    case SS_COMPARE:
    {
        if(model->elementB() < minVal)
        {
            minAddr = model->B();
            minVal = model->elementB();
        }

        step = SS_INCREMENT;
        emit stepDone();
        break;
    }
    case SS_INCREMENT:
    {
        model->setB(model->B() + 1);

        if(model->B() >= model->size())
        {
            model->setB(minAddr);
            step = SS_SWAP;
        }
        else
        {
            step = SS_COMPARE;
        }
        emit stepDone();
        break;
    }
    case SS_SWAP:
    {
        if( minAddr >= 0)
        {
            model->swap();
        }
        model->m_complete.setEnd(model->A());
        model->setA(model->A() + 1);
        model->setB(model->A() + 1);

        if(model->A() >= model->size() - 1)
        {
            resetState();
            model->m_complete.setRange(0,model->size());
            emit finished();
        }
        else
        {
            minAddr = model->A();
            minVal = model->elementA();
            step = SS_COMPARE;
        }
        emit stepDone();
        emit iterationDone();
        break;
    }
    }
}
void selection::resetState()
{
    model->setA(-1);
    model->setB(-1);
    step = SS_COMPARE;
}
