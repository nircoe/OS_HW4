if(EXISTS "/home/student/Desktop/OS_HW4/build/tests/malloc_3_test_tests-b12d07c.cmake")
  include("/home/student/Desktop/OS_HW4/build/tests/malloc_3_test_tests-b12d07c.cmake")
else()
  add_test(malloc_3_test_NOT_BUILT-b12d07c malloc_3_test_NOT_BUILT-b12d07c)
endif()
