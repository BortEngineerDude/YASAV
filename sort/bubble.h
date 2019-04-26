#ifndef BUBBLE_H
#define BUBBLE_H
#include "sorter.h"

enum bubble_step {BS_COMPARE,BS_SWAP,BS_INCREMENT};

class bubble : public sorter
{
    bubble_step step;
    bool compareState;
    bool hasSwaps;

public:
    bubble();
    SORT_TYPE sortType() const override;
    ~bubble() override = default;

public slots:
    void advance() override;
    void resetState() override;
};

#endif // BUBBLE_H
