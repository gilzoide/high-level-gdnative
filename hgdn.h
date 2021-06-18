/** @file
 * hgdn.h -- Higher level GDNative C/C++ API
 *
 * Project URL: TODO
 *
 * Do this:
 * ```c
 *    #define HGDN_IMPLEMENTATION
 * ```
 * before you include this file in *one* C or C++ file to create the implementation.
 *
 * i.e.:
 * ```c
 *    #include ...
 *    #include ...
 *    #define HGDN_IMPLEMENTATION
 *    #include "hgdn.h"
 * ```
 *
 * Optionally provide the following defines with your own implementations:
 *
 * - HGDN_STATIC:
 *   If defined and HGDN_DECL is not defined, functions will be declared `static` instead of `extern`
 * - HGDN_DECL:
 *   Function declaration prefix (default: `extern` or `static` depending on HGDN_STATIC)
 */
#ifndef __HGDN_H__
#define __HGDN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "gdnative_api_struct.gen.h"

#ifndef HGDN_DECL
    #ifdef HGDN_STATIC
        #define HGDN_DECL static
    #else
        #define HGDN_DECL extern
    #endif
#endif

// Globals 
extern const godot_gdnative_core_api_struct *hgdn_core_api;
extern const godot_gdnative_core_1_1_api_struct *hgdn_core_1_1_api;
extern const godot_gdnative_core_1_2_api_struct *hgdn_core_1_2_api;
extern const godot_gdnative_ext_nativescript_api_struct *hgdn_nativescript_api;
extern const godot_gdnative_ext_nativescript_1_1_api_struct *hgdn_nativescript_1_1_api;
extern const godot_gdnative_ext_pluginscript_api_struct *hgdn_pluginscript_api;
extern const godot_gdnative_ext_android_api_struct *hgdn_android_api;
extern const godot_gdnative_ext_arvr_api_struct *hgdn_arvr_api;
extern const godot_gdnative_ext_arvr_1_2_api_struct *hgdn_arvr_1_2_api;
extern const godot_gdnative_ext_videodecoder_api_struct *hgdn_videodecoder_api;
extern const godot_gdnative_ext_net_api_struct *hgdn_net_api;
extern const godot_gdnative_ext_net_3_2_api_struct *hgdn_net_3_2_api;

#define HGDN_LOG_ERROR(msg) \
    hgdn_core_api->godot_print_error(msg, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define HGDN_LOG_ERROR_IF_FALSE(cond, msg) \
    if (!(cond)) HGDN_LOG_ERROR("Error: !(" #cond ") " msg)
#define HGDN_ASSERT_ARRAY_SIZE(arr, min_size) \
    if (hgdn_core_api->godot_array_size(arr) < min_size) { \
        HGDN_LOG_ERROR("Error: array should have at least " #min_size " elements"); \
        return hgdn_nil_variant(); \
    }

/// Initialize globals. Call this on your own `godot_gdnative_init`
/// before any other hgdn functions.
HGDN_DECL void hgdn_gdnative_init(const godot_gdnative_init_options *options);

/// Terminate globals. Call this on your own `godot_gdnative_terminate`
HGDN_DECL void hgdn_gdnative_terminate(const godot_gdnative_terminate_options *options);

/// Create a nil Variant
HGDN_DECL godot_variant hgdn_nil_variant();
/// Create a bool Variant
HGDN_DECL godot_variant hgdn_bool_variant(godot_bool b);
/// Create an unsigned Variant
HGDN_DECL godot_variant hgdn_uint_variant(const uint64_t u);
/// Create an integral Variant
HGDN_DECL godot_variant hgdn_int_variant(const int64_t i);
/// Create a real Variant
HGDN_DECL godot_variant hgdn_real_variant(const double f);



/**
 * String abstraction.
 *
 * Handles godot_string and godot_char_string instances, providing access to
 * char buffers.
 */
typedef struct hgdn_string hgdn_string;

HGDN_DECL hgdn_string hgdn_string_from_godot_string(godot_string str);
HGDN_DECL hgdn_string hgdn_string_from_utf8(const char *cstr);
HGDN_DECL hgdn_string hgdn_string_from_utf8_with_len(const char *cstr, godot_int len);
HGDN_DECL hgdn_string hgdn_string_from_variant(const godot_variant *var);
HGDN_DECL godot_int hgdn_string_length(const hgdn_string *str);
HGDN_DECL const char *hgdn_string_chars(const hgdn_string *str);
HGDN_DECL void hgdn_string_destroy(hgdn_string *str);

/**
 * Generic buffer abstraction.
 *
 * Handles any kind of data, providing access to any kind of buffers, great
 * for using with APIs that require `void *` or other arrays.
 */
typedef struct hgdn_buffer hgdn_buffer;

/// Creates a buffer from a Variant, only borrowing memory.
HGDN_DECL hgdn_buffer hgdn_buffer_from_variant(const godot_variant *var);

/// Duplicates a buffer's memory using `godot_alloc`.
/// If `out_size` is not NULL, it will be filled with the buffer size.
HGDN_DECL void *hgdn_buffer_memdup(size_t *out_size);

struct hgdn_string {
    godot_string gdstring;
    godot_char_string gdchars;
};

#ifdef __cplusplus
}
#endif

#endif  // __HGDN_H__

///////////////////////////////////////////////////////////////////////////////

#ifdef HGDN_IMPLEMENTATION

const godot_gdnative_core_api_struct *hgdn_core_api;
const godot_gdnative_core_1_1_api_struct *hgdn_core_1_1_api;
const godot_gdnative_core_1_2_api_struct *hgdn_core_1_2_api;
const godot_gdnative_ext_nativescript_api_struct *hgdn_nativescript_api;
const godot_gdnative_ext_nativescript_1_1_api_struct *hgdn_nativescript_1_1_api;
const godot_gdnative_ext_pluginscript_api_struct *hgdn_pluginscript_api;
const godot_gdnative_ext_android_api_struct *hgdn_android_api;
const godot_gdnative_ext_arvr_api_struct *hgdn_arvr_api;
const godot_gdnative_ext_arvr_1_2_api_struct *hgdn_arvr_1_2_api;
const godot_gdnative_ext_videodecoder_api_struct *hgdn_videodecoder_api;
const godot_gdnative_ext_net_api_struct *hgdn_net_api;
const godot_gdnative_ext_net_3_2_api_struct *hgdn_net_3_2_api;

// Init and terminate
void hgdn_gdnative_init(const godot_gdnative_init_options *options) {
    hgdn_core_api = options->api_struct;
    for (const godot_gdnative_api_struct *ext = hgdn_core_api->next; ext; ext = ext->next) {
        if (ext->version.major == 1 && ext->version.minor == 1) {
			hgdn_core_1_1_api = (const godot_gdnative_core_1_1_api_struct *) ext;
		} else if (ext->version.major == 1 && ext->version.minor == 2) {
			hgdn_core_1_2_api = (const godot_gdnative_core_1_2_api_struct *) ext;
		}
    }

    for(unsigned int i = 0; i < hgdn_core_api->num_extensions; i++) {
        switch(hgdn_core_api->extensions[i]->type) {
            case GDNATIVE_EXT_NATIVESCRIPT:
                hgdn_nativescript_api = (const godot_gdnative_ext_nativescript_api_struct *) hgdn_core_api->extensions[i];
                for (const godot_gdnative_api_struct *ext = hgdn_nativescript_api->next; ext; ext = ext->next) {
                    if (ext->version.major == 1 && ext->version.minor == 1) {
                        hgdn_nativescript_1_1_api = (const godot_gdnative_ext_nativescript_1_1_api_struct *) ext;
                    }
                }
                break;

            case GDNATIVE_EXT_PLUGINSCRIPT:
                hgdn_pluginscript_api = (const godot_gdnative_ext_pluginscript_api_struct *) hgdn_core_api->extensions[i];
                break;

            case GDNATIVE_EXT_ANDROID:
                hgdn_android_api = (const godot_gdnative_ext_android_api_struct *) hgdn_core_api->extensions[i];
                break;

            case GDNATIVE_EXT_ARVR:
                hgdn_arvr_api = (const godot_gdnative_ext_arvr_api_struct *) hgdn_core_api->extensions[i];
                for (const godot_gdnative_api_struct *ext = hgdn_arvr_api->next; ext; ext = ext->next) {
                    if (ext->version.major == 1 && ext->version.minor == 2) {
                        hgdn_arvr_1_2_api = (const godot_gdnative_ext_arvr_1_2_api_struct *) ext;
                    }
                }
                break;

            case GDNATIVE_EXT_VIDEODECODER:
                hgdn_videodecoder_api = (const godot_gdnative_ext_videodecoder_api_struct *) hgdn_core_api->extensions[i];
                break;

            case GDNATIVE_EXT_NET:
                hgdn_net_api = (const godot_gdnative_ext_net_api_struct *) hgdn_core_api->extensions[i];
                for (const godot_gdnative_api_struct *ext = hgdn_net_api->next; ext; ext = ext->next) {
                    if (ext->version.major == 3 && ext->version.minor == 2) {
                        hgdn_net_3_2_api = (const godot_gdnative_ext_net_3_2_api_struct *) ext;
                    }
                }
                break;

            default:
                break;
        }
    }
}

void hgdn_gdnative_terminate(const godot_gdnative_terminate_options *options) {
    // Nothing for now
}

// Basic variants
godot_variant hgdn_nil_variant() {
    godot_variant var;
    hgdn_core_api->godot_variant_new_nil(&var);
    return var;
}

godot_variant hgdn_bool_variant(godot_bool b) {
    godot_variant var;
    hgdn_core_api->godot_variant_new_bool(&var, b);
    return var;
}

godot_variant hgdn_uint_variant(const uint64_t u) {
    godot_variant var;
    hgdn_core_api->godot_variant_new_uint(&var, u);
    return var;
}

godot_variant hgdn_int_variant(const int64_t i) {
    godot_variant var;
    hgdn_core_api->godot_variant_new_int(&var, i);
    return var;
}

godot_variant hgdn_real_variant(const double f) {
    godot_variant var;
    hgdn_core_api->godot_variant_new_real(&var, f);
    return var;
}

// String API
hgdn_string hgdn_string_from_godot_string(godot_string str) {
    hgdn_string s = {
        str,
        hgdn_core_api->godot_string_utf8(&str),
    };
    return s;
}

hgdn_string hgdn_string_from_utf8(const char *cstr) {
    return hgdn_string_from_godot_string(hgdn_core_api->godot_string_chars_to_utf8(cstr));
}

hgdn_string hgdn_string_from_utf8_with_len(const char *cstr, godot_int len) {
    return hgdn_string_from_godot_string(hgdn_core_api->godot_string_chars_to_utf8_with_len(cstr, len));
}

hgdn_string hgdn_string_from_variant(const godot_variant *var) {
    return hgdn_string_from_godot_string(hgdn_core_api->godot_variant_as_string(var));
}

godot_int hgdn_string_length(const hgdn_string *str) {
    return hgdn_core_api->godot_string_length(&str->gdstring);
}

const char *hgdn_string_chars(const hgdn_string *str) {
    return hgdn_core_api->godot_char_string_get_data(&str->gdchars);
}

void hgdn_string_destroy(hgdn_string *str) {
    hgdn_core_api->godot_char_string_destroy(&str->gdchars);
    hgdn_core_api->godot_string_destroy(&str->gdstring);
}

#endif  // HGDN_IMPLEMENTATION
