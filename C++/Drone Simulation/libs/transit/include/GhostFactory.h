#ifndef GHOSTFACTORY_H_
#define GHOSTFACTORY_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Ghost.h"

#include <vector>

class GhostFactory : public IEntityFactory {
 public:
  IEntity* CreateEntity(JsonObject& entity);
};

#endif