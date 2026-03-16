idf_component_register(
    SRCS
        "object_detector.cpp"
    INCLUDE_DIRS
        "."
    REQUIRES
        esp_http_server json esp_timer espressif__esp-dl espressif__esp_new_jpeg
)

set(DETECTOR_MODEL_FILE "${PROJECT_DIR}/models/yolo11n.espdl")
if(EXISTS "${DETECTOR_MODEL_FILE}")
    target_add_binary_data(${COMPONENT_TARGET} "${DETECTOR_MODEL_FILE}" BINARY)
    target_compile_definitions(${COMPONENT_LIB} PUBLIC OBJECT_DETECTOR_MODEL_EMBEDDED=1)
else()
    target_compile_definitions(${COMPONENT_LIB} PUBLIC OBJECT_DETECTOR_MODEL_EMBEDDED=0)
endif()
