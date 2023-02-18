#include "map/map.hpp"
#include "map/map_iterator.hpp"

int main()
{
    ft::map< int, std::string > madaniMap;

    madaniMap[ 5 ] = "mdni test";
    ft::map< int, std::string >::reverse_iterator madaniMapReverseIterator = madaniMap.rbegin();

    std::cerr   << "madaniit->first = " << madaniMapReverseIterator->first << std::endl;
    return ( 0 );
}