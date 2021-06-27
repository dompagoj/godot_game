#pragma once
#include "Godot.hpp"
#include "ResourcePreloader.hpp"
#include "Macros.hpp"
#include "PackedScene.hpp"

using namespace godot;

class SceneLoader : public ResourcePreloader
{
 GODOT_CLASS(SceneLoader, ResourcePreloader)
 public:
    _REGISTER_METHODS()
    _READY()
    _INIT()

    PackedScene* GetResource(const String& path);
    static SceneLoader* It();

 private:
    static SceneLoader* Instance;


};
