#include "bullet.h"
#include "player.h"
#include "gun.h"

#include "bee.h"
#include "enemy.h"
#include "worm.h"

#include "level.h"
#include "ui.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initializeDemo(ModuleInitializationLevel pLevel) {
    if(pLevel != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    ClassDB::register_class<Player>();
    ClassDB::register_class<Bullet>();
    ClassDB::register_class<Gun>();

    ClassDB::register_abstract_class<Enemy>();
    ClassDB::register_class<Bee>();
    ClassDB::register_class<Worm>();

    ClassDB::register_class<UI>();
    ClassDB::register_class<Level>();
}

void uninitializeDemo(ModuleInitializationLevel pLevel) {
    if(pLevel != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
    GDExtensionBool GDE_EXPORT demo_init(GDExtensionInterfaceGetProcAddress pGetProcAddress, const GDExtensionClassLibraryPtr pLibrary, GDExtensionInitialization* rInitialization) {
        godot::GDExtensionBinding::InitObject init_obj(pGetProcAddress, pLibrary, rInitialization);

        init_obj.register_initializer(initializeDemo);
        init_obj.register_terminator(uninitializeDemo);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}