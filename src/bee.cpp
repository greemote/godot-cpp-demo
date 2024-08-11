#include "bee.h"

using namespace godot;

void Bee::_bind_methods() {
    ClassDB::bind_method(D_METHOD("getMarker0"), &Bee::getMarker0);
    ClassDB::bind_method(D_METHOD("setMarker0", "marker"), &Bee::setMarker0);
    ClassDB::add_property("Bee", PropertyInfo(Variant::OBJECT, "marker0", PROPERTY_HINT_NODE_TYPE, "Marker2D"), "setMarker0", "getMarker0");

    ClassDB::bind_method(D_METHOD("getMarker1"), &Bee::getMarker1);
    ClassDB::bind_method(D_METHOD("setMarker1", "marker"), &Bee::setMarker1);
    ClassDB::add_property("Bee", PropertyInfo(Variant::OBJECT, "marker1", PROPERTY_HINT_NODE_TYPE, "Marker2D"), "setMarker1", "getMarker1");

	ClassDB::bind_method(D_METHOD("onAggroBodyEntered"), &Bee::onAggroBodyEntered);
	ClassDB::bind_method(D_METHOD("onAggroBodyExited"), &Bee::onAggroBodyExited);
}

void Bee::_ready() {
	if (Engine::get_singleton()->is_editor_hint())
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    else 
        set_process_mode(Node::ProcessMode::PROCESS_MODE_INHERIT);

	marker = getMarker1();
	if(marker != nullptr)
		set_position(getMarker0()->get_position()); 

	player = static_cast<Player*>(get_tree()->get_first_node_in_group("Player"));
}

void Bee::_process(double delta) {
	if(!chasing) {
		getMarker();
		followTarget(marker, delta);
	}
	else {
		followTarget(player, delta);
	}
}

void Bee::getMarker() {
	if( forward && get_position().distance_to(getMarker1()->get_position()) < 10.f ||
	   !forward && get_position().distance_to(getMarker0()->get_position()) < 10.f ) {
		forward = !forward;

		switch(forward)
		{
		case true:
			marker = getMarker1();
			break;
		case false:
			marker = getMarker0();
			break;
		}
	}
}

void Bee::followTarget(Node2D* target, double delta) {
	set_position({ get_position().x + static_cast<real_t>(static_cast<Vector2>(target->get_position() - get_position()).normalized().x * speed * delta),
				   get_position().y + static_cast<real_t>(static_cast<Vector2>(target->get_position() - get_position()).normalized().y * speed * delta) });
	
	//face switching
	get_node<AnimatedSprite2D>("AnimatedSprite2D")->set_flip_h(get_position().x > target->get_position().x);
}

void Bee::onAggroBodyEntered() {
	chasing = true;
}
void Bee::onAggroBodyExited() {
	chasing = false;
}