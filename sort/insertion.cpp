#include "insertion.h"

insertion::insertion()
{
    step = insertion_step::COMPARE;
}
SORT_TYPE insertion::sortType() const
{
    return SORT_TYPE::INSERTION;
}
void insertion::advance()
{
    ++steps;
    if(model->A() == -1)
    {
        steps = 0;
        model->resetStats();
        model->m_complete.setPoint(0);
        model->setA(0);
        model->setB(1);
    }

    switch(step)
    {
    case insertion_step::COMPARE:
    {
        state.clear();
        stateStream << "A > B = \n";

        if(model->compare())
        {
            stateStream << QObject::tr("true") << ".\n";
            stateStream << QObject::tr("\nNext step:\nSwap ARR[A] and ARR[B].");
            step = insertion_step::MOVE;
        }
        else
        {
            stateStream << QObject::tr("false") << ".\n";
            stateStream << QObject::tr("\nNext step:\nGo to unsorted values.");
            step = insertion_step::INCREMENT;
        }

        emit stepDone();

        break;
    }
    case insertion_step::MOVE:
    {
        model->swap();

        state.clear();
        stateStream << QObject::tr("A > B =>\nSwap A and B.\n");
        stateStream << QObject::tr("\nNext step:\nDecrement A and B");
        step = insertion_step::DECREMENT;

        emit stepDone();

        break;
    }
    case insertion_step::DECREMENT:
    {
        model->setB( model->A() );
        model->setA( model->A() - 1 );

        state.clear();
        stateStream << "B = A,\nA = A - 1.\n";

        if(model->A() == -1)
        {
            model->setA(0);
            step = insertion_step::INCREMENT;
            stateStream << QObject::tr("\nNext step:\nGo to unsorted values.");
        }
        else
        {
            step = insertion_step::COMPARE;
            stateStream << QObject::tr(
                               "\nNext step:\nCompare ARR[A] and ARR[B].");
        }
        emit stepDone();
        break;
    }

    case insertion_step::INCREMENT:
    {
        model->m_complete.setEnd(model->m_complete.end()+1);
        model->setB(model->m_complete.end());
        model->setA(model->B()-1);

        state.clear();
        stateStream << "B = " << model->B();
        stateStream << "\nA = B - 1\n";

        emit iterationDone();

        step = insertion_step::COMPARE;

        if(model->B() >= model->size())
        {
            resetState();
            stateStream << QObject::tr("Reached end =>\nSorting finished.")
                        << this->generateStats();
            emit stepDone();
            emit finished();
            return;
        }

        stateStream << QObject::tr("\nNext step:\nCompare ARR[A] and ARR[B].");
        emit stepDone();

        break;
    }
    }
}
void insertion::resetState()
{
    model->setA(-1);
    model->setB(-1);
    state.clear();
    step = insertion_step::COMPARE;
}
