#ifndef LIBS_TRANSIT_INCLUDE_ROBOTFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_ROBOTFACTORY_H_

/**
* include
*/
#include "IEntity.h"
#include "IEntityFactory.h"
#include "Robot.h"

#include <vector>

/**
* @brief Inherits from the IEntityFactory class and is used in correspondence
* with the CompositeFactory class to create robot entities.
*/
class RobotFactory : public IEntityFactory {
 public:
    /**
    * @brief Used to create robot entities.
    * @param entity A JsonObject& storing the details of the robot entity.
    * @return An IEntity* of the newly created robot.
    **/
    IEntity* CreateEntity(const JsonObject& entity);
};

#endif  // LIBS_TRANSIT_INCLUDE_ROBOTFACTORY_H_
