#ifndef _COMMON_H_
#define _COMMON_H_
#include <limits.h>
#include <string.h>

#include "getticks.h"
#include "latency.h"
#include "barrier.h"
#include "main_test_loop.h"

#define XSTR(s)                         STR(s)
#define STR(s)                          #s

#if __GNUC__ >= 4 && __GNUC_MINOR__ >= 6
#  define STATIC_ASSERT(a, msg)           _Static_assert ((a), msg);
#else 
#  define STATIC_ASSERT(a, msg)           
#endif

#define STRING_LENGTH						8

typedef intptr_t skey_t;
typedef intptr_t sval_t;

typedef struct strkey_t {
	char key[STRING_LENGTH]; 
} strkey_t;

typedef struct strval_t {
	char val[STRING_LENGTH];
} strval_t;

// static inline char* STR_KEY_MAX() {
// 	char str[] = {CHAR_MIN, '\0'};
// 	return str;
// }

// inline const char* KEY_MIN() {
// 	std::string str = "";
// 	str.push_back(CHAR_MIN);
// 	return str.data();
// }

#define STR_KEY_MIN "0000000"
#define STR_KEY_MAX "9999999"

#define ALT_KEY_MIN						INT64_MIN
#define ALT_KEY_MAX						INT64_MAX

static inline int strkey_compare(strkey_t k1, strkey_t k2) {
	return strcmp(k1.key, k2.key);
}

static inline int strkey_compare_old2(strkey_t k1, strkey_t k2) {

	//TODO write our own strcmp
	if ( strcmp(k1.key, k2.key) == 0) return 0;

	if ( strcmp(k1.key, STR_KEY_MIN) == 0) return -1;
	if ( strcmp(k2.key, STR_KEY_MIN) == 0 ) return +1;

	if ( strcmp(k1.key, STR_KEY_MAX) == 0 ) return +1;
	if ( strcmp(k2.key, STR_KEY_MAX) == 0 ) return -1;

	return strcmp(k1.key, k2.key);
}

static inline int64_t strkey_compare_old(strkey_t k1, strkey_t k2) {
    return *(int64_t *)(k1.key) - *(int64_t *)(k2.key);
}

static inline int64_t strval_compare(strval_t v1, strval_t v2) {
    return *(int64_t *)(v1.val) - *(int64_t *)(v2.val);
}

static inline int64_t char8_to_int64(char c[]) {
	return *(int64_t *)c;
}

static inline void int64_to_char8(char c[], int64_t v) {
	memcpy(c, &v, STRING_LENGTH);
}


#define KEY_MIN                         INT_MIN
#define KEY_MAX                         (INT_MAX - 2)



#define DEFAULT_DURATION                1000
#define DEFAULT_INITIAL                 1024
#define DEFAULT_NB_THREADS              1
#define DEFAULT_RANGE                   (2 * DEFAULT_INITIAL)
#define DEFAULT_UPDATE                  20

#endif	/*  _COMMON_H_ */
