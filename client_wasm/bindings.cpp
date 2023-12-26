#include "emscripten/bind.h"
#include "utility/vector2.hh"

EMSCRIPTEN_BINDINGS(Vector2) {
  emscripten::class_<Vector2>("Vector2")
    .constructor<int, int>()
    .function("x", &Vector2::x)
    .function("y", &Vector2::y)
    .function("set_x", &Vector2::set_x)
    .function("set_y", &Vector2::set_y)
    ;
}