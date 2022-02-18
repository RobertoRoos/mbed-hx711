/*
 *  HX711 Library for HX711 load cell amplifier
 *
 *
 *  Copyright (C) Anthony Hinsinger
 *                Inspired from https://github.com/bogde/HX711
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furbished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _HX711_H_
#define _HX711_H_

#include "mbed.h"

/** 
 * Read HX711 load cell amplifier data
 * 
 * Original library was made for Arduino and posted at:
 * https://github.com/bogde/HX711
 * 
 * It was forked into https://github.com/atoy40/mbed-hx711 and adapted
 * for MBED.
 *
 * Example:
 * @code
 * #include "mbed.h"
 * #include "HX711.h"
 *
 * HX711 loadcell(D7, D6);
 *
 * int main(void) {
 *   while(1) {
 *       loadcell.powerUp();
 *       printf("Weight = %.1f\r\n", loadcell.getUnits(10));
 *       loadcell.powerDown();
 *
 *       wait(3);
 *   }
 * }
 * @endcode
 */
class HX711 {

public:

    /**
     * @brief Construct a new HX711 object
     * 
     * @param pinData Pin for data
     * @param pinSck  Pin for clock
     * @param gain    Gain of the amplifier (see `setGain`)
     */
    HX711(PinName pin_data, PinName pin_sck, uint8_t gain = 128);

    /**
     * @brief Return true when device is ready to communicate
     * 
     * @return true 
     * @return false 
     */
    bool isReady();

    /**
     * @brief Perform a single read on the sensor (raw output)
     * 
     * @return int 
     */
    int read(void);

    /**
     * @brief Wait until the sensor is ready
     * 
     * @param delay_ms Time in ms to wait between checking
     */
    void waitReady(int delay_ms = 0);

    /**
     * @brief Repeatedly wait for the sensor to be ready
     * 
     * @param retries   Number of tries before giving up
     * @param delay_ms  Millisecond wait between tries
     * @return          True if device is ready at
     */
    bool waitReadyRetry(int retries = 5, int delay_ms = 0);

    /**
     * @brief Perform multiple reads and take the average
     * 
     * @param times Number of reads to perform
     * @return int  See `read()`
     */
    int readAverage(uint8_t times = 10);

    /**
     * @brief Update the internal offset
     * 
     * @param offset 
     */
    void setOffset(int offset);

    /**
     * @brief Update the internal scale - Output = buffer / scale
     * 
     * @param scale 
     */
    void setScale(float scale);

    /**
     * @brief Perform an average-read and adjust for offset and scale
     * 
     * @param times 
     * @return float 
     */
    float getUnits(uint8_t times = 1);

    /**
     * @brief Set the amplifier gain (choose: 128, 64, 32)
     * 
     * @param gain 
     */
    void setGain(uint8_t gain);

    /**
     * @brief Set device in low-power mode
     */
    void powerDown();

    /**
     * @brief Boot device out of low-power mode
     */
    void powerUp();

    /**
     * @brief Perform an average-read and adjust the offset accordingly
     * 
     * @param times 
     */
    void tare(uint8_t times = 10);

private:

    PinName _pin_data;
    PinName _pin_sck;
    
    int _offset;
    float _scale;
    uint8_t _gain;
};

#endif
