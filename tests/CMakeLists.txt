file(GLOB SRC_FILES ../src/*.cpp)
list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../src/Main.cpp)

set(TEST_NAMES singleRowMoveTest attemptWrongMovesTest getAvailableMovesTest hopMoveTest)

foreach(TARGET ${TEST_NAMES})

    
    add_executable(${TARGET} ${TARGET}.cpp ${SRC_FILES})
    add_test(NAME ${TARGET} COMMAND ${TARGET})
    

    set_target_properties(
        ${TARGET} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
    )
endforeach()
