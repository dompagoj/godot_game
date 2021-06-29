#include "Game.hpp"
#include "MyCamera.hpp"
#include "Units/Marine.hpp"
#include <Godot.hpp>
#include <SceneLoader.hpp>
#include <UnitManager.hpp>

using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o)
{
    Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o)
{
    Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle)
{
    Godot::nativescript_init(handle);
    register_class<BaseUnit>();
    register_class<Marine>();
    register_class<Game>();
    register_class<SceneLoader>();
    register_class<UnitManager>();
    register_class<MyCamera>();
}