add_executable( strategy_table src/strategy_main.cc )
target_compile_definitions( strategy_table PUBLIC -DVERBOSE)
target_compile_options( strategy_table PUBLIC -O -Wall -Wextra -Wpedantic)

add_executable( policy_table src/policy_main.cc )
target_compile_definitions( policy_table PUBLIC -DVERBOSE)
target_compile_options( policy_table PUBLIC -O -Wall -Wextra -Wpedantic)

add_executable( polymorphic_table src/polymorphic_main.cc )
target_compile_definitions( polymorphic_table PUBLIC -DVERBOSE)
target_compile_options( polymorphic_table PUBLIC -O -Wall -Wextra -Wpedantic)