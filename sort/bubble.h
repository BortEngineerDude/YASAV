#ifndef BUBBLE_H
#define BUBBLE_H
#include "sorter.h"

enum class bubble_step : unsigned char {COMPARE,SWAP,INCREMENT};

class bubble : public sorter
{
    bubble_step step;
    bool hasSwaps;
    void makeSwapsString();

public:
    bubble();
    SORT_TYPE sortType() const override;
    ~bubble() override = default;

public slots:
    void advance() override;
    void resetState() override;
};

#endif // BUBBLE_H
