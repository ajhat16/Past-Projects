#define _USE_MATH_DEFINES
#include "Helicopter.h"
#include "BeelineStrategy.h"

#include <cmath>
#include <limits>
#include <cstdlib>
#include <time.h>

Helicopter::Helicopter(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};

  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  CalcAndSetDestination();

}

Helicopter::~Helicopter() {

}

void Helicopter::CalcAndSetDestination() {
  int rand_x, rand_z;
  srand(time(0));
  rand_x = rand() % 1500;
  rand_x = rand_x - (rand() % 1400);
  rand_z = rand() % 800;
  rand_z = rand_z - (rand() % 800);
  SetDestination(Vector3(rand_x, 400, rand_z));
  destination_set = true;
  
}

void Helicopter::Update(double dt, std::vector<IEntity*> scheduler) {
  if (!destination_set) {
    CalcAndSetDestination();
  }
  
  if (toDestination != NULL) {
    toDestination->Move(this, dt);
    
    if(toDestination->IsCompleted()){
      delete toDestination;
      toDestination = NULL;
      destination_set = false;
    }  
  } else {
      toDestination = new BeelineStrategy(position, destination);
  }
}