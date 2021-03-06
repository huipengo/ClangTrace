//
//  wb-trace-pc-guard-cb.h
//  ClangTrace
//
//  Created by penghui8 on 2020/4/28.
//  Copyright © 2020 penghui8. All rights reserved.
//

#ifndef wb_trace_pc_guard_cb_h
#define wb_trace_pc_guard_cb_h

#include <stdio.h>
#import <libkern/OSAtomic.h>

//定义符号结构体
typedef struct {
    void *pc;
    void *next;
} SymbolNode;

// This callback is inserted by the compiler as a module constructor
// into every DSO. 'start' and 'stop' correspond to the
// beginning and end of the section with the guards for the entire
// binary (executable or DSO). The callback will be called at least
// once per DSO and may be called multiple times with the same parameters.
void __sanitizer_cov_trace_pc_guard_init(uint32_t *start,
                                         uint32_t *stop);

// This callback is inserted by the compiler on every edge in the
// control flow (some optimizations apply).
// Typically, the compiler will emit the code like this:
//    if(*guard)
//      __sanitizer_cov_trace_pc_guard(guard);
// But for large functions it will emit a simple call:
//    __sanitizer_cov_trace_pc_guard(guard);
void __sanitizer_cov_trace_pc_guard(uint32_t *guard);

#endif /* wb_trace_pc_guard_cb_h */
