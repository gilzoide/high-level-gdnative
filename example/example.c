#define GDNHLC_IMPLEMENTATION
#include "gdnhlc.h"

GDN_EXPORT void godot_gdnative_init(godot_gdnative_init_options *options) {
    gdnhlc_gdnative_init(options);
}

GDN_EXPORT void godot_gdnative_terminate(godot_gdnative_terminate_options *options) {
    gdnhlc_gdnative_terminate(options);
}

GDN_EXPORT void godot_nativescript_init(void *p_handle) {
}
