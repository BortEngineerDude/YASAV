#include "bubble.h"

bubble::bubble()
{
    step = BS_COMPARE;
    hasSwaps = false;
}
SORT_TYPE bubble::sortType() const
{
    return SORT_TYPE::BUBBLE;
}
void bubble::resetState()
{
    model->setTop(-1);
    model->setA(-1);
    model->setB(-1);
    step = BS_COMPARE;
    hasSwaps = false;
}
void bubble::advance()
{
    if(model->A() == -1)
    {
        model->setTop(model->size());
        model->setA(0);
        model->setB(1);
    }

    switch(step)
    {
    case BS_COMPARE:
    {
        compareState = model->elementA() > model->elementB();
        step = BS_SWAP;

        break;
    }

    case BS_SWAP:
    {
        if(compareState)
        {
            model->swap();
            hasSwaps = true;
        }
        step = BS_INCREMENT;
        break;
    }
    case BS_INCREMENT:
    {
        model->setA(model->B());
        model->setB(model->B()+1);

        if( model->B() >= model->top() )
        {
            model->setTop(model->top() - 1);
            if( model->top() <= 0 )
            {
                resetState();
                emit finished();
                return;
            }
            else
            {
                if(hasSwaps)
                {
                    model->setA(0);
                    model->setB(1);
                    hasSwaps = false;
                }
                else
                {
                    resetState();
                    emit finished();
                    return;
                }
            }
        }

        step = BS_COMPARE;
        break;
    }
    }
}
