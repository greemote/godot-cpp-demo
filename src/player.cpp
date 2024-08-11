#include "player.h"

using namespace godot;

void Player::_bind_methods() {
    ClassDB::bind_method(D_METHOD("getSpeed"), &Player::getSpeed);
    ClassDB::bind_method(D_METHOD("setSpeed", "_speed"), &Player::setSpeed);
    ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "speed"), "setSpeed", "getSpeed");

    ClassDB::bind_method(D_METHOD("getGravity"), &Player::getGravity);
    ClassDB::bind_method(D_METHOD("setGravity", "_gravity"), &Player::setGravity);
    ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "gravity"), "setGravity", "getGravity");

    ClassDB::bind_method(D_METHOD("resetCooldown"), &Player::resetCooldown);
    ClassDB::bind_method(D_METHOD("fireTimeout"), &Player::fireTimeout);
    ClassDB::bind_method(D_METHOD("setVulnerableTrue"), &Player::setVulnerableTrue);

    ADD_SIGNAL(MethodInfo("shoot", PropertyInfo(Variant::VECTOR2, "pos"), PropertyInfo(Variant::BOOL, "facingRight")));
}

Player::Player() {
    InputMap::get_singleton()->load_from_project_settings();
}

void Player::_ready() {
    if (Engine::get_singleton()->is_editor_hint())
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    else 
        set_process_mode(Node::ProcessMode::PROCESS_MODE_INHERIT);

    hpBar = static_cast<UI*>(get_tree()->get_first_node_in_group("UI"));
    if(hpBar != nullptr) {
        hpBar->get_node<ProgressBar>("MarginContainer/ProgressBar")->set_max(maxHealth);
        hpBar->get_node<ProgressBar>("MarginContainer/ProgressBar")->set_value(health);
    }
}

void Player::_process(double delta) {
    getInput();
    applyGravity();
    getFacingDirection();
    getAnimation();
    set_velocity({ directionX * speed, get_velocity()[1] });
    move_and_slide();

}

void Player::getInput() {
    directionX = Input::get_singleton()->get_axis("left", "right");

    if (Input::get_singleton()->is_action_just_pressed("jump") && is_on_floor()) {
        set_velocity({ get_velocity()[0], -200.f });
        get_node<AudioStreamPlayer2D>("Sounds/JumpSound")->play();
    }

    if (Input::get_singleton()->is_action_just_pressed("shoot") && canShoot && hasGun) {
        emit_signal("shoot", get_global_position(), facingRight);
        canShoot = false;
        get_node<Timer>("Timers/CooldownTimer")->start();
        get_node<Timer>("Timers/FireTimer")->start();
        static_cast<Sprite2D*>(get_node<Node2D>("Fire")->get_child(static_cast<int32_t>(facingRight)))->show();
        get_node<AudioStreamPlayer2D>("Sounds/FireSound")->play();
    }
}

void Player::applyGravity() {
    set_velocity({ get_velocity()[0], get_velocity()[1] += 10.f } );
}

void Player::getFacingDirection() {
    if (directionX != 0) {
        facingRight = directionX > 0;
    }
}

void Player::resetCooldown() {
    canShoot = true;
}

void Player::fireTimeout() {
    static_cast<Sprite2D*>(get_node<Node2D>("Fire")->get_child(0))->hide();
    static_cast<Sprite2D*>(get_node<Node2D>("Fire")->get_child(1))->hide();
}

void Player::getAnimation() {
    animation = "idle";

    if (!is_on_floor()) {
        animation = "jump";
    }
    else if (directionX != 0.f) {
        animation = "walk";
    }
    if (hasGun) animation = animation + gun;

    get_node<AnimatedSprite2D>("AnimatedSprite2D")->set_animation(animation);
    get_node<AnimatedSprite2D>("AnimatedSprite2D")->set_flip_h(!facingRight);
}

void Player::checkDeath() {
	if(health <= 0)
		get_tree()->quit();
}

void Player::damage(int32_t amount)
{
    if(vulnerable)
    {
        create_tween()->tween_property(get_node<Node2D>("AnimatedSprite2D"), static_cast<NodePath>("material:shader_parameter/amount"), 1.0, 0.0);
	    create_tween()->tween_property(get_node<Node2D>("AnimatedSprite2D"), static_cast<NodePath>("material:shader_parameter/amount"), 0.0, 0.1)->set_delay(0.2);
        health -= amount;
        checkDeath();
        vulnerable = false;
        get_node<Timer>("Timers/InvisibleFrames")->start();
        hpBar->get_node<ProgressBar>("MarginContainer/ProgressBar")->set_value(health);
        get_node<AudioStreamPlayer2D>("Sounds/DamageSound")->play();
    }
}


void Player::setSpeed(const float _speed) {
    speed = _speed;
}

float Player::getSpeed() const {
    return speed;
}

void Player::setGravity(const float _gravity) {
    gravity = _gravity;
}

float Player::getGravity() const {
    return gravity;
}

void Player::setHasGun(bool _hasGun) {
    hasGun = _hasGun;
}
void Player::setCanShoot(bool _canShoot) {
    canShoot = _canShoot;
}
void Player::setVulnerableTrue() {
    vulnerable = true;
}