#ifndef LIBS_TRANSIT_INCLUDE_COMPOSITEFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_COMPOSITEFACTORY_H_

/**
* include
*/
#include "IEntityFactory.h"

/**
* @brief Inherits from the IEntityFactory class; Calls all other factories to
* create the entities of the simulation.
**/
class CompositeFactory : public IEntityFactory {
 public:
    /**
    * @brief Loops through an vector of factories to create all entities listed
    * in that vector that match the type in the parameter.
    * @param entity A JsonObject& variable storing the type of the entity to be
    * created.
    * @return The entity that was created based on the parameter and factory
    * vector.
    **/
    IEntity* CreateEntity(const JsonObject& entity);

    /**
    * @brief Adds factories to the factory vector.
    * @param factoryEntity An IEntityFactory variable that will be added to the
    * vector of factories.
    **/
    void AddFactory(IEntityFactory* factoryEntity);

    /**
    * @brief Destructor for the CompositeFactory class; automatically deletes
    * any allocated variabled.
    **/
    virtual ~CompositeFactory();

 private:
    std::vector<IEntityFactory*> componentFactories;
};

#endif  // LIBS_TRANSIT_INCLUDE_COMPOSITEFACTORY_H_
