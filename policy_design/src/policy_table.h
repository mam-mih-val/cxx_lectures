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

template< typename T, size_t Attr, typename Classifier>
class Table{
public:
    Table() = delete;
    Table( Classifier classifier ) : classifier_( std::move(classifier) ){  };
    Table(TableType<T, Attr> table, Classifier classifier) : table_( std::move(table) ), classifier_(classifier){ 
        for( const auto& row : table_ ){
            classification_.push_back( classifier_( row ) );
        }
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
        classification_.push_back( classifier_( row ) );
    }
    size_t NEntries(){ return table_.size(); }
private:
    TableType<T, Attr> table_{};
    std::vector<size_t> classification_{};
    Classifier classifier_;
};

template< typename T, size_t Attr, typename Classifier>
auto MakeTable( TableType<T, Attr> data, Classifier function ){
    return Table<T, Attr, Classifier>( data, function );
}

#endif // _TABLE_