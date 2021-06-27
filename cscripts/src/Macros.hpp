#pragma once

#define REGISTER_METHOD(METHOD_NAME, CLASS) register_method(#METHOD_NAME, &CLASS::METHOD_NAME);
#define REGISTER_PROCESS(CLASS) register_method("_process", &CLASS::_process);
#define REGISTER_INPUT(CLASS) register_method("_input", &CLASS::_input);
#define REGISTER_UNHANDLED_INPUT(CLASS) register_method("_unhandled_input", &CLASS::_unhandled_input);
#define REGISTER_UNHANDLED_KEY_INPUT(CLASS) register_method("_unhandled_key_input", &CLASS::_unhandled_key_input);
#define REGISTER_READY(CLASS) register_method("_ready", &CLASS::_ready);
#define REGISTER_PHYSICS_PROCESS(CLASS) register_method("_physics_process", &CLASS::_physics_process);
#define REGISTER_DRAW(CLASS) register_method("_draw", &CLASS::_draw);
#define REGISTER_INTEGRATE_FORCES(CLASS) register_method("_integrate_forces", &CLASS::_integrate_forces);

#define _REGISTER_METHODS() static void _register_methods();
#define _PROCESS() void _process(float);
#define _PHYSICS_PROCESS() void _physics_process(float);
#define _INIT() void _init();
#define _EMPTY_INIT() void _init() {}
#define _INPUT() void _input(const InputEvent* event);
#define _READY() void _ready();
#define _UNHANDLED_INPUT() void _unhandled_input(const InputEvent* event);
#define _UNHANDLED_KEY_INPUT() void _unhandled_input(const InputEventKey* event);
#define _DRAW() void _draw();
#define _FIXED_PROCESS() void _fixed_process(float);
#define _INTEGRATE_FORCES() void _integrate_forces(const Physics2DDirectBodyState* state);

#define _INHERITED_METHOD(BASE_CLASS, METHOD)  \
void METHOD()              \
{                                               \
    BASE_CLASS::METHOD();        \
}

#define _INHERITED_INIT(BASE_CLASS) _INHERITED_METHOD(BASE_CLASS, _init)
