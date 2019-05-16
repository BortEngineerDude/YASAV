#include "bubble.h"

void bubble::makeSwapsString()
{
    stateStream << QObject::tr("Swaps were done?: ");
    if(hasSwaps)
    {
        stateStream << QObject::tr("true");
    }
    else
    {
        stateStream << QObject::tr("false");
    }
    stateStream << ".\n";
}

bubble::bubble()
{
    step = bubble_step::COMPARE;
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
    step = bubble_step::COMPARE;
    hasSwaps = false;
}
void bubble::advance()
{
    ++steps;
    if(model->A() == -1)
    {
        model->resetStats();
        steps = 0;
        model->m_complete.setPoint(model->size());
        model->setA(0);
        model->setB(1);
    }

    switch(step)
    {
    case bubble_step::COMPARE:
    {
        state.clear();
        makeSwapsString();

        stateStream << "ARR[A] > ARR[B] = ";
        if(model->compare())
        {
            stateStream << QObject::tr("true") << ".\n";
            stateStream << QObject::tr("\nNext step:\nSwap ARR[A] and ARR[B].");
            step = bubble_step::SWAP;
        }
        else
        {
            stateStream << QObject::tr("false") << ".\n";
            stateStream << QObject::tr("\nNext step:\nIncrement A and B.");
            step = bubble_step::INCREMENT;
        }

        emit stepDone();

        break;
    }

    case bubble_step::SWAP:
    {
        state.clear();
        makeSwapsString();

        model->swap();
        hasSwaps = true;

        stateStream << QObject::tr("A > B => Swap A and B.\n");
        stateStream << QObject::tr("\nNext step:\nIncrement A and B.");
        step = bubble_step::INCREMENT;

        emit stepDone();

        break;
    }
    case bubble_step::INCREMENT:
    {
        model->setA(model->B());
        model->setB(model->B()+1);

        state.clear();
        makeSwapsString();
        stateStream << "A = B, B = B + 1.\n";

        if( model->B() >= model->m_complete.begin() )
        {
            model->m_complete.setBegin(model->m_complete.begin() - 1);
            if( model->m_complete.begin() <= 0 )
            {
                resetState();
                model->m_complete.setRange(0,model->size());

                stateStream << QObject::tr(
                                   "Reached 0 =>\nSorting finished.")
                            << this->generateStats();

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

                    stateStream << QObject::tr(
                                       "No swaps =>\nSorting finished.")
                                << this->generateStats();

                    emit stepDone();
                    emit finished();
                    return;
                }
            }
        }

        stateStream << QObject::tr("\nNext step:\nCompare ARR[A] and ARR[B].");
        step = bubble_step::COMPARE;

        emit stepDone();

        break;
    }
    }
}
