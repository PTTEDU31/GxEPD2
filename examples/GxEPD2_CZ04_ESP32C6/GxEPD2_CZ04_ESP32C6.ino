#include <GxEPD2_BW.h>
#include <SPI.h>

static constexpr int EPD_SCK = 9;
static constexpr int EPD_MOSI = 3; // Display SDA.
static constexpr int EPD_RST = 7;
static constexpr int EPD_DC = 6;
static constexpr int EPD_CS = 5;
static constexpr int EPD_BUSY = 4;

GxEPD2_BW<GxEPD2_213_CZ04, GxEPD2_213_CZ04::HEIGHT> display(
  GxEPD2_213_CZ04(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY));

void setup()
{
  Serial.begin(115200);
  SPI.begin(EPD_SCK, -1, EPD_MOSI, EPD_CS);
  display.init(115200, true, 10, false, SPI,
               SPISettings(4000000, MSBFIRST, SPI_MODE0));

  display.setRotation(1);
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setTextSize(2);
    display.setCursor(20, 45);
    display.print("CZ04 OK");
  }
  while (display.nextPage());

  display.hibernate();
}

void loop()
{
}
