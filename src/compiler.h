#ifndef NOTEPAD2_COMPILER_H_
#define NOTEPAD2_COMPILER_H_

#if defined(__cplusplus)
#undef NULL
#define NULL	nullptr
#endif

#if (defined(__GNUC__) || defined(__clang__)) && !defined(__cplusplus)
// https://stackoverflow.com/questions/19452971/array-size-macro-that-rejects-pointers
// trigger error for pointer: GCC: void value not ignored as it ought to be. Clang: invalid operands to binary expression.
#define COUNTOF(ar)	_Generic(&(ar), __typeof__((ar)[0]) **: (void)0, default: _countof(ar))
// trigger warning for non-literal string: GCC: division by zero [-Wdiv-by-zero]. Clang: division by zero is undefined [-Wdivision-by-zero].
#if defined(__GNUC__)
#define CSTRLEN(s)	(__builtin_constant_p(s) ? (_countof(s) - 1) : (1 / 0))
#else
// Clang complains when above CSTRLEN() is used in certain macros, such as EDITLEXER_HOLE()
#define CSTRLEN(s)	(COUNTOF(s) - 1)
#endif
#else
// C++ template based version of _countof(), or plain old unsafe version
#define COUNTOF(ar)	_countof(ar)
#define CSTRLEN(s)	(_countof(s) - 1)
#endif

/*
#if defined(__GNUC__) || defined(__clang__)
#define GCC_NO_WARNING_MISSING_BRACES_BEGIN \
	_Pragma("GCC diagnostic push")			\
	_Pragma("GCC diagnostic ignored \"-Wmissing-braces\"")
#define GCC_NO_WARNING_MISSING_BRACES_END	\
	_Pragma("GCC diagnostic pop")
#else
#define GCC_NO_WARNING_MISSING_BRACES_BEGIN
#define GCC_NO_WARNING_MISSING_BRACES_END
#endif
*/

#if defined(__GNUC__) && !defined(__cplusplus)
#if defined(__NO_INLINE__) // O0
#define NP2_inline	static inline
#else
#define NP2_inline	extern inline __attribute__((__gnu_inline__))
#endif
#else
#define NP2_inline	inline
#endif

// force compile C as CPP: /TP for MSVC and clang-cl, -x c++ for GCC and clang
#define NP2_FORCE_COMPILE_C_AS_CPP	0

#if defined(__cplusplus) && !defined(__clang__)
#define NP2_USE_DESIGNATED_INITIALIZER	0
#else
#define NP2_USE_DESIGNATED_INITIALIZER	1
#endif

#endif // NOTEPAD2_COMPILER_H_
