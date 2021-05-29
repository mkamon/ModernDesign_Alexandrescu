add_library( commonLib SHARED
            Widgets/ExampleWidgets.cpp
        )
target_include_directories(commonLib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Widgets)
