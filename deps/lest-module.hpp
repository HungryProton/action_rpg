// C++11 - use multiple source files.

#include "lest.hpp"

#define lest_ADD_MODULE( collection, module ) \
    namespace { lest::module_registrar _( collection, module ); }
    
namespace lest {

struct module_registrar
{
    template <std::size_t N>
    module_registrar( lest::tests & collection, test const (&module)[N] )
    {
        collection.insert( collection.end(), std::begin( module ), std::end( module ) );
    }
};

}
