# High level GDNative C/C++ API (HGDN)
Single header [GDNative](https://docs.godotengine.org/en/stable/tutorials/plugins/gdnative/gdnative-c-example.html)
high level API for C/C++.

- Single header: just copy `hgdn.h` to your project, put `#define HGDN_IMPLEMENTATION`
  in a single C/C++ source file before `#include`ing it and compile.
- Depends only on [godot-headers](https://github.com/godotengine/godot-headers),
  so GDNative libraries can be built with a single compiler invocation.
  No need to generate Godot API bindings if you only use core GDNative stuff.
- `hgdn_gdnative_init` fetches all current GDNative APIs.
- Useful definitions for all math types, including Vector2, Vector3 and Color.
- Wrappers around strings and pool arrays with pointer and size available.
- Functions to get values from method arguments or native calls
  argument arrays.
- Functions to create Variants, Strings, Arrays, Pool Arrays and Dictionaries
  in single calls.
- Overloaded macro/functions to create Variants, available in C11 and C++.
- Macros to assert arguments preconditions, like expected argument count and
  (TODO) expected argument types.


## Documentation
Code is documented using [Doxygen](https://www.doxygen.nl) and is available [online here](https://gilzoide.github.io/high-level-gdnative/).


## Usage example
For a working example with full Godot project, check out the
[high-level-gdnative-example](https://github.com/gilzoide/high-level-gdnative-example)
repository.

```c
// example.c

// 1) #define HGDN_IMPLEMENTATION on exactly one C/C++ file and include hgdn.h
// Optionally #define other compile-time options, check out hgdn.h for documentation
#define HGDN_STATIC
#define HGDN_IMPLEMENTATION
#include "hgdn.h"

// 2.a) Declare native functions to be used by script code, if there are any
//      Any function with prototype `godot_variant (godot_array *)` can be called in script with
//      `gdnative_instance.call_native("standard_varcall", "<name of your C function", ["some", "arguments", "..."])`
GDN_EXPORT godot_variant get_message(godot_array *args) {
    // `hgdn_new_variant` is type-aware using C11 _Generic/C++ overloads
    // In this case, it calls `hgdn_new_cstring_variant`
    return hgdn_new_variant("Hello world!");
}

GDN_EXPORT godot_variant square(godot_array *args) {
    // returns null and prints an error if array size < 1
    HGDN_ASSERT_ARRAY_SIZE(args, 1);
    godot_real x = hgdn_array_get_real(args, 0);
    // Overloaded to `hgdn_new_real_variant(x * x)`
    return hgdn_new_variant(x * x);
}

GDN_EXPORT godot_variant sum_ints(godot_array *args) {
    HGDN_ASSERT_ARRAY_SIZE(args, 1);
    hgdn_int_array int_array = hgdn_array_get_int_array(args, 0);
    int sum = 0;
    for (int i = 0; i < int_array.size; i++) {
        sum += int_array.ptr[i];
    }
    // Overloaded to `hgdn_new_int_variant(sum)`
    return hgdn_new_variant(sum);
}

// 2.b) Declare NativeScript methods, if there are any (TODO)


// 3.a) Add `godot_gdnative_init`, the function that will be called when Godot
// initializes this GDNativeLibrary, and call `hgdn_gdnative_init` from it.
GDN_EXPORT void godot_gdnative_init(godot_gdnative_init_options *options) {
    // `hgdn_gdnative_init` needs to be called before any other HGDN call,
    // as it populates the global API pointers from options
    hgdn_gdnative_init(options);
    // `hgdn_print` uses `printf` formatted values
    hgdn_print("GDNative initialized%s", options->in_editor ? " in editor" : "");
}

// 3.b) Add `godot_gdnative_terminate`, the function that will be called when Godot
// unloads this GDNativeLibrary, and call `hgdn_gdnative_terminate` from it.
GDN_EXPORT void godot_gdnative_terminate(godot_gdnative_terminate_options *options) {
    hgdn_gdnative_terminate(options);
}

// 4) Add `godot_nativescript_init`, the function that will be called when Godot
// initializes a NativeScript with this GDNativeLibrary, and register classes,
// if there are any.
GDN_EXPORT void godot_nativescript_init(void *desc) {
    // TODO
}
```

```gdscript
# example.gd
extends Reference

func _ready() -> void:
	var example = GDNative.new()
	example.library = preload("res://path_to_gdnativelibrary.gdnlib")
	example.initialize()  # --> "GDNative initialized"
	print(example.call_native("standard_varcall", "get_message", []))  # --> "Hello world!"
	print(example.call_native("standard_varcall", "square", [5]))  # --> 25
	print(example.call_native("standard_varcall", "sum_ints", [[1, 2.5, 3]]))  # --> 6
```

