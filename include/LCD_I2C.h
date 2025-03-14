/**
  *************************************************************************************************
  * @file       LCD_I2C.h
  * @author     SPSE Havirov
  * @version    1.0.0
  * @date       18-January-2025
  * @history    Viz CHANGELOG.md
  * @brief      Driver pro praci s LCD (8x2, 16x2 nebo 20x4) s radicem HD44780 pripojenym pres I2C.
  *
  *************************************************************************************************
  * @attention
  *
  *   Zdroj:
  *     https://ruturajn.hashnode.dev/interfacing-an-i2c-based-lcd-with-stm32f407-discovery-kit
  *
  *   Pro casovani LCD je pouzit SysTick Timer s nastavenym podtecenim co 1ms.
  *     - Podrobnejsi informace o nastaveni viz "chrono.h".
  *
  *   Podporovane desky:
  *     STM32F4-DISCOVERY (STM32F407VGTx)
  *       CLK:
  *               16MHz   HSI
  *       I2C:
  *               SDA     PB7 (I2C1 - default); PB9 (I2C1), PB11 (I2C2), PC9 (I2C3)
  *               SCL     PB6 (I2C1 - default); PB8 (I2C1), PB10 (I2C2), PA8 (I2C3)
  *
  *************************************************************************************************
  * @copyright Copyright SPSE Havirov (c) 2025 *
  **********************************************
*/

#ifndef ARM_KIT_LCD_I2C
#define ARM_KIT_LCD_I2C

#include "chrono.h"                 // Pripojeni driveru pro praci s CLK.
#include "I2C.h"                    // Pripojeni driveru pro praci s I2C sbernici.

#ifndef STRING_H_
  #include <string.h>
#endif

//#================================================================================================
//#=== Makra pro LCD - ZACATEK
#define LCD_ON            0x0C        // Zapnuti displeje (bez kurzoru).
#define LCD_OFF           0x08        // Vypnuti displeje.
#define LCD_CLR           0x01        // Smazani displeje, navrat kurzoru na 0. radek a 0. sloupec.
#define LCD_CUR_ON        0x0E        // Zapnuti kurzoru bez blikani (vcetne zapnuti displeje).
#define LCD_CUR_OFF       LCD_ON      // Vypnuti kurzoru (displej zustane zapnuty).
#define LCD_CUR_BLINK     0x0F        // Zapnuti blikajiciho kurzoru (vcetne zapnuti displeje).
#define LCD_CUR_NO_BLINK  LCD_CUR_ON  // Vypnuti blikajiciho kurzoru (vcetne zapnuti displeje).
#define LCD_CUR_HOME      0x03        // Navrat kurzoru na prvni pozici prvniho radku.
#define LCD_SL            0x18        // Rotace displeje vlevo.
#define LCD_SR            0x1C        // Rotace displeje vpravo.
#define LCD_LINE0         0x80        // Nulty (nejvyssi) radek prvni pozice  (0x00 + DDRAM = 0x80).
#define LCD_LINE1         0xC0        // Prvni            radek prvni pozice	(0x40 + DDRAM = 0xC0).
#define LCD_LINE2         0x94        // Druhy            radek prvni pozice  (0x14 + DDRAM = 0x94).
#define LCD_LINE3         0xD4        // Treti (nejnizsi) radek prvni pozice  (0x54 + DDRAM = 0xD4).
#define LCD_INST_REG      0x00        // Instrukcni registr
#define LCD_DATA_REG      0x40        // Datovy registr
//#=== Makra pro LCD - KONEC
//#================================================================================================

//#================================================================================================
//#=== Prototypy funkci pro LCD_I2C - ZACATEK
void LCD_init(void);
void LCD_set(uint16_t);
void LCD_clear(void);
void LCD_setCursor(uint8_t, uint8_t);
void LCD_put(uint8_t);
void LCD_print(const char *__restrict__ text);
//#=== Prototypy funkci pro LCD_I2C - KONEC
//#================================================================================================

//#================================================================================================
//#=== Rutiny pro rizeni s LCD_I2C - ZACATEK
/**
 * @brief  Pocatecni nastaveni pro LCD.
 *
 */
void LCD_init(void) {
  // 1. Reset a nastaveni komunikace
  delay(50);
  LCD_set(0x03);
  delay(5);
  
  LCD_set(0x03);
  delay(1);
  
  LCD_set(0x02);  // Nastaveni 4bit komunikace
  delay(10);
  
  // 2. Nastaveni/inicializace LCD  - ZACATEK
  LCD_set(0x28);  // 2) Nastaveni komunikace, poctu radku a rozliseni: 4bit ; 2 radky ; 5x8 bodu
  delay(5);
  LCD_set(0x0F);  // 3) Aktivace displeje: zapnuti displeje a blikajiciho kurzoru
  delay(5);
  LCD_set(0x06);  // 4) Chovani displeje pri vypisu znaku: inkrementace adresy a posun kurzoru vpravo po vypsani znaku na LCD
  delay(5);
  LCD_set(0x01);  // 5) Smazani displeje
  delay(5);
  // 2. Nastaveni/inicializace LCD  - KONEC
}

/**
 * @brief  Funkce pro rizeni/nastaveni LCD.
 *
 * @param  cmd Kod pro ridici prikaz. Pro zapis do IR je kod 8bit, pro zapis do DR je 8bit kod doplneni o 9bit (0x100)
 *
 */
void LCD_set(uint16_t cmd) {
  uint8_t d_h, d_l;
  
  d_h = (cmd & 0x00F0);           // Zjisteni hornich 4 bitu
  d_l = ((cmd << 4) & 0x00F0);    // Zjisteni nizsich 4 bitu
  
  I2C_start();
  
  I2C_send_addr(LCD_ADDR);
  
  if(cmd & 0x0100) {
    I2C_write(LCD_DATA_REG);
    
    I2C_write(d_h | 0x0D);        // Zapis do Data Register: EN=1, RS=1, R/W=0        
    delay(2);
    
    I2C_write(d_h | 0x09);        // Zapis do Data Register: EN=0, RS=1, Backlight ON
    I2C_write(d_l | 0x0D);  
    delay(2);
    
    I2C_write(d_l | 0x09);    
  } else {
    I2C_write(LCD_INST_REG);
    
    I2C_write(d_h | 0x0C);        // Zapis do Data Register: EN=1, RS=0, R/W=0        
    delay(2);
    
    I2C_write(d_h | 0x08);        // Zapis do Data Register: EN=0, RS=0, Backlight ON
    I2C_write(d_l | 0x0C);  
    delay(2);
    
    I2C_write(d_l | 0x08);
  }
  
  I2C_stop();
}
//#=== Rutiny pro rizeni s LCD_I2C - KONEC
//#================================================================================================

//#================================================================================================
//#=== Rutiny pro praci s LCD_I2C - ZACATEK
/**
 * @brief  Funkce pro vypis retezce znaku na LCD.
 *         Funkce neresi pocet znaku na radek, ani pocet radku, nutno resit v samotnem programu nebo si napsat vl. funkci.
 *
 * @param  text Retezec/pole znaku, jez se maji vypsat na LCD.
 *
 */
void LCD_print(const char *__restrict__ text) {
  uint8_t i;

  for (i = 0; i < strlen(text); i++) {
    LCD_put(text[i]);
  }
}

/**
 * @brief  Funkce pro vypis 1 znaku na LCD.
 *
 * @param  data Kod pro vypisovany znak, pripadne konkretni znak.
 *
 */
void LCD_put(uint8_t mark) {
  LCD_set(0x0100 | mark);     // 0x0100 pridano pro rozliseni zapisu do Data Registru LCD, viz LCD_set()
}
/**
 * @brief  Funkce pro smazani LCD. Po smazani dojde k presunu kurzoru na 0. radek a 0. sloupec.
 *
 */
void LCD_clear(void) {
  LCD_set(LCD_CLR);
}

/**
 * @brief  Funkce pro umisteni kurzoru na LCD.
 *
 * @param  row pro cislo radku, col pro cislo sloupce (hodnoty zacinaji od 0).
 *
 */
void LCD_setCursor(uint8_t row, uint8_t col) {
  switch (row) {
    case 0:
      LCD_set(LCD_LINE0 + col);
      break;
    case 1:
      LCD_set(LCD_LINE1 + col);
      break;
    case 2:
      LCD_set(LCD_LINE2 + col);
      break;
    case 3:
      LCD_set(LCD_LINE3 + col);
      break;
    default:
      LCD_set(LCD_LINE0);
  }
}
//#=== Rutiny pro praci s LCD_I2C - KONEC
//#================================================================================================
#endif
