#ifndef LIBS_TRANSIT_INCLUDE_BEELINESTRATEGY_H_
#define LIBS_TRANSIT_INCLUDE_BEELINESTRATEGY_H_

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
class BeelineStrategy : public IStrategy {
 public:
    /**
    * @brief The constructor for the BeelineStrategy class. This constructor is
    * used to initialize the current position of the entity as well as it's destination.
    * @param positon Initializes a private member variable for the entity's
    * position to the value of this argument.
    * @param destination Initializes a private member variable for the entity's
    * destination to the value of this argument.
    **/
    BeelineStrategy(Vector3 position, Vector3 destination);
    /**
    * @brief Destructor for the BeelineStrategy class: automatically deletes all
    * allocated variables in BeelineStrategy.
    **/
    ~BeelineStrategy();

    /**
    * @brief This function moves the entity along the path set in the
    * constructor of BeelineStrategy. The path is a straight line (hence
    * beeline) from the positon of the entity to the destination of the entity.
    * @param entity This variable is the entity that will be moving using the
    * Beeline Strategy.
    * @param dt This variable stands for "delta time" and is used in the
    * calculation of the next positon the entity should be at.
    **/
    void Move(IEntity* entity, double dt);

    /**
    * @brief Determines if the entity has completed its movement and reached its
    * destination by checking if the magnitude between the current position and
    * destination vectors is less that 1.0.
    * @return The result of the comparison mentioned above.
    **/
    bool IsCompleted();

 private:
    Vector3 position;
    Vector3 destination;
    float trip_dist;
};  // end class
#endif  // LIBS_TRANSIT_INCLUDE_BEELINESTRATEGY_H_
