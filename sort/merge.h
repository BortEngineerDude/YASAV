//https://habr.com/ru/post/138146/
//this is attempt to visualise in-place merge sort
#ifndef MERGE_H
#define MERGE_H

#include "sorter.h"
#include <QStack>

enum class merge_step : unsigned char {SPLIT, ARRANGE, MERGE};

class merge : public sorter
{
    merge_step step;

public:
    merge();
    SORT_TYPE sortType() const override;
    ~merge() override = default;

public slots:
    void advance() override;
    void resetState() override;

};

#endif // MERGE_H
