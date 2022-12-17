#ifndef LIBS_TRANSIT_INCLUDE_DRONE_H_
#define LIBS_TRANSIT_INCLUDE_DRONE_H_

/**
* include
*/
#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

/**
* @brief This class inherits from the IEntity class and is responsible for
* moving the physical drone entity around the simulation.
*/
class Drone : public IEntity {
 public:
  /**
  * @brief Constructor for the Drone class; initializes the drone's position,
  * direction, and speed as well as setting its availability to true so it may
  * pickup robots.
  * @param obj A JsonObject& variable storing the information listed in the
  * description for the function.
  **/
  Drone(const JsonObject& obj);

  /**
  * @brief Destructor for the Drone class; automatically deletes any
  * allocated variables.
  **/
  ~Drone();


  /**
  * @brief Used to get the current position of the drone entity on the map.
  * @return A Vector3 value of the current potion of the drone entity.
  **/
  Vector3 GetPosition() const { return position; }

  /**
  * @brief Used to get the current direction of the drone entity on the map.
  * @return A Vector3 value of the current direction of the drone entity.
  **/
  Vector3 GetDirection() const { return direction; }

  /**
  * @brief Used to get the current destination that the drone entity is trying
  * to reach.
  * @return A Vector3 value storing the current destination of the drone entity.
  **/
  Vector3 GetDestination() const { return destination; }

  /**
  * @brief Used to get all details of the drone entity, including position,
  * model, speed, etc.
  * @return A JsonObject value storing the details of the drone entity.
  **/
  JsonObject GetDetails() const { return details; }

  /**
  * @brief Used to set the details of the drone entity.
  * @param dets A JsonObject& variable storing the new details of the drone
  * entity.
  **/
  void SetDetails(JsonObject dets) { details = dets; }

  /**
  * @brief Used to get the drone's current availability in the simulation.
  * @return A bool of the drone's availability (true if available).
  **/
  bool GetAvailability() const { return available; }

  /**
  * @brief Loops through all robots in the simulation to determine which one is
  * the closest to the drone's current position. It also determines the movement
  * pattern the drone will use based on the user's choice in the scheduler.
  * @param scheduler An IEntity* vector containing all robot entities of the
  * simulation.
  **/
  void GetNearestEntity(std::vector<IEntity*> scheduler);

  /**
  * @brief Updates the drone's current position by first beelining to the robot,
  * then using the movement pattern determined in the GetNearestEntity()
  * function.
  * @param dt Stands for "delta time"; A double variable used in the calculation
  * of the drone's next position.
  * @param scheduler An IEntity* vector storing all robots currently in the
  * simulation.
  **/
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
  * @brief Used to set the new positon of the drone entity.
  * @param pos_ A Vector3 variable storing the new position for the drone
  * entity.
  **/
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
  * @brief Used to set the direction of the drone entity.
  * @param dir_ A Vector3 variable storing the new direction of the drone
  * entity.
  **/
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
  * @brief Used to set the new destination for the drone entity.
  * @param des_ A Vector3 variable storing the new destination of the drone
  * entity.
  **/
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
  * @brief Used to rotate the drone entity.
  * @param angle A double variable used in the calculation of the rotation.
  **/
  void Rotate(double angle);

  /**
  * @brief Used to make the drone entity jump.
  * @param height A double value storing the height the drone's jump.
  **/
  void Jump(double height);


	/**
  * @brief A copy constructor for the Drone class; Being deleted so the drone
  * cannot be copied.
  * @param drone The drone that would have been copied had the function not been
  * deleted.
  **/
  Drone(const Drone& drone) = delete;

  /**
  * @brief An override of the = operator; Being deleted so the drone cannot be
  * copied.
  * @param drone The drone that would have been copied had the function not been
  * deleted.
  **/
  Drone& operator=(const Drone& drone) = delete;


 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  float jumpHeight = 0;
  bool goUp = true;  // jump helper
  Vector3 destination;
  bool available;
  bool pickedUp;
  std::string strategyName;
  IEntity* nearestEntity = NULL;
  IStrategy* toTargetPosStrategy = NULL;
  IStrategy* toTargetDestStrategy = NULL;
};

#endif  // LIBS_TRANSIT_INCLUDE_DRONE_H_
