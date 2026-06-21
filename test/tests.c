#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

void test_function_exists(void) {
  int today = 12;
  TEST_ASSERT_EQUAL_INT_MESSAGE(today, 12, "Assert happened");
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_function_exists);
  return UNITY_END();
}
