//
//  wb-trace-pc-guard-cb.c
//  ClangTrace
//
//  Created by penghui8 on 2020/4/28.
//  Copyright © 2020 penghui8. All rights reserved.
//  https://clang.llvm.org/docs/SanitizerCoverage.html#tracing-pcs

#include "wb-trace-pc-guard-cb.h"
#include <stdlib.h>

//原子队列
OSQueueHead symbolList = OS_ATOMIC_QUEUE_INIT;

// This callback is inserted by the compiler as a module constructor
// into every DSO. 'start' and 'stop' correspond to the
// beginning and end of the section with the guards for the entire
// binary (executable or DSO). The callback will be called at least
// once per DSO and may be called multiple times with the same parameters.
void __sanitizer_cov_trace_pc_guard_init(uint32_t *start,
                                         uint32_t *stop) {
  static uint64_t N;  // Counter for the guards.
  if (start == stop || *start) return;  // Initialize only once.
  printf("INIT: %p %p\n", start, stop);
  for (uint32_t *x = start; x < stop; x++)
    *x = (uint32_t)++N;  // Guards should start from 1.
}

// This callback is inserted by the compiler on every edge in the
// control flow (some optimizations apply).
// Typically, the compiler will emit the code like this:
//    if(*guard)
//      __sanitizer_cov_trace_pc_guard(guard);
// But for large functions it will emit a simple call:
//    __sanitizer_cov_trace_pc_guard(guard);
void __sanitizer_cov_trace_pc_guard(uint32_t *guard) {
  if (!*guard) return;  // Duplicate the guard check.
  // If you set *guard to 0 this code will not be called again for this edge.
  // Now you can get the PC and do whatever you want:
  //   store it somewhere or symbolize it and print right away.
  // The values of `*guard` are as you set them in
  // __sanitizer_cov_trace_pc_guard_init and so you can make them consecutive
  // and use them to dereference an array or a bit vector.
  void *PC = __builtin_return_address(0);
  SymbolNode *node = malloc(sizeof(SymbolNode));
  *node = (SymbolNode){PC, NULL};
  //进入
  OSAtomicEnqueue(&symbolList, node, offsetof(SymbolNode, next));
  /*
  printf("fname:%s \nfbase:%p \nsname:%s \nsaddr:%p\n",
         info.dli_fname,
         info.dli_fbase,
         info.dli_sname,
         info.dli_saddr);
   */
}
