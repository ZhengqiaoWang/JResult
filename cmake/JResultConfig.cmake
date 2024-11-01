
set(JRESULT_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
string(REGEX REPLACE "\\\\" "/" JRESULT_ROOT_DIR "${JRESULT_ROOT_DIR}/..")
set(JRESULT_INCLUDE_DIR "${JRESULT_ROOT_DIR}/interface")

message(STATUS "JRESULT_ROOT_DIR: ${JRESULT_ROOT_DIR}")
message(STATUS "JRESULT_INCLUDE_DIR: ${JRESULT_INCLUDE_DIR}")

find_path(
    JRESULT_INCLUDE_DIR
    NO_DEFAULT_PATH
)

include_directories(JResult ${JRESULT_INCLUDE_DIR})
