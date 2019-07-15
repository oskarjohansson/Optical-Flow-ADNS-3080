/**
 * @file ADNS3080.h
 * @author Oskar Johansson (oskar@irinset.se)
 * @brief A library to control the ADNS3080 Flow Sensor. 
 * @version 0.1
 * @date 2019-06-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef ADNS3080_H
#define ADNS3080_H

#include <SPI.h>

// ADNS3080 hardware config
#define ADNS3080_PIXELS_X               30
#define ADNS3080_PIXELS_Y               30
#define ADNS3080_CLOCK_SPEED            24000000


// Registers for ADNS 3080 OpticalFlow Sensor
#define ADNS3080_PRODUCT_ID                         0x00
#define ADNS3080_REVISION_ID                        0x01
#define ADNS3080_MOTION                             0x02
#define ADNS3080_DELTA_X                            0x03
#define ADNS3080_DELTA_Y                            0x04
#define ADNS3080_SQUAL                              0x05
#define ADNS3080_PIXEL_SUM                          0x06
#define ADNS3080_MAXIMUM_PIXEL                      0x07
#define ADNS3080_CONFIGURATION_BITS                 0x0a
#define ADNS3080_EXTENDED_CONFIG                    0x0b
#define ADNS3080_DATA_OUT_LOWER                     0x0c
#define ADNS3080_DATA_OUT_UPPER                     0x0d
#define ADNS3080_SHUTTER_LOWER                      0x0e
#define ADNS3080_SHUTTER_UPPER                      0x0f
#define ADNS3080_FRAME_PERIOD_LOWER                 0x10
#define ADNS3080_FRAME_PERIOD_UPPER                 0x11
#define ADNS3080_MOTION_CLEAR                       0x12
#define ADNS3080_FRAME_CAPTURE                      0x13
#define ADNS3080_SROM_ENABLE                        0x14
#define ADNS3080_FRAME_PERIOD_MAX_BOUND_LOWER       0x19
#define ADNS3080_FRAME_PERIOD_MAX_BOUND_UPPER       0x1a
#define ADNS3080_FRAME_PERIOD_MIN_BOUND_LOWER       0x1b
#define ADNS3080_FRAME_PERIOD_MIN_BOUND_UPPER       0x1c
#define ADNS3080_SHUTTER_MAX_BOUND_LOWER            0x1e
#define ADNS3080_SHUTTER_MAX_BOUND_UPPER            0x1e
#define ADNS3080_SROM_ID                            0x1f
#define ADNS3080_OBSERVATION                        0x3d
#define ADNS3080_INVERSE_PRODUCT_ID                 0x3f
#define ADNS3080_PIXEL_BURST                        0x40
#define ADNS3080_MOTION_BURST                       0x50
#define ADNS3080_SROM_LOAD                          0x60


class ADNS3080 {
    public:
        /**
         * @brief Construct a new ADNS3080 object
         */
        ADNS3080();
        /**
         * @brief Construct a new ANDS3080 object
         * 
         * @param fps - sets the targeted frame rate
         * @param pinLed - pin for controlling LED 
         * @param res - Resolution in A x A matrix
         */
        ADNS3080(int pinSS, int pinReset);

        void begin();
      

        /**
         * @brief Get the last frame but with less bit-depth. 
         * 
         */
        void getLastFrame(byte *pdata); 
        


    private: 
    int _pinSS, _pinReset; 

        uint8_t readRegister(uint8_t adress);
        void writeRegister(uint8_t adress, uint8_t data);

        void delaySystem();

        void reset(); 

        void takePicture();

        void setFramerate(int fps);
        void setResolution(int res);

};
#endif