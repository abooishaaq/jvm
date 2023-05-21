#ifndef EXEC_H
#define EXEC_H
#endif

#include "classfile.h"

// Code_attribute {
//     u2 attribute_name_index;
//     u4 attribute_length;
//     u2 max_stack;
//     u2 max_locals;
//     u4 code_length;
//     u1 code[code_length];
//     u2 exception_table_length;
//     {   u2 start_pc;
//         u2 end_pc;
//         u2 handler_pc;
//         u2 catch_type;
//     } exception_table[exception_table_length];
//     u2 attributes_count;
//     attribute_info attributes[attributes_count];
// }

struct t_code_attribute {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t max_stack;
    uint16_t max_locals;
    uint32_t code_length;
    uint8_t *code;
    uint16_t exception_table_length;
    struct t_exception_table *exception_table;
    uint16_t attributes_count;
    struct t_attribute_info *attributes;
};

struct t_exception_table {
    uint16_t start_pc;
    uint16_t end_pc;
    uint16_t handler_pc;
    uint16_t catch_type;
};

struct Frame {
    struct t_class_file *classfile;
    struct t_method_info *method;
    struct t_code_attribute *code;

    struct Frame *prev;
    struct Frame *next;
    int pc;
};

void exec_class_file(struct t_class_file *classfile);