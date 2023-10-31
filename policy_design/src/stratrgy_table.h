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

template< typename T, size_t Attr>
class Table{
public:
    Table( ) = default;
    Table(TableType<T, Attr> table) : table_( std::move(table) ){ };
    Table(const Table&) = default;
    Table(Table&&) = default;
    Table& operator=(const Table&) = default;
    Table& operator=(Table&&) = default;
    ~Table() = default;
    const RowType<T, Attr>& operator[]( size_t idx ) const { return table_.at(idx); }
    void AddRow(RowType<T, Attr> row){ table_.emplace_back( row ); }
    size_t NEntries(){ return table_.size(); }
private:
    TableType<T, Attr> table_{};
};

#endif // _TABLE_