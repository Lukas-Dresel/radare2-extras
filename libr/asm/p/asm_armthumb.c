/* radare - LGPL - Copyright 2010-2015 - pancake */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <r_types.h>
#include <r_util.h>
#include <r_lib.h>
#include <r_asm.h>
#include "../arch/arm/arm.h"

static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	int *p = (int*)buf; // TODO : endian
	op->buf_asm[0]='\0';
	op->size = armthumb_disassemble (op->buf_asm, (ut32)a->pc, *p);
	if (!op->size)
		strncpy (op->buf_asm, " (data)", R_ASM_BUFSIZE);
	return op->size;
}

#if 0
static int assemble(RAsm *a, RAsmOp *op, const char *buf) {
	int opcode = armass_assemble (buf, a->pc, R_TRUE);
	if (opcode==-1)
		return -1;
	r_mem_copyendian (op->buf, (void *)&opcode, 2, a->big_endian);
	return armthumb_length (opcode);
}
#endif

RAsmPlugin r_asm_plugin_armthumb = {
	.name = "arm.thumb",
	.arch = "arm",
	.bits = 16,
	.desc = "ARM THUMB disassembly plugin",
	.init = NULL,
	.fini = NULL,
	.disassemble = &disassemble,
//	.assemble = &assemble 
};

#ifndef CORELIB
struct r_lib_struct_t radare_plugin = {
	.type = R_LIB_TYPE_ASM,
	.data = &r_asm_plugin_armthumb,
	.version = R2_VERSION
};
#endif
