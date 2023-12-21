add_executable( task1 src/task1.cc )
target_compile_definitions( task1 PUBLIC -DVERBOSE)
target_compile_options( task1 PUBLIC -O -Wall -Wextra -Wpedantic)

add_executable( task2 src/task2.cc )
target_compile_definitions( task2 PUBLIC -DVERBOSE)
target_compile_options( task2 PUBLIC -O -Wall -Wextra -Wpedantic)

add_executable( task3 src/task3.cc )
target_compile_definitions( task3 PUBLIC -DVERBOSE)
target_compile_options( task3 PUBLIC -O -Wall -Wextra -Wpedantic)

add_executable( task4 src/task4.cc )
target_compile_definitions( task4 PUBLIC -DVERBOSE)
target_compile_options( task4 PUBLIC -O -Wall -Wextra -Wpedantic)

add_executable( task5 src/task5.cc )
target_compile_definitions( task5 PUBLIC -DVERBOSE)
target_compile_options( task5 PUBLIC -O -Wall -Wextra -Wpedantic)
