#include "bubble.h"

void bubble::makeSwapsString()
{
    stateStream << QObject::tr("Swaps were done? ");
    if(hasSwaps)
    {
        stateStream << QObject::tr("true");
    }
    else
    {
        stateStream << QObject::tr("false");
    }
    stateStream << ".\n\n";
}

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
    state.clear();
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

        state.clear();
        makeSwapsString();

        stateStream << "A > B = \n" << (compareState ? QObject::tr("true") : QObject::tr("false")) << ".\n";
        stateStream << QObject::tr("\nNext step:\nswap A and B.");

        emit stepDone();

        break;
    }

    case BS_SWAP:
    {
        state.clear();
        makeSwapsString();

        if(compareState)
        {
            model->swap();
            hasSwaps = true;

            stateStream << QObject::tr("A > B =>\nswap A and B.\n");
        }
        else
        {
            stateStream << QObject::tr("A < B =>\nno swaps necessary.\n");
        }

        step = BS_INCREMENT;

        stateStream << QObject::tr("\nNext step:\nincrement [A] and [B]");

        emit stepDone();

        break;
    }
    case BS_INCREMENT:
    {
        model->setA(model->B());
        model->setB(model->B()+1);

        state.clear();
        makeSwapsString();
        stateStream << "[A] = [B],\n[B] = [B] + 1.\n";

        if( model->B() >= model->m_complete.begin() )
        {
            model->m_complete.setBegin(model->m_complete.begin() - 1);
            if( model->m_complete.begin() <= 0 )
            {
                resetState();
                model->m_complete.setRange(0,model->size());

                stateStream << QObject::tr("Reached 0 => sorting finished.");

                emit stepDone();
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
                    emit iterationDone();
                }
                else
                {
                    resetState();
                    model->m_complete.setRange(0,model->size());

                    stateStream << QObject::tr("No swaps =>\nsorting finished.");

                    emit stepDone();
                    emit finished();
                    return;
                }
            }
        }

        step = BS_COMPARE;

        stateStream << QObject::tr("\nNext step:\ncompare A and B.");

        emit stepDone();

        break;
    }
    }
}
