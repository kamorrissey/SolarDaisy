# The following variables contains the files used by the different stages of the build process.
set(solar_charlie_16f13115_default_default_XC8_FILE_TYPE_assemble)
set_source_files_properties(${solar_charlie_16f13115_default_default_XC8_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${solar_charlie_16f13115_default_default_XC8_FILE_TYPE_assemble})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(solar_charlie_16f13115_default_default_XC8_FILE_TYPE_assemblePreprocess)
set_source_files_properties(${solar_charlie_16f13115_default_default_XC8_FILE_TYPE_assemblePreprocess} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${solar_charlie_16f13115_default_default_XC8_FILE_TYPE_assemblePreprocess})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(solar_charlie_16f13115_default_default_XC8_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../app.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../battery.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../cplex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../fader.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../fsm.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../jsf8.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../led6_app.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../ledcc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/adc/src/adc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/comparator/src/cmp1.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/dac/src/dac1.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/fvr/src/fvr.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/pwm/src/pwm1.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/system/src/clock.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/system/src/config_bits.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/system/src/interrupt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/system/src/pins.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/system/src/system.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/timer/src/tmr0.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/timer/src/tmr1.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/timer/src/tmr2.c")
set_source_files_properties(${solar_charlie_16f13115_default_default_XC8_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(solar_charlie_16f13115_default_default_XC8_FILE_TYPE_link)
set(solar_charlie_16f13115_default_default_XC8_FILE_TYPE_objcopy_lss)
set(solar_charlie_16f13115_default_image_name "default.elf")
set(solar_charlie_16f13115_default_image_base_name "default")

# The output directory of the final image.
set(solar_charlie_16f13115_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/solar-charlie-16f13115")

# The full path to the final image.
set(solar_charlie_16f13115_default_full_path_to_image ${solar_charlie_16f13115_default_output_dir}/${solar_charlie_16f13115_default_image_name})

# Potential output file extensions
set(output_extensions
    .hex
    .hxl
    .mum
    .o
    .sdb
    .sym
    .cmf)
list(TRANSFORM output_extensions PREPEND "${solar_charlie_16f13115_default_output_dir}/${solar_charlie_16f13115_default_image_base_name}")
