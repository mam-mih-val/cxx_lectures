#include <cstddef>
#include <gtest/gtest.h>
#include <random>
#include <stdexcept>
#include "math_vector.h"

TEST(MathVector, MoveConstructor){
  const size_t vec_size{3};
  std::random_device rnd_dev;
  std::mt19937 rnd_engine{rnd_dev()};
  std::uniform_real_distribution<double> uniform_distribution{0, 1};
  MathVector vec1(vec_size);
  std::vector<double> filled_values{};
  filled_values.reserve(vec_size);
  for( size_t i=0; i<vec_size; i++ ){
    auto num = uniform_distribution( rnd_engine );
    filled_values.push_back(num);
    vec1[i] = num;
  }
  MathVector vec2{ std::move( vec1 ) };
  for( size_t i=0; i<vec_size; ++i ){
    EXPECT_DOUBLE_EQ(vec2[i], filled_values[i]);
  }
}

TEST(MathVector, CopyConstructor){
  const size_t vec_size{3};
  std::random_device rnd_dev;
  std::mt19937 rnd_engine{rnd_dev()};
  std::uniform_real_distribution<double> uniform_distribution{0, 1};
  MathVector vec1(vec_size);
  std::vector<double> filled_values{};
  filled_values.reserve(vec_size);
  for( size_t i=0; i<vec_size; i++ ){
    auto num = uniform_distribution( rnd_engine );
    filled_values.push_back(num);
    vec1[i] = num;
  }
  MathVector vec2{ vec1 };
  for( size_t i=0; i<vec_size; ++i ){
    EXPECT_DOUBLE_EQ(vec1[i], filled_values[i]);
  }
  for( size_t i=0; i<vec_size; ++i ){
    EXPECT_DOUBLE_EQ(vec2[i], filled_values[i]);
  }
}

TEST(MathVector, Sum){
  const size_t vec_size{3};
  std::random_device rnd_dev;
  std::mt19937 rnd_engine{rnd_dev()};
  std::uniform_real_distribution<double> uniform_distribution{0, 1};
  MathVector vec1(vec_size);
  MathVector vec2(vec_size);
  for( size_t i=0; i<vec_size; i++ ){
    vec1[i] = uniform_distribution( rnd_engine );
    vec2[i] = uniform_distribution( rnd_engine );
  }
  auto vec3 = vec1 + vec2;
  for( size_t i=0; i<vec_size; ++i ){
    auto sum = vec1[i] + vec2[i];
    EXPECT_DOUBLE_EQ(vec3[i], sum);
  }
}

TEST(MathVector, Diff){
  const size_t vec_size{3};
  std::random_device rnd_dev;
  std::mt19937 rnd_engine{rnd_dev()};
  std::uniform_real_distribution<double> uniform_distribution{0, 1};
  MathVector vec1(vec_size);
  MathVector vec2(vec_size);
  for( size_t i=0; i<vec_size; i++ ){
    vec1[i] = uniform_distribution( rnd_engine );
    vec2[i] = uniform_distribution( rnd_engine );
  }
  auto vec3 = vec1 - vec2;
  for( size_t i=0; i<vec_size; ++i ){
    auto sum = vec1[i] - vec2[i];
    EXPECT_DOUBLE_EQ(vec3[i], sum);
  }
}

TEST(MathVector, AccessOperator){
  const size_t vec_size{3};
  std::random_device rnd_dev;
  std::mt19937 rnd_engine{rnd_dev()};
  std::uniform_real_distribution<double> uniform_distribution{0, 1};
  MathVector vec1(vec_size);
  for( size_t i=0; i<vec_size; i++ ){
    vec1[i] = uniform_distribution( rnd_engine );
  }
  for( size_t i=0; i<vec_size; i++ ){
    EXPECT_NO_THROW(vec1[i]);
  }
  EXPECT_THROW(vec1[vec_size+1], std::out_of_range);
}


int main(int argc, char** argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}