#include <gen/GlobalConstants.hpp>
#include <InputEventMouseMotion.hpp>
#include "Game.hpp"
#include "World2D.hpp"
#include "Physics2DShapeQueryParameters.hpp"
#include "Physics2DDirectSpaceState.hpp"
#include "KinematicCollision2D.hpp"
#include "Dictionary.hpp"
#include "InputEventKey.hpp"
#include "SceneTree.hpp"
#include "UnitManager.hpp"
#include "Color.hpp"
#include "Utils.hpp"

godot::String AddBool(const godot::String& str, bool val)
{
    return str + (val ? "True" : "False");
}

void Game::_register_methods()
{
    REGISTER_UNHANDLED_INPUT(Game)
    REGISTER_DRAW(Game)
    REGISTER_READY(Game)
//    REGISTER_METHOD(on_timeout, Game)
    register_method("on_circle_indicator_timeout", &Game::OnCircleIndicatorTimeout);
    register_method("on_unit_select", &Game::OnUnitSelectChange);
}

void Game::_ready()
{
    PosIndicatorTimer = Timer::_new();
    add_child(PosIndicatorTimer);

    auto units = get_node("Units")->get_children();
    for (int i = 0; i < units.size(); i++)
    {
        auto unit = cast_to<BaseUnit>(units[i]);
        unit->connect("selected_change", this, "on_unit_select");
    }

    PosIndicatorTimer->connect("timeout", this, "on_circle_indicator_timeout");
}

void Game::_init()
{
    SelectRectangle = Ref(RectangleShape2D::_new());
}

void Game::_unhandled_input(const InputEvent* event)
{
    auto* inputEvent = cast_to<InputEventMouseButton>(event);
    if (inputEvent)
    {
        if (inputEvent->is_action("left_click")) HandleLeftClick(inputEvent);
        else if (inputEvent->is_action_pressed("right_click")) HandleRightClick(inputEvent);
    }

    auto* motionEvent = cast_to<InputEventMouseMotion>(event);
    if (motionEvent && Dragging)
    {
        update();
    }
}

void Game::_draw()
{
    if (Dragging)
    {
        auto mousePos = get_global_mouse_position();
        draw_rect(Rect2(DragStart, mousePos - DragStart), Color{ 1.8, 2.3, 2.55, 0.1 });
        draw_rect(Rect2(DragStart, mousePos - DragStart), Color{ 1.8, 2.3, 2.55, 1 }, false);
    }

    if (RightClickPosition != Vector2::ZERO)
    {
        draw_circle(RightClickPosition, 10, Color(0.5, 0.5, 0.5));
    }
}

void Game::DrawCircle(Vector2 pos)
{
    RightClickPosition = pos;
    update();
    PosIndicatorTimer->start(1);
}

void Game::HandleLeftClick(InputEventMouseButton* input_event)
{
    if (input_event->is_pressed())
    {
        for (const auto& unit: Selected)
        {
            if (unit->Selected) unit->ToggleSelect();
        }
        Selected.clear();
        Dragging = true;
        DragStart = get_canvas_transform().xform_inv(input_event->get_global_position());
    }
    else if (Dragging)
    {
        Dragging = false;
        update();

        auto drag_end = get_canvas_transform().xform_inv(input_event->get_global_position());
        SelectRectangle->set_extents((drag_end - DragStart) / 2);

        auto* space = get_world_2d()->get_direct_space_state();
        Ref<Physics2DShapeQueryParameters> query = Physics2DShapeQueryParameters::_new();
        query->set_shape(SelectRectangle);
        query->set_transform(Transform2D(0, (drag_end + DragStart) / 2));
        query->set_collide_with_areas(true); // TODO make this work with Selector area in unit scene
        query->set_collision_layer(GetLayers(UNITS));

        auto result = space->intersect_shape(query, 1000);

        for (int i = 0; i < result.size(); i++)
        {
            auto collider = ((Dictionary)result[i])["collider"];

            auto* base_unit = cast_to<BaseUnit>(collider);
            if (base_unit)
            {
                base_unit->ToggleSelect();
                Selected.push_back(base_unit);
            }
        }
    }
}
void Game::HandleRightClick(InputEventMouseButton* input_event)
{
    if (Selected.empty()) return;
    auto position = get_canvas_transform().xform_inv(input_event->get_global_position());
    DrawCircle(position);
    for (auto unit : Selected) unit->Move(position);
}
void Game::OnCircleIndicatorTimeout()
{
    RightClickPosition = Vector2::ZERO;
    update();
}
void Game::OnUnitSelectChange(BaseUnit* unit, bool selected)
{
    Godot::print("On unit select change!");
    if (selected)
    {
        Godot::print("On unit select!");
        Dragging = false;
        for (const auto& selectedUnit: Selected)
        {
            if (selectedUnit->Selected) selectedUnit->ToggleSelect();
        }
        Selected.clear();
        Selected.push_back(unit);

    }
}
