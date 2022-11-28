#include "GhostFactory.h"

IEntity* GhostFactory::CreateEntity(JsonObject& entity){
  std::string type = entity["type"];
  if(type.compare("ghost") == 0){
    std::cout << "Ghost Created" << std::endl;
    return new Ghost(entity);
  }
  return nullptr;
}