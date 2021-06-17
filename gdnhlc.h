/** @file
 * gdnhlc.h -- Higher level C/C++ API for GDNative
 *
 * Project URL: TODO
 *
 * Do this:
 * ```c
 *    #define PEGA_TEXTO_IMPLEMENTATION
 * ```
 * before you include this file in *one* C or C++ file to create the implementation.
 *
 * i.e.:
 * ```c
 *    #include ...
 *    #include ...
 *    #define GDNHLC_IMPLEMENTATION
 *    #include "gdnhlc.h"
 * ```
 *
 * Optionally provide the following defines with your own implementations:
 *
 * - GDNHLC_STATIC:
 *   If defined and GDNHLC_DECL is not defined, functions will be declared `static` instead of `extern`
 * - GDNHLC_DECL:
 *   Function declaration prefix (default: `extern` or `static` depending on GDNHLC_STATIC)
 */
#ifndef __GDNHLC_H__
#define __GDNHLC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "gdnative_api_struct.gen.h"

#ifndef GDNHLC_DECL
    #ifdef GDNHLC_STATIC
        #define GDNHLC_DECL static
    #else
        #define GDNHLC_DECL extern
    #endif
#endif

// Globals 
extern const godot_gdnative_core_api_struct *gdnhlc_core_api;
extern const godot_gdnative_core_1_1_api_struct *gdnhlc_core_1_1_api;
extern const godot_gdnative_core_1_2_api_struct *gdnhlc_core_1_2_api;
extern const godot_gdnative_ext_nativescript_api_struct *gdnhlc_nativescript_api;
extern const godot_gdnative_ext_nativescript_1_1_api_struct *gdnhlc_nativescript_1_1_api;
extern const godot_gdnative_ext_pluginscript_api_struct *gdnhlc_pluginscript_api;
extern const godot_gdnative_ext_android_api_struct *gdnhlc_android_api;
extern const godot_gdnative_ext_arvr_api_struct *gdnhlc_arvr_api;
extern const godot_gdnative_ext_arvr_1_2_api_struct *gdnhlc_arvr_1_2_api;
extern const godot_gdnative_ext_videodecoder_api_struct *gdnhlc_videodecoder_api;
extern const godot_gdnative_ext_net_api_struct *gdnhlc_net_api;
extern const godot_gdnative_ext_net_3_2_api_struct *gdnhlc_net_3_2_api;

/// Initialize globals. Call this on your own `godot_gdnative_init`
/// before any other gdnhlc functions.
GDNHLC_DECL void gdnhlc_gdnative_init(const godot_gdnative_init_options *options);

/// Terminate globals. Call this on your own `godot_gdnative_terminate`
GDNHLC_DECL void gdnhlc_gdnative_terminate(const godot_gdnative_terminate_options *options);

GDNHLC_DECL godot_variant gdnhlc_nil_variant();
GDNHLC_DECL godot_variant gdnhlc_bool_variant(godot_bool b);
GDNHLC_DECL godot_variant gdnhlc_uint_variant(const uint64_t u);
GDNHLC_DECL godot_variant gdnhlc_int_variant(const int64_t i);
GDNHLC_DECL godot_variant gdnhlc_real_variant(const double f);

/**
 * String abstraction.
 *
 * Handles godot_string and godot_char_string instances, providing access to
 * char buffers.
 */
typedef struct gdnhlc_string gdnhlc_string;

GDNHLC_DECL gdnhlc_string gdnhlc_string_from_godot_string(godot_string str);
GDNHLC_DECL gdnhlc_string gdnhlc_string_from_utf8(const char *cstr);
GDNHLC_DECL gdnhlc_string gdnhlc_string_from_utf8_with_len(const char *cstr, godot_int len);
GDNHLC_DECL gdnhlc_string gdnhlc_string_from_variant(const godot_variant *var);
GDNHLC_DECL godot_int gdnhlc_string_length(const gdnhlc_string *str);
GDNHLC_DECL const char *gdnhlc_string_chars(const gdnhlc_string *str);
GDNHLC_DECL void gdnhlc_string_destroy(gdnhlc_string *str);

/**
 * Generic buffer abstraction.
 *
 * Handles any kind of data, providing access to any kind of buffers, great
 * for using with APIs that require `void *` or other arrays.
 */
typedef struct gdnhlc_buffer gdnhlc_buffer;

/// Creates a buffer from a Variant, only borrowing memory.
GDNHLC_DECL gdnhlc_buffer gdnhlc_buffer_from_variant(const godot_variant *var);

/// Duplicates a buffer's memory using `godot_alloc`.
/// If `out_size` is not NULL, it will be filled with the buffer size.
GDNHLC_DECL void *gdnhlc_buffer_memdup(size_t *out_size);

struct gdnhlc_string {
    godot_string gdstring;
    godot_char_string gdchars;
};

#ifdef __cplusplus
}
#endif

#endif  // __GDNHLC_H__

///////////////////////////////////////////////////////////////////////////////

#ifdef GDNHLC_IMPLEMENTATION

const godot_gdnative_core_api_struct *gdnhlc_core_api;
const godot_gdnative_core_1_1_api_struct *gdnhlc_core_1_1_api;
const godot_gdnative_core_1_2_api_struct *gdnhlc_core_1_2_api;
const godot_gdnative_ext_nativescript_api_struct *gdnhlc_nativescript_api;
const godot_gdnative_ext_nativescript_1_1_api_struct *gdnhlc_nativescript_1_1_api;
const godot_gdnative_ext_pluginscript_api_struct *gdnhlc_pluginscript_api;
const godot_gdnative_ext_android_api_struct *gdnhlc_android_api;
const godot_gdnative_ext_arvr_api_struct *gdnhlc_arvr_api;
const godot_gdnative_ext_arvr_1_2_api_struct *gdnhlc_arvr_1_2_api;
const godot_gdnative_ext_videodecoder_api_struct *gdnhlc_videodecoder_api;
const godot_gdnative_ext_net_api_struct *gdnhlc_net_api;
const godot_gdnative_ext_net_3_2_api_struct *gdnhlc_net_3_2_api;

#define GDNHLC_LOG_ERROR(msg) gdnhlc_core_api->godot_print_error(msg, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define GDNHLC_LOG_ERROR_IF_FALSE(cond, msg) if(!(cond)) GDNHLC_LOG_ERROR("Error: !(" #cond ") " msg)

// Init and terminate
void gdnhlc_gdnative_init(const godot_gdnative_init_options *options) {
    gdnhlc_core_api = options->api_struct;
    for (const godot_gdnative_api_struct *ext = gdnhlc_core_api->next; ext; ext = ext->next) {
        if (ext->version.major == 1 && ext->version.minor == 1) {
			gdnhlc_core_1_1_api = (const godot_gdnative_core_1_1_api_struct *) ext;
		} else if (ext->version.major == 1 && ext->version.minor == 2) {
			gdnhlc_core_1_2_api = (const godot_gdnative_core_1_2_api_struct *) ext;
		}
    }

    for(unsigned int i = 0; i < gdnhlc_core_api->num_extensions; i++) {
        switch(gdnhlc_core_api->extensions[i]->type) {
            case GDNATIVE_EXT_NATIVESCRIPT:
                gdnhlc_nativescript_api = (const godot_gdnative_ext_nativescript_api_struct *) gdnhlc_core_api->extensions[i];
                for (const godot_gdnative_api_struct *ext = gdnhlc_nativescript_api->next; ext; ext = ext->next) {
                    if (ext->version.major == 1 && ext->version.minor == 1) {
                        gdnhlc_nativescript_1_1_api = (const godot_gdnative_ext_nativescript_1_1_api_struct *) ext;
                    }
                }
                break;

            case GDNATIVE_EXT_PLUGINSCRIPT:
                gdnhlc_pluginscript_api = (const godot_gdnative_ext_pluginscript_api_struct *) gdnhlc_core_api->extensions[i];
                break;

            case GDNATIVE_EXT_ANDROID:
                gdnhlc_android_api = (const godot_gdnative_ext_android_api_struct *) gdnhlc_core_api->extensions[i];
                break;

            case GDNATIVE_EXT_ARVR:
                gdnhlc_arvr_api = (const godot_gdnative_ext_arvr_api_struct *) gdnhlc_core_api->extensions[i];
                for (const godot_gdnative_api_struct *ext = gdnhlc_arvr_api->next; ext; ext = ext->next) {
                    if (ext->version.major == 1 && ext->version.minor == 2) {
                        gdnhlc_arvr_1_2_api = (const godot_gdnative_ext_arvr_1_2_api_struct *) ext;
                    }
                }
                break;

            case GDNATIVE_EXT_VIDEODECODER:
                gdnhlc_videodecoder_api = (const godot_gdnative_ext_videodecoder_api_struct *) gdnhlc_core_api->extensions[i];
                break;

            case GDNATIVE_EXT_NET:
                gdnhlc_net_api = (const godot_gdnative_ext_net_api_struct *) gdnhlc_core_api->extensions[i];
                for (const godot_gdnative_api_struct *ext = gdnhlc_net_api->next; ext; ext = ext->next) {
                    if (ext->version.major == 3 && ext->version.minor == 2) {
                        gdnhlc_net_3_2_api = (const godot_gdnative_ext_net_3_2_api_struct *) ext;
                    }
                }
                break;

            default:
                break;
        }
    }
}

void gdnhlc_gdnative_terminate(const godot_gdnative_terminate_options *options) {
    // Nothing for now
}

// Basic variants
godot_variant gdnhlc_nil_variant() {
    godot_variant var;
    gdnhlc_core_api->godot_variant_new_nil(&var);
    return var;
}

godot_variant gdnhlc_bool_variant(godot_bool b) {
    godot_variant var;
    gdnhlc_core_api->godot_variant_new_bool(&var, b);
    return var;
}

godot_variant gdnhlc_uint_variant(const uint64_t u) {
    godot_variant var;
    gdnhlc_core_api->godot_variant_new_uint(&var, u);
    return var;
}

godot_variant gdnhlc_int_variant(const int64_t i) {
    godot_variant var;
    gdnhlc_core_api->godot_variant_new_int(&var, i);
    return var;
}

godot_variant gdnhlc_real_variant(const double f) {
    godot_variant var;
    gdnhlc_core_api->godot_variant_new_real(&var, f);
    return var;
}

// String API
gdnhlc_string gdnhlc_string_from_godot_string(godot_string str) {
    gdnhlc_string s = {
        str,
        gdnhlc_core_api->godot_string_utf8(&str),
    };
    return s;
}

gdnhlc_string gdnhlc_string_from_utf8(const char *cstr) {
    return gdnhlc_string_from_godot_string(gdnhlc_core_api->godot_string_chars_to_utf8(cstr));
}

gdnhlc_string gdnhlc_string_from_utf8_with_len(const char *cstr, godot_int len) {
    return gdnhlc_string_from_godot_string(gdnhlc_core_api->godot_string_chars_to_utf8_with_len(cstr, len));
}

gdnhlc_string gdnhlc_string_from_variant(const godot_variant *var) {
    return gdnhlc_string_from_godot_string(gdnhlc_core_api->godot_variant_as_string(var));
}

godot_int gdnhlc_string_length(const gdnhlc_string *str) {
    return gdnhlc_core_api->godot_string_length(&str->gdstring);
}

const char *gdnhlc_string_chars(const gdnhlc_string *str) {
    return gdnhlc_core_api->godot_char_string_get_data(&str->gdchars);
}

void gdnhlc_string_destroy(gdnhlc_string *str) {
    gdnhlc_core_api->godot_char_string_destroy(&str->gdchars);
    gdnhlc_core_api->godot_string_destroy(&str->gdstring);
}

#endif  // GDNHLC_IMPLEMENTATION
