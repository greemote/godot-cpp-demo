#pragma once

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {
    class UI : public CanvasLayer {
        GDCLASS(UI, CanvasLayer);

	protected:
		static void _bind_methods() {};
    };
}