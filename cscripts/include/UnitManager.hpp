#pragma once
#include "Prelude.hpp"
#include "Node.hpp"
#include "SceneLoader.hpp"
#include "cassert"
#include "Units/BaseUnit.hpp"
#include "Units/Marine.hpp"
#include "PackedScene.hpp"
#include "Ref.hpp"

#define TYPE_TO_STRING_SPECIFIC(TYPE, NAME) \
    static_assert(std::is_base_of<BaseUnit, TYPE>::value); \
    if (std::is_same<T, TYPE>::value) return #NAME;

#define TYPE_TO_STRING(TYPE) \
    TYPE_TO_STRING_SPECIFIC(TYPE, TYPE)

class UnitManager : public Node
{
 GODOT_CLASS(UnitManager, Node)

 public:
    _INIT()
    _REGISTER_METHODS()

    template<typename T>
    constexpr std::string_view ResolveName()
    {
        static_assert(std::is_base_of<BaseUnit, T>::value);
        TYPE_TO_STRING(Marine)
    }

    template<typename T>
    T* CreateUnit(Node* parent)
    {
        auto name = ResolveName<T>();
        static auto resource = Loader->GetResource(String(name.data()));

        auto unit = cast_to<T>(resource->instance());
        parent->add_child(unit);

        return unit;
    }
    static UnitManager* It();

 private:
    static UnitManager* Instance;
    SceneLoader* Loader;
};

#undef TYPE_TO_STRING
#undef TYPE_TO_STRING_SPECIFIC