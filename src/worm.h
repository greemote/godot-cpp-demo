#pragma once

#include <godot_cpp/classes/area2D.hpp>
#include <godot_cpp/classes/sprite2D.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "enemy.h"

namespace godot {
	class Worm : public Enemy {
		GDCLASS(Worm, Enemy);

	int32_t directionX = 1;

	protected:
		static void _bind_methods();

	public:
		Worm() : Enemy(2, 1) {}

		virtual void _process(double) override;
		void changeDirectionAndFlip();
	};
}