#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "classfile.h"
#include "read.h"

void error(char *msg) {
    printf("%s\n", msg);
    exit(1);
}

void parse_constant_pool(struct t_cp_info *constant_pool,
                         uint16_t constant_pool_count, uint8_t *bytes,
                         int *index) {
    for (int i = 1; i < constant_pool_count; i++) {
        uint8_t tag = read_u8(bytes, index);
        constant_pool[i].tag = tag;
#ifdef VERBOSE_PARSING
        printf("read constant of tag: %d\n", tag);
#endif
        switch (tag) {
        case CONSTANT_Utf8: {
            constant_pool[i].info.utf8_info =
                malloc(sizeof(struct t_constant_utf8_info));
            constant_pool[i].info.utf8_info->length = read_u16(bytes, index);
            constant_pool[i].info.utf8_info->bytes = malloc(
                sizeof(uint8_t) * constant_pool[i].info.utf8_info->length);
            for (int j = 0; j < constant_pool[i].info.utf8_info->length; j++) {
                constant_pool[i].info.utf8_info->bytes[j] =
                    read_u8(bytes, index);
            }
            constant_pool[i]
                .info.utf8_info
                ->bytes[constant_pool[i].info.utf8_info->length] = '\0';
#ifdef VERBOSE_PARSING
            printf("UTF-8\n");
            printf("  length: %d\n", constant_pool[i].info.utf8_info->length);
            printf("  bytes: %s\n", constant_pool[i].info.utf8_info->bytes);
#endif
            break;
        }
        case CONSTANT_Integer:
            constant_pool[i].info.integer_info =
                malloc(sizeof(struct t_constant_integer_info));
            constant_pool[i].info.integer_info->bytes = read_u32(bytes, index);
#ifdef VERBOSE_PARSING
            printf("Integer\n");
            printf("  bytes: %d\n", constant_pool[i].info.integer_info->bytes);
#endif
            break;
        case CONSTANT_Float:
            constant_pool[i].info.float_info =
                malloc(sizeof(struct t_constant_float_info));
            constant_pool[i].info.float_info->bytes = read_u32(bytes, index);
#ifdef VERBOSE_PARSING
            printf("Float\n");
            printf("  bytes: %d\n", constant_pool[i].info.float_info->bytes);
#endif
            break;
        case CONSTANT_Long:
            constant_pool[i].info.long_info =
                malloc(sizeof(struct t_constant_long_info));
            constant_pool[i].info.long_info->high_bytes =
                read_u32(bytes, index);
            constant_pool[i].info.long_info->low_bytes = read_u32(bytes, index);
            i++;
#ifdef VERBOSE_PARSING
            printf("Long\n");
            printf("  high_bytes: %x\n",
                   constant_pool[i].info.long_info->high_bytes);
            printf("  low_bytes: %x\n",
                   constant_pool[i].info.long_info->low_bytes);
#endif
            break;
        case CONSTANT_Double:
            constant_pool[i].info.double_info =
                malloc(sizeof(struct t_constant_double_info));
            constant_pool[i].info.double_info->high_bytes =
                read_u32(bytes, index);
            constant_pool[i].info.double_info->low_bytes =
                read_u32(bytes, index);
            i++;
#ifdef VERBOSE_PARSING
            printf("Long\n");
            printf("  high_bytes: %x\n",
                   constant_pool[i].info.double_info->high_bytes);
            printf("  low_bytes: %x\n",
                   constant_pool[i].info.double_info->low_bytes);
#endif
            break;
        case CONSTANT_Class:
            constant_pool[i].info.class_info =
                malloc(sizeof(struct t_constant_class_info));
            constant_pool[i].info.class_info->name_index =
                read_u16(bytes, index);
#ifdef VERBOSE_PARSING
            printf("Class\n");
            printf("  name_index: %d\n",
                   constant_pool[i].info.class_info->name_index);
#endif
            break;
        case CONSTANT_String:
            constant_pool[i].info.string_info =
                malloc(sizeof(struct t_constant_string_info));
            constant_pool[i].info.string_info->string_index =
                read_u16(bytes, index);
#ifdef VERBOSE_PARSING
            printf("String\n");
            printf("  string_index: %d\n",
                   constant_pool[i].info.string_info->string_index);
#endif
            break;
        case CONSTANT_Fieldref:
            constant_pool[i].info.fieldref_info =
                malloc(sizeof(struct t_constant_fieldref_info));
            constant_pool[i].info.fieldref_info->class_index =
                read_u16(bytes, index);
            constant_pool[i].info.fieldref_info->name_and_type_index =
                read_u16(bytes, index);
#ifdef VERBOSE_PARSING
            printf("Fieldref\n");
            printf("  class_index: %d\n",
                   constant_pool[i].info.fieldref_info->class_index);
            printf("  name_and_type_index: %d\n",
                   constant_pool[i].info.fieldref_info->name_and_type_index);
#endif
            break;
        case CONSTANT_Methodref:
            constant_pool[i].info.methodref_info =
                malloc(sizeof(struct t_constant_methodref_info));
            constant_pool[i].info.methodref_info->class_index =
                read_u16(bytes, index);
            constant_pool[i].info.methodref_info->name_and_type_index =
                read_u16(bytes, index);
            break;
        case CONSTANT_InterfaceMethodref:
            constant_pool[i].info.interface_methodref_info =
                malloc(sizeof(struct t_constant_interface_methodref_info));
            constant_pool[i].info.interface_methodref_info->class_index =
                read_u16(bytes, index);
            constant_pool[i]
                .info.interface_methodref_info->name_and_type_index =
                read_u16(bytes, index);
            break;
        case CONSTANT_NameAndType:
            constant_pool[i].info.name_and_type_info =
                malloc(sizeof(struct t_constant_name_and_type_info));
            constant_pool[i].info.name_and_type_info->name_index =
                read_u16(bytes, index);
            constant_pool[i].info.name_and_type_info->descriptor_index =
                read_u16(bytes, index);
            break;
        case CONSTANT_MethodHandle:
            constant_pool[i].info.method_handle_info =
                malloc(sizeof(struct t_constant_method_handle_info));
            constant_pool[i].info.method_handle_info->reference_kind =
                read_u8(bytes, index);
            constant_pool[i].info.method_handle_info->reference_index =
                read_u16(bytes, index);
            break;
        case CONSTANT_MethodType:
            constant_pool[i].info.method_type_info =
                malloc(sizeof(struct t_constant_method_type_info));
            constant_pool[i].info.method_type_info->descriptor_index =
                read_u16(bytes, index);
            break;
        case CONSTANT_InvokeDynamic:
            constant_pool[i].info.invoke_dynamic_info =
                malloc(sizeof(struct t_constant_invoke_dynamic_info));
            constant_pool[i]
                .info.invoke_dynamic_info->bootstrap_method_attr_index =
                read_u16(bytes, index);
            constant_pool[i].info.invoke_dynamic_info->name_and_type_index =
                read_u16(bytes, index);
            break;
        default:
            error("unknown constant pool tag");
        }
    }
}

// Read a class file from a file
struct t_class_file *parse_class_file_from_bytes(uint8_t *bytes) {
    struct t_class_file *class_file = malloc(sizeof(struct t_class_file));

    int i = 0;
    int *index = &i;

    uint32_t magic = read_u32(bytes, index);
    if (magic != 0xCAFEBABE) {
        error("magic number is not 0xCAFEBABE");
    }

    class_file->magic = magic;

    class_file->minor_version = read_u16(bytes, index);
    class_file->major_version = read_u16(bytes, index);
    class_file->constant_pool_count = read_u16(bytes, index);

    // constant pool
    struct t_cp_info *constant_pool =
        malloc(sizeof(struct t_cp_info) * class_file->constant_pool_count);
    parse_constant_pool(constant_pool, class_file->constant_pool_count, bytes,
                        index);
    class_file->constant_pool = constant_pool;

    class_file->access_flags = read_u16(bytes, index);
    class_file->this_class = read_u16(bytes, index);
    class_file->super_class = read_u16(bytes, index);

    // interfaces
    class_file->interfaces_count = read_u16(bytes, index);
    class_file->interfaces =
        malloc(sizeof(uint16_t) * class_file->interfaces_count);
    for (int i = 0; i < class_file->interfaces_count; i++) {
        class_file->interfaces[i] = read_u16(bytes, index);
    }

    // fields
    class_file->fields_count = read_u16(bytes, index);
    class_file->fields =
        malloc(sizeof(struct t_field_info) * class_file->fields_count);
    for (int i = 0; i < class_file->fields_count; i++) {
        class_file->fields[i].access_flags = read_u16(bytes, index);
        class_file->fields[i].name_index = read_u16(bytes, index);
        class_file->fields[i].descriptor_index = read_u16(bytes, index);
        class_file->fields[i].attributes_count = read_u16(bytes, index);
        class_file->fields[i].attributes =
            malloc(sizeof(struct t_attribute_info) *
                   class_file->fields[i].attributes_count);
        for (int j = 0; j < class_file->fields[i].attributes_count; j++) {
            class_file->fields[i].attributes[j].attribute_name_index =
                read_u16(bytes, index);
            class_file->fields[i].attributes[j].attribute_length =
                read_u32(bytes, index);
            class_file->fields[i].attributes[j].info =
                malloc(sizeof(uint8_t) *
                       class_file->fields[i].attributes[j].attribute_length);
            for (int k = 0;
                 k < class_file->fields[i].attributes[j].attribute_length;
                 k++) {
                class_file->fields[i].attributes[j].info[k] =
                    read_u8(bytes, index);
            }
        }
    }

    // methods
    class_file->methods_count = read_u16(bytes, index);
    class_file->methods =
        malloc(sizeof(struct t_method_info) * class_file->methods_count);
    for (int i = 0; i < class_file->methods_count; i++) {
        class_file->methods[i].access_flags = read_u16(bytes, index);
        class_file->methods[i].name_index = read_u16(bytes, index);
        class_file->methods[i].descriptor_index = read_u16(bytes, index);
        class_file->methods[i].attributes_count = read_u16(bytes, index);
        class_file->methods[i].attributes =
            malloc(sizeof(struct t_attribute_info) *
                   class_file->methods[i].attributes_count);
        for (int j = 0; j < class_file->methods[i].attributes_count; j++) {
            class_file->methods[i].attributes[j].attribute_name_index =
                read_u16(bytes, index);
            class_file->methods[i].attributes[j].attribute_length =
                read_u32(bytes, index);
            class_file->methods[i].attributes[j].info =
                malloc(sizeof(uint8_t) *
                       class_file->methods[i].attributes[j].attribute_length);
            for (int k = 0;
                 k < class_file->methods[i].attributes[j].attribute_length;
                 k++) {
                class_file->methods[i].attributes[j].info[k] =
                    read_u8(bytes, index);
            }
        }
    }

    // attributes
    class_file->attributes_count = read_u16(bytes, index);
    class_file->attributes =
        malloc(sizeof(struct t_attribute_info) * class_file->attributes_count);
    for (int i = 0; i < class_file->attributes_count; i++) {
        class_file->attributes[i].attribute_name_index = read_u16(bytes, index);
        class_file->attributes[i].attribute_length = read_u32(bytes, index);
        class_file->attributes[i].info = malloc(
            sizeof(uint8_t) * class_file->attributes[i].attribute_length);
        for (int j = 0; j < class_file->attributes[i].attribute_length; j++) {
            class_file->attributes[i].info[j] = read_u8(bytes, index);
        }
    }

    return class_file;
}
