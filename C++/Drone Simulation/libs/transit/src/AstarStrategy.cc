#include "AstarStrategy.h"
#include "routing/astar.h"
#include "routing_api.h"
#include "graph.h"
#include "Car.h"
using namespace routing;

AstarStrategy::AstarStrategy(Vector3 position,
                             Vector3 destination, const IGraph* graph) {
    this->graph = graph;

    std::vector<float> positionV;
    positionV.push_back(position.x);
    positionV.push_back(position.y);
    positionV.push_back(position.z);

    std::vector<float> destinationV;
    destinationV.push_back(destination.x);
    destinationV.push_back(destination.y);
    destinationV.push_back(destination.z);

    std::vector<float> start = graph->NearestNode(positionV,
                                            EuclideanDistance())->GetPosition();
    std::vector<float> end = graph->NearestNode(destinationV,
                                            EuclideanDistance())->GetPosition();

    path = graph->GetPath(start, end, AStar::Default());
    currentIndex = 0;
    maxIndex = path.size() - 1;
}

bool AstarStrategy::IsCompleted() {
    return currentIndex == maxIndex;
}

void AstarStrategy::Move(IEntity* entity, double dt) {
    IStrategy::Move(entity, dt);
//    entity->AddXP(maxIndex * 0.01);
	dynamic_cast<IUpgradeable*>(entity)->AddXP(maxIndex*0.01);

    Vector3 currentPos = entity->GetPosition();
    Vector3 destination = Vector3(path[currentIndex].at(0),
                                  path[currentIndex].at(1),
                                  path[currentIndex].at(2));
    Vector3 direction = (destination - currentPos).Unit();
    float speed = entity->GetSpeed();
    currentPos = currentPos + direction * speed * dt;
    entity->SetPosition(currentPos);
    entity->SetDirection(direction);

    if ((destination - currentPos).Magnitude() < 1.0) {
        currentIndex++;
    }
}
