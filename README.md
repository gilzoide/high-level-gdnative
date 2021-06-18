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
