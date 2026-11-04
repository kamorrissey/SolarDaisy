include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(solar_charlie_16f13115_default_library_list )

set(OUTPUT_SUFFIX elf)
# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(solar_charlie_16f13115_default_default_XC8_FILE_TYPE_assemble)
add_library(solar_charlie_16f13115_default_default_XC8_assemble OBJECT ${solar_charlie_16f13115_default_default_XC8_FILE_TYPE_assemble})
    solar_charlie_16f13115_default_default_XC8_assemble_rule(solar_charlie_16f13115_default_default_XC8_assemble)
    list(APPEND solar_charlie_16f13115_default_library_list "$<TARGET_OBJECTS:solar_charlie_16f13115_default_default_XC8_assemble>")

endif()

# Handle files with suffix S, for group default-XC8
if(solar_charlie_16f13115_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(solar_charlie_16f13115_default_default_XC8_assemblePreprocess OBJECT ${solar_charlie_16f13115_default_default_XC8_FILE_TYPE_assemblePreprocess})
    solar_charlie_16f13115_default_default_XC8_assemblePreprocess_rule(solar_charlie_16f13115_default_default_XC8_assemblePreprocess)
    list(APPEND solar_charlie_16f13115_default_library_list "$<TARGET_OBJECTS:solar_charlie_16f13115_default_default_XC8_assemblePreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC8
if(solar_charlie_16f13115_default_default_XC8_FILE_TYPE_compile)
add_library(solar_charlie_16f13115_default_default_XC8_compile OBJECT ${solar_charlie_16f13115_default_default_XC8_FILE_TYPE_compile})
    solar_charlie_16f13115_default_default_XC8_compile_rule(solar_charlie_16f13115_default_default_XC8_compile)
    list(APPEND solar_charlie_16f13115_default_library_list "$<TARGET_OBJECTS:solar_charlie_16f13115_default_default_XC8_compile>")

endif()

# Handle files with suffix elf, for group default-XC8
if(solar_charlie_16f13115_default_default_XC8_FILE_TYPE_objcopy_lss)
add_library(solar_charlie_16f13115_default_default_XC8_objcopy_lss OBJECT ${solar_charlie_16f13115_default_default_XC8_FILE_TYPE_objcopy_lss})
    solar_charlie_16f13115_default_default_XC8_objcopy_lss_rule(solar_charlie_16f13115_default_default_XC8_objcopy_lss)
    list(APPEND solar_charlie_16f13115_default_library_list "$<TARGET_OBJECTS:solar_charlie_16f13115_default_default_XC8_objcopy_lss>")

endif()


# Main target for this project
add_executable(solar_charlie_16f13115_default_image_PVmkDY9a ${solar_charlie_16f13115_default_library_list})

set_target_properties(solar_charlie_16f13115_default_image_PVmkDY9a PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf"
    ADDITIONAL_CLEAN_FILES "${output_extensions}"
    RUNTIME_OUTPUT_DIRECTORY "${solar_charlie_16f13115_default_output_dir}")
target_link_libraries(solar_charlie_16f13115_default_image_PVmkDY9a PRIVATE ${solar_charlie_16f13115_default_default_XC8_FILE_TYPE_link})
# Add the link options from the rule file.
solar_charlie_16f13115_default_link_rule( solar_charlie_16f13115_default_image_PVmkDY9a)


#Add objcopy steps
solar_charlie_16f13115_default_objcopy_lss_rule(solar_charlie_16f13115_default_image_PVmkDY9a)

