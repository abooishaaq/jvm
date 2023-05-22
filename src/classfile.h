#ifndef CLASSFILE_H
#define CLASSFILE_H
#endif

#include <stdint.h>

#define VERBOSE_PARSING

/// java class file
struct t_class_file {
    uint32_t magic;
    uint16_t minor_version;
    uint16_t major_version;
    uint16_t constant_pool_count;
    struct t_cp_info *constant_pool;
    uint16_t access_flags;
    uint16_t this_class;
    uint16_t super_class;
    uint16_t interfaces_count;
    uint16_t *interfaces;
    uint16_t fields_count;
    struct t_field_info *fields;
    uint16_t methods_count;
    struct t_method_info *methods;
    uint16_t attributes_count;
    struct t_attribute_info *attributes;
};

/// constant pool info
struct t_cp_info {
    uint8_t tag;
    union {
        struct t_constant_class_info *class_info;
        struct t_constant_fieldref_info *fieldref_info;
        struct t_constant_methodref_info *methodref_info;
        struct t_constant_interface_methodref_info *interface_methodref_info;
        struct t_constant_string_info *string_info;
        struct t_constant_integer_info *integer_info;
        struct t_constant_float_info *float_info;
        struct t_constant_long_info *long_info;
        struct t_constant_double_info *double_info;
        struct t_constant_name_and_type_info *name_and_type_info;
        struct t_constant_utf8_info *utf8_info;
        struct t_constant_method_handle_info *method_handle_info;
        struct t_constant_method_type_info *method_type_info;
        struct t_constant_dynamic_info *dynamic_info;
        struct t_constant_invoke_dynamic_info *invoke_dynamic_info;
        struct t_constant_module_info *module_info;
        struct t_constant_package_info *package_info;
    } info;
};

/// field info
struct t_field_info {
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    struct t_attribute_info *attributes;
};

/// method info
struct t_method_info {
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    struct t_attribute_info *attributes;
};

/// attribute info
struct t_attribute_info {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint8_t *info;
};

/// constant pool tag
#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1
#define CONSTANT_MethodHandle 15
#define CONSTANT_MethodType 16
#define CONSTANT_Dynamic 17
#define CONSTANT_InvokeDynamic 18
#define CONSTANT_Module 19
#define CONSTANT_Package 20

/// constant pool info
struct t_constant_class_info {
    uint8_t tag;
    uint16_t name_index;
};

struct t_constant_fieldref_info {
    uint8_t tag;
    uint16_t class_index;
    uint16_t name_and_type_index;
};

struct t_constant_methodref_info {
    uint8_t tag;
    uint16_t class_index;
    uint16_t name_and_type_index;
};

struct t_constant_interface_methodref_info {
    uint8_t tag;
    uint16_t class_index;
    uint16_t name_and_type_index;
};

struct t_constant_string_info {
    uint8_t tag;
    uint16_t string_index;
};

struct t_constant_integer_info {
    uint8_t tag;
    uint32_t bytes;
};

struct t_constant_float_info {
    uint8_t tag;
    uint32_t bytes;
};

struct t_constant_long_info {
    uint8_t tag;
    uint32_t high_bytes;
    uint32_t low_bytes;
};

struct t_constant_double_info {
    uint8_t tag;
    uint32_t high_bytes;
    uint32_t low_bytes;
};

struct t_constant_name_and_type_info {
    uint8_t tag;
    uint16_t name_index;
    uint16_t descriptor_index;
};

struct t_constant_utf8_info {
    uint8_t tag;
    uint16_t length;
    uint8_t *bytes;
};

struct t_constant_method_handle_info {
    uint8_t tag;
    uint8_t reference_kind;
    uint16_t reference_index;
};

struct t_constant_method_type_info {
    uint8_t tag;
    uint16_t descriptor_index;
};

struct t_constant_dynamic_info {
    uint8_t tag;
    uint16_t bootstrap_method_attr_index;
    uint16_t name_and_type_index;
};

struct t_constant_invoke_dynamic_info {
    uint8_t tag;
    uint16_t bootstrap_method_attr_index;
    uint16_t name_and_type_index;
};

struct t_constant_module_info {
    uint8_t tag;
    uint16_t name_index;
};

struct t_constant_package_info {
    uint8_t tag;
    uint16_t name_index;
};

/// Field access and property flags
#define FIELD_ACC_PUBLIC 0x0001
#define FIELD_ACC_PRIVATE 0x0002
#define FIELD_ACC_PROTECTED 0x0004
#define FIELD_ACC_STATIC 0x0008
#define FIELD_ACC_FINAL 0x0010
#define FIELD_ACC_VOLATILE 0x0040
#define FIELD_ACC_TRANSIENT 0x0080
#define FIELD_ACC_SYNTHETIC 0x1000
#define FIELD_ACC_ENUM 0x4000

/// Method access and property flags
#define METHOD_ACC_PUBLIC 0x0001
#define METHOD_ACC_PRIVATE 0x0002
#define METHOD_ACC_PROTECTED 0x0004
#define METHOD_ACC_STATIC 0x0008
#define METHOD_ACC_FINAL 0x0010
#define METHOD_ACC_SYNCHRONIZED 0x0020
#define METHOD_ACC_BRIDGE 0x0040
#define METHOD_ACC_VARARGS 0x0080
#define METHOD_ACC_NATIVE 0x0100
#define METHOD_ACC_ABSTRACT 0x0400
#define METHOD_ACC_STRICT 0x0800
#define METHOD_ACC_SYNTHETIC 0x1000

// attribute names
static const char *attribute_names[] = {"ConstantValue",
                                        "Code",
                                        "StackMapTable",
                                        "Exceptions",
                                        "InnerClasses",
                                        "EnclosingMethod",
                                        "Synthetic",
                                        "Signature",
                                        "SourceFile",
                                        "SourceDebugExtension",
                                        "LineNumberTable",
                                        "LocalVariableTable",
                                        "LocalVariableTypeTable",
                                        "Deprecated",
                                        "RuntimeVisibleAnnotations",
                                        "RuntimeInvisibleAnnotations",
                                        "RuntimeVisibleParameterAnnotations",
                                        "RuntimeInvisibleParameterAnnotations",
                                        "RuntimeVisibleTypeAnnotations",
                                        "RuntimeInvisibleTypeAnnotations",
                                        "AnnotationDefault",
                                        "BootstrapMethods",
                                        "MethodParameters",
                                        "Module",
                                        "ModulePackages",
                                        "ModuleMainClass",
                                        "NestHost",
                                        "NestMembers",
                                        "Record"};

// attribute name index
enum e_attribute_name_index {
    ATTRIBUTE_NAME_INDEX_ConstantValue,
    ATTRIBUTE_NAME_INDEX_Code,
    ATTRIBUTE_NAME_INDEX_StackMapTable,
    ATTRIBUTE_NAME_INDEX_Exceptions,
    ATTRIBUTE_NAME_INDEX_InnerClasses,
    ATTRIBUTE_NAME_INDEX_EnclosingMethod,
    ATTRIBUTE_NAME_INDEX_Synthetic,
    ATTRIBUTE_NAME_INDEX_Signature,
    ATTRIBUTE_NAME_INDEX_SourceFile,
    ATTRIBUTE_NAME_INDEX_SourceDebugExtension,
    ATTRIBUTE_NAME_INDEX_LineNumberTable,
    ATTRIBUTE_NAME_INDEX_LocalVariableTable,
    ATTRIBUTE_NAME_INDEX_LocalVariableTypeTable,
    ATTRIBUTE_NAME_INDEX_Deprecated,
    ATTRIBUTE_NAME_INDEX_RuntimeVisibleAnnotations,
    ATTRIBUTE_NAME_INDEX_RuntimeInvisibleAnnotations,
    ATTRIBUTE_NAME_INDEX_RuntimeVisibleParameterAnnotations,
    ATTRIBUTE_NAME_INDEX_RuntimeInvisibleParameterAnnotations,
    ATTRIBUTE_NAME_INDEX_RuntimeVisibleTypeAnnotations,
    ATTRIBUTE_NAME_INDEX_RuntimeInvisibleTypeAnnotations,
    ATTRIBUTE_NAME_INDEX_AnnotationDefault,
    ATTRIBUTE_NAME_INDEX_BootstrapMethods,
    ATTRIBUTE_NAME_INDEX_MethodParameters,
    ATTRIBUTE_NAME_INDEX_Module,
    ATTRIBUTE_NAME_INDEX_ModulePackages,
    ATTRIBUTE_NAME_INDEX_ModuleMainClass,
    ATTRIBUTE_NAME_INDEX_NestHost,
    ATTRIBUTE_NAME_INDEX_NestMembers,
    ATTRIBUTE_NAME_INDEX_Record
};

struct t_class_file *parse_class_file_from_bytes(uint8_t *bytes);
