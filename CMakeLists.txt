cmake_minimum_required(VERSION 3.7)
project(data_struct2019)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        linear/linear_list.cpp linear/linear_list.hpp stack/stack.cpp stack/stack.hpp queue/queue.cpp queue/queue.hpp string/string.cpp string/string.hpp matrix/matrix.cpp matrix/matrix.hpp tree/btree.cpp tree/btree.hpp heap/heap.cpp heap/heap.hpp picture/picture.cpp picture/picture.hpp sort/sort.cpp sort/sort.hpp tree/mfset.cpp tree/mfset.hpp tree/ptree.cpp tree/ptree.hpp search/search.cpp search/search.hpp search/hash.cpp search/hash.hpp)
add_executable(data_struct2019 ${SOURCE_FILES})