#ifndef LIBS_TRANSIT_INCLUDE_SPINDECORATOR_H_
#define LIBS_TRANSIT_INCLUDE_SPINDECORATOR_H_

/**
* include
*/
#include <vector>

#include "CelebrationDecorator.h"
#include "IStrategy.h"

/**
* @brief Inherits from the CelebrationDecorator class to create a class entities
* can use to spin.
*/
class SpinDecorator : public CelebrationDecorator {
 public:
  /**
  * @brief Constructor for the SpinDecorator class; calls the
  * CelebrationDecorator constructor to initialize protected variables.
  * @param strategy_ IStrategy* object used to determine the movement strategy
  * to wrap the decorator around.
  */
  SpinDecorator(IStrategy* strategy_) : CelebrationDecorator(strategy_) {}
  /**
  * @brief Checks if the spinning motion is completed by comparing the current
  * time to the time that has passed since the animitation started.
  * @return The result of the comparison mentioned in the function description.
  */
  bool IsCompleted();
  /**
  * @brief Moves the entity using the strategy from the constructor and spins
  * when the movement is complete.
  * @param entity An IEntity* object of the entity to move and do the spin
  * animation on.
  * @param dt Stands for "delta time"; used in the calculation of the entity's
  * next position.
  */
  void Move(IEntity* entity, double dt);
};  // close class

#endif  // LIBS_TRANSIT_INCLUDE_SPINDECORATOR_H_
