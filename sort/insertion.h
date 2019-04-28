#ifndef INSERTION_H
#define INSERTION_H

#include "sorter.h"

enum insertion_step {IS_COMPARE,IS_MOVE,IS_DECREMENT,IS_INCREMENT};

class insertion : public sorter
{
    insertion_step step;
    bool compareState;

public:
    insertion();
    SORT_TYPE sortType() const override;
    ~insertion() override = default;

public slots:
    void advance() override;
    void resetState() override;
};

#endif // INSERTION_H
