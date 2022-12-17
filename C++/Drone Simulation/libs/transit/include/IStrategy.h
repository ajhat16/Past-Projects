#ifndef LIBS_TRANSIT_INCLUDE_ISTRATEGY_H_
#define LIBS_TRANSIT_INCLUDE_ISTRATEGY_H_

/**
* include
*/
#include <vector>
#include "graph.h"
#include "IEntity.h"

using namespace routing;

/**
* @brief A class using the strategy design pattern to implement the movement for
* entities in the simulation.
*/
class IStrategy {
 public:
    /**
    * @brief Moves the entity using one of four movement strategies.
    * @param entity An IEntity* object which is the entity that will be moved.
    * @param dt Stands for "delta time"; a double variable used in the
    * calculation of the entity's next position.
    */
    virtual void Move(IEntity* entity, double dt) {}
    /**
    * @brief Checks if the movement of an entity has completed.
    * @return The result of a comparison between the entity's current position
    * and the destination.
    */
    virtual bool IsCompleted() = 0;
 protected:
    // IGraph object to be used in the simulation.
    const IGraph* graph;
};  // close class

#endif  // LIBS_TRANSIT_INCLUDE_ISTRATEGY_H_
