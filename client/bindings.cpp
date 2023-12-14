#include "emscripten/bind.h"
#include "utility/vector2.hh"

EMSCRIPTEN_BINDINGS(Vector2) {
  emscripten::class_<Vector2>("Vector2")
    .constructor<int, int>()
    .function("x", &Vector2::GetX)
    .function("y", &Vector2::GetY)
    .function("SetX", &Vector2::SetX)
    .function("SetY", &Vector2::SetY)
    ;
}