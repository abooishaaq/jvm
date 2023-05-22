#ifndef EXEC_H
#define EXEC_H
#endif

#include "classfile.h"

#define VERBOSE_EXEC
#define LOG_EXEC(...) printf(__VA_ARGS__);

struct t_code_attribute {
    uint16_t max_stack;
    uint16_t max_locals;
    uint32_t code_length;
    uint8_t *code;
    uint16_t exception_table_length;
    struct t_exception_table *exception_table;
    uint16_t attributes_count;
    struct t_attribute_info *attributes;
};

struct t_module_attribute {
    uint16_t module_name_index;
    uint16_t module_flags;
    uint16_t module_version_index;
    uint16_t requires_count;
    struct t_requires *
        requires;
    uint16_t exports_count;
    struct t_exports *exports;
    uint16_t opens_count;
    struct t_opens *opens;
    uint16_t uses_count;
    uint16_t *uses_index;
    uint16_t provides_count;
    struct t_provides *provides;
};

struct t_requires {
    uint16_t requires_index;
    uint16_t requires_flags;
    uint16_t requires_version_index;
};

struct t_exports {
    uint16_t exports_index;
    uint16_t exports_flags;
    uint16_t exports_to_count;
    uint16_t *exports_to_index;
};

struct t_opens {
    uint16_t opens_index;
    uint16_t opens_flags;
    uint16_t opens_to_count;
    uint16_t *opens_to_index;
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

    uint64_t *local_variables;
    uint64_t *operand_stack;
    uint64_t sp;

    struct Frame *prev;
    struct Frame *next;
    int pc;
};

void exec_class_file(struct t_class_file *classfile);

// OPCODE
#define op_nop 0x00
#define op_aconst_null 0x01
#define op_iconst_m1 0x02
#define op_iconst_0 0x03
#define op_iconst_1 0x04
#define op_iconst_2 0x05
#define op_iconst_3 0x06
#define op_iconst_4 0x07
#define op_iconst_5 0x08
#define op_lconst_0 0x09
#define op_lconst_1 0x0A
#define op_fconst_0 0x0B
#define op_fconst_1 0x0C
#define op_fconst_2 0x0D
#define op_dconst_0 0x0E
#define op_dconst_1 0x0F
#define op_bipush 0x10
#define op_sipush 0x11
#define op_ldc 0x12
#define op_ldc_w 0x13
#define op_ldc2_w 0x14
#define op_iload 0x15
#define op_lload 0x16
#define op_fload 0x17
#define op_dload 0x18
#define op_aload 0x19
#define op_iload_0 0x1A
#define op_iload_1 0x1B
#define op_iload_2 0x1C
#define op_iload_3 0x1D
#define op_lload_0 0x1E
#define op_lload_1 0x1F
#define op_lload_2 0x20
#define op_lload_3 0x21
#define op_fload_0 0x22
#define op_fload_1 0x23
#define op_fload_2 0x24
#define op_fload_3 0x25
#define op_dload_0 0x26
#define op_dload_1 0x27
#define op_dload_2 0x28
#define op_dload_3 0x29
#define op_aload_0 0x2A
#define op_aload_1 0x2B
#define op_aload_2 0x2C
#define op_aload_3 0x2D
#define op_iaload 0x2E
#define op_laload 0x2F
#define op_faload 0x30
#define op_daload 0x31
#define op_aaload 0x32
#define op_baload 0x33
#define op_caload 0x34
#define op_saload 0x35
#define op_istore 0x36
#define op_lstore 0x37
#define op_fstore 0x38
#define op_dstore 0x39
#define op_astore 0x3A
#define op_istore_0 0x3B
#define op_istore_1 0x3C
#define op_istore_2 0x3D
#define op_istore_3 0x3E
#define op_lstore_0 0x3F
#define op_lstore_1 0x40
#define op_lstore_2 0x41
#define op_lstore_3 0x42
#define op_fstore_0 0x43
#define op_fstore_1 0x44
#define op_fstore_2 0x45
#define op_fstore_3 0x46
#define op_dstore_0 0x47
#define op_dstore_1 0x48
#define op_dstore_2 0x49
#define op_dstore_3 0x4A
#define op_astore_0 0x4B
#define op_astore_1 0x4C
#define op_astore_2 0x4D
#define op_astore_3 0x4E
#define op_iastore 0x4F
#define op_lastore 0x50
#define op_fastore 0x51
#define op_dastore 0x52
#define op_aastore 0x53
#define op_bastore 0x54
#define op_castore 0x55
#define op_sastore 0x56
#define op_pop 0x57
#define op_pop2 0x58
#define op_dup 0x59
#define op_dup_x1 0x5A
#define op_dup_x2 0x5B
#define op_dup2 0x5C
#define op_dup2_x1 0x5D
#define op_dup2_x2 0x5E
#define op_swap 0x5F
#define op_iadd 0x60
#define op_ladd 0x61
#define op_fadd 0x62
#define op_dadd 0x63
#define op_isub 0x64
#define op_lsub 0x65
#define op_fsub 0x66
#define op_dsub 0x67
#define op_imul 0x68
#define op_lmul 0x69
#define op_fmul 0x6A
#define op_dmul 0x6B
#define op_idiv 0x6C
#define op_ldiv 0x6D
#define op_fdiv 0x6E
#define op_ddiv 0x6F
#define op_irem 0x70
#define op_lrem 0x71
#define op_frem 0x72
#define op_drem 0x73
#define op_ineg 0x74
#define op_lneg 0x75
#define op_fneg 0x76
#define op_dneg 0x77
#define op_ishl 0x78
#define op_lshl 0x79
#define op_ishr 0x7A
#define op_lshr 0x7B
#define op_iushr 0x7C
#define op_lushr 0x7D
#define op_iand 0x7E
#define op_land 0x7F
#define op_ior 0x80
#define op_lor 0x81
#define op_ixor 0x82
#define op_lxor 0x83
#define op_iinc 0x84
#define op_i2l 0x85
#define op_i2f 0x86
#define op_i2d 0x87
#define op_l2i 0x88
#define op_l2f 0x89
#define op_l2d 0x8A
#define op_f2i 0x8B
#define op_f2l 0x8C
#define op_f2d 0x8D
#define op_d2i 0x8E
#define op_d2l 0x8F
#define op_d2f 0x90
#define op_i2b 0x91
#define op_i2c 0x92
#define op_i2s 0x93
#define op_lcmp 0x94
#define op_fcmpl 0x95
#define op_fcmpg 0x96
#define op_dcmpl 0x97
#define op_dcmpg 0x98
#define op_ifeq 0x99
#define op_ifne 0x9A
#define op_iflt 0x9B
#define op_ifge 0x9C
#define op_ifgt 0x9D
#define op_ifle 0x9E
#define op_if_icmpeq 0x9F
#define op_if_icmpne 0xA0
#define op_if_icmplt 0xA1
#define op_if_icmpge 0xA2
#define op_if_icmpgt 0xA3
#define op_if_icmple 0xA4
#define op_if_acmpeq 0xA5
#define op_if_acmpne 0xA6
#define op_goto 0xA7
#define op_jsr 0xA8
#define op_ret 0xA9
#define op_tableswitch 0xAA
#define op_lookupswitch 0xAB
#define op_ireturn 0xAC
#define op_lreturn 0xAD
#define op_freturn 0xAE
#define op_dreturn 0xAF
#define op_areturn 0xB0
#define op_return 0xB1
#define op_getstatic 0xB2
#define op_putstatic 0xB3
#define op_getfield 0xB4
#define op_putfield 0xB5
#define op_invokevirtual 0xB6
#define op_invokespecial 0xB7
#define op_invokestatic 0xB8
#define op_invokeinterface 0xB9
#define op_new 0xBB
#define op_newarray 0xBC
#define op_anewarray 0xBD
#define op_arraylength 0xBE
#define op_athrow 0xBF
#define op_checkcast 0xC0
#define op_instanceof 0xC1
#define op_monitorenter 0xC2
#define op_monitiorexit 0xC3
#define op_wide 0xC4
#define op_multianewarray 0xC5
#define op_ifnull 0xC6
#define op_ifnonnull 0xC7
#define op_goto_w 0xC8
#define op_jsr_w 0xC9
#define op_breakpoint 0xCA
#define op_impdep1 0xFE
#define op_impdep2 0xFF
