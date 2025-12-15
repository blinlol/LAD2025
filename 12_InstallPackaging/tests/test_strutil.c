#include <check.h>
#include <string.h>

#include "strutil.h"

START_TEST(test_lower_to_upper)
{
	char buf[] = "abc";
	str_to_upper(buf);
	ck_assert_str_eq(buf, "ABC");
}
END_TEST

START_TEST(test_mixed_digits)
{
	char buf[] = "Abc123";
	str_to_upper(buf);
	ck_assert_str_eq(buf, "ABC123");
}
END_TEST

START_TEST(test_empty_string)
{
	char buf[] = "";
	str_to_upper(buf);
	ck_assert_str_eq(buf, "");
}
END_TEST

Suite *strutil_suite(void)
{
	Suite *s = suite_create("strutil");
	TCase *tc = tcase_create("core");

	tcase_add_test(tc, test_lower_to_upper);
	tcase_add_test(tc, test_mixed_digits);
	tcase_add_test(tc, test_empty_string);
	suite_add_tcase(s, tc);
	return s;
}

int main(void)
{
	int failed = 0;
	Suite *s = strutil_suite();
	SRunner *sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return failed == 0 ? 0 : 1;
}
