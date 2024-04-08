#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "arduipac.h"
#include "arduipac_vmachine.h"
#include "arduipac_8048.h"
#include "arduipac_8245.h"
#include "arduipac_bios_rom.h"
#include "arduipac_config.h"

#define DEBUG_TFT
#define DEBUG_SERIAL
#undef DEBUG_STDERR

#define TEXT_TFT_CS 0
#define TEXT_TFT_RST -1
#define TEXT_TFT_DC 1

#define GRAPHIC_TFT_CS 6
#define GRAPHIC_TFT_RST -1
#define GRAPHIC_TFT_DC 7

Adafruit_ST7735 text_tft = Adafruit_ST7735(TEXT_TFT_CS, TEXT_TFT_DC, TEXT_TFT_RST);
Adafruit_ST7789 graphic_tft = Adafruit_ST7789(GRAPHIC_TFT_CS, GRAPHIC_TFT_DC, GRAPHIC_TFT_RST);

void text_print_string(char *text)
{
  text_tft.print(text);
}

void text_print_dec(uint32_t number)
{
  text_tft.print(number, DEC);
}

void text_print_hex(uint32_t number)
{
  text_tft.print(number, HEX);
}

void graphic_drawtext(char *text)
{
  graphic_tft.setCursor(0, 0);
  graphic_tft.print(text);
}

#define ARDUIPAC_VERSION "This is the end"
void setup()
{
  Serial.begin(115200);
  delay(100);

  text_tft.initR(INITR_BLACKTAB);
  text_tft.setSPISpeed(1000000); // 1 MHZ, il smeble que l'on puisse aller jusqu'à 25, 40 voire 100 MHz
  text_tft.fillScreen(ST77XX_BLACK);
  text_tft.setRotation(1);
  text_tft.setTextColor(ST77XX_GREEN);

  delay(TFT_DEBUG_DELAY);

  graphic_tft.fillScreen(ST77XX_BLACK);
  graphic_tft.setSPISpeed(1000000); // 1 MHZ, il smeble que l'on puisse aller jusqu'à 25, 40 voire 100 MHz
  graphic_tft.setRotation(1);
  graphic_tft.setTextColor(ST77XX_WHITE);
  delay(TFT_DEBUG_DELAY);

#define WELCOME_STRING "Arduipac MKR Wifi 1010 " ARDUIPAC_VERSION
#ifdef DEBUG_STDERR
  fprintf(stderr, "%s\n", WELCOME_STRING);
#endif
#ifdef DEBUG_SERIAL
  Serial.println(WELCOME_STRING);
#endif
#ifdef DEBUG_TFT
  text_print_string(WELCOME_STRING);
  delay(TFT_DEBUG_DELAY);
  graphic_drawtext(WELCOME_STRING, ST77XX_WHITE);
  delay(TFT_DEBUG_DELAY);
#endif

#ifdef DEBUG_STDERR
  fprintf(stderr, "Entering main()\n");
#endif
#ifdef DEBUG_SERIAL
  Serial.println("Entering main()");
#endif
#ifdef DEBUG_TFT
  text_print_string("Entering main()\n");
  delay(TFT_DEBUG_DELAY);
#endif

  // collision = NULL;

#ifdef DEBUG_STDERR
  fprintf(stderr, "main(): launching init_intel8245()\n");
#endif
#ifdef DEBUG_SERIAL
  Serial.println("main(): launching init_intel8245()");
#endif
#ifdef DEBUG_TFT
  text_print_string("main(): launching init_intel8245()\n");
  delay(TFT_DEBUG_DELAY);
#endif

  init_intel8245();

#ifdef DEBUG_STDERR
  fprintf(stderr, "main(): launching init_intel8048()\n");
#endif
#ifdef DEBUG_SERIAL
  Serial.println("main(): launching init_intel8048()");
#endif
#ifdef DEBUG_TFT
  text_print_string("main(): launching init_intel8048()\n");
  delay(TFT_DEBUG_DELAY);
#endif

  init_intel8048();

#ifdef DEBUG_STDERR
  fprintf(stderr, "main(): launching init_vmachine()\n");
#endif
#ifdef DEBUG_SERIAL
  Serial.println("main(): launching init_vmachine()");
#endif
#ifdef DEBUG_TFT
  text_print_string("main(): launching init_vmachine()\n");
  delay(TFT_DEBUG_DELAY);
#endif

  init_vmachine();

#ifdef DEBUG_STDERR
  fprintf(stderr, "main(): launching exec_8048()\n");
#endif
#ifdef DEBUG_SERIAL
  Serial.println("main(): launching exec_8048()");
#endif
#ifdef DEBUG_TFT
  text_print_string("main(): launching exec_8048()\n");
  delay(TFT_DEBUG_DELAY);
#endif

  exec_8048();
}

void loop()
{
#ifdef DEBUG_STDERR
  fprintf(stderr, "loop()\n");
#endif
#ifdef DEBUG_SERIAL
  Serial.println("loop()");
#endif
#ifdef DEBUG_TFT
  text_print_string("loop\n");
  delay(TFT_DEBUG_DELAY);
#endif

}