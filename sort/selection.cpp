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

        m_stateStream << QObject::tr( "Current element is less than MIN: " );
        if( m_model->compare() )
        {
            m_model->setA(m_model->B());
            m_stateStream << QObject::tr( "true" ) << ".\n"
                          << QObject::tr( "Set new MIN at current element." );
        }
        else
        {
            m_stateStream << QObject::tr( "false" ) << ".\n"
                          << QObject::tr( "Current element is not MIN." );
        }

        m_stateStream << QObject::tr( "\nNext step:\n" )
                      << QObject::tr( "Select next element." );

        step = selection_step::INCREMENT;
        emit stepDone();
        break;
    }
    case selection_step::INCREMENT:
    {
        m_state.clear();

        m_model->setB(m_model->B() + 1);
        m_stateStream << QObject::tr( "Selected next element" );

        if(m_model->B() >= m_model->size())
        {
            m_model->setB( m_model->m_complete.end() );
            m_stateStream << QObject::tr( ", but reached end - \nreset to last"
                                          " unsorted element" )
                          << QObject::tr( "\nNext step:\n" )
                          << QObject::tr( "Swap MIN and current element." );
            step = selection_step::SWAP;
        }
        else
        {
            m_stateStream << ".\n"
                          << QObject::tr( "\nNext step:\n" )
                          << QObject::tr( "Compare MIN and current element." );
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
            m_stateStream << QObject::tr( "No MIN - no swap.\n" );
        }
        else
        {
            m_model->swap();
            m_stateStream << QObject::tr( "Swapped MIN and current element.\n");
        }

        step = selection_step::ADVANCE;
        m_stateStream << QObject::tr( "\nNext step:\n" )
                      << QObject::tr( "Select next unsorted element." );
        emit stepDone();

        break;
    }
    case selection_step::ADVANCE:
    {
        m_state.clear();

        m_model->m_complete.setEnd( m_model->m_complete.end() + 1);
        m_model->setA( m_model->m_complete.end() );
        m_model->setB( m_model->A() + 1 );

        m_stateStream << QObject::tr( "Selected next unsorted element.\n" );

        if( m_model->A() >= m_model->size() - 1 )
        {
            resetState();
            m_model->m_complete.setRange( 0, m_model->size() );
            m_stateStream << QObject::tr( "Reached end => " )
                          << QObject::tr( "\nSorting finished." )
                          << this->generateStats();
            emit finished();
        }
        else
        {
            m_stateStream << QObject::tr( "\nNext step:\n" )
                          << QObject::tr( "Compare MIN and current element." );
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
