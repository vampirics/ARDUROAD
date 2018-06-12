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