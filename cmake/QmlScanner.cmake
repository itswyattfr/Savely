function(scan_qml_files QML_DIR OUTPUT_QRC)

    file(GLOB_RECURSE QML_FILES 
        "${QML_DIR}/*.qml"
        "${QML_DIR}/*.js"
        "${QML_DIR}/*.mjs"
    )
    
    set(QRC_CONTENT "<!DOCTYPE RCC>\n<RCC version=\"1.0\">\n    <qresource prefix=\"/\">\n")
    foreach(QML_FILE ${QML_FILES})
        file(RELATIVE_PATH REL_PATH "${QML_DIR}" "${QML_FILE}")
        string(APPEND QRC_CONTENT "        <file>qml/${REL_PATH}</file>\n")
    endforeach()
    

    string(APPEND QRC_CONTENT "    </qresource>\n</RCC>\n")
    
    file(WRITE "${OUTPUT_QRC}" "${QRC_CONTENT}")
    
    list(LENGTH QML_FILES QML_COUNT)
    message(STATUS "Added ${QML_COUNT} QML files to ${OUTPUT_QRC}")
endfunction()