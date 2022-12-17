#ifndef LIBS_TRANSIT_INCLUDE_ICONTROLLER_H_
#define LIBS_TRANSIT_INCLUDE_ICONTROLLER_H_

/**
* include
*/
#include "IEntity.h"
#include "util/json.h"

//--------------------  Controller Interface ----------------------------

/**
* @brief Abstract controller class used in the Transit Service. Uses the Model
* View Controller Pattern.
**/
class IController {
 public:
  /**
  * @brief Destructor for the IController class; automatically deletes any
  * allocated variables.
  **/
  virtual ~IController() {}
  /**
  * @brief Adds an entity to the program.
  * @param entity An IEntity& object for entity that will be added to the
  * program.
  **/
  virtual void AddEntity(const IEntity& entity) = 0;
  /**
  * @brief Updates an entity within the program.
  * @param entity An IEntity& object for entity that will be updated in the
  * program.
  **/
  virtual void UpdateEntity(const IEntity& entity) = 0;
  /**
  * @brief Removes an entity from the program.
  * @param id An int of the id of the entity that will be removed.
  **/
  virtual void RemoveEntity(int id) = 0;
  /**
  * @brief Adds a path to the program.
  * @param id An int of the id of the path that will be added.
  * @param path A vector containing vectors of nodes, where the nodes combined
  * create a path.
  */
  virtual void AddPath(int id,
                       const std::vector<std::vector<float> >& path) = 0;
  /**
  * @brief Removes a path from the program.
  * @param id An int containing the id of th path that will be removed.
  */
  virtual void RemovePath(int id) = 0;
  /**
  * @brief Allows messages to be passed back to view.
  * @param event A string& of the event that will be passed.
  * @param details A JsonObject& of the details of the event that will be passed
  * to view.
  */
  virtual void SendEventToView(const std::string& event,
                               const JsonObject& details) = 0;
};

#endif  // LIBS_TRANSIT_INCLUDE_ICONTROLLER_H_
