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
        m_stateStream << QObject::tr( "Elements are in order: " );

        if(m_model->compare())
        {
            m_stateStream << QObject::tr( "false" ) << ".\n"
                          << QObject::tr( "\nNext step:\n" )
                          << QObject::tr( "Swap elements." );
            step = insertion_step::MOVE;
        }
        else
        {
            m_stateStream << QObject::tr( "true" ) << ".\n"
                          << QObject::tr( "\nNext step:\n" )
                          << QObject::tr( "Select next elements." );

            step = insertion_step::INCREMENT;
        }

        emit stepDone();

        break;
    }
    case insertion_step::MOVE:
    {
        m_model->swap();

        m_state.clear();
        m_stateStream << QObject::tr( "Elements swapped.\n" )
                      << QObject::tr( "\nNext step:\n" )
                      << QObject::tr( "Select previous elements." );

        step = insertion_step::DECREMENT;

        emit stepDone();

        break;
    }
    case insertion_step::DECREMENT:
    {
        m_model->setB( m_model->A() );
        m_model->setA( m_model->A() - 1 );

        m_state.clear();
        m_stateStream << QObject::tr( "Selected previous elements" );

        if(m_model->A() == -1)
        {
            m_model->setA(0);
            step = insertion_step::INCREMENT;
            m_stateStream << QObject::tr( ", but reached beginning." )
                          << QObject::tr( "\nNext step:\n" )
                          << QObject::tr( "Select next elements." );
        }
        else
        {
            step = insertion_step::COMPARE;
            m_stateStream << ".\n"
                          << QObject::tr( "\nNext step:\n" )
                          << QObject::tr( "Check elements order." );
        }
        emit stepDone();
        break;
    }

    case insertion_step::INCREMENT:
    {
        m_model->m_complete.setEnd( m_model->m_complete.end() + 1 );
        m_model->setB( m_model->m_complete.end() );
        m_model->setA( m_model->B() - 1 );

        m_state.clear();
        m_stateStream << QObject::tr( "Selected next elements.\n" );

        emit iterationDone();

        step = insertion_step::COMPARE;

        if(m_model->B() >= m_model->size())
        {
            resetState();
            m_stateStream << QObject::tr( "Reached end => " )
                          << QObject::tr( "\nSorting finished." )
                          << this->generateStats();
            emit stepDone();
            emit finished();
            return;
        }

        m_stateStream << QObject::tr( "\nNext step:\n" )
                      << QObject::tr( "Check elements order." );
        emit stepDone();

        break;
    }
    }
}
void insertion::resetState()
{
    m_model->setA( -1 );
    m_model->setB( -1 );
    m_state.clear();
    step = insertion_step::COMPARE;
}
