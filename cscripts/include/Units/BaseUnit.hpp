#pragma once
#include "Macros.hpp"
#include "Prelude.hpp"
#include "RigidBody2D.hpp"
#include "Timer.hpp"
#include "Physics2DDirectBodyState.hpp"

class BaseUnit : public RigidBody2D
{
 GODOT_CLASS(BaseUnit, RigidBody2D)

 public:
    _EMPTY_INIT()
    _REGISTER_METHODS()
//    _PHYSICS_PROCESS()
    _READY()
    _INTEGRATE_FORCES()




    BaseUnit() = default;
    BaseUnit(float speed);

    void Attack();
    void TakeDamage(int64_t damage);
    void Move(Vector2);
    void MovementLoop(float);
    void Die();

    int64_t Health = 100;
    bool Selected{false};
    bool Dead{false};

    float Speed = BaseSpeed;

    void OnInputEvent(Node* viewport, const InputEvent* inputEvent, int64_t shapeIdx);
    void BodyEntered(Node* body);

 private:
    Vector2 TargetPosition = Vector2::ZERO;
    Vector2 Velocity = Vector2::ZERO;
    Timer* DieTimer = nullptr;

 protected:
    constexpr static const float BaseSpeed = 5;
    static consteval float MultiplySpeedFromBaseConst(float val)
    {
        return BaseSpeed * val;
    }

    static consteval float AddSpeedFromBaseConst(float val)
    {
        return BaseSpeed + val;
    }

};