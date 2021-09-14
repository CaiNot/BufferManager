cmake_minimum_required (VERSION 3.5)

project(BufferManager)

include_directories(include)

file(GLOB_RECURSE BUF_MGR_SRC_FILES src/buf/*)

add_executable (buf_mgr_test test/buf_mgr_test.cpp ${BUF_MGR_SRC_FILES})
