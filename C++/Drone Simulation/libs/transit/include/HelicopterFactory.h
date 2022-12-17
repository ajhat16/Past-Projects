#ifndef LIBS_TRANSIT_INCLUDE_HELICOPTERFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_HELICOPTERFACTORY_H_

/**
* include
*/
#include "IEntity.h"
#include "IEntityFactory.h"
#include "Helicopter.h"

#include <vector>

/**
* @brief This class inherits from the IEntityFactory class and is used in the
* creation of helicopter entities.
*/
class HelicopterFactory : public IEntityFactory {
 public:
    /**
    * @brief Destructor for the HelicopterFactory class; automatically deletes
    * allocated vairables.
    **/
    virtual ~HelicopterFactory() {}

    /**
    * @brief The function that creates the helicopter entities.
    * @param entity A JsonObject& storing the information about the helicopter
    * entity, namely the type, which is used to make the entity.
    **/
    IEntity* CreateEntity(const JsonObject& entity);
};

#endif  // LIBS_TRANSIT_INCLUDE_HELICOPTERFACTORY_H_
