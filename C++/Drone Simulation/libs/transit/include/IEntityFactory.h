#ifndef LIBS_TRANSIT_INCLUDE_IENTITYFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_IENTITYFACTORY_H_

/**
* include
*/
#include "util/json.h"

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Drone.h"

/**
* @brief A class used to create entity's using the AbstractFactory design
* pattern.
*/
class IEntityFactory {
 public:
    /**
    * @brief Destructor for the IEntityFactory class; automatically deletes any
    * allocated variables.
    */
    virtual ~IEntityFactory() {}
    /**
    * @brief A function used in the creation of all entities in the factory.
    * @param entity A JsonObject& variable containing the details, namely the
    * type, used to create the new entity.
    * @return An IEntit* object of the newly created entity.
    */
    virtual IEntity* CreateEntity(const JsonObject& entity) = 0;
};

#endif  // LIBS_TRANSIT_INCLUDE_IENTITYFACTORY_H_
