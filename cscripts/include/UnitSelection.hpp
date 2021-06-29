#pragma once
#include <vector>

#include "Units/BaseUnit.hpp"

class UnitSelection
{
public:
    std::vector<BaseUnit*> Units;
    void AddUnit(BaseUnit* unit);
    void Clear();
    void MoveAllToTarget(Vector2 target);
    bool Empty() const;
    void SelectOne(BaseUnit* unit);
    
};
