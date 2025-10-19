#ifndef AXS15231B_TOUCH_H
#define AXS15231B_TOUCH_H

#include "Arduino.h"
#include <Wire.h>
// Максимальное количество одновременных касаний
#define AXS_MAX_TOUCH_NUMBER 1  // only single touch

class TP_Point {
  public:
    TP_Point(void) : id(0), x(0), y(0), size(0) {}
    TP_Point(uint8_t id, uint16_t x, uint16_t y, uint16_t size) : id(id), x(x), y(y), size(size) {}
    bool operator==(TP_Point p) { return (x == p.x && y == p.y && id == p.id); }
    bool operator!=(TP_Point p) { return !(*this == p); }
    uint8_t id;
    uint16_t x;
    uint16_t y;
    uint8_t size;
};

class AXS15231B_Touch {
  public:
    AXS15231B_Touch(int8_t _sda, int8_t _scl, int8_t _int, int8_t _rst, uint16_t _width, uint16_t _height);
    void begin();
    void setRotation(uint8_t rot);
    void setResolution(uint16_t _width, uint16_t _height);
    void read();
    uint8_t touches = 0;
    bool isTouched = false;
    TP_Point points[AXS_MAX_TOUCH_NUMBER];
  private:
    bool _getPoint(uint8_t pointnum, uint8_t *data);
    uint8_t pinSda;
    uint8_t pinScl;
    uint8_t pinInt;
    int8_t pinRst;
    uint16_t width;
    uint16_t height;
    uint8_t rotation = 0;
};

#endif // AXS15231B_TOUCH_H 