#include "selection.h"

void selection::makeMinStr()
{
    stateStream << "MIN [ " << minAddr << " ] = " << minVal << '\n';
}

selection::selection()
{
    step = selection_step::COMPARE;
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
        minAddr = model->A();
    }

    switch(step)
    {
    case selection_step::COMPARE:
    {
        state.clear();
        makeMinStr();

        model->compare();//just to count comparisons in future
        if(model->elementB() < minVal)
        {
            minAddr = model->B();
            minVal = model->elementB();
            stateStream << QObject::tr("\nNew MIN: [ ") << minAddr
                        << " ] = " << minVal << ".\n";
        }
        else
        {
            stateStream << QObject::tr("\nLooking for new MIN...\n");
        }

        stateStream << QObject::tr("\nNext step:\nincrement [B].");
        step = selection_step::INCREMENT;
        emit stepDone();
        break;
    }
    case selection_step::INCREMENT:
    {
        state.clear();
        makeMinStr();

        model->setB(model->B() + 1);
        stateStream << "\n[B] = [B] + 1";

        if(model->B() >= model->size())
        {
            model->setB(minAddr);
            stateStream << QObject::tr(" //END.\n\nNextStep:\nswap MIN and A.");
            step = selection_step::SWAP;
        }
        else
        {
            stateStream << '\n'
                        << QObject::tr("\nNext step:\ncompare MIN and B.");
            step = selection_step::COMPARE;
        }
        emit stepDone();
        break;
    }
    case selection_step::SWAP:
    {
        state.clear();
        makeMinStr();

        if( minAddr >= 0 )
        {
            model->swap();
            stateStream << "\nMIN <=> A\n";
        }
        else
        {
            stateStream << "\nNo MIN to swap.\n";
        }

        step = selection_step::ADVANCE;
        stateStream << QObject::tr("\nNext step:\nincrement [A] and [B].");
        emit stepDone();

        break;
    }
    case selection_step::ADVANCE:
    {
        state.clear();
        makeMinStr();

        model->m_complete.setEnd(model->A());
        model->setA(model->A() + 1);
        model->setB(model->A() + 1);

        stateStream << "\n[A]=[A]+1; [B]=[A]+1\n";

        if(model->A() >= model->size() - 1)
        {
            resetState();
            model->m_complete.setRange(0,model->size());
            stateStream << QObject::tr("Reached end =>\nsorting finished.");
            emit finished();
        }
        else
        {
            minAddr = model->A();
            minVal = model->elementA();
            stateStream << QObject::tr("\nNext step:\ncompare MIN and B.");
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
