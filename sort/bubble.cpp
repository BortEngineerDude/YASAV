#include "bubble.h"

bubble::bubble()
{
    top = 0;
    idx = 0;
    step = BS_COMPARE;
    hasSwaps = false;
    model = nullptr;
}
void bubble::setModel(arraymodel * newModel)
{
    model = newModel;
    top = model->size();
}
void bubble::reset()
{
    top = model->size();
    idx = 0;
    step = BS_COMPARE;
    hasSwaps = false;
}
void bubble::advance()
{
    switch(step)
    {
    case BS_COMPARE:
    {
        if( idx+1 >= top )
        {
            --top;
            if( top == 0 )
            {
                emit finished();
                reset();
                return;
            }
            else
            {
                if(hasSwaps)
                {
                    idx = 0;
                    hasSwaps = false;
                }
                else
                {
                    emit finished();
                    reset();
                    return;
                }
            }
        }

        compareState = model->getElement(idx) > model->getElement(idx + 1);
        step = BS_SWAP;

        break;
    }

    case BS_SWAP:
    {
        if(compareState)
        {
            model->swap(idx, idx+1);
            hasSwaps = true;
        }
        ++idx;
        step = BS_COMPARE;
        break;
    }
    }
}
void bubble::updateModel()
{
    top = model->size();
}
