add_executable(run_tests tests.c)

target_include_directories(run_tests PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(run_tests PRIVATE unity)

if(PICO_BUILD)
  target_link_libraries(run_tests PRIVATE pico_stdlib hardware_adc)
  pico_add_extra_outputs(run_tests)
endif()

add_test(NAME hardware_tests COMMAND run_tests)
