#include "bit.h"

namespace udsc2::util
{

int popcount(int bitset) noexcept
{
    // This algorithm is optimized for 32 bit.
    // I have no idea how this works. Credit goes to Sean Eron Anderson.
    // http://graphics.stanford.edu/~seander/bithacks.html
    bitset = bitset - ( ( bitset >> 1 ) & 0x55555555 );
    bitset = ( bitset & 0x33333333 ) + ( ( bitset >> 2 ) & 0x33333333 );
    return ( ( bitset + ( bitset >> 4 ) & 0xF0F0F0F ) * 0x1010101 ) >> 24;
}

}
