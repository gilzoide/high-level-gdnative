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
extern const godot_gdnative_core_api_struct *gdnhlc_api;
extern const godot_gdnative_core_1_1_api_struct *gdnhlc_1_1_api;
extern const godot_gdnative_core_1_2_api_struct *gdnhlc_1_2_api;

/// Initialize globals. Always call this before doing anything else
void gdnhlc_api_init(const godot_gdnative_init_options *options);

/**
 * Generic buffer abstraction.
 *
 * Handles any kind of data, providing access to any kind of buffers, great
 * for using with APIs that require `void *` or other arrays.
 */
typedef struct gdnhlc_buffer gdnhlc_buffer;

/**
 * String abstraction.
 *
 * Handles godot_string and godot_char_string instances, providing access to
 * char buffers.
 */
typedef struct gdnhlc_string gdnhlc_string;

/// Creates a buffer from a Variant, only borrowing memory.
gdnhlc_buffer gdnhlc_buffer_from_variant(const godot_variant *var);

/// Duplicates a buffer's memory using `godot_alloc`.
/// If `out_size` is not NULL, it will be filled with the buffer size.
void *gdnhlc_buffer_memdup(size_t *out_size);

#ifdef __cplusplus
}
#endif

#endif  // __GDNHLC_H__

///////////////////////////////////////////////////////////////////////////////

#ifdef GDNHLC_IMPLEMENTATION

#define GDNHLC_LOG_ERROR(msg) gdnhlc_api->godot_print_error(msg, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define GDNHLC_LOG_ERROR_IF_FALSE(cond, msg) if(!(cond)) GDNHLC_LOG_ERROR("Error: !(" #cond ") " msg)

void gdnhlc_api_init(const godot_gdnative_init_options *options) {
    gdnhlc_api = options->api_struct;
    // Now find our extensions.
    for(int i = 0; i < gdnhlc_api->num_extensions; i++) {
        char msg[2] = { '0' + gdnhlc_api->extensions[i]->type, 0 };
        GDNHLC_LOG_ERROR(msg);
        switch(gdnhlc_api->extensions[i]->type) {
            default: break;
        }
    }
}

#endif  // GDNHLC_IMPLEMENTATION
