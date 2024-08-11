#pragma once

#include <godot_cpp/classes/area2D.hpp>
#include <godot_cpp/classes/property_tweener.hpp>
#include <godot_cpp/classes/sprite2D.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "bullet.h"
#include "player.h"

namespace godot {
	class Enemy : public Area2D {
		GDCLASS(Enemy, Area2D);

	protected:
        int32_t health;
		int32_t damage;
		std::vector<Player*> overlappingPlayer;

		float speed = 25.f;

		static void _bind_methods();

	public:
        Enemy(int32_t health, int32_t damage) : health(health), damage(damage) {}

		virtual void _ready() override;
		virtual void _physics_process(double) override;
		virtual void _process(double) override = 0;

		void onAreaEntered(Area2D*);
		void checkDeath();
		void onPlayerCollision(Player*);
		void onPlayerEscaped();

		void setSpeed(float _speed) { speed = _speed; }
		float getSpeed() const { return speed; }
	};

}