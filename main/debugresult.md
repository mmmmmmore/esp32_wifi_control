
-- Configuring incomplete, errors occurred!
HINT: The component 'esp_jpeg_enc' could not be found. This could be because: component name was misspelled, the component was not added to the build, the component has been moved to the IDF component manager, the component has been removed and refactored into some other component or the component may not be supported by the selected target.
Please look out for component in 'https://components.espressif.com' and add using 'idf.py add-dependency' command.
Refer to the migration guide for more details about moved components.
Refer to the build-system guide for more details about how components are found and included in the build.

Adding "set-target"'s dependency "fullclean" to list of commands with default set of options.
Executing action: fullclean
Build directory '/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/build' not found. Nothing to clean.
Executing action: set-target
Set Target to: esp32s3, new sdkconfig will be created.
Running cmake in directory /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/build
Executing "cmake -G Ninja -DPYTHON_DEPS_CHECKED=1 -DPYTHON=/Users/maochun/.espressif/python_env/idf6.0_py3.13_env/bin/python -DESP_PLATFORM=1 -DIDF_TARGET=esp32s3 -DCCACHE_ENABLE=0 /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control"...
CMake Deprecation Warning at CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


-- Found Git: /usr/bin/git (found version "2.37.1 (Apple Git-137.1)")
CMake Error at /Users/maochun/esp32prj/esp-idf/tools/cmake/project.cmake:472 (message):
  Directory specified in EXTRA_COMPONENT_DIRS doesn't exist:
  /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/fifo
Call Stack (most recent call first):
  /Users/maochun/esp32prj/esp-idf/tools/cmake/project.cmake:574 (__project_init)
  CMakeLists.txt:8 (project)


-- Configuring incomplete, errors occurred!
cmake failed with exit code 1, output of the command is in the /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/build/log/idf_py_stderr_output_2992 and /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/build/log/idf_py_stdout_output_2992