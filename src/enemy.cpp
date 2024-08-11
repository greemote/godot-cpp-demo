#include "enemy.h"

using namespace godot;

void Enemy::_bind_methods() {
    ClassDB::bind_method(D_METHOD("getSpeed"), &Enemy::getSpeed);
    ClassDB::bind_method(D_METHOD("setSpeed", "_speed"), &Enemy::setSpeed);
    ClassDB::add_property("Enemy", PropertyInfo(Variant::FLOAT, "speed"), "setSpeed", "getSpeed");

	ClassDB::bind_method(D_METHOD("onAreaEntered"), &Enemy::onAreaEntered);
	ClassDB::bind_method(D_METHOD("onPlayerCollision"), &Enemy::onPlayerCollision);
	ClassDB::bind_method(D_METHOD("onPlayerEscaped"), &Enemy::onPlayerEscaped);
}

void Enemy::_physics_process(double delta) {
	for(auto player : overlappingPlayer)
		player->damage(damage);
}

void Enemy::_ready() {
    if (Engine::get_singleton()->is_editor_hint())
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    else 
        set_process_mode(Node::ProcessMode::PROCESS_MODE_INHERIT);
}

void Enemy::checkDeath() {
	if(health <= 0)
		queue_free();
}

void Enemy::onAreaEntered(Area2D* area) {
	health -= 1;
	checkDeath();
    create_tween()->tween_property(get_node<Node2D>("AnimatedSprite2D"), static_cast<NodePath>("material:shader_parameter/amount"), 1.0, 0.0);
	create_tween()->tween_property(get_node<Node2D>("AnimatedSprite2D"), static_cast<NodePath>("material:shader_parameter/amount"), 0.0, 0.1)->set_delay(0.2);
	static_cast<Bullet*>(area)->targetHit();
}

void Enemy::onPlayerCollision(Player* player) {
	overlappingPlayer.push_back(player);
}

void Enemy::onPlayerEscaped() {
	overlappingPlayer.pop_back();
}