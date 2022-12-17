#ifndef LIBS_TRANSIT_INCLUDE_CARFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_CARFACTORY_H_

/**
* include
*/
#include "IEntity.h"
#include "IEntityFactory.h"
#include "Car.h"

#include <vector>

/**
* @brief This class inherits from the IEntityFactory class and is used in the
* creation of car entities.
*/
class CarFactory : public IEntityFactory {
 public:
    /**
    * @brief Destructor for the CarFactory class; automatically deletes
    * allocated vairables.
    **/
    virtual ~CarFactory() {}

    /**
    * @brief The function that creates the car entities.
    * @param entity A JsonObject& storing the information about the car entity,
    * namely the type, which is used to make the entity.
    **/
    IEntity* CreateEntity(const JsonObject& entity);
};

#endif  // LIBS_TRANSIT_INCLUDE_CARFACTORY_H_
