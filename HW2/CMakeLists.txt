cmake_minimum_required(VERSION 3.13)
project(AP)
cmake_policy(SET CMP0144 NEW)
set(CMAKE_CXX_STANDARD 20)

set(OPENSSL_ROOT_DIR "C:\\Program Files (x86)\\OpenSSL-Win64")
set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
set(OPENSSL_CRYPTO_LIBRARY "${OPENSSL_ROOT_DIR}/lib/libcrypto.lib")
set(OPENSSL_SSL_LIBRARY "${OPENSSL_ROOT_DIR}/lib/libssl.lib")
set(GTEST_ROOT "C:\\Program Files (x86)\\googletest-distribution\\lib\\cmake\\GTest")


find_package(OpenSSL REQUIRED)
find_package(GTest REQUIRED)

include_directories(include/)

add_executable(main
        src/main.cpp
        src/server.cpp
        src/client.cpp
        src/crypto.cpp
        src/unit_test.cpp
)
target_link_libraries(main
        OpenSSL::SSL
        GTest::GTest
        GTest::Main
)