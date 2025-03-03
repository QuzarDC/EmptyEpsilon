#ifndef FIGHTER_AI_H
#define FIGHTER_AI_H

#include "ai.h"

class FighterAI : public ShipAI
{
    enum class State
    {
        Dive,
        Evade,
        Recharge
    };
    State attack_state;
    float timeout;
    float evade_direction;
    float aggression;
public:
    FighterAI(sp::ecs::Entity owner);

    /**!
     * Are we allowed to switch to a different AI right now?
     * When true is returned, and the CpuShip wants to change their AI this AI object will be destroyed and a new one will be created.
     */
    virtual bool canSwitchAI() override;

    virtual void run(float delta) override;
    virtual void runOrders() override;
    virtual void runAttack(sp::ecs::Entity target) override;
};


#endif//FIGHTER_AI_H
