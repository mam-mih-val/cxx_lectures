#ifndef _TABLE_
#define _TABLE_

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cassert>
#include <exception>
#include <initializer_list>
#include <math.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <iostream>
#include <vector>

template< typename T, size_t Attr >
using RowType = std::array<T, Attr>;

template< typename T, size_t Attr >
using TableType = std::vector< RowType<T, Attr> >;

template< typename T, size_t Attr >
class Table{
public:
    Table() = default;
    Table(TableType<T, Attr> table) : table_( std::move(table) ) {
    };
    Table(const Table&) = default;
    Table(Table&&) = default;
    Table& operator=(const Table&) = default;
    Table& operator=(Table&&) = default;
    ~Table() = default;
    const RowType<T, Attr>& operator[]( size_t idx ) const { return table_.at(idx); }
    size_t Classification( size_t idx ) const { return classification_.at(idx); }
    void AddRow(RowType<T, Attr> row){ 
        table_.emplace_back( std::move(row) ); 
        classification_.push_back( Classify( row ) );
    }
    size_t NEntries(){ return table_.size(); }
protected:
    virtual size_t Classify( [[maybe_unused]] const RowType<T, Attr>& row) const { return 0; }
    TableType<T, Attr> table_{};
    std::vector<size_t> classification_{};
};

template< typename T, size_t Attr > 
class MagnitudeClassifier : public Table<T, Attr> {
public:
    MagnitudeClassifier() = default;
    MagnitudeClassifier( TableType<T, Attr> table ) : Table<T, Attr>( table ) {
        for( const auto& row : Table<T, Attr>::table_ ){
            Table<T, Attr>::classification_.push_back( Classify(row) );
        }
    }
    ~MagnitudeClassifier() = default;
private:
    size_t Classify( const RowType<T, Attr>& row ) const override {
        auto mag2 = T{};
        for( auto comp : row ){
            mag2+=comp*comp;
        }
        if( sqrt(mag2) > 5 )
            return 1;
        return 0;
    }
};

#endif // _TABLE_