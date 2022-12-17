#ifndef LIBS_TRANSIT_INCLUDE_SIMULATIONMODEL_H_
#define LIBS_TRANSIT_INCLUDE_SIMULATIONMODEL_H_

/**
* include
*/
#include "IController.h"
#include "CompositeFactory.h"
#include "IEntity.h"
#include "graph.h"
using namespace routing;

//--------------------  Model ----------------------------

/**
* @brief Simulation Model handling the transit simulation. The model can
* communicate with the controller.
*/
class SimulationModel {
 public:
  /**
  * @brief Constructor for the SimulationModel class; initializes teh controller
  * and creates all factories for entities.
  * @param controller An IController& object storing the controller for the
  * simulation.
  */
  SimulationModel(IController& controller);

  /**
  * @brief Sets the graph for the simulation model.
  * @param graph An IGraph* object used to set the graph of the simulation
  * model.
  */
  void SetGraph(const IGraph* graph) { this->graph = graph; }

  /**
  * @brief Creates a simulation entity.
  * @param entity A JsonObject& object whose components are used to make the
  * entities.
  */
  void CreateEntity(const JsonObject& entity);

  /**
  * @brief Schedules a trip for an object in the scene.
  * @param details A JsonObject& object storing the details of the trip.
  */
  void ScheduleTrip(const JsonObject& details);

  /**
  * @brief Updates the simulation.
  * @param dt Stands for "delta time"; used in the calculation of the entities'
  * update functions.
  */
  void Update(double dt);

  /**
  * @brief Adds a new entity type.
  * @param factory The IEntityFactory* object that will be added to the vector
  * of factories.
  */
  void AddFactory(IEntityFactory* factory);

 protected:
  IController& controller;
  std::vector<IEntity*> entities;
  std::vector<IEntity*> scheduler;
  const IGraph* graph;
  CompositeFactory* compFactory;
};

#endif  // LIBS_TRANSIT_INCLUDE_SIMULATIONMODEL_H_
