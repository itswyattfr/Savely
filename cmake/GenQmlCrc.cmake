set(QML_FOLDER_PATH "${CMAKE_SOURCE_DIR}/qml")
set(OUTPUT_QRC_PATH "${CMAKE_SOURCE_DIR}/qml.qrc")

file(GLOB_RECURSE QML_FILES
    "${QML_FOLDER_PATH}/*.qml"
    "${QML_FOLDER_PATH}/*.qml.ui"
)


set(QRC_CONTENT "<!DOCTYPE RCC>\n<RCC version=\"1.0\">\n    <qresource prefix=\"/\">\n")

foreach(filepath IN LISTS QML_FILES)
    file(RELATIVE_PATH relativePath "${QML_FOLDER_PATH}" "${filepath}")
    set(QRC_CONTENT "${QRC_CONTENT}        <file>qml/${relativePath}</file>\n")
endforeach()

set(QRC_CONTENT "${QRC_CONTENT}    </qresource>\n</RCC>\n")

file(WRITE "${OUTPUT_QRC_PATH}" "${QRC_CONTENT}")
message(STATUS "Generated QML resource file: ${OUTPUT_QRC_PATH}")