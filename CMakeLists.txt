cmake_minimum_required(VERSION 3.17)
project(portable_ed25519 C)

set(CMAKE_C_STANDARD 11)
include_directories(src)

add_executable(portable_ed25519 test.c src/seed.c src/sha512.c src/add_scalar.c src/fe.c src/ge.c src/sc.c src/sign.c src/verify.c src/keypair.c src/key_exchange.c)