#include "bubble.h"

bubble::bubble()
{
    top = 0;
    step = BS_COMPARE;
    hasSwaps = false;
    model = nullptr;
}
void bubble::setModel(arraymodel * newModel)
{
    model = newModel;
    top = model->size()-1;
    model->setA(-1);
    model->setB(-1);
}
void bubble::reset()
{
    top = model->size()-1;
    model->setA(-1);
    model->setB(-1);
    step = BS_COMPARE;
    hasSwaps = false;
}
void bubble::advance()
{
    if(model->A() == -1)
    {
        model->setA(0);
        model->setB(1);
    }

    switch(step)
    {
    case BS_COMPARE:
    {
        compareState = model->elementA() > model->elementB();
        step = BS_SWAP;

        break;
    }

    case BS_SWAP:
    {
        if(compareState)
        {
            model->swap();
            hasSwaps = true;
        }
        step = BS_INCREMENT;
        break;
    }
    case BS_INCREMENT:
    {
        model->setA(model->B());
        model->setB(model->B()+1);

        if( model->B() > top )
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
                    model->setA(0);
                    model->setB(1);
                    hasSwaps = false;
                }
                else
                {
                    model->setA(-1);
                    model->setB(-1);
                    emit finished();
                    reset();
                    return;
                }
            }
        }

        step = BS_COMPARE;
        break;
    }
    }
}
void bubble::updateModel()
{
    top = model->size();
}
