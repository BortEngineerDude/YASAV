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
    ++m_steps;
    m_model->m_highlight = false;

    if(m_model->A() == -1)
    {
        m_steps = 0;
        m_model->resetStats();
        m_model->m_complete.setPoint(0);
        m_model->setA(0);
        m_model->setB(1);
    }

    switch(step)
    {
    case insertion_step::COMPARE:
    {
        m_state.clear();
        m_model->m_highlight = true;
        m_stateStream << "A > B = \n";

        if(m_model->compare())
        {
            m_stateStream << QObject::tr( "true" ) << ".\n";
            m_stateStream << QObject::tr(
                                 "\nNext step:\nSwap ARR[A] and ARR[B]." );
            step = insertion_step::MOVE;
        }
        else
        {
            m_stateStream << QObject::tr( "false" ) << ".\n";
            m_stateStream << QObject::tr(
                                 "\nNext step:\nGo to unsorted values." );
            step = insertion_step::INCREMENT;
        }

        emit stepDone();

        break;
    }
    case insertion_step::MOVE:
    {
        m_model->swap();

        m_state.clear();
        m_stateStream << QObject::tr("A > B =>\nSwap A and B.\n");
        m_stateStream << QObject::tr("\nNext step:\nDecrement A and B");
        step = insertion_step::DECREMENT;

        emit stepDone();

        break;
    }
    case insertion_step::DECREMENT:
    {
        m_model->setB( m_model->A() );
        m_model->setA( m_model->A() - 1 );

        m_state.clear();
        m_stateStream << "B = A,\nA = A - 1.\n";

        if(m_model->A() == -1)
        {
            m_model->setA(0);
            step = insertion_step::INCREMENT;
            m_stateStream << QObject::tr("\nNext step:\nGo to unsorted values.");
        }
        else
        {
            step = insertion_step::COMPARE;
            m_stateStream << QObject::tr(
                               "\nNext step:\nCompare ARR[A] and ARR[B].");
        }
        emit stepDone();
        break;
    }

    case insertion_step::INCREMENT:
    {
        m_model->m_complete.setEnd(m_model->m_complete.end()+1);
        m_model->setB(m_model->m_complete.end());
        m_model->setA(m_model->B()-1);

        m_state.clear();
        m_stateStream << "B = " << m_model->B();
        m_stateStream << "\nA = B - 1\n";

        emit iterationDone();

        step = insertion_step::COMPARE;

        if(m_model->B() >= m_model->size())
        {
            resetState();
            m_stateStream << QObject::tr("Reached end =>\nSorting finished.")
                        << this->generateStats();
            emit stepDone();
            emit finished();
            return;
        }

        m_stateStream << QObject::tr("\nNext step:\nCompare ARR[A] and ARR[B].");
        emit stepDone();

        break;
    }
    }
}
void insertion::resetState()
{
    m_model->setA(-1);
    m_model->setB(-1);
    m_state.clear();
    step = insertion_step::COMPARE;
}
