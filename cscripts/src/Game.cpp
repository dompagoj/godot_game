#include "Game.hpp"
#include "Dictionary.hpp"
#include "Physics2DDirectSpaceState.hpp"
#include "Physics2DShapeQueryParameters.hpp"
#include "UnitManager.hpp"
#include "Utils.hpp"
#include "World2D.hpp"
#include <GlobalConstants.hpp>
#include <InputEventMouseMotion.hpp>

void Game::_register_methods()
{
    REGISTER_UNHANDLED_INPUT(Game)
    REGISTER_DRAW(Game)
    REGISTER_READY(Game)
    //    REGISTER_METHOD(on_timeout, Game)
    register_method("on_circle_indicator_timeout", &Game::OnCircleIndicatorTimeout);
    register_method("on_unit_select", &Game::AddUnitToSelected);
}

void Game::_ready()
{
    PosIndicatorTimer = Timer::_new();
    add_child(PosIndicatorTimer);

    auto units2 = get_node("Units")->get_children();

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

void Game::_unhandled_input(const InputEvent *event)
{
    if (auto *inputEvent = cast_to<InputEventMouseButton>(event); inputEvent)
    {
        if (inputEvent->is_action("left_click"))
            HandleLeftClick(inputEvent);
        else if (inputEvent->is_action_pressed("right_click"))
            HandleRightClick(inputEvent);
    }

    if (auto *motionEvent = cast_to<InputEventMouseMotion>(event); motionEvent && Dragging) { update(); }
}

void Game::_draw()
{
    if (Dragging)
    {
        auto mousePos = get_global_mouse_position();
        draw_rect(Rect2(DragStart, mousePos - DragStart), Color{1.8, 2.3, 2.55, 0.1});
        draw_rect(Rect2(DragStart, mousePos - DragStart), Color{1.8, 2.3, 2.55, 1}, false);
    }

    if (RightClickPosition != Vector2::ZERO) { draw_circle(RightClickPosition, 10, Color(0.5, 0.5, 0.5)); }
}

void Game::DrawCircle(Vector2 pos)
{
    RightClickPosition = pos;
    update();
    PosIndicatorTimer->start(1);
}

void Game::HandleLeftClick(InputEventMouseButton *input_event)
{
    if (input_event->is_pressed())
    {
        for (const auto &unit : Selected.Units)
        {
            if (unit->Selected) unit->SetSelected(false);
        }
        Selected.Clear();
        Dragging = true;
        DragStart = get_canvas_transform().xform_inv(input_event->get_global_position());
    }
    else if (Dragging)
    {
        Dragging = false;
        update();

        const auto drag_end = get_canvas_transform().xform_inv(input_event->get_global_position());
        SelectRectangle->set_extents((drag_end - DragStart) / 2);

        auto *space = get_world_2d()->get_direct_space_state();
        Ref query = Physics2DShapeQueryParameters::_new();
        query->set_shape(SelectRectangle);
        query->set_transform(Transform2D(0, (drag_end + DragStart) / 2));
        query->set_collide_with_areas(true); // TODO make this work with Selector area in unit scene
        query->set_collision_layer(GetLayers(UNITS));

        auto result = space->intersect_shape(query, 1000);

        for (int i = 0; i < result.size(); i++)
        {
            auto collider = static_cast<Dictionary>(result[i])["collider"];

            if (auto *baseUnit = cast_to<BaseUnit>(collider); baseUnit)
            {
                baseUnit->SetSelected(true);
                Selected.AddUnit(baseUnit);
            }
        }
    }
}

void Game::HandleRightClick(InputEventMouseButton *input_event)
{
    if (Selected.Empty()) return;
    const auto position = get_canvas_transform().xform_inv(input_event->get_global_position());
    DrawCircle(position);

    for (auto unit : Selected.Units)
        unit->Move(position);
}

void Game::OnCircleIndicatorTimeout()
{
    RightClickPosition = Vector2::ZERO;
    update();
}

void Game::AddUnitToSelected(BaseUnit *unit)
{
    Selected.SelectOne(unit);
}
