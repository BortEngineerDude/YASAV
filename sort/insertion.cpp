#include "insertion.h"

insertion::insertion()
{
    step = IS_COMPARE;
}
SORT_TYPE insertion::sortType() const
{
    return SORT_TYPE::INSERTION;
}

void insertion::advance()
{
    if(model->A() == -1)
    {
        model->m_complete.setPoint(0);
        model->setA(0);
        model->setB(1);
    }

    switch(step)
    {
    case IS_COMPARE:
    {
        compareState = model->elementA() > model->elementB();
        step = IS_MOVE;
        emit stepDone();

        break;
    }
    case IS_MOVE:
    {
        if(compareState)
        {
            model->swap();
            step = IS_DECREMENT;
        }
        else
        {
            step = IS_INCREMENT;
        }
        emit stepDone();

        break;
    }
    case IS_DECREMENT:
    {
        model->setB( model->A() );
        model->setA( model->A() - 1 );
        if(model->A() == -1)
        {
            model->setA(0);
            step = IS_INCREMENT;
        }
        else
        {
            step = IS_COMPARE;
        }
        emit stepDone();
        break;
    }

    case IS_INCREMENT:
    {
        model->m_complete.setEnd(model->m_complete.end()+1);
        model->setB(model->m_complete.end());
        model->setA(model->B()-1);

        if(model->B() >= model->size())
        {
            resetState();
            emit finished();
        }
        step = IS_COMPARE;
        emit iterationDone();
        emit stepDone();
        break;
    }
    }
}
void insertion::resetState()
{
    model->setA(-1);
    model->setB(-1);
    step = IS_COMPARE;
}
