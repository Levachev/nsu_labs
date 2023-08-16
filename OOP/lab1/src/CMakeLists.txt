add_executable(BigInt main.cpp)

add_library(BigIntLib BigInt.cpp BigInt.hpp)

target_link_libraries(BigInt PRIVATE BigIntLib)
