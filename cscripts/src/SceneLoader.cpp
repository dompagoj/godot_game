#include "SceneLoader.hpp"

SceneLoader* SceneLoader::Instance = nullptr;

void SceneLoader::_register_methods()
{
}

void SceneLoader::_init()
{
    Instance = this;
}

SceneLoader* SceneLoader::It()
{
    return Instance;
}

PackedScene* SceneLoader::GetResource(const String& path)
{
    Ref<PackedScene> scene = get_resource("Marine");

    return scene.ptr();
}
