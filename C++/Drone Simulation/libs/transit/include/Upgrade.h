#ifndef LIBS_TRANSIT_INCLUDE_UPGRADE_H_
#define LIBS_TRANSIT_INCLUDE_UPGRADE_H_

/**
* include
*/
#include "IEntity.h"
#include "../../../libs/util/include/xutil.h"
#include <string>

/**
* @enum UpgradeId
* @brief Used to store the chosen Upgrade ID by the user.
*/
enum class UpgradeId {
    /**
    * @var UpgradeId::NONE
    * No upgrade has been selected.
    */
    NONE  = -1,

    /**
    * @var UpgradeId::SPEED
    * The speed upgrade has been selected.
    */
    SPEED = 1,

    /**
    * @var UpgradeId::COLOR
    * The color upgrade has been selected.
    */
    COLOR  = 2,
};


/**
* @enum ColorId
* @brief Used to store the chosen color ID by the user.
*/
enum class ColorId {
    /**
    * @var ColorId::NONE
    * No color has been selected.
    */
    NONE  = -1,

    /**
    * @var colorId::BLACK
    * The color black has been selected.
    */
    BLACK = 1,

	/**
    * @var colorId::RED
    * The color red has been selected.
    */
    RED = 2,

	/**
    * @var colorId::ORANGE
    * The color orange has been selected.
    */
    ORANGE = 3,

	/**
    * @var colorId::YELLOW
    * The color yellow has been selected.
    */
    YELLOW = 4,

	/**
    * @var colorId::GREEN
    * The color green has been selected.
    */
    GREEN = 5,

	/**
    * @var colorId::BLUE
    * The color blue has been selected.
    */
    BLUE = 6,

	/**
    * @var colorId::PURPLE
    * The color purple has been selected.
    */
    PURPLE = 7,
};


constexpr const char* KEY_TYPE   = "type";
constexpr const char* KEY_ENTITY = "entity";
constexpr const char* KEY_VALUE  = "value";

/**
* @brief The Upgrade class uses the Adapter pattern and upgrades entities based
* on the user's choice in the simulation.
*/
class Upgrade {
 private:
    Upgrade(int eid, UpgradeId id, float val = 0.0,
            ColorId color = ColorId::NONE)
            : m_eid(eid), m_id(id), m_color(color), m_value(val) {}

    Upgrade(JsonValue type, JsonValue entity, JsonValue value)
            : Upgrade(static_cast<int>(entity),
                      static_cast<UpgradeId>(static_cast<int>(type)),
                      static_cast<float>(value),
                      static_cast<ColorId>(static_cast<int>(value))) {}

 public:
    /**
    * @brief Constructor for the Upgrade class; initializes various values used
    * throughout the simulation including the entity and the upgrade.
    * @param data A JsonObject& object that stores the information stated in the
    * description of this function.
    */
    Upgrade(JsonObject data)
            : Upgrade(data[KEY_TYPE], data[KEY_ENTITY], data[KEY_VALUE]) {}

    /**
    * @brief Gets the ID of the entity that will be upgraded.
    * @return An int value of the entity's ID.
    */
    inline int GetEId() const {
        return m_eid;
    }

    /**
    * @brief Gets the ID of the upgrade that will be applied to the entity.
    * @return An UpgradeId enum value of the upgrade ID that will be applied to
    * the entity.
    */
    inline UpgradeId GetId() const {
        return m_id;
    }

    /**
    * @brief Gets the user chosen value for the speed upgrade (if applicable).
    * @return A float of the user chosen speed for the upgrade.
    */
    inline float GetValue() const {
        return m_value;
    }

    /**
    * @brief Gets the user chosen color for the color upgrade (if applicable).
    * @return A ColorId enum value of the chosen color for the color upgrade.
    */
    inline ColorId GetColorId() const {
        return m_color;
    }

    /**
    * @brief Called if the "Reset Upgrade" button is pressed in the simulation;
    * resets all upgrades back to their original values.
    * @param ent An IEntity* object of the entity the upgrades should be reset
    * for.
    */
    inline void ResetUpgrade(IEntity* ent) {
        ent->RefundXP();

        printf("Upgrades reset\n");
        printf("XP spent on upgrades refunded\n");
        std::cout << "Current XP: " << ent->GetXP() << std::endl << std::endl;
        ent->SetSpeed(ent->GetOriginalSpeed());
        ent->SetColor("None");
    }

    /**
    * @brief Applies the upgrade to the chosen entity.
    * @param ent An IEntity* object of the entity that will be upgraded.
    */
    inline void ApplyUpgrade(IEntity* ent) {
        if (!ent->AtGoal()) {
            printf("XP goal not yet reached\n");
            std::cout << "Current XP: " << ent->GetXP() << std::endl;
            std::cout << "Required XP: " << ent->GetGoal() << std::endl;
            return;
        }
        switch (m_id) {
            case UpgradeId::SPEED: {
                float newSpeed = ent->GetSpeed() + m_value;
                auto  oldSpeed = ent->SetSpeed(newSpeed);
                printf("%F -> set speed to %F\n", oldSpeed, newSpeed);
                break;
            }
            case UpgradeId::COLOR: {
                switch (m_color) {
                    case ColorId::BLACK: {
                        ent->SetColor("black");
                        break;
                    }
                    case ColorId::RED: {
                        ent->SetColor("red");
                        break;
                    }
                    case ColorId::ORANGE: {
                        ent->SetColor("orange");
                        break;
                    }
                    case ColorId::YELLOW: {
                        ent->SetColor("yellow");
                        break;
                    }
                    case ColorId::GREEN: {
                        ent->SetColor("green");
                        break;
                    }
                    case ColorId::BLUE: {
                        ent->SetColor("blue");
                        break;
                    }
                    case ColorId::PURPLE: {
                        ent->SetColor("purple");
                        break;
                    }
                }
                break;
            }
        }
        if (m_id == UpgradeId::NONE ||
            m_color == ColorId::NONE ||
            m_value == 0.0) {
            printf("No upgrade selected\nNo XP was spent\n");
            std::cout << "Current XP: " << ent->GetXP() << std::endl;
        } else {
            printf("Applying upgrade\n");
            std::cout << "XP after upgrade: " << ent->UpgradeAdded()
                                              << std::endl;
        }
    }

 private:
    const int       m_eid;
    const UpgradeId m_id;
    const float     m_value;
    const ColorId   m_color;
};

#endif  // LIBS_TRANSIT_INCLUDE_UPGRADE_H_
