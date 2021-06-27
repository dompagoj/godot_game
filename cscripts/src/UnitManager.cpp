#include "UnitManager.hpp"
#include "string_view"


UnitManager* UnitManager::Instance = nullptr;

void UnitManager::_register_methods()
{
}

void UnitManager::_init()
{
    Loader = SceneLoader::It();
    Instance = this;
}


UnitManager* UnitManager::It()
{
    return Instance;
}
