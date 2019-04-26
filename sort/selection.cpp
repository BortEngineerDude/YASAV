#include "selection.h"

selection::selection()
{
    step = SS_COMPARE;
    maxAddr = -1;
    maxVal = -1;
}
SORT_TYPE selection::sortType() const
{
    return SORT_TYPE::SELECTION;
}
void selection::advance()
{
    if(model->A() == -1)
    {
        model->setTop(model->size());
        model->setA(model->size()-1);
        model->setB(model->size()-2);
        maxVal = model->elementA();
        maxAddr = -1;
    }

    switch(step)
    {
    case SS_COMPARE:
    {
        if(model->elementB() > maxVal)
        {
            maxAddr = model->B();
            maxVal = model->elementB();
        }

        step = SS_INCREMENT;
        break;
    }
    case SS_INCREMENT:
    {
        model->setB(model->B() - 1);

        if(model->B() < 0)
        {
            model->setB(maxAddr);
            step = SS_SWAP;
        }
        else
        {
            step = SS_COMPARE;
        }
        break;
    }
    case SS_SWAP:
    {
        if( maxAddr >= 0)
        {
            model->swap();
        }
        model->setTop(model->A());
        model->setA(model->A() - 1);
        model->setB(model->A() - 1);

        if(model->A() == 0)
        {
            resetState();
            emit finished();
        }
        else
        {
            maxAddr = model->A();
            maxVal = model->elementA();
            step = SS_COMPARE;
        }
        break;
    }
    }
}
void selection::resetState()
{
    model->setTop(-1);
    model->setA(-1);
    model->setB(-1);
    step = SS_COMPARE;
}
