#include "level.h"

using namespace godot;

void Level::_bind_methods() {
    ClassDB::bind_method(D_METHOD("onPlayerShoot", "pos", "facingRight"), &Level::onPlayerShoot);
    ClassDB::bind_method(D_METHOD("onEnemiesChildExitingTree"), &Level::onEnemiesChildExitingTree);
}

void Level::_ready() {
    if (Engine::get_singleton()->is_editor_hint())
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    else 
        set_process_mode(Node::ProcessMode::PROCESS_MODE_INHERIT);

    bulletScene = ResourceLoader::get_singleton()->load("res://scenes/bullet.tscn");
}

void Level::onPlayerShoot(Vector2 pos, bool facingRight) {
    bullet = static_cast<Bullet*>(bulletScene->instantiate());
    offset = Vector2(-14.0, 0.0);
    if(facingRight)
        offset.x *= -1.0;
    get_node<Node2D>("Bullets")->add_child(bullet);
    bullet->set_position(get_node<Player>("Player")->get_position() + offset);
    bullet->setDirection(facingRight);
}

void Level::onEnemiesChildExitingTree() {
    if(get_node<Node2D>("Enemies")->get_child_count() == 1)
        get_tree()->quit();
}