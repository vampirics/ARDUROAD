#pragma once

#include "Arduboy2Ext.h"
#include "Enums.h"


// ---------------------------------------------------------------------------------
// Extract individual digits of a uint8_t
//
template< size_t size >
void extractDigits(uint8_t (&buffer)[size], uint8_t value) {

  for (uint8_t i = 0; i < size; ++i) {
    buffer[i] = value % 10;
    value /= 10;
  }

}

// ---------------------------------------------------------------------------------
// Extract individual digits of a uint16_t
//
template< size_t size >
void extractDigits(uint8_t (&buffer)[size], uint16_t value) {

  for(uint8_t i = 0; i < size; ++i) {
    buffer[i] = value % 10;
    value /= 10;
  }

}

// ---------------------------------------------------------------------------------
// Extract individual digits of a uint32_t
//
template< size_t size >
void extractDigits(uint8_t (&buffer)[size], uint32_t value) {

  for(uint8_t i = 0; i < size; ++i) {
    buffer[i] = value % 10;
    value /= 10;
  }

}

// ---------------------------------------------------------------------------------
// Type traits
//
namespace traits
{
	template< typename T > struct remove_reference { using type = T; };
	template< typename T > struct remove_reference<T&> { using type = T; };
	template< typename T > struct remove_reference<T&&> { using type = T; };
}

// ---------------------------------------------------------------------------------
// Move a value
//
template< typename T >
constexpr typename traits::remove_reference<T>::type&& move(T && value) {

  return static_cast<typename traits::remove_reference<T>::type&&>(value);

}

// ---------------------------------------------------------------------------------
// Swap two values via moving
//
template< typename T >
void swap(T & first, T & second) {

  auto temp = move(first);
  first = move(second);
  second = move(temp);

}

// ---------------------------------------------------------------------------------
// Swap two values via copying
//
template< typename T >
void copySwap(T & first, T & second) {

  auto temp = first;
  first = second;
  second = temp;

}



// enum class CollisionDirection : uint8_t {
//   None = 0,
//   Up = 1,  
//   Down = 2,
//   Left = 4,
//   Right = 8,
// };

// constexpr CollisionDirection operator |(const CollisionDirection &left, const CollisionDirection &right) {
//   return static_cast<CollisionDirection>(static_cast<uint8_t>(left) | static_cast<uint8_t>(right));
// }

// constexpr CollisionDirection operator &(const CollisionDirection &left, const CollisionDirection &right) {
//   return static_cast<CollisionDirection>(static_cast<uint8_t>(left) & static_cast<uint8_t>(right));
// }


// /* -----------------------------------------------------------------------------------------------------------------------------
//  *  Determine on which sides two Rects may have collided.
//  *       
//  *  Note that the returned directions are relative to Rect1.       
//  */
// CollisionDirection collide(Rect rect1, Rect rect2) {

//   CollisionDirection direction = CollisionDirection::None;
 
//   if (!(rect2.x                >= rect1.x + rect1.width  ||
//         rect2.x + rect2.width  <= rect1.x                ||
//         rect2.y                >= rect1.y + rect1.height ||
//         rect2.y + rect2.height <= rect1.y)) {

//     if ((rect1.x < rect2.x) && (rect1.x + rect1.width > rect2.x))    direction = direction | CollisionDirection::Right;     // Rect 2 is to the right of Rect 1?
//     if ((rect2.x < rect1.x) && (rect2.x + rect2.width > rect1.x))    direction = direction | CollisionDirection::Left;      // Rect 2 is to the left of Rect 1?
//     if ((rect2.y < rect1.y) && (rect2.y + rect2.height > rect1.y))   direction = direction | CollisionDirection::Up;        // Rect 2 is above Rect 1?
//     if ((rect1.y < rect2.y) && (rect1.y + rect1.height > rect2.y))   direction = direction | CollisionDirection::Down;      // Rect 2 is below Rect 1?

//   }

//   return direction;

// }


// /* -----------------------------------------------------------------------------------------------------------------------------
//  *  Determine if the Rect1 has collided with Rect2 in the nominated direction.
//  *       
//  *  Note that the direction is relative to Rect1.       
//  */
// bool collide(Rect rect1, Rect rect2, CollisionDirection testDirection) {
  
//   return ((collide(rect1, rect2) & testDirection) == testDirection);
  
// }

