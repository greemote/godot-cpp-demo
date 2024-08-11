#include "bullet.h"

using namespace godot;

void Bullet::_bind_methods() {

	ClassDB::bind_method(D_METHOD("getSpeed"), &Bullet::getSpeed);
	ClassDB::bind_method(D_METHOD("setSpeed", "_speed"), &Bullet::setSpeed);
	ClassDB::add_property("Bullet", PropertyInfo(Variant::FLOAT, "speed"), "setSpeed", "getSpeed");

	ClassDB::bind_method(D_METHOD("setDirection"), &Bullet::setDirection);
	ClassDB::bind_method(D_METHOD("targetHit"), &Bullet::targetHit);
	ClassDB::bind_method(D_METHOD("queueFree"), &Bullet::queueFree);
}

void Bullet::_ready() {
    if (Engine::get_singleton()->is_editor_hint())
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    else 
        set_process_mode(Node::ProcessMode::PROCESS_MODE_INHERIT);

	get_node<Timer>("TimeToLive")->start();
}

void Bullet::_process(double delta) {
	set_position({ get_position().x + static_cast<real_t>(300.f * delta * direction), get_position().y });
}

void Bullet::setDirection(bool facingRight)
{
	direction = facingRight ? 1 : -1;
	get_node<Sprite2D>("Sprite2D")->set_flip_h(!facingRight);
}

void Bullet::targetHit()
{
	get_node<Timer>("TimeToLive")->stop();
	get_node<AudioStreamPlayer2D>("HitSound")->play();
	get_node<CollisionShape2D>("CollisionShape2D")->hide();
	get_node<Sprite2D>("Sprite2D")->hide();
}

void Bullet::setSpeed(const float _speed) {
	speed = _speed;
}

float Bullet::getSpeed() const {
	return speed;
}