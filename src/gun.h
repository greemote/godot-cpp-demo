#pragma once

#include <godot_cpp/classes/area2D.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/sprite2D.hpp>
#include <godot_cpp/classes/time.hpp>

#include "player.h"

namespace godot {
	class Gun : public Area2D {
		GDCLASS(Gun, Area2D);

	Player* player;

	protected:
		static void _bind_methods();

	public:
		void _ready() override;
		void _process(double) override;
		void onBodyEntered(Player* body);

	};

}