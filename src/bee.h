#pragma once

#include <godot_cpp/classes/area2D.hpp>
#include <godot_cpp/classes/marker2D.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/sprite2D.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "enemy.h"

namespace godot {
	class Bee : public Enemy {
		GDCLASS(Bee, Enemy);

		ObjectID marker0;
		ObjectID marker1;

		Marker2D* marker;
		bool forward = true;

		Player* player;
		bool chasing = false;

	protected:
		static void _bind_methods();

	public:
		Bee() : Enemy(3, 2) {}

		virtual void _ready() override;
		virtual void _process(double) override;

		void getMarker();
		void followTarget(Node2D*, double);

		void onAggroBodyEntered();
		void onAggroBodyExited();

		Marker2D* getMarker0() const { return Object::cast_to<Marker2D>(ObjectDB::get_instance(marker0)); }
		Marker2D* getMarker1() const { return Object::cast_to<Marker2D>(ObjectDB::get_instance(marker1)); }
		void setMarker0(Marker2D* marker) { marker0 = marker->get_instance_id(); }
		void setMarker1(Marker2D* marker) { marker1 = marker->get_instance_id(); }
	};

}