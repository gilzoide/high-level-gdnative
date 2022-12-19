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
 * - HGDN_NO_CORE_1_1:
 * - HGDN_NO_CORE_1_2:
 * - HGDN_NO_CORE_1_3:
 * - HGDN_NO_EXT_NATIVESCRIPT:
 * - HGDN_NO_EXT_PLUGINSCRIPT:
 * - HGDN_NO_EXT_ANDROID:
 * - HGDN_NO_EXT_ARVR:
 * - HGDN_NO_EXT_VIDEOCODER:
 * - HGDN_NO_EXT_NET:
 *   Disable global pointers to extensions. If NativeScript is disabled, its helper functions will not be available as well.
 */
#ifndef __HGDN_H__
#define __HGDN_H__

#include <stdint.h>

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

#if defined(__cplusplus) && __cplusplus >= 201103L  // `constexpr` is a C++11 feature
    #define HGDN_CONSTEXPR constexpr
#else
    #define HGDN_CONSTEXPR
#endif

#ifndef HGDN_METHOD_ARGUMENTS_INFO_MAX
    #define HGDN_METHOD_ARGUMENTS_INFO_MAX 16
#endif

// Macro magic to get the number of variable arguments
// Ref: https://groups.google.com/g/comp.std.c/c/d-6Mj5Lko_s
#define HGDN__NARG(...)  HGDN__NARG_(__VA_ARGS__, HGDN__NARG_RSEQ_N())
#define HGDN__NARG_(...)  HGDN__NARG_N(__VA_ARGS__)
#define HGDN__NARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,N,...)  N
#define HGDN__NARG_RSEQ_N()  63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0

// Macro magic to apply a function macro to variadic arguments
// Ref: https://stackoverflow.com/questions/6707148/foreach-macro-on-macros-arguments/13459454#13459454
#define HGDN__EVAL0(...)  __VA_ARGS__
#define HGDN__EVAL1(...)  HGDN__EVAL0(HGDN__EVAL0(HGDN__EVAL0(__VA_ARGS__)))
#define HGDN__EVAL2(...)  HGDN__EVAL1(HGDN__EVAL1(HGDN__EVAL1(__VA_ARGS__)))
#define HGDN__EVAL3(...)  HGDN__EVAL2(HGDN__EVAL2(HGDN__EVAL2(__VA_ARGS__)))
#define HGDN__EVAL4(...)  HGDN__EVAL3(HGDN__EVAL3(HGDN__EVAL3(__VA_ARGS__)))
#define HGDN__EVAL(...)  HGDN__EVAL4(HGDN__EVAL4(HGDN__EVAL4(__VA_ARGS__)))
#define HGDN__MAP_END(...)
#define HGDN__MAP_OUT
#define HGDN__MAP_COMMA ,
#define HGDN__MAP_GET_END()  0, HGDN__MAP_END
#define HGDN__MAP_NEXT0(item, next, ...)  next HGDN__MAP_OUT
#define HGDN__MAP_NEXT1(item, next)  HGDN__MAP_NEXT0(item, HGDN__MAP_COMMA next, 0)
#define HGDN__MAP_NEXT(item, next)  HGDN__MAP_NEXT1(HGDN__MAP_GET_END item, next)
#define HGDN__MAP0(f, x, peek, ...)  f(x)  HGDN__MAP_NEXT(peek, HGDN__MAP1)(f, peek, __VA_ARGS__)
#define HGDN__MAP1(f, x, peek, ...)  f(x)  HGDN__MAP_NEXT(peek, HGDN__MAP0)(f, peek, __VA_ARGS__)
#define HGDN__MAP(f, ...)  HGDN__EVAL(HGDN__MAP1(f, __VA_ARGS__, (), 0))



/// @defgroup custom_math_types Custom math types
/// Useful definitions for Godot math types
/// @{
typedef union hgdn_vector2 {
    // raw data, must be the first field for guaranteeing ABI compatibility with Godot
    uint8_t data[sizeof(float[2])];
    // float elements
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

typedef union hgdn_vector3 {
    // raw data, must be the first field for guaranteeing ABI compatibility with Godot
    uint8_t data[sizeof(float[3])];
    // float elements
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

typedef union hgdn_vector4 {
    // raw data, must be the first field for guaranteeing ABI compatibility with Godot
    uint8_t data[sizeof(float[4])];
    // float elements
    float elements[4];
    // xyzw
    struct { float x, y, z, w; };
    struct { hgdn_vector2 xy; hgdn_vector2 zw; };
    struct { float _0; hgdn_vector2 yz; float _1; };
    struct { hgdn_vector3 xyz; float _2; };
    struct { float _3; hgdn_vector3 yzw; };
    // rgba
    struct { float r, g, b, a; };
    struct { hgdn_vector2 rg; hgdn_vector2 ba; };
    struct { float _4; hgdn_vector2 gb; float _5; };
    struct { hgdn_vector3 rgb; float _6; };
    struct { float _7; hgdn_vector3 gba; };
    // stpq
    struct { float s, t, p, q; };
    struct { hgdn_vector2 st; hgdn_vector2 pq; };
    struct { float _8; hgdn_vector2 tp; float _9; };
    struct { hgdn_vector3 stp; float _10; };
    struct { float _11; hgdn_vector3 tpq; };
    // uv
    struct { float u, v; float _12[2]; };
    struct { hgdn_vector2 uv; float _13[2]; };
} hgdn_vector4;

#ifndef GODOT_CORE_API_GODOT_COLOR_TYPE_DEFINED
/// Color is present on Pool Arrays and as MultiMesh instance data, so it's convenient having a full vector4 definition for it
typedef hgdn_vector4 godot_color;
#define GODOT_CORE_API_GODOT_COLOR_TYPE_DEFINED
#endif

typedef union hgdn_rect2 {
    // raw data, must be the first field for guaranteeing ABI compatibility with Godot
    uint8_t data[sizeof(float[4])];
    float elements[4];
    struct { float x, y, width, height; };
    struct { hgdn_vector2 position; hgdn_vector2 size; };
} hgdn_rect2;

#ifndef GODOT_CORE_API_GODOT_RECT2_TYPE_DEFINED
typedef hgdn_rect2 godot_rect2;
#define GODOT_CORE_API_GODOT_RECT2_TYPE_DEFINED
#endif

typedef union hgdn_plane {
    // raw data, must be the first field for guaranteeing ABI compatibility with Godot
    uint8_t data[sizeof(float[4])];
    float elements[4];
    struct { hgdn_vector3 normal; float d; };
} hgdn_plane;

#ifndef GODOT_CORE_API_GODOT_PLANE_TYPE_DEFINED
typedef hgdn_plane godot_plane;
#define GODOT_CORE_API_GODOT_PLANE_TYPE_DEFINED
#endif

typedef union hgdn_quat {
    // raw data, must be the first field for guaranteeing ABI compatibility with Godot
    uint8_t data[sizeof(float[4])];
    float elements[4];
    struct { float x, y, z, w; };
    struct { hgdn_vector2 xy; hgdn_vector2 zw; };
    struct { float _0; hgdn_vector2 yz; float _1; };
    struct { hgdn_vector3 xyz; float _2; };
    struct { float _3; hgdn_vector3 yzw; };
} hgdn_quat;
#define HGDN_QUAT_IDENTITY ((hgdn_quat){ .elements = {0, 0, 0, 1} })

#ifndef GODOT_CORE_API_GODOT_QUAT_TYPE_DEFINED
typedef hgdn_quat godot_quat;
#define GODOT_CORE_API_GODOT_QUAT_TYPE_DEFINED
#endif

typedef union hgdn_basis {
    // raw data, must be the first field for guaranteeing ABI compatibility with Godot
    uint8_t data[sizeof(float[9])];
    float elements[9];
    hgdn_vector3 rows[3];
} hgdn_basis;
#define HGDN_BASIS_IDENTITY ((hgdn_basis){ .elements = {1, 0, 0, 0, 1, 0, 0, 0, 1} })

#ifndef GODOT_CORE_API_GODOT_BASIS_TYPE_DEFINED
typedef hgdn_basis godot_basis;
#define GODOT_CORE_API_GODOT_BASIS_TYPE_DEFINED
#endif

typedef union hgdn_aabb {
    // raw data, must be the first field for guaranteeing ABI compatibility with Godot
    uint8_t data[sizeof(float[6])];
    float elements[6];
    struct { hgdn_vector3 position, size; };
} hgdn_aabb;

#ifndef GODOT_CORE_API_GODOT_AABB_TYPE_DEFINED
typedef hgdn_aabb godot_aabb;
#define GODOT_CORE_API_GODOT_AABB_TYPE_DEFINED
#endif

typedef union hgdn_transform2d {
    // raw data, must be the first field for guaranteeing ABI compatibility with Godot
    uint8_t data[sizeof(float[6])];
    float elements[6];
    hgdn_vector2 columns[3];
    struct { hgdn_vector2 x, y, origin; };
} hgdn_transform2d;
#define HGDN_TRANSFORM2D_IDENTITY  ((hgdn_transform2d){ .elements = {1, 0, 0, 1, 0, 0} })

#ifndef GODOT_CORE_API_GODOT_TRANSFORM2D_TYPE_DEFINED
typedef hgdn_transform2d godot_transform2d;
#define GODOT_CORE_API_GODOT_TRANSFORM2D_TYPE_DEFINED
#endif

typedef union hgdn_transform {
    // raw data, must be the first field for guaranteeing ABI compatibility with Godot
    uint8_t data[sizeof(float[12])];
    float elements[12];
    struct { hgdn_basis basis; hgdn_vector3 origin; };
} hgdn_transform;
#define HGDN_TRANSFORM3D_IDENTITY  ((hgdn_transform){ .elements = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0} })

#ifndef GODOT_CORE_API_GODOT_TRANSFORM_TYPE_DEFINED
typedef hgdn_transform godot_transform;
#define GODOT_CORE_API_GODOT_TRANSFORM_TYPE_DEFINED
#endif
/// @}

#include "gdnative_api_struct.gen.h"

/// @defgroup global Global GDNative pointers
/// Global API structs and GDNativeLibrary pointers
/// @{
extern const godot_gdnative_core_api_struct *hgdn_core_api;
#ifndef HGDN_NO_CORE_1_1
extern const godot_gdnative_core_1_1_api_struct *hgdn_core_1_1_api;
#endif
#ifndef HGDN_NO_CORE_1_2
extern const godot_gdnative_core_1_2_api_struct *hgdn_core_1_2_api;
#endif
#ifndef HGDN_NO_CORE_1_3
extern const godot_gdnative_core_1_3_api_struct *hgdn_core_1_3_api;
#endif
#ifndef HGDN_NO_EXT_NATIVESCRIPT
extern const godot_gdnative_ext_nativescript_api_struct *hgdn_nativescript_api;
extern const godot_gdnative_ext_nativescript_1_1_api_struct *hgdn_nativescript_1_1_api;
#endif
#ifndef HGDN_NO_EXT_PLUGINSCRIPT
extern const godot_gdnative_ext_pluginscript_api_struct *hgdn_pluginscript_api;
#endif
#ifndef HGDN_NO_EXT_ANDROID
extern const godot_gdnative_ext_android_api_struct *hgdn_android_api;
#endif
#ifndef HGDN_NO_EXT_ARVR
extern const godot_gdnative_ext_arvr_api_struct *hgdn_arvr_api;
extern const godot_gdnative_ext_arvr_1_2_api_struct *hgdn_arvr_1_2_api;
#endif
#ifndef HGDN_NO_EXT_VIDEOCODER
extern const godot_gdnative_ext_videodecoder_api_struct *hgdn_videodecoder_api;
#endif
#ifndef HGDN_NO_EXT_NET
extern const godot_gdnative_ext_net_api_struct *hgdn_net_api;
extern const godot_gdnative_ext_net_3_2_api_struct *hgdn_net_3_2_api;
#endif
extern godot_object *hgdn_library;  ///< GDNativeLibrary object being initialized
extern godot_method_bind *hgdn_method_Object_callv;
/// @}


/// @defgroup init_deinit Initialization and deinitialization
/// Initialize and deinitialize library, to be called on your own `godot_gdnative_init` and `godot_gdnative_terminate` functions.
/// @{
HGDN_DECL void hgdn_gdnative_init(const godot_gdnative_init_options *options);
HGDN_DECL void hgdn_gdnative_terminate(const godot_gdnative_terminate_options *options);
/// @}


/// @defgroup memory Memory related functions
/// `stdlib.h` compatible functions that track memory usage when Godot is running in debug mode
/// @{
HGDN_DECL void *hgdn_alloc(size_t size);  ///< Compatible with `malloc`
HGDN_DECL void *hgdn_realloc(void *ptr, size_t size);  ///< Compatible with `realloc`
/// Compatible with `free`. It is safe to pass NULL without triggering an error message.
HGDN_DECL void hgdn_free(void *ptr);
/// @}


/// @defgroup print Printing functions
/// Functions that print a `printf` formatted message to Godot's output
/// @{
HGDN_DECL void hgdn_print(const char *fmt, ...);
HGDN_DECL void hgdn_print_warning(const char *funcname, const char *filename, int line, const char *fmt, ...);
HGDN_DECL void hgdn_print_error(const char *funcname, const char *filename, int line, const char *fmt, ...);
#ifdef _MSC_VER
#define HGDN_PRINT_WARNING(fmt, ...)  (hgdn_print_warning(__FUNCTION__, __FILE__, __LINE__, fmt, ##__VA_ARGS__))
#define HGDN_PRINT_ERROR(fmt, ...)  (hgdn_print_error(__FUNCTION__, __FILE__, __LINE__, fmt, ##__VA_ARGS__))
#else
#define HGDN_PRINT_WARNING(fmt, ...)  (hgdn_print_warning(__PRETTY_FUNCTION__, __FILE__, __LINE__, fmt, ##__VA_ARGS__))
#define HGDN_PRINT_ERROR(fmt, ...)  (hgdn_print_error(__PRETTY_FUNCTION__, __FILE__, __LINE__, fmt, ##__VA_ARGS__))
#endif
/// @}

/// @defgroup assert Runtime assertions
/// Macros that check for a condition, aborting current function if this condition is false
///
/// If condition is false, prints an error message and return a nil variant, so
/// they are meant to be used in GDNative functions that return `godot_variant`
/// like native calls or methods.
/// @{
#define HGDN_ASSERT(cond)  HGDN_ASSERT_MSG((cond), "Assertion error: !(" #cond ")")
/// If `cond` is false, print formatted error message and return nil Variant
#define HGDN_ASSERT_MSG(cond, fmt, ...)  if(!(cond)){ HGDN_PRINT_ERROR(fmt, ##__VA_ARGS__); return hgdn_new_nil_variant(); }
/// If `arr` doesn't have at least `min_size` elements, print error message and return nil Variant
#define HGDN_ASSERT_ARRAY_SIZE(arr, min_size)  HGDN_ASSERT_MSG(hgdn_core_api->godot_array_size((arr)) >= (min_size), "Error: array should have size of at least " #min_size ", got %d", hgdn_core_api->godot_array_size((arr)))
/// If `argc` isn't at least `min_size`, print error message and return nil Variant
#define HGDN_ASSERT_ARGS_SIZE(argc, min_size)  HGDN_ASSERT_MSG((argc) >= (min_size), "Error: expected at least " #min_size " arguments, got %d", argc)
/// @}

/// @defgroup string_wrapper String wrapper
/// Wrapper around String/CharStrings with pointer and length
/// @{
typedef struct hgdn_string {
    godot_char_string gd_char_string;
    const char *ptr;
    godot_int length;
} hgdn_string;
HGDN_DECL hgdn_string hgdn_string_get(const godot_string *str);
HGDN_DECL hgdn_string hgdn_string_get_own(godot_string str);
HGDN_DECL void hgdn_string_destroy(hgdn_string *str);

typedef struct hgdn_wide_string {
    godot_string gd_string;
    const wchar_t *ptr;
    godot_int length;
} hgdn_wide_string;
HGDN_DECL hgdn_wide_string hgdn_wide_string_get(const godot_string *str);
HGDN_DECL hgdn_wide_string hgdn_wide_string_get_own(godot_string str);
HGDN_DECL void hgdn_wide_string_destroy(hgdn_wide_string *str);
/// @}


/// @defgroup pool_array_wrapper Pool*Array wrapper
/// Wrapper around Pool*Array types with pointer and array size
/// @{
typedef struct hgdn_byte_array {
    godot_pool_byte_array_read_access *gd_read_access;
    const uint8_t *ptr;
    godot_int size;
} hgdn_byte_array;
HGDN_DECL hgdn_byte_array hgdn_byte_array_get(const godot_pool_byte_array *array);
HGDN_DECL hgdn_byte_array hgdn_byte_array_get_own(godot_pool_byte_array array);
HGDN_DECL void hgdn_byte_array_destroy(hgdn_byte_array *array);

typedef struct hgdn_int_array {
    godot_pool_int_array_read_access *gd_read_access;
    const godot_int *ptr;
    godot_int size;
} hgdn_int_array;
HGDN_DECL hgdn_int_array hgdn_int_array_get(const godot_pool_int_array *array);
HGDN_DECL hgdn_int_array hgdn_int_array_get_own(godot_pool_int_array array);
HGDN_DECL void hgdn_int_array_destroy(hgdn_int_array *array);

typedef struct hgdn_real_array {
    godot_pool_real_array_read_access *gd_read_access;
    const godot_real *ptr;
    godot_int size;
} hgdn_real_array;
HGDN_DECL hgdn_real_array hgdn_real_array_get(const godot_pool_real_array *array);
HGDN_DECL hgdn_real_array hgdn_real_array_get_own(godot_pool_real_array array);
HGDN_DECL void hgdn_real_array_destroy(hgdn_real_array *array);

typedef struct hgdn_vector2_array {
    godot_pool_vector2_array_read_access *gd_read_access;
    const godot_vector2 *ptr;
    godot_int size;
} hgdn_vector2_array;
HGDN_DECL hgdn_vector2_array hgdn_vector2_array_get(const godot_pool_vector2_array *array);
HGDN_DECL hgdn_vector2_array hgdn_vector2_array_get_own(godot_pool_vector2_array array);
HGDN_DECL void hgdn_vector2_array_destroy(hgdn_vector2_array *array);

typedef struct hgdn_vector3_array {
    godot_pool_vector3_array_read_access *gd_read_access;
    const godot_vector3 *ptr;
    godot_int size;
} hgdn_vector3_array;
HGDN_DECL hgdn_vector3_array hgdn_vector3_array_get(const godot_pool_vector3_array *array);
HGDN_DECL hgdn_vector3_array hgdn_vector3_array_get_own(godot_pool_vector3_array array);
HGDN_DECL void hgdn_vector3_array_destroy(hgdn_vector3_array *array);

typedef struct hgdn_color_array {
    godot_pool_color_array_read_access *gd_read_access;
    const godot_color *ptr;
    godot_int size;
} hgdn_color_array;
HGDN_DECL hgdn_color_array hgdn_color_array_get(const godot_pool_color_array *array);
HGDN_DECL hgdn_color_array hgdn_color_array_get_own(godot_pool_color_array array);
HGDN_DECL void hgdn_color_array_destroy(hgdn_color_array *array);

typedef struct hgdn_string_array {
    hgdn_string *strings;
    const char **ptr;
    godot_int size;
} hgdn_string_array;
HGDN_DECL hgdn_string_array hgdn_string_array_get(const godot_pool_string_array *array);
HGDN_DECL hgdn_string_array hgdn_string_array_get_own(godot_pool_string_array array);
HGDN_DECL void hgdn_string_array_destroy(hgdn_string_array *array);
/// @}


/// @defgroup variant_get Typed values from Variants
/// Helper functions to get values directly from a `godot_variant`
///
/// The `*_own` functions own the passed argument, destroying it.
/// @{
HGDN_DECL godot_bool hgdn_variant_get_bool(const godot_variant *var);
HGDN_DECL uint64_t hgdn_variant_get_uint(const godot_variant *var);
HGDN_DECL int64_t hgdn_variant_get_int(const godot_variant *var);
HGDN_DECL double hgdn_variant_get_real(const godot_variant *var);
HGDN_DECL godot_vector2 hgdn_variant_get_vector2(const godot_variant *var);
HGDN_DECL godot_vector3 hgdn_variant_get_vector3(const godot_variant *var);
HGDN_DECL godot_rect2 hgdn_variant_get_rect2(const godot_variant *var);
HGDN_DECL godot_plane hgdn_variant_get_plane(const godot_variant *var);
HGDN_DECL godot_quat hgdn_variant_get_quat(const godot_variant *var);
HGDN_DECL godot_aabb hgdn_variant_get_aabb(const godot_variant *var);
HGDN_DECL godot_basis hgdn_variant_get_basis(const godot_variant *var);
HGDN_DECL godot_transform2d hgdn_variant_get_transform2d(const godot_variant *var);
HGDN_DECL godot_transform hgdn_variant_get_transform(const godot_variant *var);
HGDN_DECL godot_color hgdn_variant_get_color(const godot_variant *var);
HGDN_DECL godot_node_path hgdn_variant_get_node_path(const godot_variant *var);
HGDN_DECL godot_rid hgdn_variant_get_rid(const godot_variant *var);
HGDN_DECL godot_object *hgdn_variant_get_object(const godot_variant *var);
HGDN_DECL godot_dictionary hgdn_variant_get_dictionary(const godot_variant *var);
HGDN_DECL godot_array hgdn_variant_get_array(const godot_variant *var);

HGDN_DECL hgdn_string hgdn_variant_get_string(const godot_variant *var);
HGDN_DECL hgdn_wide_string hgdn_variant_get_wide_string(const godot_variant *var);
HGDN_DECL hgdn_byte_array hgdn_variant_get_byte_array(const godot_variant *var);
HGDN_DECL hgdn_int_array hgdn_variant_get_int_array(const godot_variant *var);
HGDN_DECL hgdn_real_array hgdn_variant_get_real_array(const godot_variant *var);
HGDN_DECL hgdn_vector2_array hgdn_variant_get_vector2_array(const godot_variant *var);
HGDN_DECL hgdn_vector3_array hgdn_variant_get_vector3_array(const godot_variant *var);
HGDN_DECL hgdn_color_array hgdn_variant_get_color_array(const godot_variant *var);
HGDN_DECL hgdn_string_array hgdn_variant_get_string_array(const godot_variant *var);

HGDN_DECL godot_bool hgdn_variant_get_bool_own(godot_variant var);
HGDN_DECL uint64_t hgdn_variant_get_uint_own(godot_variant var);
HGDN_DECL int64_t hgdn_variant_get_int_own(godot_variant var);
HGDN_DECL double hgdn_variant_get_real_own(godot_variant var);
HGDN_DECL godot_vector2 hgdn_variant_get_vector2_own(godot_variant var);
HGDN_DECL godot_vector3 hgdn_variant_get_vector3_own(godot_variant var);
HGDN_DECL godot_rect2 hgdn_variant_get_rect2_own(godot_variant var);
HGDN_DECL godot_plane hgdn_variant_get_plane_own(godot_variant var);
HGDN_DECL godot_quat hgdn_variant_get_quat_own(godot_variant var);
HGDN_DECL godot_aabb hgdn_variant_get_aabb_own(godot_variant var);
HGDN_DECL godot_basis hgdn_variant_get_basis_own(godot_variant var);
HGDN_DECL godot_transform2d hgdn_variant_get_transform2d_own(godot_variant var);
HGDN_DECL godot_transform hgdn_variant_get_transform_own(godot_variant var);
HGDN_DECL godot_color hgdn_variant_get_color_own(godot_variant var);
HGDN_DECL godot_node_path hgdn_variant_get_node_path_own(godot_variant var);
HGDN_DECL godot_rid hgdn_variant_get_rid_own(godot_variant var);
HGDN_DECL godot_object *hgdn_variant_get_object_own(godot_variant var);
HGDN_DECL godot_dictionary hgdn_variant_get_dictionary_own(godot_variant var);
HGDN_DECL godot_array hgdn_variant_get_array_own(godot_variant var);

HGDN_DECL hgdn_string hgdn_variant_get_string_own(godot_variant var);
HGDN_DECL hgdn_wide_string hgdn_variant_get_wide_string_own(godot_variant var);
HGDN_DECL hgdn_byte_array hgdn_variant_get_byte_array_own(godot_variant var);
HGDN_DECL hgdn_int_array hgdn_variant_get_int_array_own(godot_variant var);
HGDN_DECL hgdn_real_array hgdn_variant_get_real_array_own(godot_variant var);
HGDN_DECL hgdn_vector2_array hgdn_variant_get_vector2_array_own(godot_variant var);
HGDN_DECL hgdn_vector3_array hgdn_variant_get_vector3_array_own(godot_variant var);
HGDN_DECL hgdn_color_array hgdn_variant_get_color_array_own(godot_variant var);
HGDN_DECL hgdn_string_array hgdn_variant_get_string_array_own(godot_variant var);
/// @}


/// @defgroup array_get Typed values from Arrays
/// Helper functions to get values directly from a `godot_array` position
/// @{
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

HGDN_DECL hgdn_string hgdn_array_get_string(const godot_array *array, const godot_int index);
HGDN_DECL hgdn_wide_string hgdn_array_get_wide_string(const godot_array *array, const godot_int index);
HGDN_DECL hgdn_byte_array hgdn_array_get_byte_array(const godot_array *array, const godot_int index);
HGDN_DECL hgdn_int_array hgdn_array_get_int_array(const godot_array *array, const godot_int index);
HGDN_DECL hgdn_real_array hgdn_array_get_real_array(const godot_array *array, const godot_int index);
HGDN_DECL hgdn_vector2_array hgdn_array_get_vector2_array(const godot_array *array, const godot_int index);
HGDN_DECL hgdn_vector3_array hgdn_array_get_vector3_array(const godot_array *array, const godot_int index);
HGDN_DECL hgdn_color_array hgdn_array_get_color_array(const godot_array *array, const godot_int index);
HGDN_DECL hgdn_string_array hgdn_array_get_string_array(const godot_array *array, const godot_int index);
/// @}


/// @defgroup args_get Typed values from method arguments
/// Helper functions to get values directly from method arguments
/// @{
HGDN_DECL godot_bool hgdn_args_get_bool(godot_variant **args, const godot_int index);
HGDN_DECL uint64_t hgdn_args_get_uint(godot_variant **args, const godot_int index);
HGDN_DECL int64_t hgdn_args_get_int(godot_variant **args, const godot_int index);
HGDN_DECL double hgdn_args_get_real(godot_variant **args, const godot_int index);
HGDN_DECL godot_vector2 hgdn_args_get_vector2(godot_variant **args, const godot_int index);
HGDN_DECL godot_vector3 hgdn_args_get_vector3(godot_variant **args, const godot_int index);
HGDN_DECL godot_rect2 hgdn_args_get_rect2(godot_variant **args, const godot_int index);
HGDN_DECL godot_plane hgdn_args_get_plane(godot_variant **args, const godot_int index);
HGDN_DECL godot_quat hgdn_args_get_quat(godot_variant **args, const godot_int index);
HGDN_DECL godot_aabb hgdn_args_get_aabb(godot_variant **args, const godot_int index);
HGDN_DECL godot_basis hgdn_args_get_basis(godot_variant **args, const godot_int index);
HGDN_DECL godot_transform2d hgdn_args_get_transform2d(godot_variant **args, const godot_int index);
HGDN_DECL godot_transform hgdn_args_get_transform(godot_variant **args, const godot_int index);
HGDN_DECL godot_color hgdn_args_get_color(godot_variant **args, const godot_int index);
HGDN_DECL godot_node_path hgdn_args_get_node_path(godot_variant **args, const godot_int index);
HGDN_DECL godot_rid hgdn_args_get_rid(godot_variant **args, const godot_int index);
HGDN_DECL godot_object *hgdn_args_get_object(godot_variant **args, const godot_int index);
HGDN_DECL godot_dictionary hgdn_args_get_dictionary(godot_variant **args, const godot_int index);
HGDN_DECL godot_array hgdn_args_get_array(godot_variant **args, const godot_int index);

HGDN_DECL hgdn_string hgdn_args_get_string(godot_variant **args, const godot_int index);
HGDN_DECL hgdn_wide_string hgdn_args_get_wide_string(godot_variant **args, const godot_int index);
HGDN_DECL hgdn_byte_array hgdn_args_get_byte_array(godot_variant **args, const godot_int index);
HGDN_DECL hgdn_int_array hgdn_args_get_int_array(godot_variant **args, const godot_int index);
HGDN_DECL hgdn_real_array hgdn_args_get_real_array(godot_variant **args, const godot_int index);
HGDN_DECL hgdn_vector2_array hgdn_args_get_vector2_array(godot_variant **args, const godot_int index);
HGDN_DECL hgdn_vector3_array hgdn_args_get_vector3_array(godot_variant **args, const godot_int index);
HGDN_DECL hgdn_color_array hgdn_args_get_color_array(godot_variant **args, const godot_int index);
HGDN_DECL hgdn_string_array hgdn_args_get_string_array(godot_variant **args, const godot_int index);
/// @}


/// @defgroup dictionary_get Typed values from Dictionaries
/// Helper functions to get values directly from a `godot_dictionary` with Variant or String key
/// @{
HGDN_DECL godot_bool hgdn_dictionary_get_bool(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL uint64_t hgdn_dictionary_get_uint(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL int64_t hgdn_dictionary_get_int(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL double hgdn_dictionary_get_real(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL godot_vector2 hgdn_dictionary_get_vector2(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL godot_vector3 hgdn_dictionary_get_vector3(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL godot_rect2 hgdn_dictionary_get_rect2(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL godot_plane hgdn_dictionary_get_plane(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL godot_quat hgdn_dictionary_get_quat(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL godot_aabb hgdn_dictionary_get_aabb(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL godot_basis hgdn_dictionary_get_basis(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL godot_transform2d hgdn_dictionary_get_transform2d(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL godot_transform hgdn_dictionary_get_transform(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL godot_color hgdn_dictionary_get_color(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL godot_node_path hgdn_dictionary_get_node_path(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL godot_rid hgdn_dictionary_get_rid(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL godot_object *hgdn_dictionary_get_object(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL godot_dictionary hgdn_dictionary_get_dictionary(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL godot_array hgdn_dictionary_get_array(const godot_dictionary *dict, const godot_variant *key);

HGDN_DECL hgdn_string hgdn_dictionary_get_string(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL hgdn_wide_string hgdn_dictionary_get_wide_string(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL hgdn_byte_array hgdn_dictionary_get_byte_array(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL hgdn_int_array hgdn_dictionary_get_int_array(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL hgdn_real_array hgdn_dictionary_get_real_array(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL hgdn_vector2_array hgdn_dictionary_get_vector2_array(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL hgdn_vector3_array hgdn_dictionary_get_vector3_array(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL hgdn_color_array hgdn_dictionary_get_color_array(const godot_dictionary *dict, const godot_variant *key);
HGDN_DECL hgdn_string_array hgdn_dictionary_get_string_array(const godot_dictionary *dict, const godot_variant *key);

HGDN_DECL godot_bool hgdn_dictionary_string_get_bool(const godot_dictionary *dict, const char *key);
HGDN_DECL uint64_t hgdn_dictionary_string_get_uint(const godot_dictionary *dict, const char *key);
HGDN_DECL int64_t hgdn_dictionary_string_get_int(const godot_dictionary *dict, const char *key);
HGDN_DECL double hgdn_dictionary_string_get_real(const godot_dictionary *dict, const char *key);
HGDN_DECL godot_vector2 hgdn_dictionary_string_get_vector2(const godot_dictionary *dict, const char *key);
HGDN_DECL godot_vector3 hgdn_dictionary_string_get_vector3(const godot_dictionary *dict, const char *key);
HGDN_DECL godot_rect2 hgdn_dictionary_string_get_rect2(const godot_dictionary *dict, const char *key);
HGDN_DECL godot_plane hgdn_dictionary_string_get_plane(const godot_dictionary *dict, const char *key);
HGDN_DECL godot_quat hgdn_dictionary_string_get_quat(const godot_dictionary *dict, const char *key);
HGDN_DECL godot_aabb hgdn_dictionary_string_get_aabb(const godot_dictionary *dict, const char *key);
HGDN_DECL godot_basis hgdn_dictionary_string_get_basis(const godot_dictionary *dict, const char *key);
HGDN_DECL godot_transform2d hgdn_dictionary_string_get_transform2d(const godot_dictionary *dict, const char *key);
HGDN_DECL godot_transform hgdn_dictionary_string_get_transform(const godot_dictionary *dict, const char *key);
HGDN_DECL godot_color hgdn_dictionary_string_get_color(const godot_dictionary *dict, const char *key);
HGDN_DECL godot_node_path hgdn_dictionary_string_get_node_path(const godot_dictionary *dict, const char *key);
HGDN_DECL godot_rid hgdn_dictionary_string_get_rid(const godot_dictionary *dict, const char *key);
HGDN_DECL godot_object *hgdn_dictionary_string_get_object(const godot_dictionary *dict, const char *key);
HGDN_DECL godot_dictionary hgdn_dictionary_string_get_dictionary(const godot_dictionary *dict, const char *key);
HGDN_DECL godot_array hgdn_dictionary_string_get_array(const godot_dictionary *dict, const char *key);

HGDN_DECL hgdn_string hgdn_dictionary_string_get_string(const godot_dictionary *dict, const char *key);
HGDN_DECL hgdn_wide_string hgdn_dictionary_string_get_wide_string(const godot_dictionary *dict, const char *key);
HGDN_DECL hgdn_byte_array hgdn_dictionary_string_get_byte_array(const godot_dictionary *dict, const char *key);
HGDN_DECL hgdn_int_array hgdn_dictionary_string_get_int_array(const godot_dictionary *dict, const char *key);
HGDN_DECL hgdn_real_array hgdn_dictionary_string_get_real_array(const godot_dictionary *dict, const char *key);
HGDN_DECL hgdn_vector2_array hgdn_dictionary_string_get_vector2_array(const godot_dictionary *dict, const char *key);
HGDN_DECL hgdn_vector3_array hgdn_dictionary_string_get_vector3_array(const godot_dictionary *dict, const char *key);
HGDN_DECL hgdn_color_array hgdn_dictionary_string_get_color_array(const godot_dictionary *dict, const char *key);
HGDN_DECL hgdn_string_array hgdn_dictionary_string_get_string_array(const godot_dictionary *dict, const char *key);
/// @}


/// @defgroup new_variant Variant constructors
/// Helper functions to create Variant values
///
/// The `*_own` functions own the passed argument, destroying it. Useful
/// when you create the object just for creating a Variant of it, enabling
/// the idiom `hgdn_new_string_variant_own(hgdn_new_string("..."))`.
/// @{
HGDN_DECL godot_variant hgdn_new_variant_copy(const godot_variant *value);
HGDN_DECL godot_variant hgdn_new_nil_variant();
HGDN_DECL godot_variant hgdn_new_bool_variant(const godot_bool value);
HGDN_DECL godot_variant hgdn_new_uint_variant(const uint64_t value);
HGDN_DECL godot_variant hgdn_new_int_variant(const int64_t value);
HGDN_DECL godot_variant hgdn_new_real_variant(const double value);
HGDN_DECL godot_variant hgdn_new_string_variant(const godot_string *value);
HGDN_DECL godot_variant hgdn_new_cstring_variant(const char *value);
HGDN_DECL godot_variant hgdn_new_wide_string_variant(const wchar_t *value);
HGDN_DECL godot_variant hgdn_new_vector2_variant(const godot_vector2 value);
HGDN_DECL godot_variant hgdn_new_vector3_variant(const godot_vector3 value);
HGDN_DECL godot_variant hgdn_new_rect2_variant(const godot_rect2 value);
HGDN_DECL godot_variant hgdn_new_plane_variant(const godot_plane value);
HGDN_DECL godot_variant hgdn_new_quat_variant(const godot_quat value);
HGDN_DECL godot_variant hgdn_new_aabb_variant(const godot_aabb value);
HGDN_DECL godot_variant hgdn_new_basis_variant(const godot_basis value);
HGDN_DECL godot_variant hgdn_new_transform2d_variant(const godot_transform2d value);
HGDN_DECL godot_variant hgdn_new_transform_variant(const godot_transform value);
HGDN_DECL godot_variant hgdn_new_color_variant(const godot_color value);
HGDN_DECL godot_variant hgdn_new_node_path_variant(const godot_node_path *value);
HGDN_DECL godot_variant hgdn_new_rid_variant(const godot_rid *value);
HGDN_DECL godot_variant hgdn_new_object_variant(const godot_object *value);
HGDN_DECL godot_variant hgdn_new_dictionary_variant(const godot_dictionary *value);
HGDN_DECL godot_variant hgdn_new_array_variant(const godot_array *value);
HGDN_DECL godot_variant hgdn_new_pool_byte_array_variant(const godot_pool_byte_array *value);
HGDN_DECL godot_variant hgdn_new_pool_int_array_variant(const godot_pool_int_array *value);
HGDN_DECL godot_variant hgdn_new_pool_real_array_variant(const godot_pool_real_array *value);
HGDN_DECL godot_variant hgdn_new_pool_vector2_array_variant(const godot_pool_vector2_array *value);
HGDN_DECL godot_variant hgdn_new_pool_vector3_array_variant(const godot_pool_vector3_array *value);
HGDN_DECL godot_variant hgdn_new_pool_color_array_variant(const godot_pool_color_array *value);
HGDN_DECL godot_variant hgdn_new_pool_string_array_variant(const godot_pool_string_array *value);

HGDN_DECL godot_variant hgdn_new_string_variant_own(godot_string value);
HGDN_DECL godot_variant hgdn_new_node_path_variant_own(godot_node_path value);
HGDN_DECL godot_variant hgdn_new_dictionary_variant_own(godot_dictionary value);
HGDN_DECL godot_variant hgdn_new_array_variant_own(godot_array value);
HGDN_DECL godot_variant hgdn_new_pool_byte_array_variant_own(godot_pool_byte_array value);
HGDN_DECL godot_variant hgdn_new_pool_int_array_variant_own(godot_pool_int_array value);
HGDN_DECL godot_variant hgdn_new_pool_real_array_variant_own(godot_pool_real_array value);
HGDN_DECL godot_variant hgdn_new_pool_vector2_array_variant_own(godot_pool_vector2_array value);
HGDN_DECL godot_variant hgdn_new_pool_vector3_array_variant_own(godot_pool_vector3_array value);
HGDN_DECL godot_variant hgdn_new_pool_color_array_variant_own(godot_pool_color_array value);
HGDN_DECL godot_variant hgdn_new_pool_string_array_variant_own(godot_pool_string_array value);

#ifdef __cplusplus
extern "C++" {
    HGDN_DECL godot_variant hgdn_new_variant(const godot_bool value);
    HGDN_DECL godot_variant hgdn_new_variant(const unsigned int value);
    HGDN_DECL godot_variant hgdn_new_variant(const uint64_t value);
    HGDN_DECL godot_variant hgdn_new_variant(const int value);
    HGDN_DECL godot_variant hgdn_new_variant(const int64_t value);
    HGDN_DECL godot_variant hgdn_new_variant(const double value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_string *value);
    HGDN_DECL godot_variant hgdn_new_variant(const char *value);
    HGDN_DECL godot_variant hgdn_new_variant(const wchar_t *value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_vector2 value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_vector3 value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_rect2 value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_plane value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_quat value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_aabb value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_basis value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_transform2d value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_transform value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_color value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_node_path *value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_rid *value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_object *value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_dictionary *value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_array *value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_pool_byte_array *value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_pool_int_array *value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_pool_real_array *value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_pool_vector2_array *value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_pool_vector3_array *value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_pool_color_array *value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_pool_string_array *value);
    HGDN_DECL godot_variant hgdn_new_variant(godot_string value);
    HGDN_DECL godot_variant hgdn_new_variant(godot_node_path value);
    HGDN_DECL godot_variant hgdn_new_variant(godot_dictionary value);
    HGDN_DECL godot_variant hgdn_new_variant(godot_array value);
    HGDN_DECL godot_variant hgdn_new_variant(godot_pool_byte_array value);
    HGDN_DECL godot_variant hgdn_new_variant(godot_pool_int_array value);
    HGDN_DECL godot_variant hgdn_new_variant(godot_pool_real_array value);
    HGDN_DECL godot_variant hgdn_new_variant(godot_pool_vector2_array value);
    HGDN_DECL godot_variant hgdn_new_variant(godot_pool_vector3_array value);
    HGDN_DECL godot_variant hgdn_new_variant(godot_pool_color_array value);
    HGDN_DECL godot_variant hgdn_new_variant(godot_pool_string_array value);
    HGDN_DECL godot_variant hgdn_new_variant(const godot_variant *value);
    HGDN_DECL HGDN_CONSTEXPR godot_variant hgdn_new_variant(godot_variant value);
}
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L  // C11
/// Overloaded function/macro for creating Variants from any values. Available in C++ and C11.
#define hgdn_new_variant(value) \
    (_Generic((value), \
        godot_bool: hgdn_new_bool_variant, \
        unsigned int: hgdn_new_uint_variant, \
        uint64_t: hgdn_new_uint_variant, \
        int: hgdn_new_int_variant, \
        int64_t: hgdn_new_int_variant, \
        float: hgdn_new_real_variant, \
        double: hgdn_new_real_variant, \
        godot_string*: hgdn_new_string_variant, const godot_string*: hgdn_new_string_variant, \
        char*: hgdn_new_cstring_variant, const char*: hgdn_new_cstring_variant, \
        wchar_t*: hgdn_new_wide_string_variant, const wchar_t*: hgdn_new_wide_string_variant, \
        godot_vector2: hgdn_new_vector2_variant, \
        godot_vector3: hgdn_new_vector3_variant, \
        godot_rect2: hgdn_new_rect2_variant, \
        godot_plane: hgdn_new_plane_variant, \
        godot_quat: hgdn_new_quat_variant, \
        godot_aabb: hgdn_new_aabb_variant, \
        godot_basis: hgdn_new_basis_variant, \
        godot_transform2d: hgdn_new_transform2d_variant, \
        godot_transform: hgdn_new_transform_variant, \
        godot_color: hgdn_new_color_variant, \
        godot_node_path*: hgdn_new_node_path_variant, const godot_node_path*: hgdn_new_node_path_variant, \
        godot_rid*: hgdn_new_rid_variant, const godot_rid*: hgdn_new_rid_variant, \
        godot_object*: hgdn_new_object_variant, const godot_object*: hgdn_new_object_variant, \
        godot_dictionary*: hgdn_new_dictionary_variant, const godot_dictionary*: hgdn_new_dictionary_variant, \
        godot_array*: hgdn_new_array_variant, const godot_array*: hgdn_new_array_variant, \
        godot_pool_byte_array*: hgdn_new_pool_byte_array_variant, const godot_pool_byte_array*: hgdn_new_pool_byte_array_variant, \
        godot_pool_int_array*: hgdn_new_pool_int_array_variant, const godot_pool_int_array*: hgdn_new_pool_int_array_variant, \
        godot_pool_real_array*: hgdn_new_pool_real_array_variant, const godot_pool_real_array*: hgdn_new_pool_real_array_variant, \
        godot_pool_vector2_array*: hgdn_new_pool_vector2_array_variant, const godot_pool_vector2_array*: hgdn_new_pool_vector2_array_variant, \
        godot_pool_vector3_array*: hgdn_new_pool_vector3_array_variant, const godot_pool_vector3_array*: hgdn_new_pool_vector3_array_variant, \
        godot_pool_color_array*: hgdn_new_pool_color_array_variant, const godot_pool_color_array*: hgdn_new_pool_color_array_variant, \
        godot_pool_string_array*: hgdn_new_pool_string_array_variant, const godot_pool_string_array*: hgdn_new_pool_string_array_variant, \
        godot_string: hgdn_new_string_variant_own, \
        godot_node_path: hgdn_new_node_path_variant_own, \
        godot_dictionary: hgdn_new_dictionary_variant_own, \
        godot_array: hgdn_new_array_variant_own, \
        godot_pool_byte_array: hgdn_new_pool_byte_array_variant_own, \
        godot_pool_int_array: hgdn_new_pool_int_array_variant_own, \
        godot_pool_real_array: hgdn_new_pool_real_array_variant_own, \
        godot_pool_vector2_array: hgdn_new_pool_vector2_array_variant_own, \
        godot_pool_vector3_array: hgdn_new_pool_vector3_array_variant_own, \
        godot_pool_color_array: hgdn_new_pool_color_array_variant_own, \
        godot_pool_string_array: hgdn_new_pool_string_array_variant_own, \
        godot_variant*: hgdn_new_variant_copy, const godot_variant*: hgdn_new_variant_copy, \
        godot_variant: hgdn__variant_return \
    )(value))
HGDN_DECL godot_variant hgdn__variant_return(godot_variant value);
#else
#define hgdn_new_variant(value)  (value)  // No transformations in C without C11 support
#endif
/// @}


/// @defgroup string String creation
/// Helper functions to create Strings
/// @{
HGDN_DECL godot_string hgdn_new_string(const char *cstr);
HGDN_DECL godot_string hgdn_new_string_with_len(const char *cstr, const godot_int len);
/// @param fmt A `printf` compatible format
HGDN_DECL godot_string hgdn_new_formatted_string(const char *fmt, ...);

HGDN_DECL godot_string hgdn_new_wide_string(const wchar_t *wstr);
HGDN_DECL godot_string hgdn_new_wide_string_with_len(const wchar_t *wstr, const godot_int len);
/// @}


/// @defgroup array Pool*Array/Array creation
/// Helper functions to create Pool*Array/Array objects from sized buffers
///
/// The `*_args` variadic functions/macros construct a temporary array and call
/// the functions. On C++11 they are implemented using templates with parameter pack.
/// @{
HGDN_DECL godot_pool_byte_array hgdn_new_byte_array(const uint8_t *buffer, const godot_int size);
HGDN_DECL godot_pool_int_array hgdn_new_int_array(const godot_int *buffer, const godot_int size);
HGDN_DECL godot_pool_real_array hgdn_new_real_array(const godot_real *buffer, const godot_int size);
HGDN_DECL godot_pool_vector2_array hgdn_new_vector2_array(const godot_vector2 *buffer, const godot_int size);
HGDN_DECL godot_pool_vector3_array hgdn_new_vector3_array(const godot_vector3 *buffer, const godot_int size);
HGDN_DECL godot_pool_color_array hgdn_new_color_array(const godot_color *buffer, const godot_int size);
/// @note All strings must be NULL terminated.
HGDN_DECL godot_pool_string_array hgdn_new_string_array(const char *const *buffer, const godot_int size);
HGDN_DECL godot_array hgdn_new_array(const godot_variant *const *buffer, const godot_int size);
/// @note Variants in `buffer` will be destroyed, convenient if you create Variants only for constructing the Array
HGDN_DECL godot_array hgdn_new_array_own(godot_variant *buffer, const godot_int size);

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
        godot_variant buffer[] = { hgdn_new_variant(args)... };
        return hgdn_new_array_own(buffer, sizeof...(args));
    }
}
#else
    #define hgdn_new_byte_array_args(...)  (hgdn_new_byte_array((const uint8_t[]){ __VA_ARGS__ }, HGDN__NARG(__VA_ARGS__)))
    #define hgdn_new_int_array_args(...)  (hgdn_new_int_array((const godot_int[]){ __VA_ARGS__ }, HGDN__NARG(__VA_ARGS__)))
    #define hgdn_new_real_array_args(...)  (hgdn_new_real_array((const godot_real[]){ __VA_ARGS__ }, HGDN__NARG(__VA_ARGS__)))
    #define hgdn_new_vector2_array_args(...)  (hgdn_new_vector2_array((const godot_vector2[]){ __VA_ARGS__ }, HGDN__NARG(__VA_ARGS__)))
    #define hgdn_new_vector3_array_args(...)  (hgdn_new_vector3_array((const godot_vector3[]){ __VA_ARGS__ }, HGDN__NARG(__VA_ARGS__)))
    #define hgdn_new_color_array_args(...)  (hgdn_new_color_array((const godot_color[]){ __VA_ARGS__ }, HGDN__NARG(__VA_ARGS__)))
    #define hgdn_new_string_array_args(...)  (hgdn_new_string_array((const char *const []){ __VA_ARGS__ }, HGDN__NARG(__VA_ARGS__)))
    /// @note In C++ and C11 the arguments passed are transformed by `hgdn_new_variant`, so primitive C data can be passed directly
    #define hgdn_new_array_args(...)  (hgdn_new_array_own((godot_variant[]){ HGDN__MAP(hgdn_new_variant, __VA_ARGS__) }, HGDN__NARG(__VA_ARGS__)))
#endif
/// @}


/// @defgroup dictionary Dictionary creation
/// Helper functions to create Dictionaries
///
/// The `*_own` functions own the passed Variants, destroying them. Useful
/// when you create the Variants just for creating a Dictionary with them.
/// @{
typedef struct hgdn_dictionary_entry {
    godot_variant *key, *value;
} hgdn_dictionary_entry;

typedef struct hgdn_dictionary_entry_own {
    godot_variant key, value;
} hgdn_dictionary_entry_own;

typedef struct hgdn_dictionary_entry_string {
    const char *key;
    godot_variant *value;
} hgdn_dictionary_entry_string;

typedef struct hgdn_dictionary_entry_string_own {
    const char *key;
    godot_variant value;
} hgdn_dictionary_entry_string_own;

typedef struct hgdn_dictionary_entry_string_string {
    const char *key, *value;
} hgdn_dictionary_entry_string_string;

typedef struct hgdn_dictionary_entry_string_int {
    const char *key;
    godot_int value;
} hgdn_dictionary_entry_string_int;

HGDN_DECL godot_dictionary hgdn_new_dictionary(const hgdn_dictionary_entry *buffer, const godot_int size);
HGDN_DECL godot_dictionary hgdn_new_dictionary_string(const hgdn_dictionary_entry_string *buffer, const godot_int size);
HGDN_DECL godot_dictionary hgdn_new_dictionary_string_int(const hgdn_dictionary_entry_string_int *buffer, const godot_int size);
HGDN_DECL godot_dictionary hgdn_new_dictionary_string_string(const hgdn_dictionary_entry_string_string *buffer, const godot_int size);
HGDN_DECL godot_dictionary hgdn_new_dictionary_own(hgdn_dictionary_entry_own *buffer, const godot_int size);
HGDN_DECL godot_dictionary hgdn_new_dictionary_string_own(hgdn_dictionary_entry_string_own *buffer, const godot_int size);

#define hgdn_new_dictionary_args(...)  (hgdn_new_dictionary((const hgdn_dictionary_entry[]){ __VA_ARGS__ }, HGDN__NARG(__VA_ARGS__)))
#define hgdn_new_dictionary_string_args(...)  (hgdn_new_dictionary_string((const hgdn_dictionary_entry_string[]){ __VA_ARGS__ }, HGDN__NARG(__VA_ARGS__)))
#define hgdn_new_dictionary_string_int_args(...)  (hgdn_new_dictionary_string_int((const hgdn_dictionary_entry_string_int[]){ __VA_ARGS__ }, HGDN__NARG(__VA_ARGS__)))
#define hgdn_new_dictionary_string_string_args(...)  (hgdn_new_dictionary_string_string((const hgdn_dictionary_entry_string_string[]){ __VA_ARGS__ }, HGDN__NARG(__VA_ARGS__)))
#define hgdn_new_dictionary_own_args(...)  (hgdn_new_dictionary_own((hgdn_dictionary_entry_own[]){ __VA_ARGS__ }, HGDN__NARG(__VA_ARGS__)))
#define hgdn_new_dictionary_string_own_args(...)  (hgdn_new_dictionary_string_own((hgdn_dictionary_entry_string_own[]){ __VA_ARGS__ }, HGDN__NARG(__VA_ARGS__)))
/// @}


/// @defgroup object Object functions
/// Helper functions to work with `godot_object` values
/// @{
HGDN_DECL godot_variant hgdn_object_callv(godot_object *instance, const char *method, const godot_array *args);
HGDN_DECL godot_variant hgdn_object_callv_own(godot_object *instance, const char *method, godot_array args);
#define hgdn_object_get(instance, property)  (hgdn_object_call(instance, "get", property))
#define hgdn_object_set(instance, property, value)  (hgdn_object_call(instance, "set", property, value))

#if defined(__cplusplus) && __cplusplus >= 201103L  // Parameter pack is a C++11 feature
extern "C++" template<typename... Args> godot_variant hgdn_object_call(godot_object *instance, const char *method, Args... args) {
    godot_array args_array = hgdn_new_array_args(args...);
    return hgdn_object_callv_own(instance, method, args_array);
}
#else
/// @note In C++ and C11 the arguments passed are transformed by `hgdn_new_variant`, so primitive C data can be passed directly
#define hgdn_object_call(instance, method, ...)  (hgdn_object_callv_own((instance), (method), hgdn_new_array_args(__VA_ARGS__)))
#endif
/// @}


/// @defgroup nativescript NativeScript helpers
/// Definitions that help registering classes in Godot, focusing on wrapping C structs
/// @{
#ifndef HGDN_NO_EXT_NATIVESCRIPT
typedef struct hgdn_property_info {
    const char *path;
    godot_property_set_func setter;
    godot_property_get_func getter;
    // godot_property_attributes
    godot_int type;
    godot_property_hint hint;
    const char *hint_string;
    godot_property_usage_flags usage;
    godot_variant default_value;
    godot_method_rpc_mode rset_type;
    /// NativeScript 1.1 documentation
    const char *documentation;
} hgdn_property_info;

typedef struct hgdn_method_argument_info {
    const char *name;
    godot_variant_type type;
    godot_property_hint hint;
    const char *hint_string;
} hgdn_method_argument_info;

typedef struct hgdn_method_info {
    const char *name;
    godot_instance_method method;
    // godot_method_attributes
    godot_method_rpc_mode rpc_type;
    /// NativeScript 1.1 documentation
    const char *documentation;
    /// NULL-terminated array of argument info. If NULL, no documentation is registered.
    /// When a property with NULL `name` is encountered, stops registering.
    /// @see @ref hgdn_method_arguments
    hgdn_method_argument_info *arguments_info;
} hgdn_method_info;

typedef struct hgdn_signal_argument_info {
    const char *name;
    godot_int type;
    godot_property_hint hint;
    const char *hint_string;
    godot_variant default_value;
} hgdn_signal_argument_info;

typedef struct hgdn_signal_info {
    const char *name;
    hgdn_signal_argument_info *arguments_info;
    int num_default_args;
    /// NativeScript 1.1 documentation
    const char *documentation;
} hgdn_signal_info;

typedef struct hgdn_class_info {
    const char *name;
    const char *base;
    godot_instance_create_func create;
    godot_instance_destroy_func destroy;
    /// NULL-terminated array of properties. If NULL, no properties are registered.
    /// When a property with NULL `path` is encountered, stops registering.
    /// @see @ref hgdn_properties
    hgdn_property_info *properties;
    /// NULL-terminated array of methods. If NULL, no methods are registered.
    /// When a method with NULL `name` is encountered, stops registering.
    /// @see @ref hgdn_methods
    hgdn_method_info *methods;
    /// NULL-terminated array of signals. If NULL, no signals are registered.
    /// When a signal with NULL `name` is encountered, stops registering.
    /// @see @ref hgdn_signals
    hgdn_signal_info *signals;
    godot_bool tool;
    /// NativeScript 1.1 documentation
    const char *documentation;
} hgdn_class_info;

/// Helper for a literal NULL-terminated array of `hgdn_property_info`
#define hgdn_properties(...)  ((hgdn_property_info[]){ __VA_ARGS__, {} })
/// Helper for a literal NULL-terminated array of `hgdn_method_info`
#define hgdn_methods(...)  ((hgdn_method_info[]){ __VA_ARGS__, {} })
/// Helper for a literal NULL-terminated array of `hgdn_method_argument_info`
#define hgdn_method_arguments(...)  ((hgdn_method_argument_info[]){ __VA_ARGS__, {} })
/// Helper for a literal NULL-terminated array of `hgdn_signal_info`
#define hgdn_signals(...)  ((hgdn_signal_info[]){ __VA_ARGS__, {} })
/// Helper for a literal NULL-terminated array of `hgdn_signal_argument_info`
#define hgdn_signal_arguments(...)  ((hgdn_signal_argument_info[]){ __VA_ARGS__, {} })

HGDN_DECL void hgdn_register_class(void *gdnative_handle, const hgdn_class_info *class_info);

/// Function that allocates and returns zero-initialized `alloc_size` bytes, to be used as instance create function
HGDN_DECL void *hgdn_instance_alloc(godot_object *instance, void *alloc_size);
/// Create a `godot_instance_create_func` that allocates a zero-initialized `ctype`
#define hgdn_instance_create_func_alloc(ctype) ((const godot_instance_create_func){ &hgdn_instance_alloc, (void *) sizeof(ctype) })
/// Function that frees data with `hgdn_free`, to be used as instance destroy function
HGDN_DECL void hgdn_instance_free(godot_object *instance, void *method_data, void *data);
/// Create a `godot_instance_destroy_func` that frees instance data
#define hgdn_instance_destroy_func_free() ((const godot_instance_destroy_func){ &hgdn_instance_free })

HGDN_DECL godot_variant *hgdn_property_constant_alloc(godot_variant value);
HGDN_DECL void hgdn_property_constant_free(void *value);
HGDN_DECL godot_variant hgdn_property_constant_get(godot_object *instance, void *value, void *data);
/// @note In C++ and C11 the value passed is transformed by `hgdn_new_variant`, so primitive C data can be passed directly
#define hgdn_property_constant(value)  ((const godot_property_get_func){ &hgdn_property_constant_get, (void *) hgdn_property_constant_alloc(hgdn_new_variant((value))), &hgdn_property_constant_free })
#endif  // HGDN_NO_EXT_NATIVESCRIPT
/// @}

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
#ifndef HGDN_NO_CORE_1_1
const godot_gdnative_core_1_1_api_struct *hgdn_core_1_1_api;
#endif
#ifndef HGDN_NO_CORE_1_2
const godot_gdnative_core_1_2_api_struct *hgdn_core_1_2_api;
#endif
#ifndef HGDN_NO_CORE_1_3
const godot_gdnative_core_1_3_api_struct *hgdn_core_1_3_api;
#endif
#ifndef HGDN_NO_EXT_NATIVESCRIPT
const godot_gdnative_ext_nativescript_api_struct *hgdn_nativescript_api;
const godot_gdnative_ext_nativescript_1_1_api_struct *hgdn_nativescript_1_1_api;
#endif
#ifndef HGDN_NO_EXT_PLUGINSCRIPT
const godot_gdnative_ext_pluginscript_api_struct *hgdn_pluginscript_api;
#endif
#ifndef HGDN_NO_EXT_ANDROID
const godot_gdnative_ext_android_api_struct *hgdn_android_api;
#endif
#ifndef HGDN_NO_EXT_ARVR
const godot_gdnative_ext_arvr_api_struct *hgdn_arvr_api;
const godot_gdnative_ext_arvr_1_2_api_struct *hgdn_arvr_1_2_api;
#endif
#ifndef HGDN_NO_EXT_VIDEOCODER
const godot_gdnative_ext_videodecoder_api_struct *hgdn_videodecoder_api;
#endif
#ifndef HGDN_NO_EXT_NET
const godot_gdnative_ext_net_api_struct *hgdn_net_api;
const godot_gdnative_ext_net_3_2_api_struct *hgdn_net_3_2_api;
#endif
godot_object *hgdn_library;
godot_method_bind *hgdn_method_Object_callv;

static char hgdn__format_string_buffer[HGDN_STRING_FORMAT_BUFFER_SIZE];
#define HGDN__FILL_FORMAT_BUFFER(fmt, ...) \
    va_list args; \
    va_start(args, fmt); \
    godot_int size = vsnprintf(hgdn__format_string_buffer, HGDN_STRING_FORMAT_BUFFER_SIZE, fmt, args); \
    if (size > HGDN_STRING_FORMAT_BUFFER_SIZE) { \
        size = HGDN_STRING_FORMAT_BUFFER_SIZE; \
    } \
    va_end(args)

static godot_array hgdn__empty_array;

// Init and terminate
void hgdn_gdnative_init(const godot_gdnative_init_options *options) {
    hgdn_library = options->gd_native_library;
    hgdn_core_api = options->api_struct;
    for (const godot_gdnative_api_struct *ext = hgdn_core_api->next; ext; ext = ext->next) {
#ifndef HGDN_NO_CORE_1_1
        if (ext->version.major == 1 && ext->version.minor == 1) {
            hgdn_core_1_1_api = (const godot_gdnative_core_1_1_api_struct *) ext;
        }
#endif
#ifndef HGDN_NO_CORE_1_2
        if (ext->version.major == 1 && ext->version.minor == 2) {
            hgdn_core_1_2_api = (const godot_gdnative_core_1_2_api_struct *) ext;
        }
#endif
#ifndef HGDN_NO_CORE_1_3
        if (ext->version.major == 1 && ext->version.minor == 3) {
            hgdn_core_1_3_api = (const godot_gdnative_core_1_3_api_struct *) ext;
        }
#endif
    }

    for (unsigned int i = 0; i < hgdn_core_api->num_extensions; i++) {
        switch(hgdn_core_api->extensions[i]->type) {
#ifndef HGDN_NO_EXT_NATIVESCRIPT
            case GDNATIVE_EXT_NATIVESCRIPT:
                hgdn_nativescript_api = (const godot_gdnative_ext_nativescript_api_struct *) hgdn_core_api->extensions[i];
                for (const godot_gdnative_api_struct *ext = hgdn_nativescript_api->next; ext; ext = ext->next) {
                    if (ext->version.major == 1 && ext->version.minor == 1) {
                        hgdn_nativescript_1_1_api = (const godot_gdnative_ext_nativescript_1_1_api_struct *) ext;
                    }
                }
                break;
#endif
#ifndef HGDN_NO_EXT_PLUGINSCRIPT
            case GDNATIVE_EXT_PLUGINSCRIPT:
                hgdn_pluginscript_api = (const godot_gdnative_ext_pluginscript_api_struct *) hgdn_core_api->extensions[i];
                break;
#endif
#ifndef HGDN_NO_EXT_ANDROID
            case GDNATIVE_EXT_ANDROID:
                hgdn_android_api = (const godot_gdnative_ext_android_api_struct *) hgdn_core_api->extensions[i];
                break;
#endif
#ifndef HGDN_NO_EXT_ARVR
            case GDNATIVE_EXT_ARVR:
                hgdn_arvr_api = (const godot_gdnative_ext_arvr_api_struct *) hgdn_core_api->extensions[i];
                for (const godot_gdnative_api_struct *ext = hgdn_arvr_api->next; ext; ext = ext->next) {
                    if (ext->version.major == 1 && ext->version.minor == 2) {
                        hgdn_arvr_1_2_api = (const godot_gdnative_ext_arvr_1_2_api_struct *) ext;
                    }
                }
                break;
#endif
#ifndef HGDN_NO_EXT_VIDEOCODER
            case GDNATIVE_EXT_VIDEODECODER:
                hgdn_videodecoder_api = (const godot_gdnative_ext_videodecoder_api_struct *) hgdn_core_api->extensions[i];
                break;
#endif
#ifndef HGDN_NO_EXT_NET
            case GDNATIVE_EXT_NET:
                hgdn_net_api = (const godot_gdnative_ext_net_api_struct *) hgdn_core_api->extensions[i];
                for (const godot_gdnative_api_struct *ext = hgdn_net_api->next; ext; ext = ext->next) {
                    if (ext->version.major == 3 && ext->version.minor == 2) {
                        hgdn_net_3_2_api = (const godot_gdnative_ext_net_3_2_api_struct *) ext;
                    }
                }
                break;
#endif
            default:
                break;
        }
    }

    hgdn_method_Object_callv = hgdn_core_api->godot_method_bind_get_method("Object", "callv");
    hgdn_core_api->godot_array_new(&hgdn__empty_array);
}

void hgdn_gdnative_terminate(const godot_gdnative_terminate_options *options) {
    hgdn_core_api->godot_array_destroy(&hgdn__empty_array);
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
godot_string hgdn_new_wide_string(const wchar_t *wstr) {
    godot_string str;
    hgdn_core_api->godot_string_new_with_wide_string(&str, wstr, -1);
    return str;
}

godot_string hgdn_new_wide_string_with_len(const wchar_t *wstr, const godot_int len) {
    godot_string str;
    hgdn_core_api->godot_string_new_with_wide_string(&str, wstr, len);
    return str;
}

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

HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(byte, uint8_t)  // hgdn_new_byte_array
HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(int, godot_int)  // hgdn_new_int_array
HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(real, godot_real)  // hgdn_new_real_array
HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(vector2, godot_vector2)  // hgdn_new_vector2_array
HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(vector3, godot_vector3)  // hgdn_new_vector3_array
HGDN_DECLARE_NEW_POOL_ARRAY_FUNC(color, godot_color)  // hgdn_new_color_array

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

// Dictionary creation API
godot_dictionary hgdn_new_dictionary(const hgdn_dictionary_entry *buffer, const godot_int size) {
    godot_dictionary dict;
    hgdn_core_api->godot_dictionary_new(&dict);
    for (godot_int i = 0; i < size; i++) {
        hgdn_core_api->godot_dictionary_set(&dict, buffer[i].key, buffer[i].value);
    }
    return dict;
}

godot_dictionary hgdn_new_dictionary_string(const hgdn_dictionary_entry_string *buffer, const godot_int size) {
    godot_dictionary dict;
    hgdn_core_api->godot_dictionary_new(&dict);
    for (godot_int i = 0; i < size; i++) {
        godot_variant key = hgdn_new_string_variant_own(hgdn_new_string(buffer[i].key));
        hgdn_core_api->godot_dictionary_set(&dict, &key, buffer[i].value);
        hgdn_core_api->godot_variant_destroy(&key);
    }
    return dict;
}

godot_dictionary hgdn_new_dictionary_string_int(const hgdn_dictionary_entry_string_int *buffer, const godot_int size) {
    godot_dictionary dict;
    hgdn_core_api->godot_dictionary_new(&dict);
    for (godot_int i = 0; i < size; i++) {
        godot_variant key = hgdn_new_string_variant_own(hgdn_new_string(buffer[i].key));
        godot_variant value = hgdn_new_int_variant(buffer[i].value);
        hgdn_core_api->godot_dictionary_set(&dict, &key, &value);
        hgdn_core_api->godot_variant_destroy(&key);
        hgdn_core_api->godot_variant_destroy(&value);
    }
    return dict;
}

godot_dictionary hgdn_new_dictionary_string_string(const hgdn_dictionary_entry_string_string *buffer, const godot_int size) {
    godot_dictionary dict;
    hgdn_core_api->godot_dictionary_new(&dict);
    for (godot_int i = 0; i < size; i++) {
        godot_variant key = hgdn_new_string_variant_own(hgdn_new_string(buffer[i].key));
        godot_variant value = hgdn_new_string_variant_own(hgdn_new_string(buffer[i].value));
        hgdn_core_api->godot_dictionary_set(&dict, &key, &value);
        hgdn_core_api->godot_variant_destroy(&key);
        hgdn_core_api->godot_variant_destroy(&value);
    }
    return dict;
}

godot_dictionary hgdn_new_dictionary_own(hgdn_dictionary_entry_own *buffer, const godot_int size) {
    godot_dictionary dict;
    hgdn_core_api->godot_dictionary_new(&dict);
    for (godot_int i = 0; i < size; i++) {
        hgdn_core_api->godot_dictionary_set(&dict, &buffer[i].key, &buffer[i].value);
        hgdn_core_api->godot_variant_destroy(&buffer[i].key);
        hgdn_core_api->godot_variant_destroy(&buffer[i].value);
    }
    return dict;
}

godot_dictionary hgdn_new_dictionary_string_own(hgdn_dictionary_entry_string_own *buffer, const godot_int size) {
    godot_dictionary dict;
    hgdn_core_api->godot_dictionary_new(&dict);
    for (godot_int i = 0; i < size; i++) {
        godot_variant key = hgdn_new_string_variant_own(hgdn_new_string(buffer[i].key));
        hgdn_core_api->godot_dictionary_set(&dict, &key, &buffer[i].value);
        hgdn_core_api->godot_variant_destroy(&key);
        hgdn_core_api->godot_variant_destroy(&buffer[i].value);
    }
    return dict;
}

// String helpers
hgdn_wide_string hgdn_wide_string_get(const godot_string *str) {
    godot_string new_str;
    hgdn_core_api->godot_string_new_copy(&new_str, str);
    return hgdn_wide_string_get_own(new_str);
}

hgdn_wide_string hgdn_wide_string_get_own(godot_string str) {
    hgdn_wide_string wrapper = {
        str,
        hgdn_core_api->godot_string_wide_str(&str),
        hgdn_core_api->godot_string_length(&str),
    };
    return wrapper;
}

void hgdn_wide_string_destroy(hgdn_wide_string *str) {
    hgdn_core_api->godot_string_destroy(&str->gd_string);
}

hgdn_string hgdn_string_get(const godot_string *str) {
    godot_char_string char_string = hgdn_core_api->godot_string_utf8(str);
    hgdn_string wrapper = {
        char_string,
        hgdn_core_api->godot_char_string_get_data(&char_string),
        hgdn_core_api->godot_char_string_length(&char_string),
    };
    return wrapper;
}

hgdn_string hgdn_string_get_own(godot_string str) {
    hgdn_string wrapper = hgdn_string_get(&str);
    hgdn_core_api->godot_string_destroy(&str);
    return wrapper;
}

void hgdn_string_destroy(hgdn_string *str) {
    hgdn_core_api->godot_char_string_destroy(&str->gd_char_string);
}

// Pool String helpers
#define HGDN_DECLARE_POOL_ARRAY_API(kind, ctype) \
    hgdn_##kind##_array hgdn_##kind##_array_get(const godot_pool_##kind##_array *array) { \
        godot_pool_##kind##_array_read_access *access = hgdn_core_api->godot_pool_##kind##_array_read(array); \
        hgdn_##kind##_array wrapper = { \
            access, \
            hgdn_core_api->godot_pool_##kind##_array_read_access_ptr(access), \
            hgdn_core_api->godot_pool_##kind##_array_size(array), \
        }; \
        return wrapper; \
    } \
    hgdn_##kind##_array hgdn_##kind##_array_get_own(godot_pool_##kind##_array array) { \
        hgdn_##kind##_array result = hgdn_##kind##_array_get(&array); \
        hgdn_core_api->godot_pool_##kind##_array_destroy(&array); \
        return result; \
    } \
    void hgdn_##kind##_array_destroy(hgdn_##kind##_array *array) { \
        hgdn_core_api->godot_pool_##kind##_array_read_access_destroy(array->gd_read_access); \
    }

HGDN_DECLARE_POOL_ARRAY_API(byte, uint8_t)  // hgdn_byte_array_get, hgdn_byte_array_get_own, hgdn_byte_array_destroy
HGDN_DECLARE_POOL_ARRAY_API(int, godot_int)  // hgdn_int_array_get, hgdn_int_array_get_own, hgdn_int_array_destroy
HGDN_DECLARE_POOL_ARRAY_API(real, godot_real)  // hgdn_real_array_get, hgdn_real_array_get_own, hgdn_real_array_destroy
HGDN_DECLARE_POOL_ARRAY_API(vector2, godot_vector2)  // hgdn_vector2_array_get, hgdn_vector2_array_get_own, hgdn_vector2_array_destroy
HGDN_DECLARE_POOL_ARRAY_API(vector3, godot_vector3)  // hgdn_vector3_array_get, hgdn_vector3_array_get_own, hgdn_vector3_array_destroy
HGDN_DECLARE_POOL_ARRAY_API(color, godot_color)  // hgdn_color_array_get, hgdn_color_array_get_own, hgdn_color_array_destroy

#undef HGDN_DECLARE_POOL_ARRAY_API

hgdn_string_array hgdn_string_array_get(const godot_pool_string_array *array) {
    godot_int size = hgdn_core_api->godot_pool_string_array_size(array);
    godot_pool_string_array_read_access *access = hgdn_core_api->godot_pool_string_array_read(array);
    hgdn_string_array wrapper = {0};
    if ((wrapper.strings = (hgdn_string *) hgdn_alloc(size * sizeof(hgdn_string))) == NULL) {
        return wrapper;
    }
    if ((wrapper.ptr = (const char **) hgdn_alloc(size * sizeof(char *))) == NULL) {
        hgdn_free(wrapper.strings);
        return wrapper;
    }
    wrapper.size = size;
    const godot_string *gd_strings = hgdn_core_api->godot_pool_string_array_read_access_ptr(access);
    for (godot_int i = 0; i < size; i++) {
        hgdn_string str = hgdn_string_get(&gd_strings[i]);
        wrapper.strings[i] = str;
        wrapper.ptr[i] = str.ptr;
    }
    hgdn_core_api->godot_pool_string_array_read_access_destroy(access);
    return wrapper;
}

hgdn_string_array hgdn_string_array_get_own(godot_pool_string_array array) {
    hgdn_string_array result = hgdn_string_array_get(&array);
    hgdn_core_api->godot_pool_string_array_destroy(&array);
    return result;
}

void hgdn_string_array_destroy(hgdn_string_array *array) {
    for (godot_int i = 0; i < array->size; i++) {
        hgdn_string_destroy(&array->strings[i]);
    }
    hgdn_free(array->strings);
    hgdn_free((void *) array->ptr);
}

// Get values from Variant, Array, Dictionary and method arguments helpers
#define HGDN_DECLARE_VARIANT_GET(kind, ctype) \
    ctype hgdn_variant_get_##kind(const godot_variant *var) { \
        return hgdn_core_api->godot_variant_as_##kind(var); \
    }
#define HGDN_DECLARE_VARIANT_GET_OWN(kind, ctype) \
    ctype hgdn_variant_get_##kind##_own(godot_variant var) { \
        ctype result = hgdn_variant_get_##kind(&var); \
        hgdn_core_api->godot_variant_destroy(&var); \
        return result; \
    }
#define HGDN_DECLARE_ARRAY_GET(kind, ctype) \
    ctype hgdn_array_get_##kind(const godot_array *array, const godot_int index) { \
        return hgdn_variant_get_##kind(hgdn_core_api->godot_array_operator_index_const(array, index)); \
    }
#define HGDN_DECLARE_ARGS_GET(kind, ctype) \
    ctype hgdn_args_get_##kind(godot_variant **args, const godot_int index) { \
        return hgdn_variant_get_##kind(args[index]); \
    }
#define HGDN_DECLARE_DICTIONARY_GET(kind, ctype) \
    ctype hgdn_dictionary_get_##kind(const godot_dictionary *dict, const godot_variant *key) { \
        return hgdn_variant_get_##kind(hgdn_core_api->godot_dictionary_operator_index_const(dict, key)); \
    } \
    ctype hgdn_dictionary_string_get_##kind(const godot_dictionary *dict, const char *key) { \
        godot_variant key_var = hgdn_new_cstring_variant(key); \
        ctype value = hgdn_dictionary_get_##kind(dict, &key_var); \
        hgdn_core_api->godot_variant_destroy(&key_var); \
        return value; \
    }

HGDN_DECLARE_VARIANT_GET(bool, godot_bool)  // hgdn_variant_get_bool
HGDN_DECLARE_VARIANT_GET_OWN(bool, godot_bool)  // hgdn_variant_get_bool_own
HGDN_DECLARE_ARRAY_GET(bool, godot_bool)  // hgdn_array_get_bool
HGDN_DECLARE_ARGS_GET(bool, godot_bool)  // hgdn_args_get_bool
HGDN_DECLARE_DICTIONARY_GET(bool, godot_bool)  // hgdn_dictionary_get_bool, hgdn_dictionary_string_get_bool

#define HGDN_DECLARE_VARIANT_API(kind, ctype) \
    HGDN_DECLARE_VARIANT_GET(kind, ctype) \
    HGDN_DECLARE_VARIANT_GET_OWN(kind, ctype) \
    HGDN_DECLARE_ARRAY_GET(kind, ctype) \
    HGDN_DECLARE_ARGS_GET(kind, ctype) \
    HGDN_DECLARE_DICTIONARY_GET(kind, ctype)

HGDN_DECLARE_VARIANT_API(uint, uint64_t)  // hgdn_variant_get_uint, hgdn_variant_get_uint_own, hgdn_array_get_uint, hgdn_args_get_uint, hgdn_dictionary_get_uint, hgdn_dictionary_string_get_uint
HGDN_DECLARE_VARIANT_API(int, int64_t)  // hgdn_variant_get_int, hgdn_variant_get_int_own, hgdn_array_get_int, hgdn_args_get_int, hgdn_dictionary_get_int, hgdn_dictionary_string_get_int
HGDN_DECLARE_VARIANT_API(real, double)  // hgdn_variant_get_real, hgdn_variant_get_real_own, hgdn_array_get_real, hgdn_args_get_real, hgdn_dictionary_get_real, hgdn_dictionary_string_get_real
HGDN_DECLARE_VARIANT_API(vector2, godot_vector2)  // hgdn_variant_get_vector2, hgdn_variant_get_vector2_own, hgdn_array_get_vector2, hgdn_args_get_vector2, hgdn_dictionary_get_vector2, hgdn_dictionary_string_get_vector2
HGDN_DECLARE_VARIANT_API(vector3, godot_vector3)  // hgdn_variant_get_vector3, hgdn_variant_get_vector3_own, hgdn_array_get_vector3, hgdn_args_get_vector3, hgdn_dictionary_get_vector3, hgdn_dictionary_string_get_vector3
HGDN_DECLARE_VARIANT_API(rect2, godot_rect2)  // hgdn_variant_get_rect2, hgdn_variant_get_rect2_own, hgdn_array_get_rect2, hgdn_args_get_rect2, hgdn_dictionary_get_rect2, hgdn_dictionary_string_get_rect2
HGDN_DECLARE_VARIANT_API(plane, godot_plane)  // hgdn_variant_get_plane, hgdn_variant_get_plane_own, hgdn_array_get_plane, hgdn_args_get_plane, hgdn_dictionary_get_plane, hgdn_dictionary_string_get_plane
HGDN_DECLARE_VARIANT_API(quat, godot_quat)  // hgdn_variant_get_quat, hgdn_variant_get_quat_own, hgdn_array_get_quat, hgdn_args_get_quat, hgdn_dictionary_get_quat, hgdn_dictionary_string_get_quat
HGDN_DECLARE_VARIANT_API(aabb, godot_aabb)  // hgdn_variant_get_aabb, hgdn_variant_get_aabb_own, hgdn_array_get_aabb, hgdn_args_get_aabb, hgdn_dictionary_get_aabb, hgdn_dictionary_string_get_aabb
HGDN_DECLARE_VARIANT_API(basis, godot_basis)  // hgdn_variant_get_basis, hgdn_variant_get_basis_own, hgdn_array_get_basis, hgdn_args_get_basis, hgdn_dictionary_get_basis, hgdn_dictionary_string_get_basis
HGDN_DECLARE_VARIANT_API(transform2d, godot_transform2d)  // hgdn_variant_get_transform2d, hgdn_variant_get_transform2d_own, hgdn_array_get_transform2d, hgdn_args_get_transform2d, hgdn_dictionary_get_transform2d, hgdn_dictionary_string_get_transform2d
HGDN_DECLARE_VARIANT_API(transform, godot_transform)  // hgdn_variant_get_transform, hgdn_variant_get_transform_own, hgdn_array_get_transform, hgdn_args_get_transform, hgdn_dictionary_get_transform, hgdn_dictionary_string_get_transform
HGDN_DECLARE_VARIANT_API(color, godot_color)  // hgdn_variant_get_color, hgdn_variant_get_color_own, hgdn_array_get_color, hgdn_args_get_color, hgdn_dictionary_get_color, hgdn_dictionary_string_get_color
HGDN_DECLARE_VARIANT_API(node_path, godot_node_path)  // hgdn_variant_get_node_path, hgdn_variant_get_node_path_own, hgdn_array_get_node_path, hgdn_args_get_node_path, hgdn_dictionary_get_node_path, hgdn_dictionary_string_get_node_path
HGDN_DECLARE_VARIANT_API(rid, godot_rid)  // hgdn_variant_get_rid, hgdn_variant_get_rid_own, hgdn_array_get_rid, hgdn_args_get_rid, hgdn_dictionary_get_rid, hgdn_dictionary_string_get_rid
HGDN_DECLARE_VARIANT_API(object, godot_object *)  // hgdn_variant_get_object, hgdn_variant_get_object_own, hgdn_array_get_object, hgdn_args_get_object, hgdn_dictionary_get_object, hgdn_dictionary_string_get_object
HGDN_DECLARE_VARIANT_API(dictionary, godot_dictionary)  // hgdn_variant_get_dictionary, hgdn_variant_get_dictionary_own, hgdn_array_get_dictionary, hgdn_args_get_dictionary, hgdn_dictionary_get_dictionary, hgdn_dictionary_string_get_dictionary
HGDN_DECLARE_VARIANT_API(array, godot_array)  // hgdn_variant_get_array, hgdn_variant_get_array_own, hgdn_array_get_array, hgdn_args_get_array, hgdn_dictionary_get_array, hgdn_dictionary_string_get_array

#undef HGDN_DECLARE_VARIANT_GET

hgdn_string hgdn_variant_get_string(const godot_variant *var) {
    return hgdn_string_get_own(hgdn_core_api->godot_variant_as_string(var));
}
HGDN_DECLARE_VARIANT_GET_OWN(string, hgdn_string)  // hgdn_variant_get_string_own
HGDN_DECLARE_ARRAY_GET(string, hgdn_string)  // hgdn_array_get_string
HGDN_DECLARE_ARGS_GET(string, hgdn_string)  // hgdn_args_get_string
HGDN_DECLARE_DICTIONARY_GET(string, hgdn_string)  // hgdn_dictionary_get_string

hgdn_wide_string hgdn_variant_get_wide_string(const godot_variant *var) {
    return hgdn_wide_string_get_own(hgdn_core_api->godot_variant_as_string(var));
}
HGDN_DECLARE_VARIANT_GET_OWN(wide_string, hgdn_wide_string)  // hgdn_variant_get_wide_string_own
HGDN_DECLARE_ARRAY_GET(wide_string, hgdn_wide_string)  // hgdn_array_get_wide_string
HGDN_DECLARE_ARGS_GET(wide_string, hgdn_wide_string)  // hgdn_args_get_wide_string
HGDN_DECLARE_DICTIONARY_GET(wide_string, hgdn_wide_string)  // hgdn_dictionary_get_wide_string

#define HGDN_DECLARE_VARIANT_GET_POOL_ARRAY(kind, ctype) \
    ctype hgdn_variant_get_##kind(const godot_variant *var) { \
        return hgdn_##kind##_get_own(hgdn_core_api->godot_variant_as_pool_##kind(var)); \
    } \
    HGDN_DECLARE_VARIANT_GET_OWN(kind, ctype) \
    HGDN_DECLARE_ARRAY_GET(kind, ctype) \
    HGDN_DECLARE_ARGS_GET(kind, ctype) \
    HGDN_DECLARE_DICTIONARY_GET(kind, ctype)

HGDN_DECLARE_VARIANT_GET_POOL_ARRAY(byte_array, hgdn_byte_array)  // hgdn_variant_get_byte_array, hgdn_variant_get_byte_array_own, hgdn_array_get_byte_array, hgdn_args_get_byte_array, hgdn_dictionary_get_byte_array, hgdn_dictionary_string_get_byte_array
HGDN_DECLARE_VARIANT_GET_POOL_ARRAY(int_array, hgdn_int_array)  // hgdn_variant_get_int_array, hgdn_variant_get_int_array_own, hgdn_array_get_int_array, hgdn_args_get_int_array, hgdn_dictionary_get_int_array, hgdn_dictionary_string_get_int_array
HGDN_DECLARE_VARIANT_GET_POOL_ARRAY(real_array, hgdn_real_array)  // hgdn_variant_get_real_array, hgdn_variant_get_real_array_own, hgdn_array_get_real_array, hgdn_args_get_real_array, hgdn_dictionary_get_real_array, hgdn_dictionary_string_get_real_array
HGDN_DECLARE_VARIANT_GET_POOL_ARRAY(string_array, hgdn_string_array)  // hgdn_variant_get_string_array, hgdn_variant_get_string_array_own, hgdn_array_get_string_array, hgdn_args_get_string_array, hgdn_dictionary_get_string_array, hgdn_dictionary_string_get_string_array
HGDN_DECLARE_VARIANT_GET_POOL_ARRAY(vector2_array, hgdn_vector2_array)  // hgdn_variant_get_vector2_array, hgdn_variant_get_vector2_array_own, hgdn_array_get_vector2_array, hgdn_args_get_vector2_array, hgdn_dictionary_get_vector2_array, hgdn_dictionary_string_get_vector2_array
HGDN_DECLARE_VARIANT_GET_POOL_ARRAY(vector3_array, hgdn_vector3_array)  // hgdn_variant_get_vector3_array, hgdn_variant_get_vector3_array_own, hgdn_array_get_vector3_array, hgdn_args_get_vector3_array, hgdn_dictionary_get_vector3_array, hgdn_dictionary_string_get_vector3_array
HGDN_DECLARE_VARIANT_GET_POOL_ARRAY(color_array, hgdn_color_array)  // hgdn_variant_get_color_array, hgdn_variant_get_color_array_own, hgdn_array_get_color_array, hgdn_args_get_color_array, hgdn_dictionary_get_color_array, hgdn_dictionary_string_get_color_array

#undef HGDN_DECLARE_VARIANT_GET_POOL_ARRAY

#undef HGDN_DECLARE_DICTIONARY_GET
#undef HGDN_DECLARE_ARGS_GET
#undef HGDN_DECLARE_ARRAY_GET
#undef HGDN_DECLARE_VARIANT_GET_OWN

// Object helpers
godot_variant hgdn_object_callv(godot_object *instance, const char *method, const godot_array *args_array) {
    if (!args_array) {
        args_array = &hgdn__empty_array;
    }
    godot_variant result;
    godot_string method_str = hgdn_new_string(method);
    const void *args[] = { &method_str, args_array };
    hgdn_core_api->godot_method_bind_ptrcall(hgdn_method_Object_callv, instance, args, &result);
    hgdn_core_api->godot_string_destroy(&method_str);
    return result;
}

godot_variant hgdn_object_callv_own(godot_object *instance, const char *method, godot_array args) {
    godot_variant result = hgdn_object_callv(instance, method, &args);
    hgdn_core_api->godot_array_destroy(&args);
    return result;
}

// Create variants
godot_variant hgdn_new_variant_copy(const godot_variant *value) {
    godot_variant var;
    hgdn_core_api->godot_variant_new_copy(&var, value);
    return var;
}

godot_variant hgdn_new_nil_variant() {
    godot_variant var;
    hgdn_core_api->godot_variant_new_nil(&var);
    return var;
}

#define HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(kind, ctype) \
    godot_variant hgdn_new_##kind##_variant(const ctype value) { \
        godot_variant var; \
        hgdn_core_api->godot_variant_new_##kind(&var, value); \
        return var; \
    }

HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(bool, godot_bool)  // hgdn_new_bool_variant
HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(uint, uint64_t)  // hgdn_new_uint_variant
HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(int, int64_t)  // hgdn_new_int_variant
HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(real, double)  // hgdn_new_real_variant
HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(string, godot_string *)  // hgdn_new_string_variant
HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(dictionary, godot_dictionary *)  // hgdn_new_dictionary_variant
HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(array, godot_array *)  // hgdn_new_array_variant
HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(pool_byte_array, godot_pool_byte_array *)  // hgdn_new_pool_byte_array_variant
HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(pool_int_array, godot_pool_int_array *)  // hgdn_new_pool_int_array_variant
HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(pool_real_array, godot_pool_real_array *)  // hgdn_new_pool_real_array_variant
HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(pool_vector2_array, godot_pool_vector2_array *)  // hgdn_new_pool_vector2_array_variant
HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(pool_vector3_array, godot_pool_vector3_array *)  // hgdn_new_pool_vector3_array_variant
HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(pool_color_array, godot_pool_color_array *)  // hgdn_new_pool_color_array_variant
HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(pool_string_array, godot_pool_string_array *)  // hgdn_new_pool_string_array_variant
HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(node_path, godot_node_path *)  // hgdn_new_node_path_variant
HGDN_DECLARE_NEW_PRIMITIVE_VARIANT(rid, godot_rid *)  // hgdn_new_rid_variant

#undef HGDN_DECLARE_NEW_PRIMITIVE_VARIANT

godot_variant hgdn_new_object_variant(const godot_object *value) {
    godot_variant var;
    if (value) {
        hgdn_core_api->godot_variant_new_object(&var, value);
    }
    else {
        hgdn_core_api->godot_variant_new_nil(&var);
    }
    return var;
}

godot_variant hgdn_new_cstring_variant(const char *value) {
    return hgdn_new_string_variant_own(hgdn_new_string(value));
}

godot_variant hgdn_new_wide_string_variant(const wchar_t *value) {
    return hgdn_new_string_variant_own(hgdn_new_wide_string(value));
}

#define HGDN_DECLARE_NEW_COMPOUND_VARIANT(kind, ctype) \
    godot_variant hgdn_new_##kind##_variant(const ctype value) { \
        godot_variant var; \
        hgdn_core_api->godot_variant_new_##kind(&var, &value); \
        return var; \
    }

HGDN_DECLARE_NEW_COMPOUND_VARIANT(vector2, godot_vector2)  // hgdn_new_vector2_variant
HGDN_DECLARE_NEW_COMPOUND_VARIANT(vector3, godot_vector3)  // hgdn_new_vector3_variant
HGDN_DECLARE_NEW_COMPOUND_VARIANT(rect2, godot_rect2)  // hgdn_new_rect2_variant
HGDN_DECLARE_NEW_COMPOUND_VARIANT(plane, godot_plane)  // hgdn_new_plane_variant
HGDN_DECLARE_NEW_COMPOUND_VARIANT(quat, godot_quat)  // hgdn_new_quat_variant
HGDN_DECLARE_NEW_COMPOUND_VARIANT(aabb, godot_aabb)  // hgdn_new_aabb_variant
HGDN_DECLARE_NEW_COMPOUND_VARIANT(basis, godot_basis)  // hgdn_new_basis_variant
HGDN_DECLARE_NEW_COMPOUND_VARIANT(transform2d, godot_transform2d)  // hgdn_new_transform2d_variant
HGDN_DECLARE_NEW_COMPOUND_VARIANT(transform, godot_transform)  // hgdn_new_transform_variant
HGDN_DECLARE_NEW_COMPOUND_VARIANT(color, godot_color)  // hgdn_new_color_variant

#undef HGDN_DECLARE_NEW_COMPOUND_VARIANT

#define HGDN_DECLARE_NEW_OWNED_VARIANT(kind, ctype) \
    godot_variant hgdn_new_##kind##_variant_own(ctype value) { \
        godot_variant var; \
        hgdn_core_api->godot_variant_new_##kind(&var, &value); \
        hgdn_core_api->ctype##_destroy(&value); \
        return var; \
    }

HGDN_DECLARE_NEW_OWNED_VARIANT(string, godot_string)  // hgdn_new_string_variant_own
HGDN_DECLARE_NEW_OWNED_VARIANT(dictionary, godot_dictionary)  // hgdn_new_dictionary_variant_own
HGDN_DECLARE_NEW_OWNED_VARIANT(array, godot_array)  // hgdn_new_array_variant_own
HGDN_DECLARE_NEW_OWNED_VARIANT(pool_byte_array, godot_pool_byte_array)  // hgdn_new_pool_byte_array_variant_own
HGDN_DECLARE_NEW_OWNED_VARIANT(pool_int_array, godot_pool_int_array)  // hgdn_new_pool_int_array_variant_own
HGDN_DECLARE_NEW_OWNED_VARIANT(pool_real_array, godot_pool_real_array)  // hgdn_new_pool_real_array_variant_own
HGDN_DECLARE_NEW_OWNED_VARIANT(pool_vector2_array, godot_pool_vector2_array)  // hgdn_new_pool_vector2_array_variant_own
HGDN_DECLARE_NEW_OWNED_VARIANT(pool_vector3_array, godot_pool_vector3_array)  // hgdn_new_pool_vector3_array_variant_own
HGDN_DECLARE_NEW_OWNED_VARIANT(pool_color_array, godot_pool_color_array)  // hgdn_new_pool_color_array_variant_own
HGDN_DECLARE_NEW_OWNED_VARIANT(pool_string_array, godot_pool_string_array)  // hgdn_new_pool_string_array_variant_own
HGDN_DECLARE_NEW_OWNED_VARIANT(node_path, godot_node_path)  // hgdn_new_node_path_variant_own

#undef HGDN_DECLARE_NEW_OWNED_VARIANT

#ifdef __cplusplus
godot_variant hgdn_new_variant(const godot_bool value) { return hgdn_new_bool_variant(value); }
godot_variant hgdn_new_variant(const unsigned int value) { return hgdn_new_uint_variant(value); }
godot_variant hgdn_new_variant(const uint64_t value) { return hgdn_new_uint_variant(value); }
godot_variant hgdn_new_variant(const int value) { return hgdn_new_int_variant(value); }
godot_variant hgdn_new_variant(const int64_t value) { return hgdn_new_int_variant(value); }
godot_variant hgdn_new_variant(const double value) { return hgdn_new_real_variant(value); }
godot_variant hgdn_new_variant(const godot_string *value) { return hgdn_new_string_variant(value); }
godot_variant hgdn_new_variant(const char *value) { return hgdn_new_cstring_variant(value); }
godot_variant hgdn_new_variant(const wchar_t *value) { return hgdn_new_wide_string_variant(value); }
godot_variant hgdn_new_variant(const godot_vector2 value) { return hgdn_new_vector2_variant(value); }
godot_variant hgdn_new_variant(const godot_vector3 value) { return hgdn_new_vector3_variant(value); }
godot_variant hgdn_new_variant(const godot_rect2 value) { return hgdn_new_rect2_variant(value); }
godot_variant hgdn_new_variant(const godot_plane value) { return hgdn_new_plane_variant(value); }
godot_variant hgdn_new_variant(const godot_quat value) { return hgdn_new_quat_variant(value); }
godot_variant hgdn_new_variant(const godot_aabb value) { return hgdn_new_aabb_variant(value); }
godot_variant hgdn_new_variant(const godot_basis value) { return hgdn_new_basis_variant(value); }
godot_variant hgdn_new_variant(const godot_transform2d value) { return hgdn_new_transform2d_variant(value); }
godot_variant hgdn_new_variant(const godot_transform value) { return hgdn_new_transform_variant(value); }
godot_variant hgdn_new_variant(const godot_color value) { return hgdn_new_color_variant(value); }
godot_variant hgdn_new_variant(const godot_node_path *value) { return hgdn_new_node_path_variant(value); }
godot_variant hgdn_new_variant(const godot_rid *value) { return hgdn_new_rid_variant(value); }
godot_variant hgdn_new_variant(const godot_object *value) { return hgdn_new_object_variant(value); }
godot_variant hgdn_new_variant(const godot_dictionary *value) { return hgdn_new_dictionary_variant(value); }
godot_variant hgdn_new_variant(const godot_array *value) { return hgdn_new_array_variant(value); }
godot_variant hgdn_new_variant(const godot_pool_byte_array *value) { return hgdn_new_pool_byte_array_variant(value); }
godot_variant hgdn_new_variant(const godot_pool_int_array *value) { return hgdn_new_pool_int_array_variant(value); }
godot_variant hgdn_new_variant(const godot_pool_real_array *value) { return hgdn_new_pool_real_array_variant(value); }
godot_variant hgdn_new_variant(const godot_pool_vector2_array *value) { return hgdn_new_pool_vector2_array_variant(value); }
godot_variant hgdn_new_variant(const godot_pool_vector3_array *value) { return hgdn_new_pool_vector3_array_variant(value); }
godot_variant hgdn_new_variant(const godot_pool_color_array *value) { return hgdn_new_pool_color_array_variant(value); }
godot_variant hgdn_new_variant(const godot_pool_string_array *value) { return hgdn_new_pool_string_array_variant(value); }
godot_variant hgdn_new_variant(godot_string value) { return hgdn_new_string_variant_own(value); }
godot_variant hgdn_new_variant(godot_node_path value) { return hgdn_new_node_path_variant_own(value); }
godot_variant hgdn_new_variant(godot_dictionary value) { return hgdn_new_dictionary_variant_own(value); }
godot_variant hgdn_new_variant(godot_array value) { return hgdn_new_array_variant_own(value); }
godot_variant hgdn_new_variant(godot_pool_byte_array value) { return hgdn_new_pool_byte_array_variant_own(value); }
godot_variant hgdn_new_variant(godot_pool_int_array value) { return hgdn_new_pool_int_array_variant_own(value); }
godot_variant hgdn_new_variant(godot_pool_real_array value) { return hgdn_new_pool_real_array_variant_own(value); }
godot_variant hgdn_new_variant(godot_pool_vector2_array value) { return hgdn_new_pool_vector2_array_variant_own(value); }
godot_variant hgdn_new_variant(godot_pool_vector3_array value) { return hgdn_new_pool_vector3_array_variant_own(value); }
godot_variant hgdn_new_variant(godot_pool_color_array value) { return hgdn_new_pool_color_array_variant_own(value); }
godot_variant hgdn_new_variant(godot_pool_string_array value) { return hgdn_new_pool_string_array_variant_own(value); }
godot_variant hgdn_new_variant(const godot_variant *value) { return hgdn_new_variant_copy(value); }
HGDN_CONSTEXPR godot_variant hgdn_new_variant(godot_variant value) { return value; }
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L  // C11
godot_variant hgdn__variant_return(godot_variant value) { return value; }
#endif  // __cplusplus

// NativeScript
#ifndef HGDN_NO_EXT_NATIVESCRIPT
void hgdn_register_class(void *handle, const hgdn_class_info *class_info) {
    if (class_info->tool) {
        hgdn_nativescript_api->godot_nativescript_register_tool_class(handle, class_info->name, class_info->base, class_info->create, class_info->destroy);
    }
    else {
        hgdn_nativescript_api->godot_nativescript_register_class(handle, class_info->name, class_info->base, class_info->create, class_info->destroy);
    }

    if (hgdn_nativescript_1_1_api && class_info->documentation) {
        godot_string documentation = hgdn_new_string(class_info->documentation);
        hgdn_nativescript_1_1_api->godot_nativescript_set_class_documentation(handle, class_info->name, documentation);
        hgdn_core_api->godot_string_destroy(&documentation);
    }

    if (class_info->properties) {
        for (hgdn_property_info *property = class_info->properties; property->path; property++) {
            godot_property_attributes attr = {
                property->rset_type,
                property->type,
                property->hint,
                hgdn_new_string(property->hint_string),
                property->usage,
                property->default_value,
            };
            hgdn_nativescript_api->godot_nativescript_register_property(handle, class_info->name, property->path, &attr, property->setter, property->getter);
            hgdn_core_api->godot_string_destroy(&attr.hint_string);
            if (hgdn_nativescript_1_1_api && property->documentation) {
                godot_string documentation = hgdn_new_string(property->documentation);
                hgdn_nativescript_1_1_api->godot_nativescript_set_property_documentation(handle, class_info->name, property->path, documentation);
                hgdn_core_api->godot_string_destroy(&documentation);
            }
        }
    }

    if (class_info->methods) {
        for (hgdn_method_info *method = class_info->methods; method->name; method++) {
            godot_method_attributes attr = { method->rpc_type };
            hgdn_nativescript_api->godot_nativescript_register_method(handle, class_info->name, method->name, attr, method->method);
            if (hgdn_nativescript_1_1_api) {
                if (method->documentation) {
                    godot_string documentation = hgdn_new_string(method->documentation);
                    hgdn_nativescript_1_1_api->godot_nativescript_set_method_documentation(handle, class_info->name, method->name, documentation);
                    hgdn_core_api->godot_string_destroy(&documentation);
                }
                if (method->arguments_info) {
                    godot_method_arg gd_args[HGDN_METHOD_ARGUMENTS_INFO_MAX];
                    int num_args = 0;
                    for (hgdn_method_argument_info *argument = method->arguments_info; argument->name; argument++) {
                        gd_args[num_args] = (godot_method_arg){
                            hgdn_new_string(argument->name),
                            argument->type,
                            argument->hint,
                            hgdn_new_string(argument->hint_string),
                        };
                        num_args++;
                    }
                    hgdn_nativescript_1_1_api->godot_nativescript_set_method_argument_information(handle, class_info->name, method->name, num_args, gd_args);
                    for (int i = 0; i < num_args; i++) {
                        hgdn_core_api->godot_string_destroy(&gd_args[i].name);
                        hgdn_core_api->godot_string_destroy(&gd_args[i].hint_string);
                    }
                }
            }
        }
    }

    if (class_info->signals) {
        for (hgdn_signal_info *signal = class_info->signals; signal->name; signal++) {
            godot_signal_argument gd_args[HGDN_METHOD_ARGUMENTS_INFO_MAX];
            int num_args = 0;
            for (hgdn_signal_argument_info *argument = signal->arguments_info; argument->name; argument++) {
                gd_args[num_args] = (godot_signal_argument){
                    hgdn_new_string(argument->name),
                    argument->type,
                    argument->hint,
                    hgdn_new_string(argument->hint_string),
                    (godot_property_usage_flags) 0,
                    argument->default_value,
                };
                num_args++;
            }
            godot_string signal_name = hgdn_new_string(signal->name);
            godot_signal gd_signal = {
                signal_name,
                num_args,
                gd_args,
                signal->num_default_args,
                NULL,
            };
            hgdn_nativescript_api->godot_nativescript_register_signal(handle, class_info->name, &gd_signal);
            hgdn_core_api->godot_string_destroy(&signal_name);
            for (int i = 0; i < num_args; i++) {
                hgdn_core_api->godot_string_destroy(&gd_args[i].name);
                hgdn_core_api->godot_string_destroy(&gd_args[i].hint_string);
            }
            if (hgdn_nativescript_1_1_api && signal->documentation) {
                godot_string documentation = hgdn_new_string(signal->documentation);
                hgdn_nativescript_1_1_api->godot_nativescript_set_signal_documentation(handle, class_info->name, signal->name, documentation);
                hgdn_core_api->godot_string_destroy(&documentation);
            }
        }
    }
}

void *hgdn_instance_alloc(godot_object *instance, void *alloc_size) {
    void *buffer = hgdn_alloc((uintptr_t) alloc_size);
    if (buffer) {
        memset(buffer, 0, (uintptr_t) alloc_size);
    }
    return buffer;
}

void hgdn_instance_free(godot_object *instance, void *method_data, void *data) {
    hgdn_free(data);
}

godot_variant *hgdn_property_constant_alloc(godot_variant value) {
    godot_variant *buffer = (godot_variant *) hgdn_alloc(sizeof(godot_variant));
    if (buffer) {
        *buffer = value;
    }
    return buffer;
}

void hgdn_property_constant_free(void *value) {
    if (value) {
        hgdn_core_api->godot_variant_destroy((godot_variant *) value);
        hgdn_core_api->godot_free(value);
    }
}

godot_variant hgdn_property_constant_get(godot_object *instance, void *value, void *data) {
    return hgdn_new_variant_copy((const godot_variant *) value);
}
#endif  // HGDN_NO_EXT_NATIVESCRIPT

#undef HGDN__FILL_FORMAT_BUFFER

#endif  // HGDN_IMPLEMENTATION
