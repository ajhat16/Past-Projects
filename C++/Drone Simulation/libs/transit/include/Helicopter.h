#ifndef LIBS_TRANSIT_INCLUDE_HELICOPTER_H_
#define LIBS_TRANSIT_INCLUDE_HELICOPTER_H_

/**
* include
*/
#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"
#include "IStrategy.h"

/**
* @brief Inherits from the IEntity class and is used in the position and
* movement of the helicopter entities.
**/
class Helicopter : public IEntity {
 public:
    /**
    * @brief Constructor for the Helicopter class; initializes the position,
    * direction, and speed of the helicopter entity, as well as calculating the
    * helicopter's destination.
    * @param obj A JsonObject& variable containing the details mentioned in the
    * description for the function (except for the destination).
    **/
    Helicopter(const JsonObject& obj);

    /**
    * @brief Destructor for the Helicopter class; automatically deletes any
    * allocated variables.
    **/
    ~Helicopter() override = default;

    /**
    * @brief Used to get the current position of the helicopter entity.
    * @return A Vector3 variable containing the helicopter's current position.
    **/
    Vector3 GetPosition() const
    { return position; }

    /**
    * @brief Used to get the direction of the helicopter entity.
    * @return A Vector3 variable storing the direction of the helicopter entity.
    **/
    Vector3 GetDirection() const
    { return direction; }

    /**
    * @brief Used to get the current destination that the helicopter entity is
    * trying to reach.
    * @return A Vector3 value storing the current destination of the helicopter
    * entity.
    **/
    Vector3 GetDestination() const
    { return destination; }

    /**
    * @brief Used to get all details of the helicopter entity, including
    *position, model, speed, etc.
    * @return A JsonObject value storing the details of the helicopter entity.
    **/
    JsonObject GetDetails() const override;

    /**
    * @brief Used to set the details of the helicopter entity.
    * @param dets A JsonObject& variable storing the new details of the
    *helicopter entity.
    **/
    void SetDetails(JsonObject dets)
    { details = dets; }

    /**
    * @brief Used to set the new positon of the helicopter entity.
    * @param pos_ A Vector3 variable storing the new position for the helicopter
    *entity.
    **/
    void SetPosition(Vector3 pos_)
    { position = pos_; }

    /**
    * @brief Used to set the direction of the helicopter entity.
    * @param dir_ A Vector3 variable storing the new direction of the helicopter
    *entity.
    **/
    void SetDirection(Vector3 dir_)
    { direction = dir_; }

    /**
    * @brief Used to set the new destination for the helicopter entity.
    * @param des_ A Vector3 variable storing the new destination of the
    *helicopter entity.
    **/
    void SetDestination(Vector3 des_)
    { destination = des_; }

    /**
    * @brief Used to rotate the helicopter entity.
    * @param angle A double variable used in the calculation of the rotation.
    **/
    void Rotate(double angle);

    /**
    * @brief The movement function for the helicopter entity; updates the
    *position and moves the helicopter using the beeline strategy.
    * @param dt Stands for "delta time"; used in the calculation of the
    *helicopter's next position.
    * @param scheduler Unused in this function but it is a parameter for
    *inheritence reasons from the IEntity class.
    **/
    void Update(double dt, std::vector<IEntity*> scheduler);

    /**
    * @brief A function to calculate the random destination that the helicopter
    *will use.
    * @param Min A float for the minimum value that the random number can be for
    *the destination (either in the x or z axis).
    * @param Max A float for the maximum value that the random number can be for
    *the destination (either in the x or z axis).
    * @return A float value of the randomly generated number (either in the x or
    *z axis).
    **/
    float Random(float Min, float Max);

    /**
    * @brief Calls the function Random() and sets the destination according to
    *what that function returned for the x and z axis.
    **/
    void SetNewDestination();


 private:
    JsonObject details;
    Vector3    position;
    Vector3    direction;
    Vector3    destination;
    IStrategy* strategy = NULL;
};

#endif  // LIBS_TRANSIT_INCLUDE_HELICOPTER_H_
