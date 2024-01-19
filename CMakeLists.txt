cmake_minimum_required(VERSION 3.10)
# Запрет компиляции
function(exit_cmake)
  message("Прерывание настройки")
  if(UNIX)
    set(KILL_COMMAND "killall")
    execute_process(COMMAND ${KILL_COMMAND} -9 cmake
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )
  else()
    set(KILL_COMMAND "taskkill")
    execute_process(COMMAND ${KILL_COMMAND} /IM cmake.exe /F
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )
  endif()
endfunction(exit_cmake)

set(PATCH_VERSION "2" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})


project(Homework3 VERSION ${PROJECT_VESRION})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
set(Boost_DEBUG OFF)
if(Boost_FOUND)
    message("Boost is found")
else()
    exit_cmake()
endif()

include(CTest)
enable_testing()

include_directories(src)

add_executable(Homework3 main.cpp)
add_executable(test_version testing_project.cpp)

set_target_properties(Homework3   PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(Homework3
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(test_version
    ${Boost_LIBRARIES}
)

if (MSVC)
    target_compile_options(Homework2 PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )

else ()
    target_compile_options(Homework3 PRIVATE
        -Wall -Wextra -pedantic 
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic 
    )

endif()


set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()
message(STATUS ${PROJECT_VERSION})
add_test(test_version test_version)
include(CPack)
