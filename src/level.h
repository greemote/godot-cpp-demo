#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "bullet.h"
#include "player.h"

namespace godot {
    class Level : public Node2D {
        GDCLASS(Level, Node2D);

    Ref<PackedScene> bulletScene;
    Bullet* bullet;
    Vector2 offset;

    protected:
        static void _bind_methods();

    public:
        virtual void _ready();

        void onPlayerShoot(Vector2 pos, bool facingRight);
        void onEnemiesChildExitingTree();
    };
}