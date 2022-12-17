#ifndef LIBS_TRANSIT_INCLUDE_ASTARSTRATEGY_H_
#define LIBS_TRANSIT_INCLUDE_ASTARSTRATEGY_H_

/**
 * include
 */
#include "math/vector3.h"
#include <vector>
#include "IStrategy.h"
#include "IEntity.h"
/**
 * @brief this class inhertis from the IStrategy class and is responsible for
 * generating the beeline that the drone will take.
 */
class AstarStrategy : public IStrategy {
 public:
    /**
    * @brief The constructor for the AstarStrategy class. This constructor
    * initializes the value for graph, and maps out the path for the entity
    * using the position and destination parameters.
    * @param positon Gets convereted into an actual vector where it is then used
    * to set the starting position of the path that will be generated using the
    * graph.
    * @param destination Gets converted into an actual vector where it is then
    * used to set the final destination of the path that will be generated using
    * the graph.
    * @param graph Used along with position and destination to create the
    * movement path for the entity to follow.
    **/
    AstarStrategy(Vector3 position, Vector3 destination, const IGraph* graph);

    /**
    * @brief Destructor for the AstarStrategy class: automatically deletes all
    * allocated variables in AstarStrategy.
    **/
    ~AstarStrategy();

    /**
    * @brief This function moves the entity along the path set in the
    * constructor of AstarStrategy. The path is made up of nodes, so after a
    * node is reached, the function automatically switches to the next node
    * until the entity reaches its destination (the last node).
    * @param entity This is the entity that will be moving using the Astar
    * Strategy.
    * @param dt This variable stands for "delta time" and is used in the
    * calculation of the next positon the entity should be at.
    **/
    void Move(IEntity* entity, double dt);

    /**
    * @brief Determines if the entity has completed its movement and reached its
    * destination by comparing two private member variables used to track where
    * in the path the entity is.
    * @return The result of the comparison mentioned above.
    **/
    bool IsCompleted();

 private:
    std::vector<std::vector<float>> path;
    int currentIndex;
    int maxIndex;
};  // end class
#endif  // LIBS_TRANSIT_INCLUDE_ASTARSTRATEGY_H_
