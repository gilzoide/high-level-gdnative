/** @file
 * hgdn.h -- High level GDNative C/C++ API
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


#ifndef HGDN_DECL
    #ifdef HGDN_STATIC
        #define HGDN_DECL static
    #else
        #define HGDN_DECL extern
    #endif
#endif


/// Custom Vector2 definition
typedef union hgdn_vector2 {
    float elements[2];
    // xy
    struct { float x, y; };
    // rg
    struct { float r, g; };
    // st
    struct { float s, t; };
    // uv
    struct { float u, v; };
    // Size: width/height
    struct { float width, height; };
} hgdn_vector2;

#ifndef GODOT_CORE_API_GODOT_VECTOR2_TYPE_DEFINED
typedef hgdn_vector2 godot_vector2;
#define GODOT_CORE_API_GODOT_VECTOR2_TYPE_DEFINED
#endif

/// Custom Vector3 definition
typedef union hgdn_vector3 {
    float elements[3];
    // xyz
    struct { float x, y, z; };
    struct { hgdn_vector2 xy; float _0; };
    struct { float _1; hgdn_vector2 yz; };
    // rgb
    struct { float r, g, b; };
    struct { hgdn_vector2 rg; float _2; };
    struct { float _3; hgdn_vector2 gb; };
    // stp
    struct { float s, t, p; };
    struct { hgdn_vector2 st; float _6; };
    struct { float _7; hgdn_vector2 tp; };
    // uv
    struct { float u, v, _4; };
    struct { hgdn_vector2 uv; float _5; };
    // 3D Size: width/height/depth
    struct { float width, height, depth; };
} hgdn_vector3;

#ifndef GODOT_CORE_API_GODOT_VECTOR3_TYPE_DEFINED
typedef hgdn_vector3 godot_vector3;
#define GODOT_CORE_API_GODOT_VECTOR3_TYPE_DEFINED
#endif

/// Custom Vector4 definition. May be used as Rect2, Plane, Quat and Color.
typedef union hgdn_vector4 {
    float elements[4];
    // xyzw
    struct { float x, y, z, w; };
    struct { hgdn_vector2 xy; hgdn_vector2 zw; };
    struct { hgdn_vector3 xyz; float _0; };
    struct { float _1; hgdn_vector3 yzw; };
    // rgba
    struct { float r, g, b, a; };
    struct { hgdn_vector2 rg; hgdn_vector2 ba; };
    struct { hgdn_vector3 rgb; float _2; };
    struct { float _3; hgdn_vector3 gba; };
    // stpq
    struct { float s, t, p, q; };
    struct { hgdn_vector2 st; hgdn_vector2 pq; };
    struct { hgdn_vector3 stp; float _6; };
    struct { float _7; hgdn_vector3 tpq; };
    // uv
    struct { float u, v; float _4[2]; };
    struct { hgdn_vector2 uv; float _5[2]; };
    // Rect2: position/size, position/width/height
    struct { float _8[2]; float width, height; };
    struct { hgdn_vector2 position; hgdn_vector2 size; };
    // Plane: normal/d
    struct { hgdn_vector3 normal; float d; };
} hgdn_vector4;

#ifndef GODOT_CORE_API_GODOT_RECT2_TYPE_DEFINED
typedef hgdn_vector4 godot_rect2;
#define GODOT_CORE_API_GODOT_RECT2_TYPE_DEFINED
#endif

#ifndef GODOT_CORE_API_GODOT_PLANE_TYPE_DEFINED
typedef hgdn_vector4 godot_plane;
#define GODOT_CORE_API_GODOT_PLANE_TYPE_DEFINED
#endif

#ifndef GODOT_CORE_API_GODOT_QUAT_TYPE_DEFINED
typedef hgdn_vector4 godot_quat;
#define GODOT_CORE_API_GODOT_QUAT_TYPE_DEFINED
#endif

#ifndef GODOT_CORE_API_GODOT_COLOR_TYPE_DEFINED
typedef hgdn_vector4 godot_color;
#define GODOT_CORE_API_GODOT_COLOR_TYPE_DEFINED
#endif

#include "gdnative_api_struct.gen.h"


// Global API pointers
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
/// GDNativeLibrary object being initialized
extern const godot_object *hgdn_library;


/// Prints the message `msg` as error
#define HGDN_LOG_ERROR(msg) \
    hgdn_core_api->godot_print_error((msg), __PRETTY_FUNCTION__, __FILE__, __LINE__)
/// If `cond` is false, print error message `msg` and return nil Variant
#define HGDN_ASSERT_MSG(cond, msg) \
    if (!(cond)) { \
        HGDN_LOG_ERROR((msg)); \
        return hgdn_new_nil_variant(); \
    }
/// If `cond` is false, print a generic error message and return nil Variant
#define HGDN_ASSERT(cond) \
    HGDN_ASSERT_MSG((cond), "Assertion error: !(" #cond ")")
/// If `arr` doesn't have at least `min_size` elements, print error message and return nil Variant
#define HGDN_ASSERT_ARRAY_SIZE(arr, min_size) \
    HGDN_ASSERT_MSG(hgdn_core_api->godot_array_size((arr)) >= (min_size), "Error: array should have size of at least " #min_size)
/// If `argc` isn't at least `min_size`, print error message and return nil Variant
#define HGDN_ASSERT_ARGS_SIZE(argc, min_size) \
    HGDN_ASSERT_MSG((argc) >= (min_size), "Error: expected at least " #min_size " arguments")


/// Initialize globals. Call this on your own `godot_gdnative_init` before any other HGDN functions.
HGDN_DECL void hgdn_gdnative_init(const godot_gdnative_init_options *options);
/// Terminate globals. Call this on your own `godot_gdnative_terminate`
HGDN_DECL void hgdn_gdnative_terminate(const godot_gdnative_terminate_options *options);


/// Wrapper for `godot_alloc` compatible with `malloc`
HGDN_DECL void *hgdn_alloc(size_t size);
/// Wrapper for `godot_realloc` compatible with `realloc`
HGDN_DECL void *hgdn_realloc(void *ptr, size_t size);
/// Wrapper for `godot_free` compatible with `free`.
/// It is safe to pass NULL without Godot triggering an error message.
HGDN_DECL void hgdn_free(void *ptr);
/// Helper to free an array of strings.
HGDN_DECL void hgdn_free_string_array(char **ptr, size_t size);


/// Allocates a new NULL terminated char string and copy `str` contents.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_len` is not NULL, it will be filled with the string length.
HGDN_DECL char *hgdn_string_dup(const godot_string *str, size_t *out_len);
/// Allocates a new byte array and copy `array` contents.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL uint8_t *hgdn_byte_array_dup(const godot_pool_byte_array *array, size_t *out_size);
/// Allocates a new int array and copy `array` contents.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_int *hgdn_int_array_dup(const godot_pool_int_array *array, size_t *out_size);
/// Allocates a new real array and copy `array` contents.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_real *hgdn_real_array_dup(const godot_pool_real_array *array, size_t *out_size);
/// Allocates a new string array and copy `array` contents.
/// Returned pointer must be freed with `hgdn_free_string_array`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL char **hgdn_string_array_dup(const godot_pool_string_array *array, size_t *out_size);
/// Allocates a new Vector2 array and copy `array` contents.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_vector2 *hgdn_vector2_array_dup(const godot_pool_vector2_array *array, size_t *out_size);
/// Allocates a new Vector3 array and copy `array` contents.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_vector3 *hgdn_vector3_array_dup(const godot_pool_vector3_array *array, size_t *out_size);
/// Allocates a new Color array and copy `array` contents.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_color *hgdn_color_array_dup(const godot_pool_color_array *array, size_t *out_size);


/// Allocates a new NULL terminated char string and copy `var` string content.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_len` is not NULL, it will be filled with the string length.
HGDN_DECL char *hgdn_string_from_variant(const godot_variant *var, size_t *out_len);
/// Allocates a new byte array and copy `var` byte array content.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL uint8_t *hgdn_byte_array_from_variant(const godot_variant *var, size_t *out_size);
/// Allocates a new int array and copy `var` int array content.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_int *hgdn_int_array_from_variant(const godot_variant *var, size_t *out_size);
/// Allocates a new real array and copy `var` real array content.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_real *hgdn_real_array_from_variant(const godot_variant *var, size_t *out_size);
/// Allocates a new string array and copy `var` string array content.
/// Returned pointer must be freed with `hgdn_free_string_array`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL char **hgdn_string_array_from_variant(const godot_variant *var, size_t *out_size);
/// Allocates a new Vector2 array and copy `var` Vector2 array content.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_vector2 *hgdn_vector2_array_from_variant(const godot_variant *var, size_t *out_size);
/// Allocates a new Vector3 array and copy `var` Vector3 array content.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_vector3 *hgdn_vector3_array_from_variant(const godot_variant *var, size_t *out_size);
/// Allocates a new Color array and copy `var` Color array content.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_color *hgdn_color_array_from_variant(const godot_variant *var, size_t *out_size);


/// Helper for getting a bool value from godot_array.
HGDN_DECL godot_bool hgdn_array_get_bool(const godot_array *array, const godot_int index);
/// Helper for getting a uint value from godot_array.
HGDN_DECL uint64_t hgdn_array_get_uint(const godot_array *array, const godot_int index);
/// Helper for getting a int value from godot_array.
HGDN_DECL int64_t hgdn_array_get_int(const godot_array *array, const godot_int index);
/// Helper for getting a real value from godot_array.
HGDN_DECL double hgdn_array_get_real(const godot_array *array, const godot_int index);
/// Helper for getting a string value from godot_array.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_len` is not NULL, it will be filled with the string length.
HGDN_DECL char *hgdn_array_get_string(const godot_array *array, const godot_int index, size_t *out_len);
/// Helper for getting a byte array from godot_array.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL uint8_t *hgdn_array_get_byte_array(const godot_array *array, const godot_int index, size_t *out_size);
/// Helper for getting an int array from godot_array.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_int *hgdn_array_get_int_array(const godot_array *array, const godot_int index, size_t *out_size);
/// Helper for getting a real array from godot_array.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_real *hgdn_array_get_real_array(const godot_array *array, const godot_int index, size_t *out_size);
/// Helper for getting a string array from godot_array.
/// Returned pointer must be freed with `hgdn_free_string_array`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL char **hgdn_array_get_string_array(const godot_array *array, const godot_int index, size_t *out_size);
/// Helper for getting a Vector2 array from godot_array.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_vector2 *hgdn_array_get_vector2_array(const godot_array *array, const godot_int index, size_t *out_size);
/// Helper for getting a Vector3 array from godot_array.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_vector3 *hgdn_array_get_vector3_array(const godot_array *array, const godot_int index, size_t *out_size);
/// Helper for getting a Color array from godot_array.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_color *hgdn_array_get_color_array(const godot_array *array, const godot_int index, size_t *out_size);


/// Helper for getting a bool value from method arguments
HGDN_DECL godot_bool hgdn_args_get_bool(const godot_variant **args, const godot_int index);
/// Helper for getting a uint value from method arguments
HGDN_DECL uint64_t hgdn_args_get_uint(const godot_variant **args, const godot_int index);
/// Helper for getting a int value from method arguments
HGDN_DECL int64_t hgdn_args_get_int(const godot_variant **args, const godot_int index);
/// Helper for getting a real value from method arguments
HGDN_DECL double hgdn_args_get_real(const godot_variant **args, const godot_int index);
/// Helper for getting a string value from method arguments
HGDN_DECL char *hgdn_args_get_string(const godot_variant **args, const godot_int index, size_t *out_len);
/// Helper for getting a byte array from method arguments.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL uint8_t *hgdn_args_get_byte_array(const godot_variant **args, const godot_int index, size_t *out_size);
/// Helper for getting an int array from method arguments.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_int *hgdn_args_get_int_array(const godot_variant **args, const godot_int index, size_t *out_size);
/// Helper for getting a real array from method arguments.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_real *hgdn_args_get_real_array(const godot_variant **args, const godot_int index, size_t *out_size);
/// Helper for getting a string array from method arguments.
/// Returned pointer must be freed with `hgdn_free_string_array`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL char **hgdn_args_get_string_array(const godot_variant **args, const godot_int index, size_t *out_size);
/// Helper for getting a Vector2 array from method arguments.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_vector2 *hgdn_args_get_vector2_array(const godot_variant **args, const godot_int index, size_t *out_size);
/// Helper for getting a Vector3 array from method arguments.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_vector3 *hgdn_args_get_vector3_array(const godot_variant **args, const godot_int index, size_t *out_size);
/// Helper for getting a Color array from method arguments.
/// Returned pointer must be freed with `hgdn_free`.
/// If `out_size` is not NULL, it will be filled with the array size.
HGDN_DECL godot_color *hgdn_args_get_color_array(const godot_variant **args, const godot_int index, size_t *out_size);


/// Create a PoolByteArray from NULL terminated buffer
HGDN_DECL godot_pool_byte_array hgdn_new_byte_array(const uint8_t *buffer);
/// Create a PoolByteArray from sized buffer
HGDN_DECL godot_pool_byte_array hgdn_new_byte_array_with_len(const uint8_t *buffer, const godot_int len);
/// Create a PoolIntArray from NULL terminated int buffer
HGDN_DECL godot_pool_int_array hgdn_new_int_array(const godot_int *buffer);
/// Create a PoolIntArray from sized int buffer
HGDN_DECL godot_pool_int_array hgdn_new_int_array_with_len(const godot_int *buffer, const godot_int len);
/// Create a PoolRealArray from NULL terminated real buffer
HGDN_DECL godot_pool_real_array hgdn_new_real_array(const godot_real *buffer);
/// Create a PoolRealArray from sized real buffer
HGDN_DECL godot_pool_real_array hgdn_new_real_array_with_len(const godot_real *buffer, const godot_int len);
/// Create a PoolStringArray from NULL terminated buffer of NULL terminated strings
HGDN_DECL godot_pool_string_array hgdn_new_string_array(const char **buffer);
/// Create a PoolStringArray from sized buffer of NULL terminated strings
HGDN_DECL godot_pool_string_array hgdn_new_string_array_with_len(const char **buffer, const godot_int len);
/// Create a PoolVector2Array from sized vector3 buffer
HGDN_DECL godot_pool_vector2_array hgdn_new_vector2_array_with_len(const godot_vector2 *buffer, const godot_int len);
/// Create a PoolVector3Array from sized vector3 buffer
HGDN_DECL godot_pool_vector3_array hgdn_new_vector3_array_with_len(const godot_vector3 *buffer, const godot_int len);
/// Create a PoolColorArray from sized color buffer
HGDN_DECL godot_pool_color_array hgdn_new_color_array_with_len(const godot_color *buffer, const godot_int len);

/// Create a nil Variant
HGDN_DECL godot_variant hgdn_new_nil_variant();
/// Create a bool Variant
HGDN_DECL godot_variant hgdn_new_bool_variant(const godot_bool b);
/// Create an unsigned Variant
HGDN_DECL godot_variant hgdn_new_uint_variant(const uint64_t u);
/// Create an integral Variant
HGDN_DECL godot_variant hgdn_new_int_variant(const int64_t i);
/// Create a real Variant
HGDN_DECL godot_variant hgdn_new_real_variant(const double f);
/// Create a string Variant from NULL terminated char string
HGDN_DECL godot_variant hgdn_new_string_variant(const char *cstr);
/// Create a string Variant from sized char string
HGDN_DECL godot_variant hgdn_new_string_variant_with_len(const char *cstr, const godot_int len);
/// Create a Vector2 Variant
HGDN_DECL godot_variant hgdn_new_vector2_variant(const godot_vector2 v);
/// Create a Vector3 Variant
HGDN_DECL godot_variant hgdn_new_vector3_variant(const godot_vector3 v);
/// Create a Color Variant
HGDN_DECL godot_variant hgdn_new_color_variant(const godot_color v);
/// Create a PoolByteArray Variant from NULL terminated byte string
HGDN_DECL godot_variant hgdn_new_byte_array_variant(const uint8_t *buffer);
/// Create a PoolByteArray Variant from sized byte string
HGDN_DECL godot_variant hgdn_new_byte_array_variant_with_len(const uint8_t *buffer, const godot_int len);
/// Create a PoolIntArray Variant from NULL terminated int string
HGDN_DECL godot_variant hgdn_new_int_array_variant(const godot_int *buffer);
/// Create a PoolIntArray Variant from sized int string
HGDN_DECL godot_variant hgdn_new_int_array_variant_with_len(const godot_int *buffer, const godot_int len);
/// Create a PoolRealArray Variant from NULL terminated real string
HGDN_DECL godot_variant hgdn_new_real_array_variant(const godot_real *buffer);
/// Create a PoolRealArray Variant from sized real string
HGDN_DECL godot_variant hgdn_new_real_array_variant_with_len(const godot_real *buffer, const godot_int len);
/// Create a PoolStringArray Variant from NULL terminated buffer of NULL terminated strings
HGDN_DECL godot_variant hgdn_new_string_array_variant(const char **buffer);
/// Create a PoolStringArray Variant from sized buffer of NULL terminated strings
HGDN_DECL godot_variant hgdn_new_string_array_variant_with_len(const char **buffer, const godot_int len);



#ifdef __cplusplus
}
#endif

#endif  // __HGDN_H__

///////////////////////////////////////////////////////////////////////////////

#ifdef HGDN_IMPLEMENTATION

#include <string.h>

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
const godot_object *hgdn_library;

// Init and terminate
void hgdn_gdnative_init(const godot_gdnative_init_options *options) {
    hgdn_library = options->gd_native_library;
    hgdn_core_api = options->api_struct;
    for (const godot_gdnative_api_struct *ext = hgdn_core_api->next; ext; ext = ext->next) {
        if (ext->version.major == 1 && ext->version.minor == 1) {
			hgdn_core_1_1_api = (const godot_gdnative_core_1_1_api_struct *) ext;
		} else if (ext->version.major == 1 && ext->version.minor == 2) {
			hgdn_core_1_2_api = (const godot_gdnative_core_1_2_api_struct *) ext;
		}
    }

    for (unsigned int i = 0; i < hgdn_core_api->num_extensions; i++) {
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
    // Noop for now
}

// Memory API
void *hgdn_alloc(size_t size) {
    return hgdn_core_api->godot_alloc(size);
}

void *hgdn_realloc(void *ptr, size_t size) {
    return hgdn_core_api->godot_realloc(ptr, size);
}

void hgdn_free(void *ptr) {
    if (ptr) {
        hgdn_core_api->godot_free(ptr);
    }
}

void hgdn_free_string_array(char **ptr, size_t size) {
    for (int i = 0; i < size; i++) {
        hgdn_free(ptr[i]);
    }
    hgdn_free(ptr);
}

// Array creation API
#define HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(kind, ctype) \
    godot_pool_##kind##_array hgdn_new_##kind##_array(const ctype *buffer) { \
        godot_pool_##kind##_array array; \
        hgdn_core_api->godot_pool_##kind##_array_new(&array); \
        for (const ctype *it = buffer; *it; it++) { \
            hgdn_core_api->godot_pool_##kind##_array_append(&array, *it); \
        } \
        return array; \
    }

HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(byte, uint8_t)
HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(int, godot_int)
HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(real, godot_real)

godot_pool_string_array hgdn_new_string_array(const char **buffer) {
    godot_pool_string_array array;
    hgdn_core_api->godot_pool_string_array_new(&array);
    for (const char **it = buffer; *it; it++) {
        godot_string str = hgdn_core_api->godot_string_chars_to_utf8(*it);
        hgdn_core_api->godot_pool_string_array_append(&array, &str);
        hgdn_core_api->godot_string_destroy(&str);
    }
    return array;
}

// Vector2, Vector3 and Color don't support NULL terminated arrays

#undef HGDN_DECLARE_NEW_POOL_ARRAY_FUNC

#define HGDN_DECLARE_NEW_POOL_ARRAY_WITH_LEN_FUNC(kind, ctype) \
    godot_pool_##kind##_array hgdn_new_##kind##_array_with_len(const ctype *buffer, godot_int len) { \
        godot_pool_##kind##_array array; \
        hgdn_core_api->godot_pool_##kind##_array_new(&array); \
        hgdn_core_api->godot_pool_##kind##_array_resize(&array, len); \
        godot_pool_##kind##_array_write_access *write = hgdn_core_api->godot_pool_##kind##_array_write(&array); \
        memcpy(hgdn_core_api->godot_pool_##kind##_array_write_access_ptr(write), buffer, len * sizeof(ctype)); \
        hgdn_core_api->godot_pool_##kind##_array_write_access_destroy(write); \
        return array; \
    }

HGDN_DECLARE_NEW_POOL_ARRAY_WITH_LEN_FUNC(byte, uint8_t)
HGDN_DECLARE_NEW_POOL_ARRAY_WITH_LEN_FUNC(int, godot_int)
HGDN_DECLARE_NEW_POOL_ARRAY_WITH_LEN_FUNC(real, godot_real)

godot_pool_string_array hgdn_new_string_array_with_len(const char **buffer, godot_int len) {
    godot_pool_string_array array;
    hgdn_core_api->godot_pool_string_array_new(&array);
    hgdn_core_api->godot_pool_string_array_resize(&array, len);
    for (godot_int i = 0; i < len; i++) {
        godot_string str = hgdn_core_api->godot_string_chars_to_utf8(buffer[i]);
        hgdn_core_api->godot_pool_string_array_set(&array, i, &str);
        hgdn_core_api->godot_string_destroy(&str);
    }
    return array;
}

HGDN_DECLARE_NEW_POOL_ARRAY_WITH_LEN_FUNC(vector2, godot_vector2)
HGDN_DECLARE_NEW_POOL_ARRAY_WITH_LEN_FUNC(vector3, godot_vector3)
HGDN_DECLARE_NEW_POOL_ARRAY_WITH_LEN_FUNC(color, godot_color)

#undef HGDN_DECLARE_NEW_POOL_ARRAY_WITH_LEN_FUNC

// Basic variants
godot_variant hgdn_new_nil_variant() {
    godot_variant var;
    hgdn_core_api->godot_variant_new_nil(&var);
    return var;
}

godot_variant hgdn_new_bool_variant(const godot_bool b) {
    godot_variant var;
    hgdn_core_api->godot_variant_new_bool(&var, b);
    return var;
}

godot_variant hgdn_new_uint_variant(const uint64_t u) {
    godot_variant var;
    hgdn_core_api->godot_variant_new_uint(&var, u);
    return var;
}

godot_variant hgdn_new_int_variant(const int64_t i) {
    godot_variant var;
    hgdn_core_api->godot_variant_new_int(&var, i);
    return var;
}

godot_variant hgdn_new_real_variant(const double f) {
    godot_variant var;
    hgdn_core_api->godot_variant_new_real(&var, f);
    return var;
}

godot_variant hgdn_new_string_variant(const char *cstr) {
    godot_string str = hgdn_core_api->godot_string_chars_to_utf8(cstr);
    godot_variant var;
    hgdn_core_api->godot_variant_new_string(&var, &str);
    hgdn_core_api->godot_string_destroy(&str);
    return var;
}

godot_variant hgdn_new_string_variant_with_len(const char *cstr, const godot_int len) {
    godot_string str = hgdn_core_api->godot_string_chars_to_utf8_with_len(cstr, len);
    godot_variant var;
    hgdn_core_api->godot_variant_new_string(&var, &str);
    hgdn_core_api->godot_string_destroy(&str);
    return var;
}

godot_variant hgdn_new_vector2_variant(const godot_vector2 v) {
    godot_variant var;
    hgdn_core_api->godot_variant_new_vector2(&var, &v);
    return var;
}

godot_variant hgdn_new_vector3_variant(const godot_vector3 v) {
    godot_variant var;
    hgdn_core_api->godot_variant_new_vector3(&var, &v);
    return var;
}

godot_variant hgdn_new_color_variant(const godot_color c) {
    godot_variant var;
    hgdn_core_api->godot_variant_new_color(&var, &c);
    return var;
}

#define HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_FUNC(kind, ctype) \
    godot_variant hgdn_new_##kind##_array_variant(const ctype *buffer) { \
        godot_pool_##kind##_array array = hgdn_new_##kind##_array(buffer); \
        godot_variant var; \
        hgdn_core_api->godot_variant_new_pool_##kind##_array(&var, &array); \
        hgdn_core_api->godot_pool_##kind##_array_destroy(&array); \
        return var; \
    }

#define HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_WITH_LEN_FUNC(kind, ctype) \
    godot_variant hgdn_new_##kind##_array_variant_with_len(const ctype *buffer, const godot_int len) { \
        godot_pool_##kind##_array array = hgdn_new_##kind##_array_with_len(buffer, len); \
        godot_variant var; \
        hgdn_core_api->godot_variant_new_pool_##kind##_array(&var, &array); \
        hgdn_core_api->godot_pool_##kind##_array_destroy(&array); \
        return var; \
    }

HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_FUNC(byte, uint8_t)
HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_WITH_LEN_FUNC(byte, uint8_t)
HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_FUNC(int, godot_int)
HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_WITH_LEN_FUNC(int, godot_int)
HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_FUNC(real, godot_real)
HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_WITH_LEN_FUNC(real, godot_real)
HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_FUNC(string, char *)
HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_WITH_LEN_FUNC(string, char *)

#undef HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_WITH_LEN_FUNC
#undef HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_FUNC

// Allocate arrays from Godot data types
HGDN_DECL char *hgdn_string_dup(const godot_string *str, size_t *out_len) {
    size_t len = hgdn_core_api->godot_string_length(str);
    char *new_string = (char *) hgdn_alloc(len + 1);
    if (new_string) {
        godot_char_string cs = hgdn_core_api->godot_string_utf8(str);
        memcpy(new_string, hgdn_core_api->godot_char_string_get_data(&cs), len + 1);
        hgdn_core_api->godot_char_string_destroy(&cs);
    }
    return new_string;
}

#define HGDN_DECLARE_POOL_ARRAY_DUP(kind, ctype) \
    ctype *hgdn_##kind##_array_dup(const godot_pool_##kind##_array *array, size_t *out_size) { \
        size_t size = hgdn_core_api->godot_pool_##kind##_array_size(array); \
        ctype *new_array = (ctype *) hgdn_alloc(size * sizeof(ctype)); \
        if (new_array) { \
            godot_pool_##kind##_array_read_access *read = hgdn_core_api->godot_pool_##kind##_array_read(array); \
            memcpy(new_array, hgdn_core_api->godot_pool_##kind##_array_read_access_ptr(read), size * sizeof(ctype)); \
            hgdn_core_api->godot_pool_##kind##_array_read_access_destroy(read); \
            *out_size = size; \
        } \
        return new_array; \
    }

HGDN_DECLARE_POOL_ARRAY_DUP(byte, uint8_t)
HGDN_DECLARE_POOL_ARRAY_DUP(int, godot_int)
HGDN_DECLARE_POOL_ARRAY_DUP(real, godot_real)

char **hgdn_string_array_dup(const godot_pool_string_array *array, size_t *out_size) {
    size_t size = hgdn_core_api->godot_pool_string_array_size(array);
    char **new_array = (char **) hgdn_alloc(size * sizeof(char *));
    if (new_array) {
        godot_pool_string_array_read_access *read = hgdn_core_api->godot_pool_string_array_read(array);
        const godot_string *ptr = hgdn_core_api->godot_pool_string_array_read_access_ptr(read);
        for (size_t i = 0; i < size; i++) {
            new_array[i] = hgdn_string_dup(&ptr[i], NULL);
        }
        hgdn_core_api->godot_pool_string_array_read_access_destroy(read);
        *out_size = size;
    }
    return new_array;
}

HGDN_DECLARE_POOL_ARRAY_DUP(vector2, godot_vector2)
HGDN_DECLARE_POOL_ARRAY_DUP(vector3, godot_vector3)
HGDN_DECLARE_POOL_ARRAY_DUP(color, godot_color)

#undef HGDN_DECLARE_POOL_ARRAY_DUP

// Get values from Variant
char *hgdn_string_from_variant(const godot_variant *var, size_t *out_len) {
    godot_string str = hgdn_core_api->godot_variant_as_string(var);
    char *res = hgdn_string_dup(&str, out_len);
    hgdn_core_api->godot_string_destroy(&str);
    return res;
}

#define HGDN_DECLARE_POOL_ARRAY_FROM_VARIANT(kind, ctype) \
    ctype *hgdn_##kind##_array_from_variant(const godot_variant *var, size_t *out_size) { \
        godot_pool_##kind##_array array = hgdn_core_api->godot_variant_as_pool_##kind##_array(var); \
        ctype *res = hgdn_##kind##_array_dup(&array, out_size); \
        hgdn_core_api->godot_pool_##kind##_array_destroy(&array); \
        return res; \
    }

HGDN_DECLARE_POOL_ARRAY_FROM_VARIANT(byte, uint8_t)
HGDN_DECLARE_POOL_ARRAY_FROM_VARIANT(int, godot_int)
HGDN_DECLARE_POOL_ARRAY_FROM_VARIANT(real, godot_real)
HGDN_DECLARE_POOL_ARRAY_FROM_VARIANT(string, char *)
HGDN_DECLARE_POOL_ARRAY_FROM_VARIANT(vector2, godot_vector2)
HGDN_DECLARE_POOL_ARRAY_FROM_VARIANT(vector3, godot_vector3)
HGDN_DECLARE_POOL_ARRAY_FROM_VARIANT(color, godot_color)

#undef HGDN_DECLARE_POOL_ARRAY_FROM_VARIANT

// Get values from array helpers
godot_bool hgdn_array_get_bool(const godot_array *array, const godot_int index) {
    return hgdn_core_api->godot_variant_as_bool(hgdn_core_api->godot_array_operator_index_const(array, index));
}

uint64_t hgdn_array_get_uint(const godot_array *array, const godot_int index) {
    return hgdn_core_api->godot_variant_as_uint(hgdn_core_api->godot_array_operator_index_const(array, index));
}

int64_t hgdn_array_get_int(const godot_array *array, const godot_int index) {
    return hgdn_core_api->godot_variant_as_int(hgdn_core_api->godot_array_operator_index_const(array, index));
}

double hgdn_array_get_real(const godot_array *array, const godot_int index) {
    return hgdn_core_api->godot_variant_as_real(hgdn_core_api->godot_array_operator_index_const(array, index));
}

char *hgdn_array_get_string(const godot_array *array, const godot_int index, size_t *out_len) {
    return hgdn_string_from_variant(hgdn_core_api->godot_array_operator_index_const(array, index), out_len);
}

#define HGDN_DECLARE_ARRAY_GET_POOL_ARRAY(kind, ctype) \
    ctype *hgdn_array_get_##kind##_array(const godot_array *array, const godot_int index, size_t *out_size) { \
        return hgdn_##kind##_array_from_variant(hgdn_core_api->godot_array_operator_index_const(array, index), out_size); \
    }

HGDN_DECLARE_ARRAY_GET_POOL_ARRAY(byte, uint8_t)
HGDN_DECLARE_ARRAY_GET_POOL_ARRAY(int, godot_int)
HGDN_DECLARE_ARRAY_GET_POOL_ARRAY(real, godot_real)
HGDN_DECLARE_ARRAY_GET_POOL_ARRAY(string, char *)
HGDN_DECLARE_ARRAY_GET_POOL_ARRAY(vector2, godot_vector2)
HGDN_DECLARE_ARRAY_GET_POOL_ARRAY(vector3, godot_vector3)
HGDN_DECLARE_ARRAY_GET_POOL_ARRAY(color, godot_color)

#undef HGDN_DECLARE_ARRAY_GET_POOL_ARRAY

// Get values from args helpers
godot_bool hgdn_args_get_bool(const godot_variant **args, const godot_int index) {
    return hgdn_core_api->godot_variant_as_bool(args[index]);
}

uint64_t hgdn_args_get_uint(const godot_variant **args, const godot_int index) {
    return hgdn_core_api->godot_variant_as_uint(args[index]);
}

int64_t hgdn_args_get_int(const godot_variant **args, const godot_int index) {
    return hgdn_core_api->godot_variant_as_int(args[index]);
}

double hgdn_args_get_real(const godot_variant **args, const godot_int index) {
    return hgdn_core_api->godot_variant_as_real(args[index]);
}

char *hgdn_args_get_string(const godot_variant **args, const godot_int index, size_t *out_len) {
    return hgdn_string_from_variant(args[index], out_len);
}

#define HGDN_DECLARE_ARGS_GET_POOL_ARRAY(kind, ctype) \
    ctype *hgdn_array_get_##kind##_array(const godot_variant **args, const godot_int index, size_t *out_size) { \
        return hgdn_##kind##_array_from_variant(args[index], out_size); \
    }

HGDN_DECLARE_ARGS_GET_POOL_ARRAY(byte, uint8_t)
HGDN_DECLARE_ARGS_GET_POOL_ARRAY(int, godot_int)
HGDN_DECLARE_ARGS_GET_POOL_ARRAY(real, godot_real)
HGDN_DECLARE_ARGS_GET_POOL_ARRAY(string, char *)
HGDN_DECLARE_ARGS_GET_POOL_ARRAY(vector2, godot_vector2)
HGDN_DECLARE_ARGS_GET_POOL_ARRAY(vector3, godot_vector3)
HGDN_DECLARE_ARGS_GET_POOL_ARRAY(color, godot_color)

#undef HGDN_DECLARE_ARRAY_GET_POOL_ARRAY

#endif  // HGDN_IMPLEMENTATION
