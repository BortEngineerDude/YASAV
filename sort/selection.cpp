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
    case selection_step::COMPARE:
    {
        m_state.clear();
        m_model->m_highlight = true;

        m_stateStream << "ARR[A] > ARR[B] = ";
        if(m_model->compare())
        {
            m_model->setA(m_model->B());
            m_stateStream << QObject::tr( "true" ) << ".\n";
            m_stateStream << QObject::tr( "New MIN found at ARR[" )
                          << m_model->A() << "]" << '\n';
        }
        else
        {
            m_stateStream << QObject::tr( "false" ) << ".\n";
            m_stateStream << QObject::tr( "Looking for new MIN...\n" );
        }

        m_stateStream << QObject::tr( "\nNext step:\nIncrement B." );
        step = selection_step::INCREMENT;
        emit stepDone();
        break;
    }
    case selection_step::INCREMENT:
    {
        m_state.clear();

        m_model->setB(m_model->B() + 1);
        m_stateStream << "\nB = B + 1";

        if(m_model->B() >= m_model->size())
        {
            m_model->setB(m_model->m_complete.end());
            m_stateStream << QObject::tr(" //Reached end of array.\n")
                        << QObject::tr(" \nNext step:\nSwap ARR[A] and ARR[B]." );
            step = selection_step::SWAP;
        }
        else
        {
            m_stateStream << '\n'
                        << QObject::tr(
                               "\nNext step:\nCompare ARR[A] and ARR[B].");
            step = selection_step::COMPARE;
        }
        emit stepDone();
        break;
    }
    case selection_step::SWAP:
    {
        m_state.clear();

        if( m_model->A() == m_model->B() )
        {
            m_stateStream << "\nNo MIN to swap.\n";
        }
        else
        {
            m_model->swap();
            m_stateStream << "\nSwap A and B\n";
        }

        step = selection_step::ADVANCE;
        m_stateStream << QObject::tr("\nNext step:\nGo to unsorted values.");
        emit stepDone();

        break;
    }
    case selection_step::ADVANCE:
    {
        m_state.clear();

        m_model->m_complete.setEnd( m_model->m_complete.end() + 1);
        m_model->setA( m_model->m_complete.end() );
        m_model->setB( m_model->A() + 1 );

        m_stateStream << "A = " << m_model->A() << "\nB = A + 1\n";

        if( m_model->A() >= m_model->size() - 1 )
        {
            resetState();
            m_model->m_complete.setRange( 0, m_model->size() );
            m_stateStream << QObject::tr( "Reached end =>\nSorting finished." )
                        << this->generateStats();
            emit finished();
        }
        else
        {
            m_stateStream << QObject::tr(
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
    m_state.clear();
    m_model->setA(-1);
    m_model->setB(-1);
    step = selection_step::COMPARE;
}
