#include "bubble.h"

void bubble::makeSwapsString()
{
    m_stateStream << QObject::tr("Swaps were done?: ");
    if(hasSwaps)
    {
        m_stateStream << QObject::tr("true");
    }
    else
    {
        m_stateStream << QObject::tr("false");
    }
    m_stateStream << ".\n";
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
    m_model->setA(-1);
    m_model->setB(-1);
    m_state.clear();
    step = bubble_step::COMPARE;
    hasSwaps = false;
}
void bubble::advance()
{
    ++m_steps;
    m_model->m_highlight = false;
    if( m_model->A() == -1 )
    {
        m_model->resetStats();
        m_steps = 0;
        m_model->m_complete.setPoint( m_model->size() );
        m_model->setA( 0 );
        m_model->setB( 1 );
    }

    switch( step )
    {
    case bubble_step::COMPARE:
    {
        m_model->m_highlight = true;
        m_state.clear();
        makeSwapsString();

        m_stateStream << QObject::tr( "Elements are in order: " );
        if( m_model->compare() )
        {
            m_stateStream << QObject::tr( "false" ) << ".\n"
                          << QObject::tr( "\nNext step:\n" )
                          << QObject::tr( "Swap elements." );
            step = bubble_step::SWAP;
        }
        else
        {
            m_stateStream << QObject::tr( "true" ) << ".\n"
                          << QObject::tr( "\nNext step:\n" )
                          << QObject::tr( "Select next elements." );
            step = bubble_step::INCREMENT;
        }

        emit stepDone();

        break;
    }

    case bubble_step::SWAP:
    {
        m_state.clear();
        makeSwapsString();

        m_model->swap();
        hasSwaps = true;

        m_stateStream << QObject::tr( "Elements swapped.\n" )
                      << QObject::tr( "\nNext step:\n" )
                      << QObject::tr( "Select next elements." );
        step = bubble_step::INCREMENT;

        emit stepDone();

        break;
    }
    case bubble_step::INCREMENT:
    {
        m_model->setA(m_model->B());
        m_model->setB(m_model->B()+1);

        m_state.clear();
        makeSwapsString();
        m_stateStream << QObject::tr( "Selected next elements.\n" );

        if( m_model->B() >= m_model->m_complete.begin() )
        {
            m_model->m_complete.setBegin(m_model->m_complete.begin() - 1);
            if( m_model->m_complete.begin() <= 0 )
            {
                resetState();
                m_model->m_complete.setRange(0,m_model->size());

                m_stateStream << QObject::tr( "Reached beginning =>" )
                              << QObject::tr( "\nSorting finished." )
                              << this->generateStats();

                emit stepDone();
                emit finished();
                return;
            }
            else
            {
                if( hasSwaps )
                {
                    m_model->setA( 0 );
                    m_model->setB( 1 );
                    hasSwaps = false;
                    m_stateStream << QObject::tr( "Reached end, selected"
                                                  " first elements." );
                    emit iterationDone();
                }
                else
                {
                    resetState();
                    m_model->m_complete.setRange(0,m_model->size());

                    m_stateStream << QObject::tr( "No swaps =>" )
                                  << QObject::tr( "\nSorting finished.")
                                  << this->generateStats();

                    emit stepDone();
                    emit finished();
                    return;
                }
            }
        }

        m_stateStream << QObject::tr( "\nNext step:\n" )
                      << QObject::tr( "Check elements order." );
        step = bubble_step::COMPARE;

        emit stepDone();

        break;
    }
    }
}
