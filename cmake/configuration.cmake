function(target_c_standard TARGET C_STD)
  set_target_properties("${TARGET}" PROPERTIES
    C_STANDARD "${C_STD}"
    C_STANDARD_REQUIRED TRUE
  )
endfunction()

function(target_configure_warnings TARGET)
  target_compile_options("${TARGET}" PRIVATE
    -Werror # Treat warnings as errors
    -Wall
    -Wextra # -Wall does not enable all warnings
  )
endfunction()

function(target_output_dir TARGET OUTPUT_DIR)
  set_target_properties("${TARGET}" PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DIR}"
  )
endfunction()

function(target_configure_executable TARGET)
  target_c_standard("${TARGET}" 23)
  target_configure_warnings("${TARGET}")
  target_output_dir("${TARGET}" "bin")
  target_include_directories("${TARGET}" PRIVATE src)
endfunction()
