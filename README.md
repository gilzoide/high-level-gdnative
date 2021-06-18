# High level GDNative C/C++ API (HGDN)
Single header [GDNative](https://docs.godotengine.org/en/stable/tutorials/plugins/gdnative/gdnative-c-example.html)
high level API for C/C++.

This API tries to bring GDNative closer to the C world, making it easier to
write bindigns for C/C++ libraries and writing pure C/C++ NativeScripts that do
not depend too much on Godot classes.

- Single header: just copy `hgdn.h` to your project, put `#define HGDN_IMPLEMENTATION`
  in a single C/C++ source file before `#include`ing it and compile.
- Depends only on [godot-headers](https://github.com/godotengine/godot-headers),
  so GDNative libraries can be built with one liner compiler invocations.
  No need to generate Godot API bindings if you only use core stuff.
- `hgdn_gdnative_init` fetches all current GDNative APIs.
- Abstractions to create and use data from Variants, including helpers for
  handling strings (`const char *`), generic memory buffers (`void *`) and
  diverse arrays.
