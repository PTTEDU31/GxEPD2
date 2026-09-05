#ifndef _GxEPD2_213_CZ04_H_
#define _GxEPD2_213_CZ04_H_

// Driver for the WT0213CZ04 104x212 panel using its custom 2-bit waveform LUT.
#include "../GxEPD2_EPD.h"

class GxEPD2_213_CZ04 : public GxEPD2_EPD
{
public:
    static const uint16_t WIDTH = 104;
    static const uint16_t WIDTH_VISIBLE = WIDTH;
    static const uint16_t HEIGHT = 212;
    static const GxEPD2::Panel panel = GxEPD2::WT0213CZ04;
    static const bool hasColor = false;
    static const bool hasPartialUpdate = false;
    static const bool hasFastPartialUpdate = false;
    static const uint16_t power_on_time = 100;
    static const uint16_t power_off_time = 100;
    static const uint16_t full_refresh_time = 7500;

    GxEPD2_213_CZ04(int16_t cs, int16_t dc, int16_t rst, int16_t busy);

    void clearScreen(uint8_t value = 0xFF) override;
    void writeScreenBuffer(uint8_t value = 0xFF) override;
    void writeImage(const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h,
                    bool invert = false, bool mirror_y = false, bool pgm = false) override;
    void writeImagePart(const uint8_t bitmap[], int16_t x_part, int16_t y_part,
                        int16_t w_bitmap, int16_t h_bitmap, int16_t x, int16_t y,
                        int16_t w, int16_t h, bool invert = false,
                        bool mirror_y = false, bool pgm = false) override;

    void writeImage(const uint8_t* black, const uint8_t* color, int16_t x, int16_t y,
                    int16_t w, int16_t h, bool invert = false,
                    bool mirror_y = false, bool pgm = false);
    void writeImagePart(const uint8_t* black, const uint8_t* color,
                        int16_t x_part, int16_t y_part, int16_t w_bitmap,
                        int16_t h_bitmap, int16_t x, int16_t y, int16_t w,
                        int16_t h, bool invert = false, bool mirror_y = false,
                        bool pgm = false);
    void writeNative(const uint8_t* data1, const uint8_t* data2, int16_t x,
                     int16_t y, int16_t w, int16_t h, bool invert = false,
                     bool mirror_y = false, bool pgm = false);

    void drawImage(const uint8_t bitmap[], int16_t x, int16_t y, int16_t w,
                   int16_t h, bool invert = false, bool mirror_y = false,
                   bool pgm = false);
    void drawImagePart(const uint8_t bitmap[], int16_t x_part, int16_t y_part,
                       int16_t w_bitmap, int16_t h_bitmap, int16_t x, int16_t y,
                       int16_t w, int16_t h, bool invert = false,
                       bool mirror_y = false, bool pgm = false);
    void drawImage(const uint8_t* black, const uint8_t* color, int16_t x,
                   int16_t y, int16_t w, int16_t h, bool invert = false,
                   bool mirror_y = false, bool pgm = false);
    void drawImagePart(const uint8_t* black, const uint8_t* color,
                       int16_t x_part, int16_t y_part, int16_t w_bitmap,
                       int16_t h_bitmap, int16_t x, int16_t y, int16_t w,
                       int16_t h, bool invert = false, bool mirror_y = false,
                       bool pgm = false);
    void drawNative(const uint8_t* data1, const uint8_t* data2, int16_t x,
                    int16_t y, int16_t w, int16_t h, bool invert = false,
                    bool mirror_y = false, bool pgm = false);

    // The CZ04 controller accepts four grey levels packed as four pixels per byte.
    void writeNative4Grey(const uint8_t bitmap[], bool invert = false,
                          bool mirror_y = false, bool pgm = false);
    void drawNative4Grey(const uint8_t bitmap[], bool invert = false,
                         bool mirror_y = false, bool pgm = false);

    void refresh(bool partial_update_mode = false) override;
    void refresh(int16_t x, int16_t y, int16_t w, int16_t h) override;
    void powerOff() override;
    void hibernate() override;

private:
    void _writeMonoImage(const uint8_t bitmap[], int16_t source_x,
                         int16_t source_y, int16_t bitmap_w, int16_t bitmap_h,
                         int16_t x, int16_t y, int16_t w, int16_t h,
                         bool invert, bool mirror_y, bool pgm);
    void _writeExpandedByte(uint8_t value);
    static uint8_t _readByte(const uint8_t* address, bool pgm);
    void _InitFull();
    void _InitDisplay();
    void _LoadLuts();
    void _PowerOn();
    void _PowerOff();

    static const uint8_t bw_to_grey[16];
    static const uint8_t lut_20_vcom0[15];
    static const uint8_t lut_21_w[15];
    static const uint8_t lut_22_b[15];
    static const uint8_t lut_23_g1[15];
    static const uint8_t lut_24_g2[15];
    static const uint8_t lut_25_vcom1[15];
    static const uint8_t lut_26_red0[15];
    static const uint8_t lut_27_red1[15];
};

#endif
