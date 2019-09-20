/*
 *       Created: 19/09/2019 08:10
 * First created: 18/12/2018
 *       License: GPL-3.0
 *      Homepage: [https://github.com/DenPus/dtest.git/#README.md]
 *        Author: Denpus
 *
 * dtest
 * Dtest header file for tested
 *
 */

#pragma once

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

#define PP_NARG(...)                                                           \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...)                                                          \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N(\
          _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
         _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
         _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
         _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
         _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
         _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
         _61, _62, _63, N, ...) N
#define PP_RSEQ_N()                                                            \
         63,62,61,60,                                                          \
         59,58,57,56,55,54,53,52,51,50,                                        \
         49,48,47,46,45,44,43,42,41,40,                                        \
         39,38,37,36,35,34,33,32,31,30,                                        \
         29,28,27,26,25,24,23,22,21,20,                                        \
         19,18,17,16,15,14,13,12,11,10,                                        \
         9,8,7,6,5,4,3,2,1,0

typedef struct {
    char *version;
    char *filename;
    int  fileline;
    void **cases;
    int  ncase;
    int  nassert;
} ts_suite_t;

typedef struct {
    int   line;
    char  *name;
    void  *fn;
    _Bool ok;
    int   id;
    int   nassert;
    int   npass_assert;
    int   nerr_assert;
} ts_case_t;

#define TS_EL(name) \
     ts_el(&TS_EL2(name), test_##name)


static char *tstype_str[7] = {
        "==",
        "!="
};

typedef enum {
    TS_ASSERT_EQ    = 1, // ==
    TS_ASSERT_NE    = 2, // !=
    TS_ASSERT_LT    = 3, // <
    TS_ASSERT_LE    = 4, // <=
    TS_ASSERT_GT    = 5, // >
    TS_ASSERT_GE    = 6, // >=
    TS_ASSERT_TRUE  = 7, // true
    TS_ASSERT_FALSE = 8, // false
}    tsassert_t;

#define TS_ITEM_INFO  "    #%d :%d %s"
#define TS_TPL_FILE        "\n"
#define _TS_TPL_IRES       TS_ITEM_INFO " %22d"
#define TS_TPL_IRES        _TS_TPL_IRES " " TS_TPL_FILE
#define TS_TPL_IERR        _TS_TPL_IRES " \033[31m%22d\033[0m" TS_TPL_FILE
#define _TS_TPL_SRES       TS_ITEM_INFO " %.*s"
#define TS_TPL_SRES        _TS_TPL_SRES " " TS_TPL_FILE
#define TS_TPL_SERR        _TS_TPL_SRES " (\033[31m%s\033[0m)" TS_TPL_FILE

typedef struct {
    int        line;
    tsassert_t tassert;
    clock_t    tm;
    int        id;
    _Bool      ok;
}    tsitem_t;

typedef ts_suite_t *(*ts_suite_fn)(void);

typedef void (Ts_fn)(ts_case_t *el, tsitem_t *item);

#define ENCODE1(x) TS_EL(x)
#define ENCODE2(x, ...) TS_EL(x), ENCODE1(__VA_ARGS__)
#define ENCODE3(x, ...) TS_EL(x), ENCODE2(__VA_ARGS__)
#define ENCODE4(x, ...) TS_EL(x), ENCODE3(__VA_ARGS__)
#define ENCODE5(x, ...) TS_EL(x), ENCODE4(__VA_ARGS__)
#define ENCODE6(x, ...) TS_EL(x), ENCODE5(__VA_ARGS__)
#define ENCODE7(x, ...) TS_EL(x), ENCODE6(__VA_ARGS__)
#define ENCODE8(x, ...) TS_EL(x), ENCODE7(__VA_ARGS__)
#define ENCODE9(x, ...) TS_EL(x), ENCODE8(__VA_ARGS__)
#define ENCODE10(x, ...) TS_EL(x), ENCODE9(__VA_ARGS__)
#define ENCODE(i, ...) ENCODE##i(__VA_ARGS__)
#define LOGG(count, ...) ENCODE(count, __VA_ARGS__)

#define TS_EL2(name) \
     _test_el_##name

#define TS_ASSERT_EQ(name) \
CASE(name) {\
\
}

#define ts_item(assert, expect, res)                                           \
    __COUNTER__;                                                               \
    *item = (tsitem_t){                                                         \
        .line    = __LINE__,                                                   \
        .tassert = assert,                                                     \
        .tm      = clock(),                                                  \
        .id      = el->nassert++,                                             \
    };                                                                          \
    _Generic((expect),                                                         \
    char*:      ts_assert_str,                                               \
    int:        ts_assert_nr_int,                                               \
    float:      ts_assert_fl,                                               \
    double:     ts_assert_dbl,                                               \
    int8_t:     ts_assert_nr_1s,                                                \
    int16_t:    ts_assert_nr_2s                                                 \
)(el, item, expect, res)

#define assert_eq(expect, res) \
    ts_item(TS_ASSERT_EQ, expect, res)

#define assert_ne(expect, res) \
    ts_item(TS_ASSERT_NE, expect, res)

#define assert_lt(expect, res) \
    ts_item(TS_ASSERT_LT, expect, res)

#define assert_le(expect, res) \
    ts_item(TS_ASSERT_LE, expect, res)

#define assert_gt(expect, res) \
    ts_item(TS_ASSERT_GT, expect, res)

#define assert_ge(expect, res) \
    el, ts_item(TS_ASSERT_GE, expect, res)

#define assert_true(res) \
    ts_item(TS_ASSERT_TRUE, 1, res)

#define assert_false(expect, res) \
    el, ts_item(TS_ASSERT_FALSE, expect, res)

/*
 * expect
 */

#define expect_eq(expect, res) \
    ts_item(TS_ASSERT_EQ, expect, res)

#define expect_ne(expect, res) \
    ts_item(TS_ASSERT_NE, expect, res)

#define expect_lt(expect, res) \
    ts_item(TS_ASSERT_LT, expect, res)

#define expect_le(expect, res) \
    ts_item(TS_ASSERT_LE, expect, res)

#define expect_gt(expect, res) \
    ts_item(TS_ASSERT_GT, expect, res)

#define expect_ge(expect, res) \
    el, ts_item(TS_ASSERT_GE, expect, res)


static char *tstime(char *passed, ts_case_t *el, tsitem_t *item) {
    clock_t time    = clock() - item->tm;
    double  elapsed = (double) time / CLOCKS_PER_SEC;

    if (elapsed < 1) {
        sprintf(passed, "%7.3f ms", elapsed * 1e3);
    } else {
        sprintf(passed, "%7.3f s", elapsed);
    }

    return passed;
}

static void tsiteme(_Bool ok, ts_case_t *el, tsitem_t *item) {
    if (ok) {
        el->npass_assert++;
    } else {
        el->nerr_assert++;
    }

    el->ok = ok;
}

inline static ts_case_t *ts_el(ts_case_t *el, Ts_fn *fn) {
    el->fn = fn;

    return el;
}

static void
ts_assert_nr_int(ts_case_t *el, tsitem_t *item, int expect, int res) {
    char  passed[100];

    tstime(passed, el, item);

    _Bool ok = 0;

    switch (item->tassert) {
    case TS_ASSERT_EQ:
        ok = expect == res;

        break;
    case TS_ASSERT_NE:
        ok = expect != res;

        break;
    case TS_ASSERT_LT:
        ok = expect < res;

        break;
    case TS_ASSERT_LE:
        ok = expect <= res;

        break;
    case TS_ASSERT_GT:
        ok = expect > res;

        break;
    case TS_ASSERT_GE:
        ok = expect >= res;

        break;
    case TS_ASSERT_TRUE:
        ok = res == 1;

        break;
    case TS_ASSERT_FALSE:
        ok = res == 0;

        break;
    }

    if (ok) {
        printf(
                TS_TPL_IRES,
                item->id,
                item->line,
                passed,
                res
        );
    } else {
        printf(
                TS_TPL_IERR,
                item->id,
                item->line,
                passed,
                res,
                expect
        );
    }

    tsiteme(ok, el, item);
};

static void
ts_assert_nr_1s(ts_case_t *el, tsitem_t *item, int8_t expect, int8_t res) {
    return ts_assert_nr_int(el, item, expect, res);
}

static void
ts_assert_nr_2s(ts_case_t *el, tsitem_t *item, int16_t expect, int16_t res) {
    return ts_assert_nr_int(el, item, expect, res);
}

static void
ts_assert_dbl(ts_case_t *el, tsitem_t *item, double expect, double res) {
    char  passed[100];

    tstime(passed, el, item);

    _Bool ok = 0;

    switch (item->tassert) {
    case TS_ASSERT_EQ:
        ok = expect == res;

        break;
    case TS_ASSERT_NE:
        ok = expect != res;

        break;
    case TS_ASSERT_LT:
        ok = expect < res;

        break;
    case TS_ASSERT_LE:
        ok = expect <= res;

        break;
    case TS_ASSERT_GT:
        ok = expect > res;

        break;
    case TS_ASSERT_GE:
        ok = expect >= res;

        break;
    case TS_ASSERT_TRUE:
        ok = res == 1;

        break;
    case TS_ASSERT_FALSE:
        ok = res == 0;

        break;
    }

    if (ok) {
        printf(
                TS_ITEM_INFO " res %f" TS_TPL_FILE,
                item->id,
                item->line,
                passed,
                res
        );
    } else {
        printf(
                TS_ITEM_INFO " res %f expect %f" TS_TPL_FILE,
                item->id,
                item->line,
                passed,
                res,
                expect
        );
    }

    tsiteme(ok, el, item);
};

static void
ts_assert_fl(ts_case_t *el, tsitem_t *item, float expect, float res) {
    return ts_assert_dbl(el, item, expect, res);
}

static void
ts_assert_str(ts_case_t *el, tsitem_t *item, char *expect, char *res) {
    char passed[100];

    tstime(passed, el, item);

    _Bool  ok      = 0;
    size_t nexpect = strlen(expect);

    switch (item->tassert) {
    case TS_ASSERT_EQ:
        ok = !strncmp(expect, res, nexpect);

        break;
    case TS_ASSERT_NE:
        ok = expect != res;

        break;
    case TS_ASSERT_LT:
        ok = expect < res;

        break;
    case TS_ASSERT_LE:
        ok = expect <= res;

        break;
    case TS_ASSERT_GT:
        ok = expect > res;

        break;
    case TS_ASSERT_GE:
        ok = expect >= res;

        break;
    case TS_ASSERT_TRUE:
        /*ok = res == 1;*/

        break;
    case TS_ASSERT_FALSE:
        ok = res == 0;

        break;
    }

    if (ok) {
        printf(
                TS_TPL_SRES,
                item->id,
                item->line,
                passed,
                nexpect,
                res
        );
    } else {
        printf(
                TS_TPL_SERR,
                item->id,
                item->line,
                passed,
                nexpect,
                res,
                expect
        );
    }

    tsiteme(ok, el, item);
};

static ts_suite_t *ts_suite_reg(ts_suite_t *suite, ...) {
    va_list   arg;
    ts_case_t *el;

    va_start(arg, suite);

    for (int i = 0; i < suite->ncase; ++i) {
        el = va_arg(arg, ts_case_t * );

        suite->cases[i] = el;
    }

    va_end(arg);

    return suite;
}

/* New suite */

#define SUITE(...)                                                             \
static ts_suite_t suite = {                                                     \
    .version  = "0.1.0.0",                                                   \
    .filename = __FILE__,                                                      \
    .fileline = __LINE__,                                                      \
    .cases    =  (void **)(ts_case_t *[PP_NARG(__VA_ARGS__)]) {0},              \
    .ncase    = PP_NARG(__VA_ARGS__),                                          \
    .nassert  = __COUNTER__                                                    \
};                                                                             \
                                                                               \
ts_suite_t *tssuite(void) {                                                     \
    return ts_suite_reg(&suite, LOGG(PP_NARG(__VA_ARGS__), __VA_ARGS__));     \
}

/* New case */

#define CASE(_name)                                                           \
static ts_case_t _test_el_##_name = {                                          \
    .name = #_name,                                                           \
    .line = __LINE__,                                                         \
};                                                                            \
static void test_##_name(ts_case_t *el, tsitem_t *item)

