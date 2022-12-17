#ifndef LIBS_TRANSIT_INCLUDE_IENTITY_H_
#define LIBS_TRANSIT_INCLUDE_IENTITY_H_

/**
* include
*/
#include <vector>

#include "../../routing/include/graph.h"
#include "math/vector3.h"
#include "util/json.h"
#include "IUpgradeable.h"

using namespace routing;

//--------------------  Controller Interface ----------------------------

/**
* @brief Abstract controller class used in the Transit Service. Uses the Model
* View Controller Pattern.
*/
class IEntity : public IUpgradeable {
 public:
    /**
    * @brief Constructor for the IEntity class; initializes counters for IDs for
    * entities and the experience counter.
    */
    IEntity() {
        static int currentId = 0;
        id = currentId;
        currentId++;
    }
    /**
    * @brief Destructor for the IEntity class; automatically deletes any
    * allocated variables.
    */
    virtual ~IEntity()
    {}
    /**
    * @brief Gets the ID of the entity.
    * @return An int of the ID of the entity.
    */
    virtual int GetId() const
    { return id; }
    /**
    * @brief Gets the position of the entity.
    * @return A Vector3 storing the position of the entity.
    */
    virtual Vector3 GetPosition() const = 0;
    /**
    * @brief Gets the direction of the entity.
    * @return A Vector3 storing the direction of the entity.
    */
    virtual Vector3 GetDirection() const = 0;
    /**
    * @brief Gets the destination of the entity.
    * @return A Vector3 of the destination of the entity.
    */
    virtual Vector3 GetDestination() const = 0;
    /**
    * @brief Gets the details of the entity.
    * @return A JsonObject of the details of the entity.
    */
    virtual JsonObject GetDetails() const = 0;
    /**
    * @brief Sets the details of the entity.
    * @param dets A JsonObject& variable storing the entity's new details.
    */
    virtual void SetDetails(JsonObject dets) = 0;


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"

    /**
    * @brief Gets the availability of the entity.
    * @return A bool of the entity's availability (true if available).
    */
    virtual bool GetAvailability() const
    {};


    /**
    * @brief Gets the strategy name used by the entity.
    * @return A string of the strategy name used by the entity.
    */
    virtual std::string GetStrategyName()
    {}
    /**
    * @brief Sets the availability of the entity.
    * @param choice A bool containing the entity's new availability (true if
    * available).
    */
    virtual void SetAvailability(bool choice)
    {}

#pragma GCC diagnostic pop

    /**
    * @brief Used to calculate the next position on an entity's path and move
    * that entity.
    * @param dt Stands for "delta time"; a double value used in the calculation
    * of the entity's next position.
    * @param scheduler An IEntity* vector storing certain entities of the
    * simulation.
    */
    virtual void Update(double dt, std::vector<IEntity*> scheduler) {
    }
    /**
    * @brief Sets the graph used by all children of this class.
    * @param graph An IGraph* object that contains the graph the child classes
    * will use.
    */
    void SetGraph(const IGraph* graph)
    { this->graph = graph; }
    /**
    * @brief Sets the position of the entity.
    * @param pos_ A Vector3 variable containing the entity's new position.
    */
    virtual void SetPosition(Vector3 pos_)
    {}
    /**
    * @brief Sets the direction of the entity.
    * @param dir_ A Vector3 variable containing the entity's new direction.
    */
    virtual void SetDirection(Vector3 dir_)
    {}
    /**
    * @brief Sets the destination of the entity.
    * @param des_ A Vector3 variable containing the entity's new destination.
    */
    virtual void SetDestination(Vector3 des_)
    {}
    /**
    * @brief Sets the stratergy name that will be used by the entity.
    * @param strategyName_ The new strategy name for the entity.
    */
    virtual void SetStrategyName(std::string strategyName_)
    {}
    /**
    * @brief Rotates the entity in the simulation.
    * @param angle A double value of the angle of the rotation.
    */
    virtual void Rotate(double angle)
    {}
    /**
    * @brief Causes the entity to jump up and down.
    * @param height A double value of the height the entity should jum to.
    */
    virtual void Jump(double height)
    {}

 protected:
    int id;
    const IGraph* graph;
};

#endif  // LIBS_TRANSIT_INCLUDE_IENTITY_H_
