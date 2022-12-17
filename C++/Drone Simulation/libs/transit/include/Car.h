#ifndef LIBS_TRANSIT_INCLUDE_CAR_H_
#define LIBS_TRANSIT_INCLUDE_CAR_H_

/**
 * include
 */
#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"
#include "IStrategy.h"
#include "IUpgradeable.h"

/**
* @brief This class inherits from the IEntity class and is responsible for
* creating and navigating a car entity that moves around the simulation and
* updates its position in real time.
**/
class Car : public IEntity {
 public:
  /**
  * @brief Constructor for the Car class. Initializes certain properties of the
  * car such as position, speed, direction, and destination.
  * @param obj This parameter is used to initialize the properties of the car
  * mentioned above, except for the destination.
  **/
  Car(const JsonObject& obj);

  /**
  * @brief Destructor for the car class: automatically deletes any allocated
  * variables.
  **/
  ~Car() override = default;

  /**
  * @brief This function is used to give the position of the car entity.
  * @return The Vector3 value of the position of the car entity.
  **/
  Vector3 GetPosition() const { return position; }

  /**
  * @brief This function is used to give the direction of the car entity.
  * @return The Vector3 value of the direction of the car entity.
  **/
  Vector3 GetDirection() const { return direction; }

  /**
  * @brief This function is used to give the destination of the car entity.
  * @return The Vector3 value of the destination of the car entity.
  **/
  Vector3 GetDestination() const { return destination; }

  /**
  * @brief This function is used to give the details/properties of the car
  * entity.
  * @return The JsonObject of the details/properties of the car entity.
  **/
  JsonObject GetDetails() const override;

  /**
  * @brief This function is used to change the details/properties of the car
  * entity.
  * @param dets A JsonObject variable that should store the new
  * details/properties of the car entity.
  **/
  void SetDetails(JsonObject dets) { details = dets; }


  /**
  * @brief Sets the position of the car entity.
  * @param pos_ A Vector3 variable storing the new position that the car will
  * use.
  **/
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
  * @brief Sets the direction of the car entity.
  * @param dir_ A Vector3 variable storing the new direction that the car will
  * use.
  **/
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
  * @brief Sets the destination of the car entity.
  * @param des_ A Vector3 variable storing the new destination that the car will
  * use.
  **/
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
  * @brief A function used to rotate the car entity.
  * @param angle A double variable of the angle used to calculate the rotation
  * of the car.
  **/
  void Rotate(double angle);

  /**
  * @brief The movement function for the car entity; updates the position and
  * moves the car using the Astar strategy.
  * @param dt Stands for "delta time"; used in the calculation of the car's next
  * position.
  * @param scheduler Unused in this function but it is a parameter for
  * inheritence reasons from the IEntity class.
  **/
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
  * @brief A function to calculate the random destination that the car will use.
  * @param Min A float for the minimum value that the random number can be for
  * the destination (either in the x or z axis).
  * @param Max A float for the maximum value that the random number can be for
  * the destination (either in the x or z axis).
  * @return A float value of the randomly generated number (either in the x or z
  * axis).
  **/
  float Random(float Min, float Max);

  /**
  * @brief Calls the function Random() and sets the destination according to
  * what that function returned for the x and z axis.
  **/
  void SetNewDestination();


 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  IStrategy* strategy = NULL;
};

#endif  // LIBS_TRANSIT_INCLUDE_CAR_H_
