#include "GxEPD2_213_CZ04.h"

const uint8_t GxEPD2_213_CZ04::bw_to_grey[16] PROGMEM = {
    0x00, 0x03, 0x0C, 0x0F, 0x30, 0x33, 0x3C, 0x3F,
    0xC0, 0xC3, 0xCC, 0xCF, 0xF0, 0xF3, 0xFC, 0xFF};

const uint8_t GxEPD2_213_CZ04::lut_20_vcom0[15] PROGMEM = {
    0x0E, 0x14, 0x01, 0x0A, 0x06, 0x04, 0x0A, 0x0A,
    0x0F, 0x03, 0x03, 0x0C, 0x06, 0x0A, 0x00};
const uint8_t GxEPD2_213_CZ04::lut_21_w[15] PROGMEM = {
    0x0E, 0x14, 0x01, 0x0A, 0x46, 0x04, 0x8A, 0x4A,
    0x0F, 0x83, 0x43, 0x0C, 0x86, 0x0A, 0x04};
const uint8_t GxEPD2_213_CZ04::lut_22_b[15] PROGMEM = {
    0x0E, 0x14, 0x01, 0x8A, 0x06, 0x04, 0x8A, 0x4A,
    0x0F, 0x83, 0x43, 0x0C, 0x06, 0x4A, 0x04};
const uint8_t GxEPD2_213_CZ04::lut_23_g1[15] PROGMEM = {
    0x8E, 0x94, 0x01, 0x8A, 0x06, 0x04, 0x8A, 0x4A,
    0x0F, 0x83, 0x43, 0x0C, 0x06, 0x0A, 0x04};
const uint8_t GxEPD2_213_CZ04::lut_24_g2[15] PROGMEM = {
    0x8E, 0x94, 0x01, 0x8A, 0x86, 0x04, 0x8A, 0x4A,
    0x0F, 0x83, 0x43, 0x0C, 0x86, 0x0A, 0x04};
const uint8_t GxEPD2_213_CZ04::lut_25_vcom1[15] PROGMEM = {
    0x03, 0x1D, 0x00, 0x01, 0x08, 0x00, 0x37, 0x37,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t GxEPD2_213_CZ04::lut_26_red0[15] PROGMEM = {
    0x83, 0x5D, 0x00, 0x81, 0x48, 0x00, 0x77, 0x77,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t GxEPD2_213_CZ04::lut_27_red1[15] PROGMEM = {
    0x03, 0x1D, 0x00, 0x01, 0x08, 0x00, 0x37, 0x37,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

GxEPD2_213_CZ04::GxEPD2_213_CZ04(int16_t cs, int16_t dc, int16_t rst,
                                 int16_t busy)
    : GxEPD2_EPD(cs, dc, rst, busy, LOW, 10000000, WIDTH, HEIGHT, panel,
                 hasColor, hasPartialUpdate, hasFastPartialUpdate)
{
}

void GxEPD2_213_CZ04::clearScreen(uint8_t value)
{
    writeScreenBuffer(value);
    refresh(false);
    powerOff();
}

void GxEPD2_213_CZ04::writeScreenBuffer(uint8_t value)
{
    _InitFull();
    _writeCommand(0x10);
    _startTransfer();
    for (uint32_t i = 0; i < uint32_t(WIDTH) * HEIGHT / 8; ++i)
    {
        _writeExpandedByte(value);
    }
    _endTransfer();
    _initial_write = false;
}

void GxEPD2_213_CZ04::writeImage(const uint8_t bitmap[], int16_t x, int16_t y,
                                 int16_t w, int16_t h, bool invert,
                                 bool mirror_y, bool pgm)
{
    _writeMonoImage(bitmap, 0, 0, w, h, x, y, w, h, invert, mirror_y, pgm);
}

void GxEPD2_213_CZ04::writeImagePart(const uint8_t bitmap[], int16_t x_part,
                                     int16_t y_part, int16_t w_bitmap,
                                     int16_t h_bitmap, int16_t x, int16_t y,
                                     int16_t w, int16_t h, bool invert,
                                     bool mirror_y, bool pgm)
{
    if (!bitmap || w_bitmap <= 0 || h_bitmap <= 0 || w <= 0 || h <= 0) return;
    if (x_part < 0 || y_part < 0 || x_part >= w_bitmap || y_part >= h_bitmap) return;
    if (x_part + w > w_bitmap) w = w_bitmap - x_part;
    if (y_part + h > h_bitmap) h = h_bitmap - y_part;
    _writeMonoImage(bitmap, x_part, y_part, w_bitmap, h_bitmap, x, y, w, h,
                    invert, mirror_y, pgm);
}

void GxEPD2_213_CZ04::writeImage(const uint8_t* black, const uint8_t* color,
                                 int16_t x, int16_t y, int16_t w, int16_t h,
                                 bool invert, bool mirror_y, bool pgm)
{
    (void)color;
    if (black) writeImage(black, x, y, w, h, invert, mirror_y, pgm);
}

void GxEPD2_213_CZ04::writeImagePart(const uint8_t* black,
                                     const uint8_t* color, int16_t x_part,
                                     int16_t y_part, int16_t w_bitmap,
                                     int16_t h_bitmap, int16_t x, int16_t y,
                                     int16_t w, int16_t h, bool invert,
                                     bool mirror_y, bool pgm)
{
    (void)color;
    if (black)
    {
        writeImagePart(black, x_part, y_part, w_bitmap, h_bitmap, x, y, w, h,
                       invert, mirror_y, pgm);
    }
}

void GxEPD2_213_CZ04::writeNative(const uint8_t* data1, const uint8_t* data2,
                                  int16_t x, int16_t y, int16_t w, int16_t h,
                                  bool invert, bool mirror_y, bool pgm)
{
    (void)data2;
    if (data1) writeImage(data1, x, y, w, h, invert, mirror_y, pgm);
}

void GxEPD2_213_CZ04::drawImage(const uint8_t bitmap[], int16_t x, int16_t y,
                                int16_t w, int16_t h, bool invert,
                                bool mirror_y, bool pgm)
{
    writeImage(bitmap, x, y, w, h, invert, mirror_y, pgm);
    refresh(false);
    powerOff();
}

void GxEPD2_213_CZ04::drawImagePart(const uint8_t bitmap[], int16_t x_part,
                                    int16_t y_part, int16_t w_bitmap,
                                    int16_t h_bitmap, int16_t x, int16_t y,
                                    int16_t w, int16_t h, bool invert,
                                    bool mirror_y, bool pgm)
{
    writeImagePart(bitmap, x_part, y_part, w_bitmap, h_bitmap, x, y, w, h,
                   invert, mirror_y, pgm);
    refresh(false);
    powerOff();
}

void GxEPD2_213_CZ04::drawImage(const uint8_t* black, const uint8_t* color,
                                int16_t x, int16_t y, int16_t w, int16_t h,
                                bool invert, bool mirror_y, bool pgm)
{
    writeImage(black, color, x, y, w, h, invert, mirror_y, pgm);
    refresh(false);
    powerOff();
}

void GxEPD2_213_CZ04::drawImagePart(const uint8_t* black,
                                    const uint8_t* color, int16_t x_part,
                                    int16_t y_part, int16_t w_bitmap,
                                    int16_t h_bitmap, int16_t x, int16_t y,
                                    int16_t w, int16_t h, bool invert,
                                    bool mirror_y, bool pgm)
{
    writeImagePart(black, color, x_part, y_part, w_bitmap, h_bitmap, x, y, w,
                   h, invert, mirror_y, pgm);
    refresh(false);
    powerOff();
}

void GxEPD2_213_CZ04::drawNative(const uint8_t* data1, const uint8_t* data2,
                                 int16_t x, int16_t y, int16_t w, int16_t h,
                                 bool invert, bool mirror_y, bool pgm)
{
    writeNative(data1, data2, x, y, w, h, invert, mirror_y, pgm);
    refresh(false);
    powerOff();
}

void GxEPD2_213_CZ04::writeNative4Grey(const uint8_t bitmap[], bool invert,
                                       bool mirror_y, bool pgm)
{
    if (!bitmap) return;
    constexpr uint16_t row_bytes = WIDTH / 4;
    _InitFull();
    _writeCommand(0x10);
    _startTransfer();
    for (uint16_t y = 0; y < HEIGHT; ++y)
    {
        const uint16_t source_y = mirror_y ? HEIGHT - 1 - y : y;
        for (uint16_t x = 0; x < row_bytes; ++x)
        {
            uint8_t value = _readByte(bitmap + uint32_t(source_y) * row_bytes + x, pgm);
            _transfer(invert ? uint8_t(~value) : value);
        }
    }
    _endTransfer();
    _initial_write = false;
}

void GxEPD2_213_CZ04::drawNative4Grey(const uint8_t bitmap[], bool invert,
                                      bool mirror_y, bool pgm)
{
    writeNative4Grey(bitmap, invert, mirror_y, pgm);
    refresh(false);
    powerOff();
}

void GxEPD2_213_CZ04::refresh(bool partial_update_mode)
{
    (void)partial_update_mode;
    _writeCommand(0x12);
    _waitWhileBusy("_Update_Full", full_refresh_time);
    _initial_refresh = false;
}

void GxEPD2_213_CZ04::refresh(int16_t x, int16_t y, int16_t w, int16_t h)
{
    (void)x;
    (void)y;
    (void)w;
    (void)h;
    refresh(false);
}

void GxEPD2_213_CZ04::powerOff()
{
    _PowerOff();
}

void GxEPD2_213_CZ04::hibernate()
{
    _PowerOff();
}

void GxEPD2_213_CZ04::_writeMonoImage(const uint8_t bitmap[],
                                      int16_t source_x, int16_t source_y,
                                      int16_t bitmap_w, int16_t bitmap_h,
                                      int16_t x, int16_t y, int16_t w,
                                      int16_t h, bool invert, bool mirror_y,
                                      bool pgm)
{
    if (!bitmap || bitmap_w <= 0 || bitmap_h <= 0 || w <= 0 || h <= 0) return;

    const int16_t source_row_bytes = (bitmap_w + 7) / 8;
    _InitFull();
    _writeCommand(0x10);
    _startTransfer();

    for (int16_t panel_y = 0; panel_y < int16_t(HEIGHT); ++panel_y)
    {
        for (int16_t byte_x = 0; byte_x < int16_t(WIDTH / 8); ++byte_x)
        {
            uint8_t output = 0xFF;
            for (int16_t bit = 0; bit < 8; ++bit)
            {
                const int16_t panel_x = byte_x * 8 + bit;
                if (panel_x < x || panel_x >= x + w ||
                    panel_y < y || panel_y >= y + h)
                {
                    continue;
                }

                const int16_t bitmap_x = source_x + panel_x - x;
                int16_t bitmap_y = source_y + panel_y - y;
                if (mirror_y) bitmap_y = bitmap_h - 1 - bitmap_y;
                if (bitmap_x < 0 || bitmap_x >= bitmap_w ||
                    bitmap_y < 0 || bitmap_y >= bitmap_h)
                {
                    continue;
                }

                const uint32_t index = uint32_t(bitmap_y) * source_row_bytes + bitmap_x / 8;
                const uint8_t source = _readByte(bitmap + index, pgm);
                bool white = (source & (0x80 >> (bitmap_x % 8))) != 0;
                if (invert) white = !white;
                if (white) output |= 0x80 >> bit;
                else output &= ~(0x80 >> bit);
            }
            _writeExpandedByte(output);
        }
    }

    _endTransfer();
    _initial_write = false;
    delay(1);
}

void GxEPD2_213_CZ04::_writeExpandedByte(uint8_t value)
{
    _transfer(pgm_read_byte(&bw_to_grey[(value >> 4) & 0x0F]));
    _transfer(pgm_read_byte(&bw_to_grey[value & 0x0F]));
}

uint8_t GxEPD2_213_CZ04::_readByte(const uint8_t* address, bool pgm)
{
#if defined(__AVR) || defined(ESP8266) || defined(ESP32)
    if (pgm) return pgm_read_byte(address);
#else
    (void)pgm;
#endif
    return *address;
}

void GxEPD2_213_CZ04::_InitFull()
{
    _InitDisplay();
    _LoadLuts();
    _using_partial_mode = false;
}

void GxEPD2_213_CZ04::_InitDisplay()
{
    // The vendor driver resets before every update after power-off.
    // Keep the controller state intact while assembling paged transfers.
    if (!_power_is_on)
    {
        _reset();
    }

    _writeCommand(0x01);
    _writeData(0x07);
    _writeData(0x00);
    _writeData(0x08);
    _writeData(0x00);

    _writeCommand(0x06);
    _writeData(0x07);
    _writeData(0x07);
    _writeData(0x07);

    _PowerOn();

    _writeCommand(0x00);
    _writeData(0xCF);
    _writeCommand(0x50);
    _writeData(0x37);
    _writeCommand(0x30);
    _writeData(0x39);
    _writeCommand(0x61);
    _writeData(WIDTH);
    _writeData(HEIGHT >> 8);
    _writeData(HEIGHT & 0xFF);
    _writeCommand(0x82);
    _writeData(0x0E);
}

void GxEPD2_213_CZ04::_LoadLuts()
{
    _writeCommand(0x20);
    _writeDataPGM(lut_20_vcom0, sizeof(lut_20_vcom0));
    _writeCommand(0x21);
    _writeDataPGM(lut_21_w, sizeof(lut_21_w));
    _writeCommand(0x22);
    _writeDataPGM(lut_22_b, sizeof(lut_22_b));
    _writeCommand(0x23);
    _writeDataPGM(lut_23_g1, sizeof(lut_23_g1));
    _writeCommand(0x24);
    _writeDataPGM(lut_24_g2, sizeof(lut_24_g2));
    _writeCommand(0x25);
    _writeDataPGM(lut_25_vcom1, sizeof(lut_25_vcom1));
    _writeCommand(0x26);
    _writeDataPGM(lut_26_red0, sizeof(lut_26_red0));
    _writeCommand(0x27);
    _writeDataPGM(lut_27_red1, sizeof(lut_27_red1));
}

void GxEPD2_213_CZ04::_PowerOn()
{
    if (_power_is_on) return;
    _writeCommand(0x04);
    _waitWhileBusy("_PowerOn", power_on_time);
    _power_is_on = true;
}

void GxEPD2_213_CZ04::_PowerOff()
{
    if (!_power_is_on) return;

    _writeCommand(0x50);
    _writeData(0x17);
    _writeCommand(0x82);
    _writeData(0x00);
    _writeCommand(0x01);
    _writeData(0x02);
    _writeData(0x00);
    _writeData(0x00);
    _writeData(0x00);
    delay(1500);
    _writeCommand(0x02);
    _waitWhileBusy("_PowerOff", power_off_time);

    _power_is_on = false;
    _using_partial_mode = false;
}

