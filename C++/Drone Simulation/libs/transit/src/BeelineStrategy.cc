#include "BeelineStrategy.h"

BeelineStrategy::BeelineStrategy(Vector3 position, Vector3 destination) {
    this->position = position;
    this->destination = destination;
    trip_dist = (destination - position).Magnitude();
    while (trip_dist >= 1.0) {
        trip_dist *= 0.1;
    }
}

bool BeelineStrategy::IsCompleted() {
    return (destination - position).Magnitude() < 1.0;
}

void BeelineStrategy::Move(IEntity* entity, double dt) {
    IStrategy::Move(entity, dt);
//    entity->AddXP(trip_dist);
	dynamic_cast<IUpgradeable*>(entity)->AddXP(trip_dist);

    position = entity->GetPosition();
    Vector3 dir = (destination - position).Unit();
    float speed = entity->GetSpeed();
    position = position + dir * speed * dt;
    entity->SetPosition(position);
    entity->SetDirection(dir);
}
