#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "exec.h"
#include "read.h"


int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <classfile>\n", argv[0]);
        exit(1);
    }
    uint8_t *bytes = read_file(argv[1]);
    struct t_class_file *classfile = parse_class_file_from_bytes(bytes);
    printf("Magic: %x\n", classfile->magic);
    printf("Minor version: %d\n", classfile->minor_version);
    printf("Major version: %d\n", classfile->major_version);
    printf("Constant pool count: %d\n", classfile->constant_pool_count);
    printf("Access flags: %x\n", classfile->access_flags);
    printf("This class: %d\n", classfile->this_class);
    printf("Super class: %d\n", classfile->super_class);
    printf("Interfaces count: %d\n", classfile->interfaces_count);
    printf("Fields count: %d\n", classfile->fields_count);
    printf("Methods count: %d\n", classfile->methods_count);
    printf("Attributes count: %d\n", classfile->attributes_count);
    exec_class_file(classfile);
    return 0;
}