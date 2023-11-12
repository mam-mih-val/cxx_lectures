add_executable( run_game src/main.cc src/units.cc src/visualizer.cc src/game.cc )
target_compile_definitions( run_game PUBLIC -DVERBOSE)
target_compile_options( run_game PUBLIC -O -Wall -Wextra -Wpedantic)