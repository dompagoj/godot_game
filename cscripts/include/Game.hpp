#pragma once

#include "Prelude.hpp"
#include "Node2D.hpp"
#include "Array.hpp"
#include "RectangleShape2D.hpp"
#include "vector"
#include "KinematicBody2D.hpp"
#include "InputEventMouseButton.hpp"
#include "Units/Marine.hpp"
#include "PackedScene.hpp"
#include "Timer.hpp"
#include "UnitSelection.hpp"


class Game : public Node2D
{
GODOT_CLASS(Game, Node2D)
public:
    bool Dragging = false;
    UnitSelection Selected;
    Vector2 DragStart = Vector2::ZERO;
    Ref<RectangleShape2D> SelectRectangle;
    Timer* PosIndicatorTimer;

    Vector2 RightClickPosition = Vector2::ZERO;

    _REGISTER_METHODS();
    _INIT();
    _READY()
    _UNHANDLED_INPUT();
    _DRAW();

    void DrawCircle(Vector2 pos);
    void HandleLeftClick(InputEventMouseButton*);
    void HandleRightClick(InputEventMouseButton*);

    void OnCircleIndicatorTimeout();
    void AddUnitToSelected(BaseUnit* unit);
};
