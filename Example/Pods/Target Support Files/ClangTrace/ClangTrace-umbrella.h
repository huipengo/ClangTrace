#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "wb-trace-pc-guard-cb.h"
#import "WBClangTrace.h"

FOUNDATION_EXPORT double ClangTraceVersionNumber;
FOUNDATION_EXPORT const unsigned char ClangTraceVersionString[];

