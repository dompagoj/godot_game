#include "UnitSelection.hpp"


void UnitSelection::AddUnit(BaseUnit* unit)
{
    Units.push_back(unit);
}

void UnitSelection::Clear()
{
    Units.clear();
}

void UnitSelection::MoveAllToTarget(Vector2 target)
{
    for (auto const unit : Units)
    {
        unit->Move(target);
    }
}

bool UnitSelection::Empty() const
{
    return Units.empty();
}

void UnitSelection::SelectOne(BaseUnit* unit)
{
    Clear();
    AddUnit(unit);
}
