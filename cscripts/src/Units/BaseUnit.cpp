#include "Units/BaseUnit.hpp"
#include "KinematicCollision2D.hpp"
#include "Math.hpp"
#include "Utils.hpp"
#include "InputEventMouseButton.hpp"
#include "Area2D.hpp"

const float SPEED_MODIFIER = 50.f;

void BaseUnit::_register_methods()
{
    REGISTER_READY(BaseUnit);
    REGISTER_INTEGRATE_FORCES(BaseUnit);
    register_method("on_input", &BaseUnit::OnInputEvent);
    register_signal<BaseUnit>("selected");
    register_method("on_body_entered", &BaseUnit::BodyEntered);
}

void BaseUnit::_ready()
{
    DieTimer = get_node<Timer>("DieTimer");
    DieTimer->connect("timeout", this, "queue_free");
    connect("body_entered", this, "on_body_entered");

//    auto* select = get_node<Area2D>("Selector");
//    select->connect("input_event", this, "on_input");

//    set_collision_layer(GetLayers(UNITS));
//    set_collision_mask(GetLayers(WORLD, UNITS));
}

void BaseUnit::OnInputEvent(Node* viewport, const InputEvent* inputEvent, int64_t shapeIdx)
{
    auto mouseEvent = cast_to<InputEventMouseButton>(inputEvent);
    if (!mouseEvent) return;

    if (mouseEvent->is_action_pressed("left_click"))
    {
        Selected = true;
        emit_signal("selected", this);
    }
}

void BaseUnit::Attack()
{
    Godot::print("Attacking!");
}

void BaseUnit::Move(Vector2 position)
{
    if (Health > 0) TargetPosition = position;
}

void BaseUnit::_integrate_forces(const Physics2DDirectBodyState* state)
{
    if (TargetPosition == Vector2::ZERO || Dead) return;
    Godot::print("Integrate forces!");
    const auto currentPosition = get_position();
    Velocity = currentPosition.direction_to(TargetPosition).normalized() * Speed * SPEED_MODIFIER;
    const auto distanceTo = currentPosition.distance_to(TargetPosition);

    if (distanceTo < 5)
    {
        TargetPosition = Vector2::ZERO;
        Velocity = Vector2::ZERO;
    }

    set_linear_velocity(Velocity);
//    else if (Velocity != Vector2::ZERO)
//    {
//        Velocity = Vector2::ZERO;
//        set_linear_velocity(Velocity);
//    }
}

//void BaseUnit::_physics_process(float delta)
//{
//    MovementLoop(delta);
//}

// Old movement logic used when unit was a KinematicBody2D,
// still here in case we realize RigidtBody2D is too complicated and decide to back to KinematicBody2D
void BaseUnit::MovementLoop(float delta)
{
//    const auto currentPosition = get_position();
//
//    Velocity = currentPosition.direction_to(TargetPosition) * Speed * SPEED_MODIFIER;
//    const auto distanceTo = currentPosition.distance_to(TargetPosition);
//
//    if (distanceTo > 5)
//    {
//        Velocity = body->move_and_slide(Velocity);
//    }
}

BaseUnit::BaseUnit(float speed)
{
    Speed = speed;
}

void BaseUnit::Die()
{
    if (Dead) return;;

    Dead = true;
    Selected = false;
    TargetPosition = Vector2::ZERO;
//    set_mode(RigidBody2D::Mode::MODE_RIGID);
//    set_linear_damp(20.f);
    apply_impulse(Vector2(), Vector2(100, 100));

    DieTimer->start(10);
}
void BaseUnit::BodyEntered(Node* body)
{
    // TODO Somehow move stationary friendly units out of the way

    Godot::print("Selected?: " + String(Selected ? "True" : "False"));
    if (!Selected || Velocity == Vector2::ZERO) return;
    auto* otherUnit = cast_to<BaseUnit>(body);
    if (!otherUnit || otherUnit->Velocity != Vector2::ZERO) return;

    otherUnit->TakeDamage(150);
}
void BaseUnit::TakeDamage(int64_t damage)
{
    Health -= damage;

    Godot::print("Death!");
    if (Health <= 0) Die();
}

