#ifndef PTR_UTILS_H
#define PTR_UTILS_H

// Some utilities when working on pointers

#define NULL ((void*)0)
#define PROPAGATE_NULL(val) if( (val)==NULL ) return NULL; else {};
#define ABORT_ON_NULL(val) if( (val)==NULL ) return; else {};

#endif
