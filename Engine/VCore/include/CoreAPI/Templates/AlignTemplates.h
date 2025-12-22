#pragma once
#include <CoreAPI/Templates/IntegralTemplates.h>
#include <CoreAPI/Templates/PointerTemplates.h>

#include <Reflection/VMacros.h>

/*----------------------------------------------------------------------------
    Align Templates
----------------------------------------------------------------------------*/

/* Array Of Binary
 * 1 = 0000 0001
 * 2 = 0000 0010
 * 3 = 0000 0011
 * 4 = 0000 0100

 * 5 = 0000 0101
 * 6 = 0000 0110
 * 7 = 0000 0111
 * 8 = 0000 1000
 
 * 9 = 0000 1001
 * 10 = 0000 1010
 * 11 = 0000 1011
 * 12 = 0000 1100
 
 * 13 = 0000 1101
 * 14 = 0000 1110
 * 15 = 0000 1111
 * 16 = 0001 0000

 * 17 = 0001 0001
 * 18 = 0001 0010
 * 19 = 0001 0011
 * 20 = 0001 0100
 */

template<typename T>
FORCEINLINE constexpr T Align(T Value, uint64 Alignment) {
    static_assert(TIsIntegral<T>::Value || TIsPointer<T>::Value, "Align expects an integer or pointer type");

    // Explain calcul :
    // Example : Value = 13 , Alignment = 8
    // Value + Alignment - 1 = 13 + 8 - 1 = 20
    // ~(Alignment - 1) = ~(8 - 1) = ~7 = 0000 0111 (in binary) = (inverse) (1111 1000) (in binary)
    // 20 & 1111 1000
    // 0001 0100 & 1111 1000
    // 0001 0000 = 16
    return (Value + Alignment - 1) & ~(Alignment - 1);
}