# High level GDNative C/C++ API (HGDN)
Single header [GDNative](https://docs.godotengine.org/en/stable/tutorials/plugins/gdnative/gdnative-c-example.html)
high level API for C/C++.

- Single header: just copy `hgdn.h` to your project, put `#define HGDN_IMPLEMENTATION`
  in a single C/C++ source file before `#include`ing it and compile.
- Depends only on [godot-headers](https://github.com/godotengine/godot-headers),
  so GDNative libraries can be built with one liner compiler invocations.
  No need to generate Godot API bindings if you only use core GDNative stuff.
- `hgdn_gdnative_init` fetches all current GDNative APIs.
- Functions to create Variants and Pool Arrays in single calls.
  TODO: functions create Arrays and Dictionaries.
- Functions and structs to get data from Variants, including abstractions for
  handling strings (`const char *`), generic memory buffers (`void *`) and
  other arrays.


## Documentation
Code is documented using [Doxygen](https://www.doxygen.nl) and is available [here](https://gilzoide.github.io/high-level-gdnative/).


## Usage example

```c
// example.c
#define HGDN_IMPLEMENTATION
#include "hgdn.h"

const char *MESSAGE = "Hello world!";

GDN_EXPORT godot_real square(godot_real x) {
    return x * x;
}

godot_variant native_callback(void *symbol, godot_array *array) {
    if (symbol == &MESSAGE) {
        return hgdn_string_variant(MESSAGE);
    }
    else if (symbol == &square) {
        // returns null and prints an error if array size < 1
        HGDN_ASSERT_ARRAY_SIZE(array, 1);
        // TODO: create getter functions for variants from array
        const godot_variant *var = hgdn_core_api->godot_array_operator_index_const(array, 0);
        godot_real arg0 = hgdn_core_api->godot_variant_as_real(var);
        godot_real result = square(arg0);
        return hgdn_real_variant(result);
    }
    return hgdn_nil_variant();
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
```
