#pragma once

#include <godot_cpp/classes/animated_sprite2D.hpp>
#include <godot_cpp/classes/audio_stream_player2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/progress_bar.hpp>
#include <godot_cpp/classes/property_tweener.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/sprite2D.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "ui.h"

namespace godot {
    class Player : public CharacterBody2D {
        GDCLASS(Player, CharacterBody2D);

        float directionX = .0f;
        bool facingRight = true;
        float speed = 100.f;
        float gravity = 10.f;
        bool canShoot = false;
        bool hasGun = false;
        int32_t maxHealth = 5;
        int32_t health = 5;
        bool vulnerable = true;
        UI* hpBar;

        StringName animation = "idle";
        const StringName gun = "Gun";

    protected:
        static void _bind_methods();

    public:
        Player();
        ~Player() {};

        virtual void _ready() override;
        virtual void _process(double) override;

        void getInput();
        void applyGravity();
        void getFacingDirection();
        void resetCooldown();
        void fireTimeout();
        void getAnimation();
		void checkDeath();
        int32_t updateHpBar() const;
        void damage(const int32_t);

        void setSpeed(const float);
        float getSpeed() const;
        void setGravity(const float _gravity);
        float getGravity() const;
        void setHasGun(bool);
        void setCanShoot(bool);
        void setVulnerableTrue();
        const int32_t getHealth() const { return health; }
    };
}