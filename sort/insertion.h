#ifndef INSERTION_H
#define INSERTION_H

#include "sorter.h"

enum class insertion_step : unsigned char {COMPARE,MOVE,DECREMENT,INCREMENT};

class insertion : public sorter
{
    insertion_step step;

public:
    insertion();
    SORT_TYPE sortType() const override;
    ~insertion() override = default;

public slots:
    void advance() override;
    void resetState() override;
};

#endif // INSERTION_H
