add_executable( except src/main.cc )
target_compile_definitions( except PUBLIC -DVERBOSE)
target_compile_options( except PUBLIC -O -Wall -Wextra -Wpedantic)

add_executable( vector src/vectors.cc )
target_compile_definitions( vector PUBLIC -DVERBOSE)
target_compile_options( vector PUBLIC -O -Wall -Wextra -Wpedantic)