#ifndef HELICOPTERFACTORY_H_
#define HELICOPTERFACTORY_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Helicopter.h"

#include <vector>

class HelicopterFactory : public IEntityFactory {
 public:
  IEntity* CreateEntity(JsonObject& entity);
};

#endif