set( SRC src/main.cc src/math_vector.cc )
add_executable( math ${SRC} )
target_compile_definitions( math PUBLIC -DVERBOSE)
target_compile_options( math PUBLIC -O -Wall -Wextra -Wpedantic)