#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "callbacks.h"

static void test_callback_handler(void *context, void *payload)
{
    function_called();
    check_expected_ptr(context);
    check_expected(payload);
}

static void test_another_callback_handler(void *context, void *payload)
{
    function_called();
    check_expected_ptr(context);
    check_expected(payload);
}

static void test_create_callbacks(void **state)
{
    callbacks_t *cbs = create_callbacks();
    assert_ptr_not_equal(cbs, NULL);
}

static void test_register_invalid_callback(void **state)
{
    assert_false(register_callback_handler(NULL, NULL, NULL));
    callbacks_t *cbs = create_callbacks();
    assert_false(register_callback_handler(cbs, NULL, NULL));
    dispatch_callbacks(NULL, NULL);
}

static void test_register_callbacks(void **state)
{
    callbacks_t *cbs = create_callbacks();

    uint8_t some_context;

    assert_true(register_callback_handler(cbs, test_callback_handler, NULL));
    assert_true(register_callback_handler(cbs, test_callback_handler, &some_context));
    assert_true(register_callback_handler(cbs, test_another_callback_handler, &some_context));

    expect_function_call(test_callback_handler);
    expect_value(test_callback_handler, context, NULL);
    expect_value(test_callback_handler, payload, NULL);
    expect_function_call(test_callback_handler);
    expect_value(test_callback_handler, context, &some_context);
    expect_value(test_callback_handler, payload, NULL);
    expect_function_call(test_another_callback_handler);
    expect_value(test_another_callback_handler, context, &some_context);
    expect_value(test_another_callback_handler, payload, NULL);
    dispatch_callbacks(cbs, NULL);

    uint8_t some_payload;
    expect_function_call(test_callback_handler);
    expect_value(test_callback_handler, context, NULL);
    expect_value(test_callback_handler, payload, &some_payload);
    expect_function_call(test_callback_handler);
    expect_value(test_callback_handler, context, &some_context);
    expect_value(test_callback_handler, payload, &some_payload);
    expect_function_call(test_another_callback_handler);
    expect_value(test_another_callback_handler, context, &some_context);
    expect_value(test_another_callback_handler, payload, &some_payload);
    dispatch_callbacks(cbs, &some_payload);
}

int main(int argc, char **argv)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_callbacks),
        cmocka_unit_test(test_register_invalid_callback),
        cmocka_unit_test(test_register_callbacks),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
