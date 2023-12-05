#ifndef _MATH_VECTOR_H_
#define _MATH_VECTOR_H_

#include <cstddef>
#include <cassert>
#include <initializer_list>
#include <stdexcept>
#include <typeinfo>
#include <iostream>

class MathVector{
public:
    MathVector(size_t size=0) : size_{size}, data_{ size > 0 ? new double[size] : nullptr }, vector_id_{ n_vectors_ } { 
        n_vectors_++;
        #ifdef VERBOSE
        std::cout << "Default Constructor for id=" << vector_id_ << std::endl; 
        #endif // VERBOSE
    };

    MathVector( const std::initializer_list<double>& list ) : size_{list.size()}, data_{ new double[list.size()] }, vector_id_{n_vectors_} { 
        n_vectors_++;
        #ifdef VERBOSE
        std::cout << "Initilizer list Constructor for id=" << vector_id_ << std::endl;
        #endif // VERBOSE
        int i{};
        for( auto el : list ){
            data_[i] = el;
            i++;
        }
    }

    MathVector( const MathVector& other ) : size_{other.size_}, data_{ new double[other.size_] }, vector_id_{n_vectors_} { 
        n_vectors_++;
        #ifdef VERBOSE
        std::cout << "Copy Constructor for id=" << vector_id_ << " from vector with id=" << other.vector_id_ << std::endl;
        #endif // VERBOSE
        for( size_t i = 0; i < size_; ++i ){
            data_[i] = other.data_[i];
        }
    }

    MathVector& operator=( const MathVector& other ){
        #ifdef VERBOSE
        std::cout << "Copy Assignment Operator for id=" << vector_id_ << " from vector with id=" << other.vector_id_ << std::endl;
        #endif // VERBOSE
        if( &other == this ) 
            return *this;
        delete [] data_;
        size_ = other.size_;
        data_ = new double[size_];
        for( size_t i = 0; i < size_; ++i ){
            data_[i] = other.data_[i];
        }
        return *this;
    }

    MathVector( MathVector&& other ) : size_{other.size_}, vector_id_{n_vectors_} { 
        n_vectors_++;
        #ifdef VERBOSE
        std::cout << "Move Constructor for id=" << vector_id_ << " from vector with id=" << other.vector_id_ << std::endl;
        #endif // VERBOSE
        data_ = other.data_;
        other.data_ = nullptr;
        other.size_ = 0;
    }
    
    MathVector& operator=( MathVector&& other ){
        #ifdef VERBOSE
        std::cout << "Move Assignment Operator for id=" << vector_id_ << " from vector with id=" << other.vector_id_ << std::endl;
        #endif // VERBOSE
        if( &other == this ) 
            return *this;
        delete [] data_;
        data_ = other.data_;
        other.data_ = nullptr;
        other.size_ = 0;
        return *this;
    }

    ~MathVector() {
        #ifdef VERBOSE
        std::cout << "Destructor for id=" << vector_id_ << std::endl; 
        #endif // VERBOSE
        delete [] data_;
        n_vectors_--;
    }

    double& operator[]( size_t idx ){ 
        if( idx >= size_ )
            throw std::out_of_range("");
        return data_[idx];
    }

    size_t Size(){ return size_; }

    friend MathVector operator+( const MathVector& first, const MathVector& second ) {
        #ifdef VERBOSE
        std::cout << "Operator+" << std::endl;
        #endif // VERBOSE
        MathVector result(first.size_);
        for( size_t i = 0; i < first.size_; ++i ){
            result.data_[i] = first.data_[i] + second.data_[i];
        }
        return result;
    }

    friend MathVector operator-( const MathVector& first, const MathVector& second  ) {
        assert( first.size_ == second.size_ );
        #ifdef VERBOSE
        std::cout << "Operator-" << std::endl;
        #endif // VERBOSE
        MathVector result(first.size_);
        for( size_t i = 0; i < first.size_; ++i ){
            result.data_[i] = first.data_[i] - second.data_[i];
        }
        return result;
    }

private:
    size_t size_{};
    double* data_{nullptr};
    const size_t vector_id_{};
    static size_t n_vectors_;
};

#endif // _MATH_VECTOR_H_