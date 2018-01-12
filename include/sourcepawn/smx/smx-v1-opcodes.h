// vim: set sts=2 ts=8 sw=2 tw=99 et:
// =============================================================================
// SourcePawn
// Copyright (C) 2004-2014 AlliedModders LLC.  All rights reserved.
// =============================================================================
// 
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License, version 3.0, as published by the
// Free Software Foundation.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
// 
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
// 
// As a special exception, AlliedModders LLC gives you permission to link the
// code of this program (as well as its derivative works) to "Half-Life 2," the
// "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
// by the Valve Corporation.  You must obey the GNU General Public License in
// all respects for all other code used.  Additionally, AlliedModders LLC grants
// this exception to all derivative works.  AlliedModders LLC defines further
// exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
// or <http://www.sourcemod.net/license.php>.

#ifndef _INCLUDE_SPFILE_HEADERS_v1_opcodes_H
#define _INCLUDE_SPFILE_HEADERS_v1_opcodes_H

#include <stddef.h>
#include <stdint.h>

namespace sp {

// Opcodes labelled "UNGEN" cannot be generated by the compiler. Quite a few,
// if they could, make little sense in the context of a JIT and could not
// work anyway. Opcodes technically present in sc4.c/sc7.c (respectively,
// the code emitter and peephole optimizer) are not necessarily ever generated.
// For example, lref.pri and lref.alt would be used if a reference could be
// stored in the global scope; but they can't, so they are unreachable.
//
// Most opcodes have been manually verified. A few have not, as they are only
// produced by the peephole optimizer, or not produced at all, or eliminated
// during optimization. We generate them anyway, just in case, but they have
// not been tested.
//    lref.s.alt (phopt only)
//    stor.alt (never)
//    stor.s.alt (never)
//    sref.s.alt (never)
//    lidx.b (phopt only, probably impossible)
//    idxaddr.b (phopt only, looks difficult)
//    move.pri (eliminated in phopt)
//    shl.c.pri (eliminated in phopt)
//    shl.c.alt (eliminated in phopt)
//    shr.c.pri (eliminated in phopt)
//    shr.c.alt (eliminated in phopt)
//    eq.c.alt (never)
//    inc.alt (never)
//    dec.alt (never)
//    sdiv (never)
//    nop (never in function bodies)
//
// Additionally, some opcodes which were supported in the earlier JIT are no
// longer supported because of the above:
//    lref.pri/alt
//    sref.pri/alt
//    sign.pri/alt
//
// _G - generated, _U - ungenerated
#define OPCODE_LIST(_G, _U)            \
  _G(NONE,           "none")           \
  _G(LOAD_PRI,       "load.pri")       \
  _G(LOAD_ALT,       "load.alt")       \
  _G(LOAD_S_PRI,     "load.s.pri")     \
  _G(LOAD_S_ALT,     "load.s.alt")     \
  _U(LREF_PRI,       "lref.pri")       \
  _U(LREF_ALT,       "lref.alt")       \
  _G(LREF_S_PRI,     "lref.s.pri")     \
  _G(LREF_S_ALT,     "lref.s.alt")     \
  _G(LOAD_I,         "load.i")         \
  _G(LODB_I,         "lodb.i")         \
  _G(CONST_PRI,      "const.pri")      \
  _G(CONST_ALT,      "const.alt")      \
  _G(ADDR_PRI,       "addr.pri")       \
  _G(ADDR_ALT,       "addr.alt")       \
  _G(STOR_PRI,       "stor.pri")       \
  _G(STOR_ALT,       "stor.alt")       \
  _G(STOR_S_PRI,     "stor.s.pri")     \
  _G(STOR_S_ALT,     "stor.s.alt")     \
  _U(SREF_PRI,       "sref.pri")       \
  _U(SREF_ALT,       "sref.alt")       \
  _G(SREF_S_PRI,     "sref.s.pri")     \
  _G(SREF_S_ALT,     "sref.s.alt")     \
  _G(STOR_I,         "stor.i")         \
  _G(STRB_I,         "strb.i")         \
  _G(LIDX,           "lidx")           \
  _U(LIDX_B,         "lidx.b")         \
  _G(IDXADDR,        "idxaddr")        \
  _U(IDXADDR_B,      "idxaddr.b")      \
  _U(ALIGN_PRI,      "align.pri")      \
  _U(ALIGN_ALT,      "align.alt")      \
  _U(LCTRL,          "lctrl")          \
  _U(SCTRL,          "sctrl")          \
  _G(MOVE_PRI,       "move.pri")       \
  _G(MOVE_ALT,       "move.alt")       \
  _G(XCHG,           "xchg")           \
  _G(PUSH_PRI,       "push.pri")       \
  _G(PUSH_ALT,       "push.alt")       \
  _U(PUSH_R,         "push.r")         \
  _G(PUSH_C,         "push.c")         \
  _G(PUSH,           "push")           \
  _G(PUSH_S,         "push.s")         \
  _G(POP_PRI,        "pop.pri")        \
  _G(POP_ALT,        "pop.alt")        \
  _G(STACK,          "stack")          \
  _G(HEAP,           "heap")           \
  _G(PROC,           "proc")           \
  _U(RET,            "ret")            \
  _G(RETN,           "retn")           \
  _G(CALL,           "call")           \
  _U(CALL_PRI,       "call.pri")       \
  _G(JUMP,           "jump")           \
  _U(JREL,           "jrel")           \
  _G(JZER,           "jzer")           \
  _G(JNZ,            "jnz")            \
  _G(JEQ,            "jeq")            \
  _G(JNEQ,           "jneq")           \
  _U(JLESS,          "jsless")         \
  _U(JLEQ,           "jleq")           \
  _U(JGRTR,          "jgrtr")          \
  _U(JGEQ,           "jgeq")           \
  _G(JSLESS,         "jsless")         \
  _G(JSLEQ,          "jsleq")          \
  _G(JSGRTR,         "jsgrtr")         \
  _G(JSGEQ,          "jsgeq")          \
  _G(SHL,            "shl")            \
  _G(SHR,            "shr")            \
  _G(SSHR,           "sshr")           \
  _G(SHL_C_PRI,      "shl.c.pri")      \
  _G(SHL_C_ALT,      "shl.c.alt")      \
  _U(SHR_C_PRI,      "shr.c.pri")      \
  _U(SHR_C_ALT,      "shr.c.alt")      \
  _G(SMUL,           "smul")           \
  _G(SDIV,           "sdiv")           \
  _G(SDIV_ALT,       "sdiv.alt")       \
  _U(UMUL,           "umul")           \
  _U(UDIV,           "udiv")           \
  _U(UDIV_ALT,       "udiv.alt")       \
  _G(ADD,            "add")            \
  _G(SUB,            "sub")            \
  _G(SUB_ALT,        "sub.alt")        \
  _G(AND,            "and")            \
  _G(OR,             "or")             \
  _G(XOR,            "xor")            \
  _G(NOT,            "not")            \
  _G(NEG,            "neg")            \
  _G(INVERT,         "invert")         \
  _G(ADD_C,          "add.c")          \
  _G(SMUL_C,         "smul.c")         \
  _G(ZERO_PRI,       "zero.pri")       \
  _G(ZERO_ALT,       "zero.alt")       \
  _G(ZERO,           "zero")           \
  _G(ZERO_S,         "zero.s")         \
  _U(SIGN_PRI,       "sign.pri")       \
  _U(SIGN_ALT,       "sign.alt")       \
  _G(EQ,             "eq")             \
  _G(NEQ,            "neq")            \
  _U(LESS,           "less")           \
  _U(LEQ,            "leq")            \
  _U(GRTR,           "grtr")           \
  _U(GEQ,            "geq")            \
  _G(SLESS,          "sless")          \
  _G(SLEQ,           "sleq")           \
  _G(SGRTR,          "sgrtr")          \
  _G(SGEQ,           "sgeq")           \
  _G(EQ_C_PRI,       "eq.c.pri")       \
  _G(EQ_C_ALT,       "eq.c.alt")       \
  _G(INC_PRI,        "inc.pri")        \
  _G(INC_ALT,        "inc.alt")        \
  _G(INC,            "inc")            \
  _G(INC_S,          "inc.s")          \
  _G(INC_I,          "inc.i")          \
  _G(DEC_PRI,        "dec.pri")        \
  _G(DEC_ALT,        "dec.alt")        \
  _G(DEC,            "dec")            \
  _G(DEC_S,          "dec.s")          \
  _G(DEC_I,          "dec.i")          \
  _G(MOVS,           "movs")           \
  _U(CMPS,           "cmps")           \
  _G(FILL,           "fill")           \
  _G(HALT,           "halt")           \
  _G(BOUNDS,         "bounds")         \
  _U(SYSREQ_PRI,     "sysreq.pri")     \
  _G(SYSREQ_C,       "sysreq.c")       \
  _U(FILE,           "file")           \
  _U(LINE,           "line")           \
  _U(SYMBOL,         "symbol")         \
  _U(SRANGE,         "srange")         \
  _U(JUMP_PRI,       "jump.pri")       \
  _G(SWITCH,         "switch")         \
  _G(CASETBL,        "casetbl")        \
  _G(SWAP_PRI,       "swap.pri")       \
  _G(SWAP_ALT,       "swap.alt")       \
  _G(PUSH_ADR,       "push.adr")       \
  _G(NOP,            "nop")            \
  _G(SYSREQ_N,       "sysreq.n")       \
  _U(SYMTAG,         "symtag")         \
  _G(BREAK,          "break")          \
  _G(PUSH2_C,        "push2.c")        \
  _G(PUSH2,          "push2")          \
  _G(PUSH2_S,        "push2.s")        \
  _G(PUSH2_ADR,      "push2.adr")      \
  _G(PUSH3_C,        "push3.c")        \
  _G(PUSH3,          "push3")          \
  _G(PUSH3_S,        "push3.s")        \
  _G(PUSH3_ADR,      "push3.adr")      \
  _G(PUSH4_C,        "push4.c")        \
  _G(PUSH4,          "push4")          \
  _G(PUSH4_S,        "push4.s")        \
  _G(PUSH4_ADR,      "push4.adr")      \
  _G(PUSH5_C,        "push5.c")        \
  _G(PUSH5,          "push5")          \
  _G(PUSH5_S,        "push5.s")        \
  _G(PUSH5_ADR,      "push5.adr")      \
  _G(LOAD_BOTH,      "load.both")      \
  _G(LOAD_S_BOTH,    "load.s.both")    \
  _G(CONST,          "const")          \
  _G(CONST_S,        "const.s")        \
  _U(SYSREQ_D,       "sysreq.d")       \
  _U(SYSREQ_ND,      "sysreq.nd")       \
  _G(TRACKER_PUSH_C, "trk.push.c")     \
  _G(TRACKER_POP_SETHEAP,"trk.pop")    \
  _G(GENARRAY,       "genarray")       \
  _G(GENARRAY_Z,     "genarray.z")     \
  _G(STRADJUST_PRI,  "stradjust.pri")  \
  _U(STKADJUST,      "stackadjust")    \
  _G(ENDPROC,        "endproc")        \
  _U(LDGFN_PRI,      "ldgfn.pri")      \
  _G(FABS,           "fabs")           \
  _G(FLOAT,          "float")          \
  _G(FLOATADD,       "float.add")      \
  _G(FLOATSUB,       "float.sub")      \
  _G(FLOATMUL,       "float.mul")      \
  _G(FLOATDIV,       "float.div")      \
  _G(RND_TO_NEAREST, "round")          \
  _G(RND_TO_FLOOR,   "floor")          \
  _G(RND_TO_CEIL,    "ceil")           \
  _G(RND_TO_ZERO,    "rndtozero")      \
  _G(FLOATCMP,       "float.cmp")      \
  _G(FLOAT_GT,       "float.gt")       \
  _G(FLOAT_GE,       "float.ge")       \
  _G(FLOAT_LT,       "float.lt")       \
  _G(FLOAT_LE,       "float.le")       \
  _G(FLOAT_NE,       "float.ne")       \
  _G(FLOAT_EQ,       "float.eq")       \
  _G(FLOAT_NOT,      "float.not")

enum OPCODE {
#define _G(op, text) OP_##op,
#define _U(op, text) OP_UNGEN_##op,
  OPCODE_LIST(_G, _U)
#undef _G
#undef _U
  OPCODES_LAST
};

#define OPCODES_TOTAL (ucell_t)OPCODES_LAST

} // namespace sp

#endif // _INCLUDE_SPFILE_HEADERS_v1_opcodes_H