//
// Created by Deci on 12/16/2022.
//
#ifndef LIBS_TRANSIT_INCLUDE_IUPGRADEABLE_H_
#define LIBS_TRANSIT_INCLUDE_IUPGRADEABLE_H_
#include <string>

constexpr float XP_GOAL = 3500.0f;
const char COLOR_DEFAULT[] = "None";
constexpr float SPEED_DEFAULT = 50.0f;

class IUpgradeable {
 public:
    /**
    * @brief This function is used to get the current speed of the entity.
    * @return A float of the current speed of the entity.
    */
    float GetSpeed() const { return speed; }

    /**
    * @brief Sets the speed of
    * @param f A float containing the value that the speed will be set to.
    * @return A float value of the speed that the entity was just set to.
    **/
    float SetSpeed(float f) { return speed = f; }


    /**
    * @brief A function to get the original speed
    * @return A float of the original speed
    **/
    virtual float GetOriginalSpeed() const { return SPEED_DEFAULT; }

    /**
    * @brief Adds xp for the user.
    * @param f is a float that holds the multiplier for the xp.
    * @return we return the xp as it's updating getting more points.
    **/
    float AddXP(float f) {
        xp += f;
        total_xp += f;
        return xp;
    }
    /**
    * @brief Calls on the GetGoal and checks whether xp is at the goal.
    * @return returns true if xp is greater than or equal to goal.
    */
    bool AtGoal() { return xp >= GetGoal(); }
    /**
     * @brief Gets the xp.
     * @return returns the xp.
     */
    float GetXP() { return xp; }

    /**
     * @brief Decrements the XP by the goal amount when the XP is spent on an
     * upgrade.
     * @return The new XP value after the XP has been spent.
     */
    float UpgradeAdded() { return xp -= GetGoal(); }
    /**
     * @brief This function gets the goal.
     * @return It gives back and returns the goal for xp.
     */
    float GetGoal() { return goal; }
    /**
    * @brief Refunds all spent XP when the upgrades are reset.
    * @return The XP after the calculated refund.
    */
    float RefundXP() { return xp = total_xp; }
    /**
    * @brief Gets the color of the car; "None" by default.
    * @return The color of the entity
    */
    std::string GetColor() const { return color; }
    /**
    * @brief Sets the color of the entity in a CSS style.
    * @param col_ The new color the entity will be set to.
    */
    void SetColor(std::string col_) { color = col_; }

 protected:
    std::string color = COLOR_DEFAULT;
    float goal = XP_GOAL;
    float total_xp = 0.0;
    float xp = 0.0;
    float speed;
};

#endif  // LIBS_TRANSIT_INCLUDE_IUPGRADEABLE_H_
