add_executable( game src/main.cc src/units.cc )
target_compile_definitions( game PUBLIC -DVERBOSE)
target_compile_options( game PUBLIC -O -Wall -Wextra -Wpedantic)

add_executable( nvi_game src/nvi_main.cc src/nvi_units.cc )
target_compile_definitions( nvi_game PUBLIC -DVERBOSE)
target_compile_options( nvi_game PUBLIC -O -Wall -Wextra -Wpedantic)