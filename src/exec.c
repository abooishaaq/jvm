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

// we'd need to load java/lang/Object, java/lang/System, java/io/PrintStream

//   public static final java.io.PrintStream out;
//     descriptor: Ljava/io/PrintStream;
//     flags: (0x0019) ACC_PUBLIC, ACC_STATIC, ACC_FINAL

//   public void println(java.lang.String);
//     descriptor: (Ljava/lang/String;)V
//     flags: (0x0001) ACC_PUBLIC
//     Code:
//       stack=2, locals=4, args_size=2
//          0: aload_0
//          1: dup
//          2: astore_2
//          3: monitorenter
//          4: aload_0
//          5: aload_1
//          6: invokevirtual #252                // Method
//                                                  print:(Ljava/lang/String;)V
//          9: aload_0
//         10: invokespecial #239                // Method newLine:()V
//         13: aload_2
//         14: monitorexit
//         15: goto          23
//         18: astore_3
//         19: aload_2
//         20: monitorexit
//         21: aload_3
//         22: athrow
//         23: return
//       Exception table:
//          from    to  target type
//              4    15    18   any
//             18    21    18   any
//       StackMapTable: number_of_entries = 2
//         frame_type = 255 /* full_frame */
//           offset_delta = 18
//           locals = [ class java/io/PrintStream, class java/lang/String, class
//           java/lang/Object ] stack = [ class java/lang/Throwable ]
//         frame_type = 250 /* chop */
//           offset_delta = 4

void print_hex(uint8_t *bytes, int len) {
    for (int i = 0; i < len; i++) {
        LOG_EXEC("%x ", bytes[i]);
    }
    LOG_EXEC("\n");
}

struct t_code_attribute *parse_code_attribute(uint8_t *bytes, int len) {
    struct t_code_attribute *code = malloc(sizeof(struct t_code_attribute));
    int idx = 0;
    code->max_stack = read_u16(bytes, &idx);
    code->max_locals = read_u16(bytes, &idx);
    code->code_length = read_u32(bytes, &idx);
    LOG_EXEC("max_stack: %d\n", code->max_stack);
    LOG_EXEC("max_locals: %d\n", code->max_locals);
    LOG_EXEC("code_length: %d\n", code->code_length);
    LOG_EXEC("code: %x\n", bytes[idx]);
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
        struct t_cp_info c =
            classfile->constant_pool[attribute.attribute_name_index];
        uint8_t *name = c.info.utf8_info->bytes;
        LOG_EXEC("Attribute name: %s\n", name);
        if (strcmp((char *)name, "Code") == 0) {
            LOG_EXEC("Found code attribute\n");
            LOG_EXEC("attribute_length: %d\n", attribute.attribute_length);
            print_hex(attribute.info, attribute.attribute_length);
            frame->code = parse_code_attribute(attribute.info,
                                               attribute.attribute_length);
        }
    }
    frame->pc = 0;
    return frame;
}

// FieldRef constant only
// print code
void print_cp_info(struct t_cp_info *c, int len) {
    for (int i = 0; i < len; i++) {
        if (c[i].tag == CONSTANT_Fieldref) {
            LOG_EXEC("field ref tag: %x\n", c[i].info.fieldref_info->tag);
            LOG_EXEC("class index: %x\n", c[i].info.fieldref_info->class_index);
            LOG_EXEC("name and type index: %x\n",
                     c[i].info.fieldref_info->name_and_type_index);
        }
    }
}

void push(struct Frame *frame, uint64_t value) {
    frame->operand_stack[frame->sp++] = value;
}

void exec(struct Frame *frame) {
    LOG_EXEC("frame->pc: %d\n", frame->pc);
    LOG_EXEC("frame->code->code_length: %d\n", frame->code->code_length);
    struct t_cp_info *constant_pool = frame->classfile->constant_pool;
    while (frame->pc < frame->code->code_length) {
        LOG_EXEC("opcode: %x\n", frame->code->code[frame->pc]);
        switch (frame->code->code[frame->pc++]) {
        case op_getstatic: {
            uint16_t index = read_u16(frame->code->code, &frame->pc);
            LOG_EXEC("cp index %d\n", index);
            struct t_cp_info cp_info = constant_pool[index];
            LOG_EXEC("cp_info.tag %d\n", cp_info.tag);
            if (cp_info.tag == CONSTANT_Fieldref) {
                LOG_EXEC("field ref tag: %x\n",
                         cp_info.info.fieldref_info->tag);
                LOG_EXEC("class index: %x\n",
                         cp_info.info.fieldref_info->class_index);
                LOG_EXEC("name and type index: %x\n",
                         cp_info.info.fieldref_info->name_and_type_index);
                struct t_cp_info class_info =
                    constant_pool[cp_info.info.fieldref_info->class_index];
                struct t_cp_info name_and_type_info =
                    constant_pool[cp_info.info.fieldref_info
                                      ->name_and_type_index];
                uint8_t *class_name =
                    constant_pool[class_info.info.class_info->name_index]
                        .info.utf8_info->bytes;
                LOG_EXEC("class name: %s\n", class_name);
                uint8_t *name =
                    constant_pool[name_and_type_info.info.name_and_type_info
                                      ->name_index]
                        .info.utf8_info->bytes;
                LOG_EXEC("name: %s\n", name);
                int is_java_lang_system =
                    strcmp((char *)class_name, "java/lang/System") == 0;
                int is_out = strcmp((char *)name, "out") == 0;
                if (is_java_lang_system && is_out) {
                    LOG_EXEC("Found System.out\n");
                    uint8_t *bytes =
                        read_file("classes/java/lang/System.class");
                    struct t_class_file *classfile =
                        parse_class_file_from_bytes(bytes);
                    push(frame, (uint64_t)classfile);
                }
            }
        }
        }
    }
}

void exec_class_file(struct t_class_file *classfile) {
    struct t_cp_info *constant_pool = classfile->constant_pool;
    for (int i = 0; i < classfile->methods_count; i++) {
        struct t_method_info method = classfile->methods[i];
        if (method.access_flags & METHOD_ACC_PUBLIC &&
            method.access_flags & METHOD_ACC_STATIC) {
            LOG_EXEC("executing main method\n");
            struct Frame *frame = new_frame(classfile, &method);
            exec(frame);
        }
    }
}
