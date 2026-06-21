cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(PICO_BUILD "Build for Pico hardware" ON)

if(PICO_BUILD)
  set(PICO_BOARD pico2_w CACHE STRING "Board type")
  include(pico_sdk_import.cmake)
endif()

project(hello_adc_manual C CXX ASM)

if(PICO_BUILD)
  pico_sdk_init()

  add_executable(hello_adc_manual hello_adc_manual.c)

  pico_enable_stdio_usb(hello_adc_manual 0)

  pico_add_extra_outputs(hello_adc_manual)

  target_link_libraries(hello_adc_manual pico_stdlib hardware_adc)

  add_custom_target(flash
    COMMAND openocd-custom
      -f interface/cmsis-dap.cfg
      -f target/rp2350.cfg
      -c "adapter speed 5000"
      -c "program ${CMAKE_CURRENT_BINARY_DIR}/hello_adc_manual.elf verify reset exit"
    DEPENDS hello_adc_manual
    USES_TERMINAL
  )
endif()

option(BUILD_TESTING "Build tests" ON)
if(BUILD_TESTING)
  add_subdirectory(third_party/unity)
  enable_testing()
  add_subdirectory(test)
endif()
