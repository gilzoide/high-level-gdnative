#define GDNHLC_IMPLEMENTATION
#include "gdnhlc.h"

GDN_EXPORT int count_chars(const char *str) {
    int i = 0;
    while (str[i]) i++;
    return i;
}

godot_variant native_callback(void *symbol, godot_array *array) {
    if (symbol == &count_chars) {
        GDNHLC_ASSERT_ARRAY_SIZE(array, 1);
        godot_variant arg = gdnhlc_core_api->godot_array_get(array, 0);
        gdnhlc_string str = gdnhlc_string_from_variant(&arg);
        int res = count_chars(gdnhlc_string_chars(&str));
        gdnhlc_string_destroy(&str);
        return gdnhlc_int_variant(res);
    }
    return gdnhlc_nil_variant();
}

GDN_EXPORT void godot_gdnative_init(godot_gdnative_init_options *options) {
    gdnhlc_gdnative_init(options);
    gdnhlc_core_api->godot_register_native_call_type("native", &native_callback);
}

GDN_EXPORT void godot_gdnative_terminate(godot_gdnative_terminate_options *options) {
    gdnhlc_gdnative_terminate(options);
}
