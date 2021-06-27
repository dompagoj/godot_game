#include "Units/Marine.hpp"


void Marine::_register_methods()
{
    BaseUnit::_register_methods();
}
Marine::Marine() : BaseUnit(BaseSpeed)
{
}
