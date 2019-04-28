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
    model->setA(-1);
    model->setB(-1);
    step = BS_COMPARE;
    hasSwaps = false;
}
void bubble::advance()
{
    if(model->A() == -1)
    {
        model->m_complete.setPoint(model->size());
        model->setA(0);
        model->setB(1);
    }

    switch(step)
    {
    case BS_COMPARE:
    {
        compareState = model->elementA() > model->elementB();
        step = BS_SWAP;
        emit stepDone();

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
        emit stepDone();

        break;
    }
    case BS_INCREMENT:
    {
        model->setA(model->B());
        model->setB(model->B()+1);

        if( model->B() >= model->m_complete.begin() )
        {
            model->m_complete.setBegin(model->m_complete.begin() - 1);
            if( model->m_complete.begin() <= 0 )
            {
                resetState();
                model->m_complete.setRange(0,model->size());

                emit finished();
            }
            else
            {
                if(hasSwaps)
                {
                    model->setA(0);
                    model->setB(1);
                    hasSwaps = false;
                    emit iterationDone();
                }
                else
                {
                    resetState();
                    model->m_complete.setRange(0,model->size());
                    emit finished();
                }
            }
        }

        step = BS_COMPARE;
        emit stepDone();

        break;
    }
    }
}
