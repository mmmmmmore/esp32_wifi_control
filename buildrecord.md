-- ESP-TEE is currently supported only on the esp32c6;esp32h2;esp32c5 SoCs
-- Project sdkconfig file /Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/sdkconfig
-- Compiler supported targets: xtensa-esp-elf
-- App "esp32_wifi_control" version: 2.0.1
Traceback (most recent call last):
  File "/Users/maochun/esp32prj/esp-idf/components/partition_table/gen_esp32part.py", line 227, in from_csv
    res.append(PartitionDefinition.from_csv(line, line_no + 1))
               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^
  File "/Users/maochun/esp32prj/esp-idf/components/partition_table/gen_esp32part.py", line 468, in from_csv
    raise InputError("CSV flag column contains unknown flag '%s'" % (flag))
gen_esp32part.InputError: CSV flag column contains unknown flag '# 1.75MB'