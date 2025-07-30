#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string>

// Integer aliases
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Floating-point aliases
typedef float     f32;
typedef double    f64;

typedef std::string str;

#define range(NAME, VAL) (u32 NAME = 0; NAME < VAL; NAME++)
