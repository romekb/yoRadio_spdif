/**
 * @file AXS15231B_Touch.cpp
 * @brief Драйвер для сенсорного экрана AXS15231B
 * @author W76W
 * @version 1.0
 * @date 2024
 * 
 * Реализация драйвера для работы с сенсорным экраном AXS15231B
 * Поддерживает:
 * - Чтение координат касания
 * - Настройку разрешения экрана
 * - Поворот координат
 * - Мультитач (до 2 одновременных касаний)
 * - Определение жестов двумя пальцами
 */

#include "AXS15231B_Touch.h"

// I2C адрес сенсорного экрана
#define AXS15231B_I2C_ADDR 0x3B

/**
 * @brief Конструктор класса AXS15231B_Touch
 * @param _sda Пин для линии SDA I2C
 * @param _scl Пин для линии SCL I2C
 * @param _int Пин прерывания
 * @param _rst Пин сброса (опционально)
 * @param _width Ширина экрана
 * @param _height Высота экрана
 */
AXS15231B_Touch::AXS15231B_Touch(int8_t _sda, int8_t _scl, int8_t _int, int8_t _rst, uint16_t _width, uint16_t _height)
  : pinSda(_sda), pinScl(_scl), pinInt(_int), pinRst(_rst), width(_width), height(_height), rotation(0) {}

/**
 * @brief Инициализация сенсорного экрана
 * Настраивает I2C интерфейс и пины управления
 */
void AXS15231B_Touch::begin() {
  Wire.begin(pinSda, pinScl);
}

/**
 * @brief Установка поворота координат
 * @param rot Угол поворота (0, 90, 180, 270 градусов)
 */
void AXS15231B_Touch::setRotation(uint8_t rot) {
  rotation = rot;
}

/**
 * @brief Установка разрешения экрана
 * @param _width Ширина экрана
 * @param _height Высота экрана
 */
void AXS15231B_Touch::setResolution(uint16_t _width, uint16_t _height) {
  width = _width;
  height = _height;
}

/**
 * @brief Чтение данных с сенсорного экрана
 * Считывает координаты касания через I2C интерфейс
 * Обрабатывает сырые данные и преобразует их в координаты экрана
 * Поддерживает определение до 2 одновременных касаний
 * Используется для реализации жестов двумя пальцами
 */
void AXS15231B_Touch::read() {
  // Буфер для чтения данных с сенсора
  uint8_t data[AXS_MAX_TOUCH_NUMBER * 6 + 2] = {0};
  
  // Команда чтения данных с сенсора
  const uint8_t read_cmd[11] = {
    0xb5, 0xab, 0xa5, 0x5a, 0x00, 0x00,
    (uint8_t)((AXS_MAX_TOUCH_NUMBER * 6 + 2) >> 8),
    (uint8_t)((AXS_MAX_TOUCH_NUMBER * 6 + 2) & 0xff),
    0x00, 0x00, 0x00
  };
  isTouched = false;
  touches = 0;

  // Отправка команды чтения
  Wire.beginTransmission(AXS15231B_I2C_ADDR);
  Wire.write(read_cmd, sizeof(read_cmd));
  if (Wire.endTransmission() != 0) return;
  // Запрос данных с сенсора
  if (Wire.requestFrom(AXS15231B_I2C_ADDR, (uint8_t)sizeof(data)) != sizeof(data)) return;
  // Чтение данных
  for (int i = 0; i < (int)sizeof(data); i++) data[i] = Wire.read();

  touches = data[1];
  if (touches > 0 && touches <= AXS_MAX_TOUCH_NUMBER) {
    isTouched = true;
    if(!_getPoint(0, data+2)) touches = 0;
    if (touches > 1) {
      if(!_getPoint(1, data+8)) touches = 0;
    }
    if(touches == 0) isTouched = false;
  } else touches = 0;
} 

bool AXS15231B_Touch::_getPoint(uint8_t pointnum, uint8_t *data) {
    uint16_t rawX = ((data[0] & 0x0F) << 8) | data[1];
    uint16_t rawY = ((data[2] & 0x0F) << 8) | data[3];
    uint8_t event = data[0]>>4;
    //Serial.printf("%02x %02x %02x\r\n", event, data[4], data[5]);
    if(event != 0x04 && event != 0x08) return false;
    if (rawX >= 320 || rawY >= 480) return false;
    uint16_t tmp=rawX;
    switch(rotation) {
      case 1: rawX=rawY; rawY=tmp; break;
      case 2: rawX = width-rawX; rawY=height-rawY; break;
      case 3: rawX=width-rawY; rawY=height-tmp; break;
      default: break;
    }
    points[pointnum] = TP_Point(pointnum, rawX, rawY, 0);
    return true;
}