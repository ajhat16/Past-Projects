#ifndef LIBS_TRANSIT_INCLUDE_DRONEFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_DRONEFACTORY_H_

/**
* include
*/
#include "IEntity.h"
#include "IEntityFactory.h"
#include "Drone.h"

#include <vector>

/**
* @brief Inherits from the IEntityFactory class and is used in correspondence
* with the CompositeFactory class to create drone entities.
*/
class DroneFactory : public IEntityFactory {
 public:
    /**
    * @brief Destructor for the DroneFactory class; automatically deletes any
    * allocated variables.
    **/
    virtual ~DroneFactory() {}

    /**
    * @brief Used to create drone entities.
    * @param entity A JsonObject& storing the details of the drone entity.
    * @return An IEntity* of the newly created drone.
    **/
    IEntity* CreateEntity(const JsonObject& entity);
};

#endif  // LIBS_TRANSIT_INCLUDE_DRONEFACTORY_H_
