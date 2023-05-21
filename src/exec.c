#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exec.h"
#include "read.h"

// public class Main {
//   public Main();
//     Code:
//        0: aload_0
//        1: invokespecial #1                  // Method
//        java/lang/Object."<init>":()V 4: return

//   public static void main(java.lang.String[]);
//     Code:
//        0: getstatic     #7                  // Field
//        java/lang/System.out:Ljava/io/PrintStream; 3: ldc           #13 //
//        String Hello World! 5: invokevirtual #15                 // Method
//        java/io/PrintStream.println:(Ljava/lang/String;)V 8: return
// }

// ability to execute this classfile

struct t_code_attribute *parse_code_attribute(uint8_t *bytes, int len) {
    struct t_code_attribute *code = malloc(sizeof(struct t_code_attribute));
    int idx = 0;
    code->attribute_name_index = read_u16(bytes, &idx);
    code->attribute_length = read_u32(bytes, &idx);
    code->max_stack = read_u16(bytes, &idx);
    code->max_locals = read_u16(bytes, &idx);
    code->code_length = read_u32(bytes, &idx);
    code->code = malloc(code->code_length);
    memcpy(code->code, bytes + idx, code->code_length);
    idx += code->code_length;
    code->exception_table_length = read_u16(bytes, &idx);
    code->exception_table =
        malloc(sizeof(struct t_exception_table) * code->exception_table_length);
    for (int i = 0; i < code->exception_table_length; i++) {
        code->exception_table[i].start_pc = read_u16(bytes, &idx);
        code->exception_table[i].end_pc = read_u16(bytes, &idx);
        code->exception_table[i].handler_pc = read_u16(bytes, &idx);
        code->exception_table[i].catch_type = read_u16(bytes, &idx);
    }
    return code;
}

struct Frame *new_frame(struct t_class_file *classfile,
                        struct t_method_info *method) {
    struct Frame *frame = malloc(sizeof(struct Frame));
    frame->classfile = classfile;
    frame->method = method;
    struct t_cp_info *constant_pool = classfile->constant_pool;
    for (int i = 0; i < method->attributes_count; i++) {
        struct t_attribute_info attribute = method->attributes[i];
        if (attribute.attribute_name_index == ATTRIBUTE_NAME_INDEX_Code) {
            frame->code = parse_code_attribute(attribute.info,
                                               attribute.attribute_length);
            break;
        }
    }
    frame->pc = 0;
    return frame;
}

const int op_getstatic = 0xb2;
const int op_invokevirtual = 0xb6;
const int op_return = 0xb1;
const int op_ldc = 0x12;

// FieldRef constant only
// print code
void print_cp_info(struct t_cp_info *c, int len) {
    for (int i = 0; i < len; i++) {
        if (c[i].tag == CONSTANT_Fieldref) {
            printf("field ref tag: %x\n", c[i].info.fieldref_info->tag);
            printf("class index: %x\n", c[i].info.fieldref_info->class_index);
            printf("name and type index: %x\n",
                   c[i].info.fieldref_info->name_and_type_index);
        }
    }
}

void exec(struct Frame *frame) {
    while (frame->pc < frame->code->code_length) {
        switch (frame->code->code[frame->pc]) {
        case op_getstatic: {
            printf("getstatic\n");
            uint64_t index = read_u8(frame->code->code, &frame->pc);
            index = (index << 8) | read_u8(frame->code->code, &frame->pc);
            struct t_cp_info *constant_pool = frame->classfile->constant_pool;
            struct t_cp_info cp_info = constant_pool[index];
            // print_cp_info(&cp_info);
            break;
        }
        default:
            printf("unknown opcode: %x\n", frame->code->code[frame->pc]);
        }
        ++frame->pc;
    }
}

void exec_class_file(struct t_class_file *classfile) {
    struct t_cp_info *constant_pool = classfile->constant_pool;
    print_cp_info(constant_pool, classfile->constant_pool_count);
    for (int i = 0; i < classfile->methods_count; i++) {
        struct t_method_info method = classfile->methods[i];
        if (method.access_flags & METHOD_ACC_PUBLIC &&
            method.access_flags & METHOD_ACC_STATIC) {
            printf("executing main method\n");
            struct Frame *frame = new_frame(classfile, &method);
            exec(frame);
        }
    }
}
