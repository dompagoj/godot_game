#pragma once
#include "BaseUnit.hpp"
#include "Macros.hpp"
#include "InputEvent.hpp"

class Marine : public BaseUnit
{
 GODOT_CLASS(Marine, BaseUnit)

 public:
    _REGISTER_METHODS()
    Marine();
};
