#include "merge.h"

merge::merge()
{
    step = merge_step::ARRANGE;
}
SORT_TYPE merge::sortType() const
{
    return SORT_TYPE::INSERTION;
}
void merge::advance()
{

}

void merge::resetState()
{

}
