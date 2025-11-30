#include <check.h>
#include "buf.h"

float *a;
long *ai;

#suite libbuf_unit
#tcase first_tcase

void setup() {
    
}

#test initialization
    ck_assert_int_eq(buf_capacity(a), 0);
    ck_assert_int_eq(buf_size(a), 0);
    buf_push(a, 1.3f);
    ck_assert_int_eq(buf_size(a), 1);
    ck_assert_float_eq(a[0], 1.3f);
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0);
    ck_assert_ptr_ne(a, 0);
    buf_free(a);
    ck_assert_ptr_eq(a, 0);

#test clearing_null_pointer_no_op
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0);
    ck_assert_ptr_eq(a, 0);

#test buf_push
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    ck_assert_int_eq(buf_size(ai), 10000);
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    ck_assert_int_eq(match, 10000);
    buf_free(ai);

#test buf_grow_buf_trunk
    buf_grow(ai, 1000);
    ck_assert_int_eq(buf_capacity(ai), 1000);
    ck_assert_int_eq(buf_size(ai), 0);
    buf_trunc(ai, 100);
    ck_assert_int_eq(buf_capacity(ai), 100);
    buf_free(ai);

#test buf_pop
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    ck_assert_int_eq(buf_size(a), 4);
    ck_assert_float_eq(buf_pop(a), 1.4f);
    buf_trunc(a, 3);
    ck_assert_int_eq(buf_size(a), 3);
    ck_assert_float_eq(buf_pop(a), 1.3f);
    ck_assert_float_eq(buf_pop(a), 1.2f);
    ck_assert_float_eq(buf_pop(a), 1.1f);
    ck_assert_int_eq(buf_size(a), 0);
    buf_free(a);


#main-pre
    tcase_add_checked_fixture(tc1_1, NULL, setup);
