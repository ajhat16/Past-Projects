#ifndef CAR_H_
#define CAR_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

class Car : public IEntity {
 public:
  Car(JsonObject& obj);

  ~Car();

  float GetSpeed() const { return speed; }

  Vector3 GetPosition() const { return position; }

  Vector3 GetDirection() const { return direction; }

  Vector3 GetDestination() const { return destination; }

  JsonObject GetDetails() const { return details; }

  void Update(double dt, std::vector<IEntity*> scheduler);

  void SetPosition(Vector3 pos_) { position = pos_; }

  void SetDirection(Vector3 dir_) { direction = dir_; }

  void CalcAndSetDestination();

  void SetDestination(Vector3 des_) { destination = des_; }

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  float speed;
  bool destination_set;
  IStrategy* toDestination = NULL;
};

#endif