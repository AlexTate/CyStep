#ifndef _STEP_VECTOR_H_
#define _STEP_VECTOR_H_

#include <map>
#include <stdexcept>
#include <climits>
#include <iostream>  //for now only

#include "Python.h"

namespace sparse_vectors {
    template< class T >
    class _StepVector {
      protected:
       std::map< long int, T > m;
       void print_container(T container);
      public:
       static const long int min_index;
       static const long int max_index;
       typedef typename std::map< long int, T >::const_iterator const_iterator;
       _StepVector( );
       const T operator[]( long int i ) const;
       long int num_values( ) const;
       void set_value( long int from, long int to, T value );
       void add_value( long int from, long int to, T value );
       void apply_to_values( long int from, long int to, void (*func)( T & val ) );
       const_iterator get_values( long int from ) const;
       const_iterator begin( ) const;
       const_iterator end( ) const;
    };
}

#endif //_STEP_VECTOR_H_