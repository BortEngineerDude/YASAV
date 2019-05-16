#include "selection.h"

selection::selection()
{
    step = selection_step::COMPARE;
}
SORT_TYPE selection::sortType() const
{
    return SORT_TYPE::SELECTION;
}
void selection::advance()
{
    if(model->A() == -1)
    {
        model->resetStats();
        model->m_complete.setPoint(0);
        model->setA(0);
        model->setB(1);
    }

    switch(step)
    {
    case selection_step::COMPARE:
    {
        state.clear();

        stateStream << "ARR[A] > ARR[B] = ";
        if(model->compare())
        {
            model->setA(model->B());
            stateStream << QObject::tr("true") << ".\n";
            stateStream << QObject::tr("New MIN found at ARR[") << model->A()
                        << "]" << '\n';
        }
        else
        {
            stateStream << QObject::tr("false") << ".\n";
            stateStream << QObject::tr("Looking for new MIN...\n");
        }

        stateStream << QObject::tr("\nNext step:\nIncrement B.");
        step = selection_step::INCREMENT;
        emit stepDone();
        break;
    }
    case selection_step::INCREMENT:
    {
        state.clear();

        model->setB(model->B() + 1);
        stateStream << "\nB = B + 1";

        if(model->B() >= model->size())
        {
            model->setB(model->m_complete.end());
            stateStream << QObject::tr(" //END.\n")
                        << QObject::tr("\nNext step:\nSwap ARR[A] and ARR[B].");
            step = selection_step::SWAP;
        }
        else
        {
            stateStream << '\n'
                        << QObject::tr(
                               "\nNext step:\nCompare ARR[A] and ARR[B].");
            step = selection_step::COMPARE;
        }
        emit stepDone();
        break;
    }
    case selection_step::SWAP:
    {
        state.clear();

        if( model->A() == model->B() )
        {
            stateStream << "\nNo MIN to swap.\n";
        }
        else
        {
            model->swap();
            stateStream << "\nSwap A and B\n";
        }

        step = selection_step::ADVANCE;
        stateStream << QObject::tr("\nNext step:\nGo to unsorted values.");
        emit stepDone();

        break;
    }
    case selection_step::ADVANCE:
    {
        state.clear();

        model->m_complete.setEnd(model->m_complete.end() + 1);
        model->setA(model->m_complete.end());
        model->setB(model->A() + 1);

        stateStream << "A = " << model->A() << "\nB = A + 1\n";

        if(model->A() >= model->size() - 1)
        {
            resetState();
            model->m_complete.setRange(0,model->size());
            stateStream << QObject::tr("Reached end =>\nSorting finished.")
                        << this->generateStats();
            emit finished();
        }
        else
        {
            //minAddr = model->A();
            //minVal = model->elementA();
            stateStream << QObject::tr(
                               "\nNext step:\nCompare ARR[A] and ARR[B].");
            step = selection_step::COMPARE;
        }
        emit stepDone();
        emit iterationDone();
    }
    }
}
void selection::resetState()
{
    state.clear();
    model->setA(-1);
    model->setB(-1);
    step = selection_step::COMPARE;
}
