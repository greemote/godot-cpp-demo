#pragma once

#include <godot_cpp/classes/area2D.hpp>
#include <godot_cpp/classes/audio_stream_player2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/sprite2D.hpp>
#include <godot_cpp/classes/timer.hpp>

namespace godot {
	class Bullet : public Area2D {
		GDCLASS(Bullet, Area2D);

		int direction = 1;
		float speed = 300.f;

	protected:
		static void _bind_methods();

	public:
		virtual void _ready() override;
		virtual void _process(double) override;

		void setDirection(bool);
		void targetHit();
		void queueFree() { queue_free(); };

		void setSpeed(const float);
		float getSpeed() const;
	};

}