#ifndef SELECTION_H
#define SELECTION_H
#include "sorter.h"

enum class selection_step{COMPARE, INCREMENT, SWAP, ADVANCE};

class selection : public sorter
{
    selection_step step;
    int minAddr;
    int minVal;
    void makeMinStr();

public:
    selection();
    SORT_TYPE sortType() const override;
    ~selection() override = default;

public slots:
    void advance() override;
    void resetState() override;
};

#endif // SELECTION_H
