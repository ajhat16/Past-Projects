
#ifndef LIBS_TRANSIT_INCLUDE_CELEBRATIONDECORATOR_H_
#define LIBS_TRANSIT_INCLUDE_CELEBRATIONDECORATOR_H_

/**
* include
*/
#include <vector>

#include "IStrategy.h"

/**
* @brief Inherits from the IStrategy class to implement a decorator to wrap
* around entities to make them celebrate.
*/
class CelebrationDecorator : public IStrategy {
 public:
  /**
  * @brief Constrcutor for the CelebrationDecorator class; initializes the
  * strategy and time it takes for the celebration.
  * @param strategy An IStrategy* used to initialize the strategy used to move
  * the entity.
  **/
  CelebrationDecorator(IStrategy *strategy_) {
    strategy = strategy_;
    time = 0;
  }

  /**
  * @brief Uses the strategy's movement pattern from the constructor to move the
  * entity.
  * @param entity An IEntity* containing the entity that will move.
  * @param dt Stands for "delta time"; used in the calculation of the next
  * position of the entiy.
  **/
  void Move(IEntity *entity, double dt);

  /**
  * @brief Checks to see if the celebration is completed by checking if the time
  * has reached/passed 1.5.
  * @return A bool of the result of the comparison mentioned in the function
  * description.
  **/
  bool IsCompleted();

 protected:
  IStrategy *strategy;
  float time;
};  // close class

#endif  // LIBS_TRANSIT_INCLUDE_CELEBRATIONDECORATOR_H_
