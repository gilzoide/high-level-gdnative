/** @file
 * hgdn.h -- High level GDNative C/C++ API
 *
 * Project URL: https://github.com/gilzoide/high-level-gdnative
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
 * - HGDN_STRING_FORMAT_BUFFER_SIZE:
 *   Size of the global char buffer used for `hgdn_print*` functions. Defaults to 1024
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

#ifndef HGDN_STRING_FORMAT_BUFFER_SIZE
    #define HGDN_STRING_FORMAT_BUFFER_SIZE 1024
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

// Macro magic to get the number of variable arguments
// Ref: https://groups.google.com/g/comp.std.c/c/d-6Mj5Lko_s
#define HGDN_NARG(...) \
         HGDN_NARG_(__VA_ARGS__, HGDN_RSEQ_N())
#define HGDN_NARG_(...) \
         HGDN_ARG_N(__VA_ARGS__)
#define HGDN_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define HGDN_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0


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
/// Helper to free an array of strings created from @ref hgdn_string_array_dup.
HGDN_DECL void hgdn_free_string_array(char **ptr, size_t size);

/// Outputs a `printf` formatted message to standard output.
HGDN_DECL void hgdn_print(const char *fmt, ...);
/// Outputs a `printf` formatted message as warning. Use HGDN_PRINT_WARNING to use inferred current function name, file name and line
HGDN_DECL void hgdn_print_warning(const char *funcname, const char *filename, int line, const char *fmt, ...);
/// Outputs a `printf` formatted message as error. Use HGDN_PRINT_ERROR to use inferred current function name, file name and line
HGDN_DECL void hgdn_print_error(const char *funcname, const char *filename, int line, const char *fmt, ...);
/// Calls `hgdn_print_warning` with current function name, file name and line
#define HGDN_PRINT_WARNING(fmt, ...)  (hgdn_print_warning(__PRETTY_FUNCTION__, __FILE__, __LINE__, fmt, ##__VA_ARGS__))
/// Calls `hgdn_print_error` with current function name, file name and line
#define HGDN_PRINT_ERROR(fmt, ...)  (hgdn_print_error(__PRETTY_FUNCTION__, __FILE__, __LINE__, fmt, ##__VA_ARGS__))

/// If `cond` is false, print formatted error message and return nil Variant
#define HGDN_ASSERT_MSG(cond, fmt, ...)  if(!(cond)){ HGDN_PRINT_ERROR(fmt, ##__VA_ARGS__); return hgdn_new_nil_variant(); }
/// If `cond` is false, print a generic error message and return nil Variant
#define HGDN_ASSERT(cond)  HGDN_ASSERT_MSG((cond), "Assertion error: !(" #cond ")")
/// If `arr` doesn't have at least `min_size` elements, print error message and return nil Variant
#define HGDN_ASSERT_ARRAY_SIZE(arr, min_size)  HGDN_ASSERT_MSG(hgdn_core_api->godot_array_size((arr)) >= (min_size), "Error: array should have size of at least " #min_size ", got %d", hgdn_core_api->godot_array_size((arr)))
/// If `argc` isn't at least `min_size`, print error message and return nil Variant
#define HGDN_ASSERT_ARGS_SIZE(argc, min_size)  HGDN_ASSERT_MSG((argc) >= (min_size), "Error: expected at least " #min_size " arguments, got %d", argc)

// Helper functions that allocate buffers and copy String/Pool*Array contents
// Returned pointer must be freed with `hgdn_free`.
// If `out_size` is not NULL, it will be filled with the string/array size.
HGDN_DECL char *hgdn_string_dup(const godot_string *str, size_t *out_size);
HGDN_DECL uint8_t *hgdn_byte_array_dup(const godot_pool_byte_array *array, size_t *out_size);
HGDN_DECL godot_int *hgdn_int_array_dup(const godot_pool_int_array *array, size_t *out_size);
HGDN_DECL godot_real *hgdn_real_array_dup(const godot_pool_real_array *array, size_t *out_size);
HGDN_DECL godot_vector2 *hgdn_vector2_array_dup(const godot_pool_vector2_array *array, size_t *out_size);
HGDN_DECL godot_vector3 *hgdn_vector3_array_dup(const godot_pool_vector3_array *array, size_t *out_size);
HGDN_DECL godot_color *hgdn_color_array_dup(const godot_pool_color_array *array, size_t *out_size);
// Returned pointer must be freed with `hgdn_free_string_array`
HGDN_DECL char **hgdn_string_array_dup(const godot_pool_string_array *array, size_t *out_size);


// Helper functions that allocate buffers and copy Variant String/Pool*Array content
// Returned pointer must be freed with `hgdn_free`.
// If `out_size` is not NULL, it will be filled with the string/array size.
HGDN_DECL char *hgdn_string_from_variant(const godot_variant *var, size_t *out_size);
HGDN_DECL uint8_t *hgdn_byte_array_from_variant(const godot_variant *var, size_t *out_size);
HGDN_DECL godot_int *hgdn_int_array_from_variant(const godot_variant *var, size_t *out_size);
HGDN_DECL godot_real *hgdn_real_array_from_variant(const godot_variant *var, size_t *out_size);
HGDN_DECL godot_vector2 *hgdn_vector2_array_from_variant(const godot_variant *var, size_t *out_size);
HGDN_DECL godot_vector3 *hgdn_vector3_array_from_variant(const godot_variant *var, size_t *out_size);
HGDN_DECL godot_color *hgdn_color_array_from_variant(const godot_variant *var, size_t *out_size);
// Returned pointer must be freed with `hgdn_free_string_array`
HGDN_DECL char **hgdn_string_array_from_variant(const godot_variant *var, size_t *out_size);


// Helper functions to get values directly from a godot_array position
HGDN_DECL godot_bool hgdn_array_get_bool(const godot_array *array, const godot_int index);
HGDN_DECL uint64_t hgdn_array_get_uint(const godot_array *array, const godot_int index);
HGDN_DECL int64_t hgdn_array_get_int(const godot_array *array, const godot_int index);
HGDN_DECL double hgdn_array_get_real(const godot_array *array, const godot_int index);
HGDN_DECL godot_vector2 hgdn_array_get_vector2(const godot_array *array, const godot_int index);
HGDN_DECL godot_vector3 hgdn_array_get_vector3(const godot_array *array, const godot_int index);
HGDN_DECL godot_rect2 hgdn_array_get_rect2(const godot_array *array, const godot_int index);
HGDN_DECL godot_plane hgdn_array_get_plane(const godot_array *array, const godot_int index);
HGDN_DECL godot_quat hgdn_array_get_quat(const godot_array *array, const godot_int index);
HGDN_DECL godot_aabb hgdn_array_get_aabb(const godot_array *array, const godot_int index);
HGDN_DECL godot_basis hgdn_array_get_basis(const godot_array *array, const godot_int index);
HGDN_DECL godot_transform2d hgdn_array_get_transform2d(const godot_array *array, const godot_int index);
HGDN_DECL godot_transform hgdn_array_get_transform(const godot_array *array, const godot_int index);
HGDN_DECL godot_color hgdn_array_get_color(const godot_array *array, const godot_int index);
HGDN_DECL godot_node_path hgdn_array_get_node_path(const godot_array *array, const godot_int index);
HGDN_DECL godot_rid hgdn_array_get_rid(const godot_array *array, const godot_int index);
HGDN_DECL godot_object *hgdn_array_get_object(const godot_array *array, const godot_int index);
HGDN_DECL godot_dictionary hgdn_array_get_dictionary(const godot_array *array, const godot_int index);
HGDN_DECL godot_array hgdn_array_get_array(const godot_array *array, const godot_int index);
// These use the `*_dup` functions and follow the same caveats
HGDN_DECL char *hgdn_array_get_string(const godot_array *array, const godot_int index, size_t *out_size);
HGDN_DECL uint8_t *hgdn_array_get_byte_array(const godot_array *array, const godot_int index, size_t *out_size);
HGDN_DECL godot_int *hgdn_array_get_int_array(const godot_array *array, const godot_int index, size_t *out_size);
HGDN_DECL godot_real *hgdn_array_get_real_array(const godot_array *array, const godot_int index, size_t *out_size);
HGDN_DECL godot_vector2 *hgdn_array_get_vector2_array(const godot_array *array, const godot_int index, size_t *out_size);
HGDN_DECL godot_vector3 *hgdn_array_get_vector3_array(const godot_array *array, const godot_int index, size_t *out_size);
HGDN_DECL godot_color *hgdn_array_get_color_array(const godot_array *array, const godot_int index, size_t *out_size);
HGDN_DECL char **hgdn_array_get_string_array(const godot_array *array, const godot_int index, size_t *out_size);


// Helper functions to get values directly from method arguments
HGDN_DECL godot_bool hgdn_args_get_bool(const godot_variant **args, const godot_int index);
HGDN_DECL uint64_t hgdn_args_get_uint(const godot_variant **args, const godot_int index);
HGDN_DECL int64_t hgdn_args_get_int(const godot_variant **args, const godot_int index);
HGDN_DECL double hgdn_args_get_real(const godot_variant **args, const godot_int index);
HGDN_DECL godot_vector2 hgdn_args_get_vector2(const godot_variant **args, const godot_int index);
HGDN_DECL godot_vector3 hgdn_args_get_vector3(const godot_variant **args, const godot_int index);
HGDN_DECL godot_rect2 hgdn_args_get_rect2(const godot_variant **args, const godot_int index);
HGDN_DECL godot_plane hgdn_args_get_plane(const godot_variant **args, const godot_int index);
HGDN_DECL godot_quat hgdn_args_get_quat(const godot_variant **args, const godot_int index);
HGDN_DECL godot_aabb hgdn_args_get_aabb(const godot_variant **args, const godot_int index);
HGDN_DECL godot_basis hgdn_args_get_basis(const godot_variant **args, const godot_int index);
HGDN_DECL godot_transform2d hgdn_args_get_transform2d(const godot_variant **args, const godot_int index);
HGDN_DECL godot_transform hgdn_args_get_transform(const godot_variant **args, const godot_int index);
HGDN_DECL godot_color hgdn_args_get_color(const godot_variant **args, const godot_int index);
HGDN_DECL godot_node_path hgdn_args_get_node_path(const godot_variant **args, const godot_int index);
HGDN_DECL godot_rid hgdn_args_get_rid(const godot_variant **args, const godot_int index);
HGDN_DECL godot_object *hgdn_args_get_object(const godot_variant **args, const godot_int index);
HGDN_DECL godot_dictionary hgdn_args_get_dictionary(const godot_variant **args, const godot_int index);
HGDN_DECL godot_array hgdn_args_get_array(const godot_variant **args, const godot_int index);
// These use the `*_dup` functions and follow the same caveats
HGDN_DECL char *hgdn_args_get_string(const godot_variant **args, const godot_int index, size_t *out_size);
HGDN_DECL uint8_t *hgdn_args_get_byte_array(const godot_variant **args, const godot_int index, size_t *out_size);
HGDN_DECL godot_int *hgdn_args_get_int_array(const godot_variant **args, const godot_int index, size_t *out_size);
HGDN_DECL godot_real *hgdn_args_get_real_array(const godot_variant **args, const godot_int index, size_t *out_size);
HGDN_DECL godot_vector2 *hgdn_args_get_vector2_array(const godot_variant **args, const godot_int index, size_t *out_size);
HGDN_DECL godot_vector3 *hgdn_args_get_vector3_array(const godot_variant **args, const godot_int index, size_t *out_size);
HGDN_DECL godot_color *hgdn_args_get_color_array(const godot_variant **args, const godot_int index, size_t *out_size);
HGDN_DECL char **hgdn_args_get_string_array(const godot_variant **args, const godot_int index, size_t *out_size);


// Helper functions to create Strings
HGDN_DECL godot_string hgdn_new_string(const char *cstr);
HGDN_DECL godot_string hgdn_new_string_with_len(const char *cstr, const godot_int len);
#define HGDN_NEW_STRING_LITERAL(literal_str) (hgdn_new_string_with_len((literal_str), sizeof(literal_str)))
// `fmt` is a `printf` compatible format
HGDN_DECL godot_string hgdn_new_formatted_string(const char *fmt, ...);


// Helper functions to create Pool*Arrays/Arrays from sized buffers
HGDN_DECL godot_pool_byte_array hgdn_new_byte_array(const uint8_t *buffer, const godot_int size);
HGDN_DECL godot_pool_int_array hgdn_new_int_array(const godot_int *buffer, const godot_int size);
HGDN_DECL godot_pool_real_array hgdn_new_real_array(const godot_real *buffer, const godot_int size);
HGDN_DECL godot_pool_vector2_array hgdn_new_vector2_array(const godot_vector2 *buffer, const godot_int size);
HGDN_DECL godot_pool_vector3_array hgdn_new_vector3_array(const godot_vector3 *buffer, const godot_int size);
HGDN_DECL godot_pool_color_array hgdn_new_color_array(const godot_color *buffer, const godot_int size);
// All strings must be NULL terminated.
HGDN_DECL godot_pool_string_array hgdn_new_string_array(const char *const *buffer, const godot_int size);
HGDN_DECL godot_array hgdn_new_array(const godot_variant *const *buffer, const godot_int size);
// Variants in `buffer` will be destroyed, convenient if you create Variants only for constructing the Array
HGDN_DECL godot_array hgdn_new_array_own(godot_variant *buffer, const godot_int size);


// Helper variadic macros/templates to create Pool*Arrays/Arrays
#if defined(__cplusplus) && __cplusplus >= 201103L  // Parameter pack is a C++11 feature
extern "C++" {
    template<typename... Args> godot_pool_byte_array hgdn_new_byte_array_args(Args... args) {
        uint8_t buffer[] = { args... };
        return hgdn_new_byte_array(buffer, sizeof...(args));
    }
    template<typename... Args> godot_pool_int_array hgdn_new_int_array_args(Args... args) {
        godot_int buffer[] = { args... };
        return hgdn_new_int_array(buffer, sizeof...(args));
    }
    template<typename... Args> godot_pool_real_array hgdn_new_real_array_args(Args... args) {
        godot_real buffer[] = { args... };
        return hgdn_new_real_array(buffer, sizeof...(args));
    }
    template<typename... Args> godot_pool_vector2_array hgdn_new_vector2_array_args(Args... args) {
        godot_vector2 buffer[] = { args... };
        return hgdn_new_vector2_array(buffer, sizeof...(args));
    }
    template<typename... Args> godot_pool_vector3_array hgdn_new_vector3_array_args(Args... args) {
        godot_vector3 buffer[] = { args... };
        return hgdn_new_vector3_array(buffer, sizeof...(args));
    }
    template<typename... Args> godot_pool_color_array hgdn_new_color_array_args(Args... args) {
        godot_color buffer[] = { args... };
        return hgdn_new_color_array(buffer, sizeof...(args));
    }
    template<typename... Args> godot_pool_string_array hgdn_new_string_array_args(Args... args) {
        const char *const buffer[] = { args... };
        return hgdn_new_string_array(buffer, sizeof...(args));
    }
    template<typename... Args> godot_array hgdn_new_array_args(Args... args) {
        godot_variant *const buffer[] = { args... };
        return hgdn_new_array(buffer, sizeof...(args));
    }
    template<typename... Args> godot_array hgdn_new_array_own_args(Args... args) {
        godot_variant buffer[] = { args... };
        return hgdn_new_array_own(buffer, sizeof...(args));
    }
}
#else
#define hgdn_new_byte_array_args(...)  (hgdn_new_byte_array((const uint8_t[]){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_int_array_args(...)  (hgdn_new_int_array((const godot_int[]){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_real_array_args(...)  (hgdn_new_real_array((const godot_real[]){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_vector2_array_args(...)  (hgdn_new_vector2_array((const godot_vector2[]){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_vector3_array_args(...)  (hgdn_new_vector3_array((const godot_vector3[]){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_color_array_args(...)  (hgdn_new_color_array((const godot_color[]){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_string_array_args(...)  (hgdn_new_string_array((const char *const []){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_array_args(...)  (hgdn_new_array((const godot_variant *const []){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_array_own_args(...)  (hgdn_new_array_own((godot_variant[]){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#endif


// Helper functions to create Variant values
HGDN_DECL godot_variant hgdn_new_nil_variant();
HGDN_DECL godot_variant hgdn_new_bool_variant(const godot_bool b);
HGDN_DECL godot_variant hgdn_new_uint_variant(const uint64_t u);
HGDN_DECL godot_variant hgdn_new_int_variant(const int64_t i);
HGDN_DECL godot_variant hgdn_new_real_variant(const double f);
HGDN_DECL godot_variant hgdn_new_string_variant(const char *cstr);
HGDN_DECL godot_variant hgdn_new_string_variant_with_len(const char *cstr, const godot_int len);
#define HGDN_NEW_STRING_LITERAL_VARIANT(literal_str) (hgdn_new_string_variant_with_len((literal_str), sizeof(literal_str)))
// `fmt` is a `printf` compatible format
HGDN_DECL godot_variant hgdn_new_formatted_string_variant(const char *fmt, ...);
HGDN_DECL godot_variant hgdn_new_vector2_variant(const godot_vector2 v);
HGDN_DECL godot_variant hgdn_new_vector3_variant(const godot_vector3 v);
HGDN_DECL godot_variant hgdn_new_color_variant(const godot_color v);
HGDN_DECL godot_variant hgdn_new_byte_array_variant(const uint8_t *buffer, const godot_int size);
HGDN_DECL godot_variant hgdn_new_int_array_variant(const godot_int *buffer, const godot_int size);
HGDN_DECL godot_variant hgdn_new_real_array_variant(const godot_real *buffer, const godot_int size);
HGDN_DECL godot_variant hgdn_new_vector2_array_variant(const godot_vector2 *buffer, const godot_int size);
HGDN_DECL godot_variant hgdn_new_vector3_array_variant(const godot_vector3 *buffer, const godot_int size);
HGDN_DECL godot_variant hgdn_new_color_array_variant(const godot_color *buffer, const godot_int size);
// All strings must be NULL terminated.
HGDN_DECL godot_variant hgdn_new_string_array_variant(const char *const *buffer, const godot_int size);
HGDN_DECL godot_variant hgdn_new_array_variant(const godot_variant *const *buffer, const godot_int size);
HGDN_DECL godot_variant hgdn_new_array_own_variant(godot_variant *buffer, const godot_int size);

// Helper variadic macros/templates to create Pool*Array/Array Variants
#if defined(__cplusplus) && __cplusplus >= 201103L  // Parameter pack is a C++11 feature
extern "C++" {
    template<typename... Args> godot_variant hgdn_new_byte_array_variant_args(Args... args) {
        uint8_t buffer[] = { args... };
        return hgdn_new_byte_array_variant(buffer, sizeof...(args));
    }
    template<typename... Args> godot_variant hgdn_new_int_array_variant_args(Args... args) {
        godot_int buffer[] = { args... };
        return hgdn_new_int_array_variant(buffer, sizeof...(args));
    }
    template<typename... Args> godot_variant hgdn_new_real_array_variant_args(Args... args) {
        godot_real buffer[] = { args... };
        return hgdn_new_real_array_variant(buffer, sizeof...(args));
    }
    template<typename... Args> godot_variant hgdn_new_vector2_array_variant_args(Args... args) {
        godot_vector2 buffer[] = { args... };
        return hgdn_new_vector2_array_variant(buffer, sizeof...(args));
    }
    template<typename... Args> godot_variant hgdn_new_vector3_array_variant_args(Args... args) {
        godot_vector3 buffer[] = { args... };
        return hgdn_new_vector3_array_variant(buffer, sizeof...(args));
    }
    template<typename... Args> godot_variant hgdn_new_color_array_variant_args(Args... args) {
        godot_color buffer[] = { args... };
        return hgdn_new_color_array_variant(buffer, sizeof...(args));
    }
    template<typename... Args> godot_variant hgdn_new_string_array_variant_args(Args... args) {
        const char *const buffer[] = { args... };
        return hgdn_new_string_array_variant(buffer, sizeof...(args));
    }
    template<typename... Args> godot_variant hgdn_new_array_variant_args(Args... args) {
        godot_variant *const buffer[] = { args... };
        return hgdn_new_array_variant(buffer, sizeof...(args));
    }
    template<typename... Args> godot_variant hgdn_new_array_own_variant_args(Args... args) {
        godot_variant buffer[] = { args... };
        return hgdn_new_array_own_variant(buffer, sizeof...(args));
    }
}
#else
#define hgdn_new_byte_array_variant_args(...)  (hgdn_new_byte_array_variant((const uint8_t[]){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_int_array_variant_args(...)  (hgdn_new_int_array_variant((const godot_int[]){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_real_array_variant_args(...)  (hgdn_new_real_array_variant((const godot_real[]){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_vector2_array_variant_args(...)  (hgdn_new_vector2_array_variant((const godot_vector2[]){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_vector3_array_variant_args(...)  (hgdn_new_vector3_array_variant((const godot_vector3[]){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_color_array_variant_args(...)  (hgdn_new_color_array_variant((const godot_color[]){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_string_array_variant_args(...)  (hgdn_new_string_array_variant((const char * const []){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_array_variant_args(...)  (hgdn_new_array_variant((const godot_variant *const []){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#define hgdn_new_array_own_variant_args(...)  (hgdn_new_array_own_variant((godot_variant[]){ __VA_ARGS__ }, HGDN_NARG(__VA_ARGS__)))
#endif

#ifdef __cplusplus
}
#endif

#endif  // __HGDN_H__

///////////////////////////////////////////////////////////////////////////////

#ifdef HGDN_IMPLEMENTATION

#include <stdarg.h>
#include <stdio.h>
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

char hgdn__format_string_buffer[HGDN_STRING_FORMAT_BUFFER_SIZE];
#define HGDN__FILL_FORMAT_BUFFER(fmt, ...) \
    va_list args; \
    va_start(args, fmt); \
    godot_int size = vsnprintf(hgdn__format_string_buffer, HGDN_STRING_FORMAT_BUFFER_SIZE, fmt, args); \
    if (size > HGDN_STRING_FORMAT_BUFFER_SIZE) { \
        size = HGDN_STRING_FORMAT_BUFFER_SIZE; \
    } \
    va_end(args)


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

// Print functions
void hgdn_print(const char *fmt, ...) {
    HGDN__FILL_FORMAT_BUFFER(fmt, ...);
    godot_string str = hgdn_new_string_with_len(hgdn__format_string_buffer, size);
    hgdn_core_api->godot_print(&str);
    hgdn_core_api->godot_string_destroy(&str);
}

void hgdn_print_warning(const char *funcname, const char *filename, int line, const char *fmt, ...) {
    HGDN__FILL_FORMAT_BUFFER(fmt, ...);
    hgdn_core_api->godot_print_warning(hgdn__format_string_buffer, funcname, filename, line);
}

void hgdn_print_error(const char *funcname, const char *filename, int line, const char *fmt, ...) {
    HGDN__FILL_FORMAT_BUFFER(fmt, ...);
    hgdn_core_api->godot_print_error(hgdn__format_string_buffer, funcname, filename, line);
}

// String creation API
godot_string hgdn_new_string(const char *cstr) {
    return hgdn_core_api->godot_string_chars_to_utf8(cstr);
}

godot_string hgdn_new_string_with_len(const char *cstr, const godot_int len) {
    return hgdn_core_api->godot_string_chars_to_utf8_with_len(cstr, len);
}

godot_string hgdn_new_formatted_string(const char *fmt, ...) {
    HGDN__FILL_FORMAT_BUFFER(fmt, ...);
    return hgdn_new_string_with_len(hgdn__format_string_buffer, size);
}

// Array creation API
#define HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(kind, ctype) \
    godot_pool_##kind##_array hgdn_new_##kind##_array(const ctype *buffer, const godot_int size) { \
        godot_pool_##kind##_array array; \
        hgdn_core_api->godot_pool_##kind##_array_new(&array); \
        hgdn_core_api->godot_pool_##kind##_array_resize(&array, size); \
        godot_pool_##kind##_array_write_access *write = hgdn_core_api->godot_pool_##kind##_array_write(&array); \
        memcpy(hgdn_core_api->godot_pool_##kind##_array_write_access_ptr(write), buffer, size * sizeof(ctype)); \
        hgdn_core_api->godot_pool_##kind##_array_write_access_destroy(write); \
        return array; \
    }

HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(byte, uint8_t)
HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(int, godot_int)
HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(real, godot_real)
HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(vector2, godot_vector2)
HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(vector3, godot_vector3)
HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(color, godot_color)

godot_pool_string_array hgdn_new_string_array(const char *const *buffer, const godot_int size) {
    godot_pool_string_array array;
    hgdn_core_api->godot_pool_string_array_new(&array);
    hgdn_core_api->godot_pool_string_array_resize(&array, size);
    for (godot_int i = 0; i < size; i++) {
        godot_string str = hgdn_core_api->godot_string_chars_to_utf8(buffer[i]);
        hgdn_core_api->godot_pool_string_array_set(&array, i, &str);
        hgdn_core_api->godot_string_destroy(&str);
    }
    return array;
}

#undef HGDN_DECLARE_NEW_POOL_ARRAY_FUNC

godot_array hgdn_new_array(const godot_variant *const *buffer, const godot_int size) {
    godot_array array;
    hgdn_core_api->godot_array_new(&array);
    hgdn_core_api->godot_array_resize(&array, size);
    for (godot_int i = 0; i < size; i++) {
        hgdn_core_api->godot_array_set(&array, i, buffer[i]);
    }
    return array;
}

godot_array hgdn_new_array_own(godot_variant *buffer, const godot_int size) {
    godot_array array;
    hgdn_core_api->godot_array_new(&array);
    hgdn_core_api->godot_array_resize(&array, size);
    for (godot_int i = 0; i < size; i++) {
        godot_variant *var = &buffer[i];
        hgdn_core_api->godot_array_set(&array, i, var);
        hgdn_core_api->godot_variant_destroy(var);
    }
    return array;
}

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

godot_variant hgdn_new_formatted_string_variant(const char *fmt, ...) {
    HGDN__FILL_FORMAT_BUFFER(fmt, ...);
    godot_string str = hgdn_core_api->godot_string_chars_to_utf8_with_len(hgdn__format_string_buffer, size);
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
    godot_variant hgdn_new_##kind##_array_variant(const ctype *buffer, const godot_int len) { \
        godot_pool_##kind##_array array = hgdn_new_##kind##_array(buffer, len); \
        godot_variant var; \
        hgdn_core_api->godot_variant_new_pool_##kind##_array(&var, &array); \
        hgdn_core_api->godot_pool_##kind##_array_destroy(&array); \
        return var; \
    }

HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_FUNC(byte, uint8_t)
HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_FUNC(int, godot_int)
HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_FUNC(real, godot_real)
HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_FUNC(string, char *const)
HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_FUNC(vector2, godot_vector2)
HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_FUNC(vector3, godot_vector3)
HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_FUNC(color, godot_color)

#undef HGDN_DECLARE_NEW_POOL_ARRAY_VARIANT_FUNC

godot_variant hgdn_new_array_variant(const godot_variant *const *buffer, const godot_int size) {
    godot_array array = hgdn_new_array(buffer, size);
    godot_variant var;
    hgdn_core_api->godot_variant_new_array(&var, &array);
    hgdn_core_api->godot_array_destroy(&array);
    return var;
}

godot_variant hgdn_new_array_own_variant(godot_variant *buffer, const godot_int size) {
    godot_array array = hgdn_new_array_own(buffer, size);
    godot_variant var;
    hgdn_core_api->godot_variant_new_array(&var, &array);
    hgdn_core_api->godot_array_destroy(&array);
    return var;
}

// Allocate arrays from Godot data types
char *hgdn_string_dup(const godot_string *str, size_t *out_size) {
    size_t size = hgdn_core_api->godot_string_length(str);
    char *new_string = (char *) hgdn_alloc(size + 1);
    if (new_string) {
        godot_char_string cs = hgdn_core_api->godot_string_utf8(str);
        memcpy(new_string, hgdn_core_api->godot_char_string_get_data(&cs), size + 1);
        hgdn_core_api->godot_char_string_destroy(&cs);
        if (out_size) {
            *out_size = size;
        }
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
            if (out_size) { \
                *out_size = size; \
            } \
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
        if (out_size) {
            *out_size = size;
        }
    }
    return new_array;
}

HGDN_DECLARE_POOL_ARRAY_DUP(vector2, godot_vector2)
HGDN_DECLARE_POOL_ARRAY_DUP(vector3, godot_vector3)
HGDN_DECLARE_POOL_ARRAY_DUP(color, godot_color)

#undef HGDN_DECLARE_POOL_ARRAY_DUP

// Get values from Variant
char *hgdn_string_from_variant(const godot_variant *var, size_t *out_size) {
    godot_string str = hgdn_core_api->godot_variant_as_string(var);
    char *res = hgdn_string_dup(&str, out_size);
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
#define HGDN_DECLARE_ARRAY_GET(kind, ctype) \
    ctype hgdn_array_get_##kind(const godot_array *array, const godot_int index) { \
        return hgdn_core_api->godot_variant_as_##kind(hgdn_core_api->godot_array_operator_index_const(array, index)); \
    }

HGDN_DECLARE_ARRAY_GET(bool, godot_bool)
HGDN_DECLARE_ARRAY_GET(uint, uint64_t)
HGDN_DECLARE_ARRAY_GET(int, int64_t)
HGDN_DECLARE_ARRAY_GET(real, double)
HGDN_DECLARE_ARRAY_GET(vector2, godot_vector2)
HGDN_DECLARE_ARRAY_GET(vector3, godot_vector3)
HGDN_DECLARE_ARRAY_GET(rect2, godot_rect2)
HGDN_DECLARE_ARRAY_GET(plane, godot_plane)
HGDN_DECLARE_ARRAY_GET(quat, godot_quat)
HGDN_DECLARE_ARRAY_GET(aabb, godot_aabb)
HGDN_DECLARE_ARRAY_GET(basis, godot_basis)
HGDN_DECLARE_ARRAY_GET(transform2d, godot_transform2d)
HGDN_DECLARE_ARRAY_GET(transform, godot_transform)
HGDN_DECLARE_ARRAY_GET(color, godot_color)
HGDN_DECLARE_ARRAY_GET(node_path, godot_node_path)
HGDN_DECLARE_ARRAY_GET(rid, godot_rid)
HGDN_DECLARE_ARRAY_GET(object, godot_object *)
HGDN_DECLARE_ARRAY_GET(dictionary, godot_dictionary)
HGDN_DECLARE_ARRAY_GET(array, godot_array)

#undef HGDN_DECLARE_ARRAY_GET

char *hgdn_array_get_string(const godot_array *array, const godot_int index, size_t *out_size) {
    return hgdn_string_from_variant(hgdn_core_api->godot_array_operator_index_const(array, index), out_size);
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
#define HGDN_DECLARE_ARGS_GET(kind, ctype) \
    ctype hgdn_args_get_##kind(const godot_variant **args, const godot_int index) { \
        return hgdn_core_api->godot_variant_as_##kind(args[index]); \
    }

HGDN_DECLARE_ARGS_GET(bool, godot_bool)
HGDN_DECLARE_ARGS_GET(uint, uint64_t)
HGDN_DECLARE_ARGS_GET(int, int64_t)
HGDN_DECLARE_ARGS_GET(real, double)
HGDN_DECLARE_ARGS_GET(vector2, godot_vector2)
HGDN_DECLARE_ARGS_GET(vector3, godot_vector3)
HGDN_DECLARE_ARGS_GET(rect2, godot_rect2)
HGDN_DECLARE_ARGS_GET(plane, godot_plane)
HGDN_DECLARE_ARGS_GET(quat, godot_quat)
HGDN_DECLARE_ARGS_GET(aabb, godot_aabb)
HGDN_DECLARE_ARGS_GET(basis, godot_basis)
HGDN_DECLARE_ARGS_GET(transform2d, godot_transform2d)
HGDN_DECLARE_ARGS_GET(transform, godot_transform)
HGDN_DECLARE_ARGS_GET(color, godot_color)
HGDN_DECLARE_ARGS_GET(node_path, godot_node_path)
HGDN_DECLARE_ARGS_GET(rid, godot_rid)
HGDN_DECLARE_ARGS_GET(object, godot_object *)
HGDN_DECLARE_ARGS_GET(dictionary, godot_dictionary)
HGDN_DECLARE_ARGS_GET(array, godot_array)

#undef HGDN_DECLARE_ARGS_GET

char *hgdn_args_get_string(const godot_variant **args, const godot_int index, size_t *out_size) {
    return hgdn_string_from_variant(args[index], out_size);
}

#define HGDN_DECLARE_ARGS_GET_POOL_ARRAY(kind, ctype) \
    ctype *hgdn_args_get_##kind##_array(const godot_variant **args, const godot_int index, size_t *out_size) { \
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

#undef HGDN__FILL_FORMAT_BUFFER

#endif  // HGDN_IMPLEMENTATION
