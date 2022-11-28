#ifndef CARFACTORY_H_
#define CARFACTORY_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Car.h"

#include <vector>

class CarFactory : public IEntityFactory {
 public:
  IEntity* CreateEntity(JsonObject& entity);
};

#endif