#include "worm.h"

using namespace godot;

void Worm::_bind_methods() {
	ClassDB::bind_method(D_METHOD("changeDirectionAndFlip"), &Worm::changeDirectionAndFlip);
}

void Worm::_process(double delta) {
	set_position({get_position().x + static_cast<real_t>(speed * directionX * delta), get_position().y});
}

void Worm::changeDirectionAndFlip() {
	directionX *= -1;
	get_node<AnimatedSprite2D>("AnimatedSprite2D")->set_flip_h(!get_node<AnimatedSprite2D>("AnimatedSprite2D")->is_flipped_h());
}