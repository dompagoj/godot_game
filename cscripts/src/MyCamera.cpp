#include "MyCamera.hpp"
#include "Area2D.hpp"
#include "InputEventMouseButton.hpp"
#include "SceneTree.hpp"
#include "Viewport.hpp"

void MyCamera::_register_methods()
{
    //    register_property("speed", &MyCamera::Speed, 5.f);
    //    register_property("move_threshold", &MyCamera::MoveThreshold, 50.f);
    register_method("on_size_change", &MyCamera::OnSizeChange);
    REGISTER_PROCESS(MyCamera)
    REGISTER_READY(MyCamera)
    REGISTER_UNHANDLED_INPUT(MyCamera)
}

MyCamera::MyCamera() : Speed(10.f), MoveThreshold(25.f)
{
    MoveThresholdPercentage = MoveThreshold / 100; // TODO
}

void MyCamera::_ready()
{
    auto viewPort = get_tree()->get_root();

    viewPort->connect("size_changed", this, "on_size_change");
    WinSize = viewPort->get_size();
}

void MyCamera::_unhandled_input(const InputEvent *event)
{
    //    auto mouseEvent = cast_to<InputEventMouseButton>(event);
    //    if (!mouseEvent) return;
    //
    //    auto currZoom = get_zoom();
    //
    //    if (mouseEvent->is_action_pressed("scroll_up"))
    //    {
    //        ZoomCamera(0.1, get_global_mouse_position());
    //    }
    //
    //    if (mouseEvent->is_action_pressed("scroll_down"))
    //    {
    //        set_zoom(currZoom + Vector2(0.05, 0.05));
    //    }
}

void MyCamera::ZoomCamera(float zoomSpeed, Vector2 position)
{
    const auto viewportSize = get_viewport()->get_size();
    const auto prevZoom = get_zoom();

    set_zoom(prevZoom - Vector2(zoomSpeed, zoomSpeed));
    set_offset((viewportSize * 0.5 - position) * prevZoom); // No idea
}

void MyCamera::_process(float delta)
{
    const auto currentPos = get_global_position();
    const auto mousePos = get_local_mouse_position();

    Vector2 newPos = currentPos;

    auto moveBy = Speed * delta * 100;
    if (mousePos.x <= MoveThreshold) { newPos.x = currentPos.x - moveBy; }

    if (mousePos.x + MoveThreshold >= WinSize.x) { newPos.x = currentPos.x + moveBy; }

    if (mousePos.y <= MoveThreshold) { newPos.y = currentPos.y - moveBy; }

    if (mousePos.y + MoveThreshold >= WinSize.y) { newPos.y = currentPos.y + moveBy; }

    set_position(newPos);
}

void MyCamera::OnSizeChange()
{
    WinSize = get_tree()->get_root()->get_size();
}
