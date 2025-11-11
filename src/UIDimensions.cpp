#include "UIDimensions.h"

UIDimensions::UIDimensions(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
    : x(x), y(y), width(w), height(h) {}

UIDimensions& UIDimensions::operator=(const UIDimensions& other) {
  this->x = other.x;
  this->y = other.y;
  this->width = other.width;
  this->height = other.height;

  return *this;
}
