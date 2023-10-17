#ifndef _MATH_VECTOR_H_
#define _MATH_VECTOR_H_

#include <array>
#include <cstddef>
#include <cassert>
#include <exception>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <iostream>

template<typename T, size_t N>
class MathVector{
public:
    MathVector() : data_{ new T[N] } { 
        n_vectors_++;
        #ifdef VERBOSE
        std::cout << "Default Constructor for id=" << vector_id_ << std::endl; 
        #endif // VERBOSE
    };

    MathVector( std::array<T, N> arr ) : data_{ new T[N] } { 
        n_vectors_++;
        #ifdef VERBOSE
        std::cout << "Initilizer list Constructor for id=" << vector_id_ << std::endl;
        #endif // VERBOSE
        for( size_t i=0; i<N; ++i ){
            data_[i] = arr[i];
        }
    }

    MathVector( const MathVector<T, N>& other ) : data_{ new T[N] } { 
        n_vectors_++;
        #ifdef VERBOSE
        std::cout << "Copy Constructor for id=" << vector_id_ << " from vector with id=" << other.vector_id_ << std::endl;
        #endif // VERBOSE
        for( size_t i = 0; i < N; ++i ){
            data_[i] = other.data_[i];
        }
    }

    MathVector& operator=( const MathVector<T, N>& other ){
        #ifdef VERBOSE
        std::cout << "Copy Assignment Operator for id=" << vector_id_ << " from vector with id=" << other.vector_id_ << std::endl;
        #endif // VERBOSE
        if( &other == this ) 
            return *this;
        for( size_t i = 0; i < N; ++i ){
            data_[i] = other.data_[i];
        }
        return *this;
    }

    MathVector( MathVector<T, N>&& other ) : data_{ new T[N]} { 
        n_vectors_++;
        #ifdef VERBOSE
        std::cout << "Move Constructor for id=" << vector_id_ << " from vector with id=" << other.vector_id_ << std::endl;
        #endif // VERBOSE
        std::swap(data_, other.data_);
    }
    
    MathVector& operator=( MathVector<T, N>&& other ){
        #ifdef VERBOSE
        std::cout << "Move Assignment Operator for id=" << vector_id_ << " from vector with id=" << other.vector_id_ << std::endl;
        #endif // VERBOSE
        if( &other == this )
            return *this;
        delete [] data_;
        data_ = new T[N];
        std::swap(data_, other.data_);
        return *this;
    }

    ~MathVector() {
        #ifdef VERBOSE
        std::cout << "Destructor for id=" << vector_id_ << std::endl; 
        #endif // VERBOSE
        delete [] data_;
        n_vectors_--;
    }

    T& operator[]( size_t idx ){ return data_[idx]; }

    constexpr size_t Size() const { return N; }

    friend MathVector<T, N> operator+( const MathVector<T, N>& first, const MathVector<T,N>& second ) {
        #ifdef VERBOSE
        std::cout << "Operator+" << std::endl;
        #endif // VERBOSE
        MathVector<T, N> result{};
        for( size_t i = 0; i < N; ++i ){
            result.data_[i] = first.data_[i] + second.data_[i];
        }
        return result;
    }

    friend MathVector operator-( const MathVector<T,N>& first, const MathVector<T,N>& second  ) {
        assert( first.size_ == second.size_ );
        #ifdef VERBOSE
        std::cout << "Operator-" << std::endl;
        #endif // VERBOSE
        MathVector<T, N> result{};
        for( size_t i = 0; i < N; ++i ){
            result.data_[i] = first.data_[i] - second.data_[i];
        }
        return result;
    }

private:
    T* data_{nullptr};
    static size_t n_vectors_;
    const size_t vector_id_{ n_vectors_ };
};

template<typename T, size_t N>
size_t MathVector<T, N>::n_vectors_ = 0;

#endif // _MATH_VECTOR_H_