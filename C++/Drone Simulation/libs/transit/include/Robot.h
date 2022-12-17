#ifndef LIBS_TRANSIT_INCLUDE_ROBOT_H_
#define LIBS_TRANSIT_INCLUDE_ROBOT_H_

/**
* include
*/
#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

/**
* @brief This class inherits from the IEntity class and is responsible for
* moving the physical robot entity around the simulation.
*/
class Robot : public IEntity {
 public:
  /**
  * @brief Constructor for the Robot class; initializes the robot's position,
  * direction, and speed as well as setting its availability to true so it may pickup robots.
  * @param obj A JsonObject& variable storing the information listed in the
  * description for the function.
  **/
  Robot(const JsonObject& obj);

  /**
  * @brief Destructor for the Robot class; automatically deletes any allocated
  * variables.
  **/
  ~Robot() override = default;

  /**
  * @brief Used to get the current position of the robot entity on the map.
  * @return A Vector3 value of the current potion of the robot entity.
  **/
  Vector3 GetPosition() const { return position; }

  /**
  * @brief Used to get the current direction of the robot entity on the map.
  * @return A Vector3 value of the current direction of the robot entity.
  **/
  Vector3 GetDirection() const { return direction; }

  /**
  * @brief Used to get the current destination that the robot entity is trying
  * to reach.
  * @return A Vector3 value storing the current destination of the robot entity.
  **/
  Vector3 GetDestination() const { return destination; }

  /**
  * @brief Used to get the robot's current availability in the simulation.
  * @return A bool of the robot's availability (true if available).
  **/
  bool GetAvailability() const { return available; }

  /**
  * @brief Used to get all details of the robot entity, including position,
  * model, speed, etc.
  * @return A JsonObject value storing the details of the robot entity.
  **/
  JsonObject GetDetails() const override;

  /**
  * @brief Used to set the details of the robot entity.
  * @param dets A JsonObject& variable storing the new details of the robot
  * entity.
  **/
  void SetDetails(JsonObject dets) { details = dets; }

  /**
  * @brief It gets the strategy name which is a string.
  * @return It returns the strategy name.
  */
  std::string GetStrategyName() {return strategyName;}

  /**
  * @brief Sets the availability of a robot (true if available).
  * @param choice A bool storing the new availability of the robot.
  */
  void SetAvailability(bool choice);

  /**
  * @brief Used to set the new positon of the robot entity.
  * @param pos_ A Vector3 variable storing the new position for the robot
  * entity.
  **/
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
  * @brief Used to set the direction of the robot entity.
  * @param dir_ A Vector3 variable storing the new direction of the robot
  * entity.
  **/
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
  * @brief Used to set the new destination for the robot entity.
  * @param des_ A Vector3 variable storing the new destination of the robot
  * entity.
  **/
  void SetDestination(Vector3 des_) { destination = des_; }
  /**
  * @brief It sets the strategy  name.
  * @param strategyName_ take in this string containing the strategy name.
  */
  void SetStrategyName(std::string strategyName_)
  { strategyName = strategyName_; }


  /**
  * @brief Used to rotate the robot entity.
  * @param angle A double variable used in the calculation of the rotation.
  **/
  void Rotate(double angle);

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  bool available;
  std::string strategyName;
};

#endif  // LIBS_TRANSIT_INCLUDE_ROBOT_H_
