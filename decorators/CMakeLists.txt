set( SRCS 
  src/main.cc
)

add_executable( decorators ${SRCS} )
target_compile_definitions( decorators PUBLIC -DVERBOSE)
target_compile_options( decorators PUBLIC -O -Wall -Wextra -Wpedantic)