#include "gun.h"

using namespace godot;

void Gun::_bind_methods() {
	ClassDB::bind_method(D_METHOD("onBodyEntered"), &Gun::onBodyEntered);
}

void Gun::_ready() {
	player = static_cast<Player*>(get_tree()->get_first_node_in_group("Player"));
}

void Gun::_process(double delta) {
	set_position({ get_position().x, (get_position().y + static_cast<real_t>(sin(Time::get_singleton()->get_ticks_msec() / 200.f) * 10.f * delta)) });
}

void Gun::onBodyEntered(Player* body) {
	body->setHasGun(true);
	body->setCanShoot(true);
	queue_free();
	
	player->get_node<AudioStreamPlayer2D>("Sounds/GunPickupSound")->play();
}