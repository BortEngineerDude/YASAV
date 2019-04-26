#ifndef SELECTION_H
#define SELECTION_H
#include "sorter.h"

enum selection_step{SS_COMPARE, SS_INCREMENT, SS_SWAP};

class selection : public sorter
{
    selection_step step;
    int maxAddr;
    int maxVal;
    bool compareState;

public:
    selection();
    SORT_TYPE sortType() const override;
    ~selection() override = default;

public slots:
    void advance() override;
    void resetState() override;
};

#endif // SELECTION_H
