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
- Functions to get buffers from strings and pool arrays.
- Functions to get values from method arguments or native calls
  argument arrays.
- Functions to create Variants, Strings, Arrays, Pool Arrays and Dictionaries
  in single calls.
- Overloaded macro/functions to create Variants, available in C11 and C++.
- Macros to assert arguments preconditions, like expected argument count and
  (TODO) expected argument types.


## Documentation
Code is documented using [Doxygen](https://www.doxygen.nl) and is available [here](https://gilzoide.github.io/high-level-gdnative/).


## Usage example

```c
// example.c
#define HGDN_STATIC
#define HGDN_IMPLEMENTATION
#include "hgdn.h"

const char *MESSAGE = "Hello world!";

GDN_EXPORT godot_real square(godot_real x) {
    return x * x;
}

GDN_EXPORT int sum_ints(godot_int *buffer, size_t size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += buffer[i];
    }
    return sum;
}

godot_variant native_callback(void *symbol, godot_array *array) {
    if (symbol == &MESSAGE) {
        return hgdn_new_variant(hgdn_new_string(MESSAGE));
    }
    else if (symbol == &square) {
        // returns null and prints an error if array size < 1
        HGDN_ASSERT_ARRAY_SIZE(array, 1);
        godot_real arg0 = hgdn_array_get_real(array, 0);
        godot_real result = square(arg0);
        return hgdn_new_variant(result);
    }
    else if (symbol == &sum_ints) {
        HGDN_ASSERT_ARRAY_SIZE(array, 1);
        size_t size;
        godot_int *buffer = hgdn_array_get_int_array(array, 0, &size);
        int res = sum_ints(buffer, size);
        hgdn_free(buffer);
        return hgdn_new_variant(res);
    }
    return hgdn_new_variant(NULL);
}

GDN_EXPORT void godot_gdnative_init(godot_gdnative_init_options *options) {
    // `hgdn_gdnative_init` needs to be called before any other HGDN call,
    // as it populates the global API pointers from options
    hgdn_gdnative_init(options);
    hgdn_core_api->godot_register_native_call_type("native", &native_callback);
}

GDN_EXPORT void godot_gdnative_terminate(godot_gdnative_terminate_options *options) {
    hgdn_gdnative_terminate(options);
}
```

```gdscript
# example.gd
var example = GDNative.new()
example.library = preload("res://path_to_gdnativelibrary.tres")
example.initialize()
print(example.call_native("native", "MESSAGE", []))  # --> "Hello world!"
print(example.call_native("native", "square", [5]))  # --> 25
print(example.call_native("native", "sum_ints", [[1, 2.5, 3]]))  # --> 6
```
