/**
 * @file ADNS3080.cpp
 * @author Oskar Johansson (oskar@irisnet.se)
 * @brief A library to control the ADNS3080 Flow Sensor. 
 * @version 0.1
 * @date 2019-06-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "ADNS3080.H"



ADNS3080::ADNS3080() {
    
}

ADNS3080::ADNS3080(int pinSS, int pinReset) {
    _pinSS = pinSS;
    _pinReset = pinReset;

    // Initialize the sensor

}

void ADNS3080::begin() {
	SPI.begin();
	SPI.setClockDivider(SPI_CLOCK_DIV32);
	SPI.setDataMode(SPI_MODE3);
	SPI.setBitOrder(MSBFIRST);
	pinMode(_pinSS, OUTPUT);
	pinMode(_pinReset, OUTPUT);
	digitalWrite(_pinSS, HIGH);
	digitalWrite(_pinReset, HIGH);
	reset();

	// turn on sensitive mode
	writeRegister(ADNS3080_CONFIGURATION_BITS, 0x19);


}

/**
 * @brief Resets the sensor by pulling reset pin high and then low 
 * 
 */

void ADNS3080::reset() {
	digitalWrite(_pinReset, HIGH);
	delay(1); // reset pulse >10us
	digitalWrite(_pinReset, LOW);
	delay(35); // 35ms from reset to functional
	writeRegister(ADNS3080_CONFIGURATION_BITS, 0x19);
}

void ADNS3080::getLastFrame(byte *pdata) {

    // Take a picture
    writeRegister(ADNS3080_FRAME_CAPTURE, 0x83); 
    

    digitalWrite(_pinSS, LOW);

    SPI.transfer(ADNS3080_PIXEL_BURST);
	  delayMicroseconds(50);

	  byte pix;
	  byte started = 0;
	  size_t count;
	  int timeout = 0;
	  size_t ret = 0;
	  for (count = 0; count < ADNS3080_PIXELS_X * ADNS3080_PIXELS_Y; )
	  {
	    pix = SPI.transfer(0xff);
	    delayMicroseconds(10);
	    if (started == 0)
	    {
	      if (pix & 0x40)
	        started = 1;
	      else
	      {
	        timeout++;
	        if (timeout == 100)
	        {
	          ret = 0;
	          break;
	        }
	      }
	    }
	    if (started == 1)
	    {
	      pdata[count++] = (pix & 0x3f); // scale to normal grayscale byte range
	    }
	  }


    

}


