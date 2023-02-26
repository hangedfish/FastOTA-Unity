//
// Created by hangedfish (bravohangedman@outlook.com) on 2023/2/26.
//

#include "api.h"
#include <cstdlib>
#include <dlfcn.h>
#include <mutex>

#include <android/log.h>

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "UPSDK", __VA_ARGS__ )

#define DO_API(r, n, p)             r (* n##_ptr ) p;
#define DO_API_NO_RETURN(r, n, p)             r (* n##_ptr ) p;

#include "il2cpp-api-functions.h"

#undef DO_API
#undef DO_API_NO_RETURN

void *g_il2cpp_handle = nullptr;

bool do_load_il2cpp() {
    const char *il2cpp_filepath = getenv("FASTOAT_UPSDK_IL2CPP_FILEPATH");
    if (il2cpp_filepath == nullptr) {
        il2cpp_filepath = "libil2cpp.so";
    }
    void *il2cpp_handle = dlopen(il2cpp_filepath, RTLD_LOCAL);
    if (il2cpp_handle == nullptr) {
        LOGE("Fail to load libil2cpp.so > %s", dlerror());
        return false;
    }
    g_il2cpp_handle = il2cpp_handle;

#define DO_API(r, n, p) \
        n##_ptr = ( r (*) p ) dlsym(g_il2cpp_handle, #n ); \
        if ( n##_ptr == nullptr) {                        \
            LOGE("Not found '" #n "' at %s", il2cpp_filepath);            \
            return false;                \
        }

#include "il2cpp-api-functions.h"

#undef DO_API
#undef DO_API_NO_RETURN

    return true;
}

// use lazy load, without attr [[gnu::constructor]]
bool load_il2cpp() {
    static std::once_flag flag{};
    std::call_once(flag, do_load_il2cpp);
    return g_il2cpp_handle != nullptr;
}

[[gnu::destructor]]
void unload_il2cpp() {
    if (g_il2cpp_handle != nullptr) {
        dlclose(g_il2cpp_handle);
    }
}


int il2cpp_init(const char *domain_name) {
    load_il2cpp();
    return il2cpp_init_ptr(domain_name);
}

int il2cpp_init_utf16(const Il2CppChar *domain_name) {
    load_il2cpp();
    return il2cpp_init_utf16_ptr(domain_name);
}

void il2cpp_shutdown() {
    load_il2cpp();
    il2cpp_shutdown_ptr();
}

void il2cpp_set_config_dir(const char *config_path) {
    load_il2cpp();
    il2cpp_set_config_dir_ptr(config_path);
}

void il2cpp_set_data_dir(const char *data_path) {
    load_il2cpp();
    il2cpp_set_data_dir_ptr(data_path);
}

void il2cpp_set_temp_dir(const char *temp_path) {
    load_il2cpp();
    il2cpp_set_temp_dir_ptr(temp_path);
}

void il2cpp_set_commandline_arguments(int argc, const char *const *argv, const char *basedir) {
    load_il2cpp();
    il2cpp_set_commandline_arguments_ptr(argc, argv, basedir);
}

void il2cpp_set_commandline_arguments_utf16(int argc, const Il2CppChar *const *argv,
                                            const char *basedir) {
    load_il2cpp();
    il2cpp_set_commandline_arguments_utf16_ptr(argc, argv, basedir);
}

void il2cpp_set_config_utf16(const Il2CppChar *executablePath) {
    load_il2cpp();
    il2cpp_set_config_utf16_ptr(executablePath);
}

void il2cpp_set_config(const char *executablePath) {
    load_il2cpp();
    il2cpp_set_config_ptr(executablePath);
}

void il2cpp_set_memory_callbacks(Il2CppMemoryCallbacks *callbacks) {
    load_il2cpp();
    il2cpp_set_memory_callbacks_ptr(callbacks);
}

const void *il2cpp_get_corlib() {
    load_il2cpp();
    return il2cpp_get_corlib_ptr();
}

void il2cpp_add_internal_call(const char *name, Il2CppMethodPointer method) {
    load_il2cpp();
    il2cpp_add_internal_call_ptr(name, method);
}

Il2CppMethodPointer il2cpp_resolve_icall(const char *name) {
    load_il2cpp();
    return il2cpp_resolve_icall_ptr(name);
}

void *il2cpp_alloc(size_t size) {
    load_il2cpp();
    return il2cpp_alloc_ptr(size);
}

void il2cpp_free(void *ptr) {
    load_il2cpp();
    il2cpp_free_ptr(ptr);
}

void *il2cpp_array_class_get(Il2CppClass *element_class, uint32_t rank) {
    load_il2cpp();
    return il2cpp_array_class_get_ptr(element_class, rank);
}

uint32_t il2cpp_array_length(Il2CppArray *array) {
    load_il2cpp();
    return il2cpp_array_length_ptr(array);
}

uint32_t il2cpp_array_get_byte_length(Il2CppArray *array) {
    load_il2cpp();
    return il2cpp_array_get_byte_length_ptr(array);
}

void *il2cpp_array_new(Il2CppClass *elementTypeInfo, il2cpp_array_size_t length) {
    load_il2cpp();
    return il2cpp_array_new_ptr(elementTypeInfo, length);
}

void *il2cpp_array_new_specific(Il2CppClass *arrayTypeInfo, il2cpp_array_size_t length) {
    load_il2cpp();
    return il2cpp_array_new_specific_ptr(arrayTypeInfo, length);
}

void *il2cpp_array_new_full(Il2CppClass *array_class, il2cpp_array_size_t *lengths,
                            il2cpp_array_size_t *lower_bounds) {
    load_il2cpp();
    return il2cpp_array_new_full_ptr(array_class, lengths, lower_bounds);
}

void *il2cpp_bounded_array_class_get(Il2CppClass *element_class, uint32_t rank, bool bounded) {
    load_il2cpp();
    return il2cpp_bounded_array_class_get_ptr(element_class, rank, bounded);
}

int il2cpp_array_element_size(const Il2CppClass *array_class) {
    load_il2cpp();
    return il2cpp_array_element_size_ptr(array_class);
}

const void *il2cpp_assembly_get_image(const Il2CppAssembly *assembly) {
    load_il2cpp();
    return il2cpp_assembly_get_image_ptr(assembly);
}

void il2cpp_class_for_each(void (*klassReportFunc)(Il2CppClass *, void *), void *userData) {
    load_il2cpp();
    il2cpp_class_for_each_ptr(klassReportFunc, userData);
}

const void *il2cpp_class_enum_basetype(Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_enum_basetype_ptr(klass);
}

bool il2cpp_class_is_generic(const Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_is_generic_ptr(klass);
}

bool il2cpp_class_is_inflated(const Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_is_inflated_ptr(klass);
}

bool il2cpp_class_is_assignable_from(Il2CppClass *klass, Il2CppClass *oklass) {
    load_il2cpp();
    return il2cpp_class_is_assignable_from_ptr(klass, oklass);
}

bool il2cpp_class_is_subclass_of(Il2CppClass *klass, Il2CppClass *klassc, bool check_interfaces) {
    load_il2cpp();
    return il2cpp_class_is_subclass_of_ptr(klass, klassc, check_interfaces);
}

bool il2cpp_class_has_parent(Il2CppClass *klass, Il2CppClass *klassc) {
    load_il2cpp();
    return il2cpp_class_has_parent_ptr(klass, klassc);
}

void *il2cpp_class_from_il2cpp_type(const Il2CppType *type) {
    load_il2cpp();
    return il2cpp_class_from_il2cpp_type_ptr(type);
}

void *il2cpp_class_from_name(const Il2CppImage *image, const char *namespaze, const char *name) {
    load_il2cpp();
    return il2cpp_class_from_name_ptr(image, namespaze, name);
}

void *il2cpp_class_from_system_type(Il2CppReflectionType *type) {
    load_il2cpp();
    return il2cpp_class_from_system_type_ptr(type);
}

void *il2cpp_class_get_element_class(Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_get_element_class_ptr(klass);
}

const void *il2cpp_class_get_events(Il2CppClass *klass, void **iter) {
    load_il2cpp();
    return il2cpp_class_get_events_ptr(klass, iter);
}

void *il2cpp_class_get_fields(Il2CppClass *klass, void **iter) {
    load_il2cpp();
    return il2cpp_class_get_fields_ptr(klass, iter);
}

void *il2cpp_class_get_nested_types(Il2CppClass *klass, void **iter) {
    load_il2cpp();
    return il2cpp_class_get_nested_types_ptr(klass, iter);
}

void *il2cpp_class_get_interfaces(Il2CppClass *klass, void **iter) {
    load_il2cpp();
    return il2cpp_class_get_interfaces_ptr(klass, iter);
}

const void *il2cpp_class_get_properties(Il2CppClass *klass, void **iter) {
    load_il2cpp();
    return il2cpp_class_get_properties_ptr(klass, iter);
}

const void *il2cpp_class_get_property_from_name(Il2CppClass *klass, const char *name) {
    load_il2cpp();
    return il2cpp_class_get_property_from_name_ptr(klass, name);
}

void *il2cpp_class_get_field_from_name(Il2CppClass *klass, const char *name) {
    load_il2cpp();
    return il2cpp_class_get_field_from_name_ptr(klass, name);
}

const void *il2cpp_class_get_methods(Il2CppClass *klass, void **iter) {
    load_il2cpp();
    return il2cpp_class_get_methods_ptr(klass, iter);
}

const void *il2cpp_class_get_method_from_name(Il2CppClass *klass, const char *name, int argsCount) {
    load_il2cpp();
    return il2cpp_class_get_method_from_name_ptr(klass, name, argsCount);
}

const char *il2cpp_class_get_name(Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_get_name_ptr(klass);
}

void il2cpp_type_get_name_chunked(const Il2CppType *type, void (*chunkReportFunc)(void *, void *), void *userData) {
    load_il2cpp();
    return il2cpp_type_get_name_chunked_ptr(type, chunkReportFunc, userData);
}

const char *il2cpp_class_get_namespace(Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_get_namespace_ptr(klass);
}

void *il2cpp_class_get_parent(Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_get_parent_ptr(klass);
}

void *il2cpp_class_get_declaring_type(Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_get_declaring_type_ptr(klass);
}

int32_t il2cpp_class_instance_size(Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_instance_size_ptr(klass);
}

size_t il2cpp_class_num_fields(const Il2CppClass *enumKlass) {
    load_il2cpp();
    return il2cpp_class_num_fields_ptr(enumKlass);
}

bool il2cpp_class_is_valuetype(const Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_is_valuetype_ptr(klass);
}

int32_t il2cpp_class_value_size(Il2CppClass *klass, uint32_t *align) {
    load_il2cpp();
    return il2cpp_class_value_size_ptr(klass, align);
}

bool il2cpp_class_is_blittable(const Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_is_blittable_ptr(klass);
}

int il2cpp_class_get_flags(const Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_get_flags_ptr(klass);
}

bool il2cpp_class_is_abstract(const Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_is_abstract_ptr(klass);
}

bool il2cpp_class_is_interface(const Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_is_interface_ptr(klass);
}

int il2cpp_class_array_element_size(const Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_array_element_size_ptr(klass);
}

void *il2cpp_class_from_type(const Il2CppType *type) {
    load_il2cpp();
    return il2cpp_class_from_type_ptr(type);
}

const void *il2cpp_class_get_type(Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_get_type_ptr(klass);
}

uint32_t il2cpp_class_get_type_token(Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_get_type_token_ptr(klass);
}

bool il2cpp_class_has_attribute(Il2CppClass *klass, Il2CppClass *attr_class) {
    load_il2cpp();
    return il2cpp_class_has_attribute_ptr(klass, attr_class);
}

bool il2cpp_class_has_references(Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_has_references_ptr(klass);
}

bool il2cpp_class_is_enum(const Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_is_enum_ptr(klass);
}

const void *il2cpp_class_get_image(Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_get_image_ptr(klass);
}

const char *il2cpp_class_get_assemblyname(const Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_get_assemblyname_ptr(klass);
}

int il2cpp_class_get_rank(const Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_get_rank_ptr(klass);
}

uint32_t il2cpp_class_get_data_size(const Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_get_data_size_ptr(klass);
}

void *il2cpp_class_get_static_field_data(const Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_get_static_field_data_ptr(klass);
}

size_t il2cpp_class_get_bitmap_size(const Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_class_get_bitmap_size_ptr(klass);
}

void il2cpp_class_get_bitmap(Il2CppClass *klass, size_t *bitmap) {
    il2cpp_class_get_bitmap_ptr(klass, bitmap);
}

bool il2cpp_stats_dump_to_file(const char *path) {
    load_il2cpp();
    return il2cpp_stats_dump_to_file_ptr(path);
}

uint64_t il2cpp_stats_get_value(Il2CppStat stat) {
    load_il2cpp();
    return il2cpp_stats_get_value_ptr(stat);
}

void *il2cpp_domain_get() {
    load_il2cpp();
    return il2cpp_domain_get_ptr();
}

const void *il2cpp_domain_assembly_open(Il2CppDomain *domain, const char *name) {
    load_il2cpp();
    return il2cpp_domain_assembly_open_ptr(domain, name);
}

const void **il2cpp_domain_get_assemblies(const Il2CppDomain *domain, size_t *size) {
    load_il2cpp();
    return il2cpp_domain_get_assemblies_ptr(domain, size);
}

void il2cpp_raise_exception(Il2CppException *ex) {
    load_il2cpp();
    il2cpp_raise_exception_ptr(ex);
}

void *
il2cpp_exception_from_name_msg(const Il2CppImage *image, const char *name_space, const char *name, const char *msg) {
    load_il2cpp();
    return il2cpp_exception_from_name_msg_ptr(image, name_space, name, msg);
}

void *il2cpp_get_exception_argument_null(const char *arg) {
    load_il2cpp();
    return il2cpp_get_exception_argument_null_ptr(arg);
}

void il2cpp_format_exception(const Il2CppException *ex, char *message, int message_size) {
    load_il2cpp();
    il2cpp_format_exception_ptr(ex, message, message_size);
}

void il2cpp_format_stack_trace(const Il2CppException *ex, char *output, int output_size) {
    load_il2cpp();
    il2cpp_format_stack_trace_ptr(ex, output, output_size);
}

void il2cpp_unhandled_exception(Il2CppException *ex) {
    load_il2cpp();
    il2cpp_unhandled_exception(ex);
}

void il2cpp_native_stack_trace(const Il2CppException *ex, uintptr_t **addresses, int *numFrames,
                               char **imageUUID, char **imageName) {
    load_il2cpp();
    il2cpp_native_stack_trace_ptr(ex, addresses, numFrames, imageUUID, imageName);
}

int il2cpp_field_get_flags(FieldInfo *field) {
    load_il2cpp();
    return il2cpp_field_get_flags_ptr(field);
}

const char *il2cpp_field_get_name(FieldInfo *field) {
    load_il2cpp();
    return il2cpp_field_get_name_ptr(field);
}

void *il2cpp_field_get_parent(FieldInfo *field) {
    load_il2cpp();
    return il2cpp_field_get_parent_ptr(field);
}

size_t il2cpp_field_get_offset(FieldInfo *field) {
    load_il2cpp();
    return il2cpp_field_get_offset_ptr(field);
}

const void *il2cpp_field_get_type(FieldInfo *field) {
    load_il2cpp();
    return il2cpp_field_get_type_ptr(field);
}

void il2cpp_field_get_value(Il2CppObject *obj, FieldInfo *field, void *value) {
    load_il2cpp();
    il2cpp_field_get_value_ptr(obj, field, value);
}

void *il2cpp_field_get_value_object(FieldInfo *field, Il2CppObject *obj) {
    load_il2cpp();
    return il2cpp_field_get_value_object_ptr(field, obj);
}

bool il2cpp_field_has_attribute(FieldInfo *field, Il2CppClass *attr_class) {
    load_il2cpp();
    return il2cpp_field_has_attribute_ptr(field, attr_class);
}

void il2cpp_field_set_value(Il2CppObject *obj, FieldInfo *field, void *value) {
    load_il2cpp();
    il2cpp_field_set_value_ptr(obj, field, value);
}

void il2cpp_field_static_get_value(FieldInfo *field, void *value) {
    load_il2cpp();
    il2cpp_field_static_get_value_ptr(field, value);
}

void il2cpp_field_static_set_value(FieldInfo *field, void *value) {
    load_il2cpp();
    il2cpp_field_static_set_value_ptr(field, value);
}

void
il2cpp_field_set_value_object(Il2CppObject *instance, FieldInfo *field, Il2CppObject *value) {
    load_il2cpp();
    il2cpp_field_set_value_object_ptr(instance, field, value);
}

bool il2cpp_field_is_literal(FieldInfo *field) {
    load_il2cpp();
    return il2cpp_field_is_literal_ptr(field);
}

void il2cpp_gc_collect(int maxGenerations) {
    load_il2cpp();
    il2cpp_gc_collect_ptr(maxGenerations);
}

int32_t il2cpp_gc_collect_a_little() {
    load_il2cpp();
    return il2cpp_gc_collect_a_little_ptr();
}

void il2cpp_gc_start_incremental_collection() {
    load_il2cpp();
    il2cpp_gc_start_incremental_collection_ptr();
}

void il2cpp_gc_disable() {
    load_il2cpp();
    il2cpp_gc_disable_ptr();
}

void il2cpp_gc_enable() {
    load_il2cpp();
    il2cpp_gc_enable_ptr();
}

bool il2cpp_gc_is_disabled() {
    load_il2cpp();
    return il2cpp_gc_is_disabled_ptr();
}

void il2cpp_gc_set_mode(Il2CppGCMode mode) {
    load_il2cpp();
    il2cpp_gc_set_mode_ptr(mode);
}

int64_t il2cpp_gc_get_max_time_slice_ns() {
    load_il2cpp();
    return il2cpp_gc_get_max_time_slice_ns_ptr();
}

void il2cpp_gc_set_max_time_slice_ns(int64_t maxTimeSlice) {
    load_il2cpp();
    il2cpp_gc_set_max_time_slice_ns_ptr(maxTimeSlice);
}

bool il2cpp_gc_is_incremental() {
    load_il2cpp();
    return il2cpp_gc_is_incremental_ptr();
}

int64_t il2cpp_gc_get_used_size() {
    load_il2cpp();
    return il2cpp_gc_get_used_size_ptr();
}

int64_t il2cpp_gc_get_heap_size() {
    load_il2cpp();
    return il2cpp_gc_get_heap_size_ptr();
}

void il2cpp_gc_wbarrier_set_field(Il2CppObject *obj, void **targetAddress, void *object) {
    load_il2cpp();
    il2cpp_gc_wbarrier_set_field_ptr(obj, targetAddress, object);
}

bool il2cpp_gc_has_strict_wbarriers() {
    load_il2cpp();
    return il2cpp_gc_has_strict_wbarriers_ptr();
}

void il2cpp_gc_set_external_allocation_tracker(void (*func)(void *, size_t, int)) {
    load_il2cpp();
    il2cpp_gc_set_external_allocation_tracker_ptr(func);
}

void il2cpp_gc_set_external_wbarrier_tracker(void (*func)(void **)) {
    load_il2cpp();
    il2cpp_gc_set_external_wbarrier_tracker_ptr(func);
}

void il2cpp_gc_foreach_heap(void (*func)(void *, void *), void *userData) {
    load_il2cpp();
    il2cpp_gc_foreach_heap_ptr(func, userData);
}

void il2cpp_stop_gc_world() {
    load_il2cpp();
    il2cpp_stop_gc_world_ptr();
}

void il2cpp_start_gc_world() {
    load_il2cpp();
    il2cpp_start_gc_world_ptr();
}

void *il2cpp_gc_alloc_fixed(size_t size) {
    load_il2cpp();
    return il2cpp_gc_alloc_fixed_ptr(size);
}

void il2cpp_gc_free_fixed(void *address) {
    load_il2cpp();
    il2cpp_gc_free_fixed_ptr(address);
}

uint32_t il2cpp_gchandle_new(Il2CppObject *obj, bool pinned) {
    load_il2cpp();
    return il2cpp_gchandle_new_ptr(obj, pinned);
}

uint32_t il2cpp_gchandle_new_weakref(Il2CppObject *obj, bool track_resurrection) {
    load_il2cpp();
    return il2cpp_gchandle_new_weakref_ptr(obj, track_resurrection);
}

void *il2cpp_gchandle_get_target(uint32_t gchandle) {
    load_il2cpp();
    return il2cpp_gchandle_get_target_ptr(gchandle);
}

void il2cpp_gchandle_free(uint32_t gchandle) {
    load_il2cpp();
    il2cpp_gchandle_free_ptr(gchandle);
}

void il2cpp_gchandle_foreach_get_target(void (*func)(void *, void *), void *userData) {
    load_il2cpp();
    il2cpp_gchandle_foreach_get_target_ptr(func, userData);
}

uint32_t il2cpp_object_header_size() {
    load_il2cpp();
    return il2cpp_object_header_size_ptr();
}

uint32_t il2cpp_array_object_header_size() {
    load_il2cpp();
    return il2cpp_array_object_header_size_ptr();
}

uint32_t il2cpp_offset_of_array_length_in_array_object_header() {
    load_il2cpp();
    return il2cpp_offset_of_array_length_in_array_object_header_ptr();
}

uint32_t il2cpp_offset_of_array_bounds_in_array_object_header() {
    load_il2cpp();
    return il2cpp_offset_of_array_bounds_in_array_object_header_ptr();
}

uint32_t il2cpp_allocation_granularity() {
    load_il2cpp();
    return il2cpp_allocation_granularity_ptr();
}

void *il2cpp_unity_liveness_allocate_struct(Il2CppClass *filter, int max_object_count,
                                            il2cpp_register_object_callback callback,
                                            void *userdata,
                                            il2cpp_liveness_reallocate_callback reallocate) {
    load_il2cpp();
    return il2cpp_unity_liveness_allocate_struct_ptr(filter, max_object_count, callback, userdata, reallocate);
}

void il2cpp_unity_liveness_calculation_from_root(Il2CppObject *root, void *state) {
    load_il2cpp();
    il2cpp_unity_liveness_calculation_from_root_ptr(root, state);
}

void il2cpp_unity_liveness_calculation_from_statics(void *state) {
    load_il2cpp();
    il2cpp_unity_liveness_calculation_from_statics_ptr(state);
}

void il2cpp_unity_liveness_finalize(void *state) {
    load_il2cpp();
    il2cpp_unity_liveness_finalize_ptr(state);
}

void il2cpp_unity_liveness_free_struct(void *state) {
    load_il2cpp();
    il2cpp_unity_liveness_free_struct_ptr(state);
}

const void *il2cpp_method_get_return_type(const MethodInfo *method) {
    load_il2cpp();
    return il2cpp_method_get_return_type_ptr(method);
}

void *il2cpp_method_get_declaring_type(const MethodInfo *method) {
    load_il2cpp();
    return il2cpp_method_get_declaring_type_ptr(method);
}

const char *il2cpp_method_get_name(const MethodInfo *method) {
    load_il2cpp();
    return il2cpp_method_get_name_ptr(method);
}

const void *il2cpp_method_get_from_reflection(const Il2CppReflectionMethod *method) {
    load_il2cpp();
    return il2cpp_method_get_from_reflection_ptr(method);
}

void *il2cpp_method_get_object(const MethodInfo *method, Il2CppClass *refclass) {
    load_il2cpp();
    return il2cpp_method_get_object_ptr(method, refclass);
}

bool il2cpp_method_is_generic(const MethodInfo *method) {
    load_il2cpp();
    return il2cpp_method_is_generic_ptr(method);
}

bool il2cpp_method_is_inflated(const MethodInfo *method) {
    load_il2cpp();
    return il2cpp_method_is_inflated_ptr(method);
}

bool il2cpp_method_is_instance(const MethodInfo *method) {
    load_il2cpp();
    return il2cpp_method_is_instance_ptr(method);
}

uint32_t il2cpp_method_get_param_count(const MethodInfo *method) {
    load_il2cpp();
    return il2cpp_method_get_param_count_ptr(method);
}

const void *il2cpp_method_get_param(const MethodInfo *method, uint32_t index) {
    load_il2cpp();
    return il2cpp_method_get_param_ptr(method, index);
}

void *il2cpp_method_get_class(const MethodInfo *method) {
    load_il2cpp();
    return il2cpp_method_get_class_ptr(method);
}

bool il2cpp_method_has_attribute(const MethodInfo *method, Il2CppClass *attr_class) {
    load_il2cpp();
    return il2cpp_method_has_attribute_ptr(method, attr_class);
}

uint32_t il2cpp_method_get_flags(const MethodInfo *method, uint32_t *iflags) {
    load_il2cpp();
    return il2cpp_method_get_flags_ptr(method, iflags);
}

uint32_t il2cpp_method_get_token(const MethodInfo *method) {
    load_il2cpp();
    return il2cpp_method_get_token_ptr(method);
}

const char *il2cpp_method_get_param_name(const MethodInfo *method, uint32_t index) {
    load_il2cpp();
    return il2cpp_method_get_param_name_ptr(method, index);
}

uint32_t il2cpp_property_get_flags(PropertyInfo *prop) {
    load_il2cpp();
    return il2cpp_property_get_flags_ptr(prop);
}

const void *il2cpp_property_get_get_method(PropertyInfo *prop) {
    load_il2cpp();
    return il2cpp_property_get_get_method_ptr(prop);
}

const void *il2cpp_property_get_set_method(PropertyInfo *prop) {
    load_il2cpp();
    return il2cpp_property_get_set_method_ptr(prop);
}

const char *il2cpp_property_get_name(PropertyInfo *prop) {
    load_il2cpp();
    return il2cpp_property_get_name_ptr(prop);
}

void *il2cpp_property_get_parent(PropertyInfo *prop) {
    load_il2cpp();
    return il2cpp_property_get_parent_ptr(prop);
}

void *il2cpp_object_get_class(Il2CppObject *obj) {
    load_il2cpp();
    return il2cpp_object_get_class_ptr(obj);
}

uint32_t il2cpp_object_get_size(Il2CppObject *obj) {
    load_il2cpp();
    return il2cpp_object_get_size_ptr(obj);
}

const void *il2cpp_object_get_virtual_method(Il2CppObject *obj, const MethodInfo *method) {
    load_il2cpp();
    return il2cpp_object_get_virtual_method_ptr(obj, method);
}

void *il2cpp_object_new(const Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_object_new_ptr(klass);
}

void *il2cpp_object_unbox(Il2CppObject *obj) {
    load_il2cpp();
    return il2cpp_object_unbox_ptr(obj);
}

void *il2cpp_value_box(Il2CppClass *klass, void *data) {
    load_il2cpp();
    return il2cpp_value_box_ptr(klass, data);
}

void il2cpp_monitor_enter(Il2CppObject *obj) {
    load_il2cpp();
    return il2cpp_monitor_enter_ptr(obj);
}

bool il2cpp_monitor_try_enter(Il2CppObject *obj, uint32_t timeout) {
    load_il2cpp();
    return il2cpp_monitor_try_enter_ptr(obj, timeout);
}

void il2cpp_monitor_exit(Il2CppObject *obj) {
    load_il2cpp();
    il2cpp_monitor_exit_ptr(obj);
}

void il2cpp_monitor_pulse(Il2CppObject *obj) {
    load_il2cpp();
    il2cpp_monitor_pulse_ptr(obj);
}

void il2cpp_monitor_pulse_all(Il2CppObject *obj) {
    load_il2cpp();
    il2cpp_monitor_pulse_all_ptr(obj);
}

void il2cpp_monitor_wait(Il2CppObject *obj) {
    load_il2cpp();
    il2cpp_monitor_wait_ptr(obj);
}

bool il2cpp_monitor_try_wait(Il2CppObject *obj, uint32_t timeout) {
    load_il2cpp();
    return il2cpp_monitor_try_wait_ptr(obj, timeout);
}

void *
il2cpp_runtime_invoke(const MethodInfo *method, void *obj, void **params, Il2CppException **exc) {
    load_il2cpp();
    return il2cpp_runtime_invoke_ptr(method, obj, params, exc);
}

void *il2cpp_runtime_invoke_convert_args(const MethodInfo *method, void *obj, Il2CppObject **params,
                                         int paramCount, Il2CppException **exc) {
    load_il2cpp();
    return il2cpp_runtime_invoke_convert_args_ptr(method, obj, params, paramCount, exc);
}

void il2cpp_runtime_class_init(Il2CppClass *klass) {
    load_il2cpp();
    il2cpp_runtime_class_init_ptr(klass);
}

void il2cpp_runtime_object_init(Il2CppObject *obj) {
    load_il2cpp();
    il2cpp_runtime_object_init_ptr(obj);
}

void il2cpp_runtime_object_init_exception(Il2CppObject *obj, Il2CppException **exc) {
    load_il2cpp();
    il2cpp_runtime_object_init_exception_ptr(obj, exc);
}

void il2cpp_runtime_unhandled_exception_policy_set(Il2CppRuntimeUnhandledExceptionPolicy value) {
    load_il2cpp();
    il2cpp_runtime_unhandled_exception_policy_set_ptr(value);
}

int32_t il2cpp_string_length(Il2CppString *str) {
    load_il2cpp();
    return il2cpp_string_length_ptr(str);
}

Il2CppChar *il2cpp_string_chars(Il2CppString *str) {
    load_il2cpp();
    return il2cpp_string_chars_ptr(str);
}

void *il2cpp_string_new(const char *str) {
    load_il2cpp();
    return il2cpp_string_new_ptr(str);
}

void *il2cpp_string_new_len(const char *str, uint32_t length) {
    load_il2cpp();
    return il2cpp_string_new_len_ptr(str, length);
}

void *il2cpp_string_new_utf16(const Il2CppChar *text, int32_t len) {
    load_il2cpp();
    return il2cpp_string_new_utf16_ptr(text, len);
}

void *il2cpp_string_new_wrapper(const char *str) {
    load_il2cpp();
    return il2cpp_string_new_wrapper_ptr(str);
}

void *il2cpp_string_intern(Il2CppString *str) {
    load_il2cpp();
    return il2cpp_string_intern_ptr(str);
}

void *il2cpp_string_is_interned(Il2CppString *str) {
    load_il2cpp();
    return il2cpp_string_is_interned_ptr(str);
}

void *il2cpp_thread_current() {
    load_il2cpp();
    return il2cpp_thread_current_ptr();
}

void *il2cpp_thread_attach(Il2CppDomain *domain) {
    load_il2cpp();
    return il2cpp_thread_attach_ptr(domain);
}

void il2cpp_thread_detach(Il2CppThread *thread) {
    load_il2cpp();
    il2cpp_thread_detach_ptr(thread);
}

void **il2cpp_thread_get_all_attached_threads(size_t *size) {
    load_il2cpp();
    return il2cpp_thread_get_all_attached_threads_ptr(size);
}

bool il2cpp_is_vm_thread(Il2CppThread *thread) {
    load_il2cpp();
    return il2cpp_is_vm_thread_ptr(thread);
}

void il2cpp_current_thread_walk_frame_stack(Il2CppFrameWalkFunc func, void *user_data) {
    load_il2cpp();
    il2cpp_current_thread_walk_frame_stack_ptr(func, user_data);
}

void
il2cpp_thread_walk_frame_stack(Il2CppThread *thread, Il2CppFrameWalkFunc func, void *user_data) {
    load_il2cpp();
    il2cpp_thread_walk_frame_stack_ptr(thread, func, user_data);
}

bool il2cpp_current_thread_get_top_frame(Il2CppStackFrameInfo *frame) {
    load_il2cpp();
    return il2cpp_current_thread_get_top_frame_ptr(frame);
}

bool il2cpp_thread_get_top_frame(Il2CppThread *thread, Il2CppStackFrameInfo *frame) {
    load_il2cpp();
    return il2cpp_thread_get_top_frame_ptr(thread, frame);
}

bool il2cpp_current_thread_get_frame_at(int32_t offset, Il2CppStackFrameInfo *frame) {
    load_il2cpp();
    return il2cpp_current_thread_get_frame_at_ptr(offset, frame);
}

bool il2cpp_thread_get_frame_at(Il2CppThread *thread, int32_t offset, Il2CppStackFrameInfo *frame) {
    load_il2cpp();
    return il2cpp_thread_get_frame_at_ptr(thread, offset, frame);
}

int32_t il2cpp_current_thread_get_stack_depth() {
    load_il2cpp();
    return il2cpp_current_thread_get_stack_depth_ptr();
}

int32_t il2cpp_thread_get_stack_depth(Il2CppThread *thread) {
    load_il2cpp();
    return il2cpp_thread_get_stack_depth_ptr(thread);
}

void il2cpp_override_stack_backtrace(Il2CppBacktraceFunc stackBacktraceFunc) {
    load_il2cpp();
    il2cpp_override_stack_backtrace_ptr(stackBacktraceFunc);
}

void *il2cpp_type_get_object(const Il2CppType *type) {
    load_il2cpp();
    return il2cpp_type_get_object_ptr(type);
}

int il2cpp_type_get_type(const Il2CppType *type) {
    load_il2cpp();
    return il2cpp_type_get_type_ptr(type);
}

void *il2cpp_type_get_class_or_element_class(const Il2CppType *type) {
    load_il2cpp();
    return il2cpp_type_get_class_or_element_class_ptr(type);
}

char *il2cpp_type_get_name(const Il2CppType *type) {
    load_il2cpp();
    return il2cpp_type_get_name_ptr(type);
}

bool il2cpp_type_is_byref(const Il2CppType *type) {
    load_il2cpp();
    return il2cpp_type_is_byref_ptr(type);
}

uint32_t il2cpp_type_get_attrs(const Il2CppType *type) {
    load_il2cpp();
    return il2cpp_type_get_attrs_ptr(type);
}

bool il2cpp_type_equals(const Il2CppType *type, const Il2CppType *otherType) {
    load_il2cpp();
    return il2cpp_type_equals_ptr(type, otherType);
}

char *il2cpp_type_get_assembly_qualified_name(const Il2CppType *type) {
    load_il2cpp();
    return il2cpp_type_get_assembly_qualified_name_ptr(type);
}

bool il2cpp_type_is_static(const Il2CppType *type) {
    load_il2cpp();
    return il2cpp_type_is_static_ptr(type);
}

bool il2cpp_type_is_pointer_type(const Il2CppType *type) {
    load_il2cpp();
    return il2cpp_type_is_pointer_type_ptr(type);
}

const void *il2cpp_image_get_assembly(const Il2CppImage *image) {
    load_il2cpp();
    return il2cpp_image_get_assembly_ptr(image);
}

const char *il2cpp_image_get_name(const Il2CppImage *image) {
    load_il2cpp();
    return il2cpp_image_get_name_ptr(image);
}

const char *il2cpp_image_get_filename(const Il2CppImage *image) {
    load_il2cpp();
    return il2cpp_image_get_filename_ptr(image);
}

const void *il2cpp_image_get_entry_point(const Il2CppImage *image) {
    load_il2cpp();
    return il2cpp_image_get_entry_point_ptr(image);
}

size_t il2cpp_image_get_class_count(const Il2CppImage *image) {
    load_il2cpp();
    return il2cpp_image_get_class_count_ptr(image);
}

const void *il2cpp_image_get_class(const Il2CppImage *image, size_t index) {
    load_il2cpp();
    return il2cpp_image_get_class_ptr(image, index);
}

void *il2cpp_capture_memory_snapshot() {
    load_il2cpp();
    return il2cpp_capture_memory_snapshot_ptr();
}

void il2cpp_free_captured_memory_snapshot(Il2CppManagedMemorySnapshot *snapshot) {
    load_il2cpp();
    il2cpp_free_captured_memory_snapshot_ptr(snapshot);
}

void il2cpp_set_find_plugin_callback(Il2CppSetFindPlugInCallback method) {
    load_il2cpp();
    il2cpp_set_find_plugin_callback_ptr(method);
}

void il2cpp_register_log_callback(Il2CppLogCallback method) {
    load_il2cpp();
    il2cpp_register_log_callback_ptr(method);
}

void il2cpp_debugger_set_agent_options(const char *options) {
    load_il2cpp();
    il2cpp_debugger_set_agent_options_ptr(options);
}

bool il2cpp_is_debugger_attached() {
    load_il2cpp();
    return il2cpp_is_debugger_attached_ptr();
}

void il2cpp_register_debugger_agent_transport(Il2CppDebuggerTransport *debuggerTransport) {
    load_il2cpp();
    il2cpp_register_debugger_agent_transport_ptr(debuggerTransport);
}

bool il2cpp_debug_get_method_info(const MethodInfo *info, Il2CppMethodDebugInfo *methodDebugInfo) {
    load_il2cpp();
    return il2cpp_debug_get_method_info_ptr(info, methodDebugInfo);
}

void il2cpp_unity_install_unitytls_interface(const void *unitytlsInterfaceStruct) {
    load_il2cpp();
    il2cpp_unity_install_unitytls_interface_ptr(unitytlsInterfaceStruct);
}

void *il2cpp_custom_attrs_from_class(Il2CppClass *klass) {
    load_il2cpp();
    return il2cpp_custom_attrs_from_class_ptr(klass);
}

void *il2cpp_custom_attrs_from_method(const MethodInfo *method) {
    load_il2cpp();
    return il2cpp_custom_attrs_from_method_ptr(method);
}

void *il2cpp_custom_attrs_get_attr(Il2CppCustomAttrInfo *ainfo, Il2CppClass *attr_klass) {
    load_il2cpp();
    return il2cpp_custom_attrs_get_attr_ptr(ainfo, attr_klass);
}

bool il2cpp_custom_attrs_has_attr(Il2CppCustomAttrInfo *ainfo, Il2CppClass *attr_klass) {
    load_il2cpp();
    return il2cpp_custom_attrs_has_attr_ptr(ainfo, attr_klass);
}

void *il2cpp_custom_attrs_construct(Il2CppCustomAttrInfo *cinfo) {
    load_il2cpp();
    return il2cpp_custom_attrs_construct_ptr(cinfo);
}

void il2cpp_custom_attrs_free(Il2CppCustomAttrInfo *ainfo) {
    load_il2cpp();
    il2cpp_custom_attrs_free_ptr(ainfo);
}

void il2cpp_class_set_userdata(Il2CppClass *klass, void *userdata) {
    load_il2cpp();
    il2cpp_class_set_userdata_ptr(klass, userdata);
}

int il2cpp_class_get_userdata_offset() {
    load_il2cpp();
    return il2cpp_class_get_userdata_offset_ptr();
}

void il2cpp_set_default_thread_affinity(int64_t affinity_mask) {
    load_il2cpp();
    il2cpp_set_default_thread_affinity_ptr(affinity_mask);
}
