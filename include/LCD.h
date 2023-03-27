/**
  *************************************************************************************************
  * @file       LCD.h
  * @author     SPSE Havirov
  * @version    1.0.0
  * @date       26-February-2023 [v0.1]
  * @history    Viz CHANGELOG.md
  * @brief      Driver pro praci s LCD (8x2, 16x2 nebo 20x4) s radicem HD44780.
  *
  *************************************************************************************************
  * @attention
  *
  *   LCD pripojeno primo s vyuzitim 4bit komunikace.
  *
  *   Pro casovani LCD je pouzit SysTick Timer s nastavenym podtecenim co 1ms.
  *     - Podrobnejsi informace o nastaveni viz "chrono.h".
  *
  *   Podporovane desky:
  *     STM32F4-DISCOVERY (STM32F407VGTx)   -   skolni pripravek
  *       CLK:
  *               16MHz   HSI
  *       LCD:
  *               RS      PE3
  *               R/W     PE4   (mozno zapojit primo na GND - omezeni prace s LCD)
  *               E       PE5
  *               DB4     PE6
  *               DB5     PE7
  *               DB6     PE8
  *               DB7     PE9
  *               DIR     PE10  (pouze na skolnim pripravku; Pouzit prevodnik '245 (z 3.3V na 5V a naopak))
  *
  *************************************************************************************************
  * @copyright Copyright SPSE Havirov (c) 2023 *
  **********************************************
*/

#ifndef ARM_KIT_LCD
#define ARM_KIT_LCD

#include "chrono.h"                  // Pripojeni driveru pro praci s CLK.

#ifndef STRING_H_
  #include <string.h>
#endif

//#================================================================================================
//#=== Makra pro LCD - ZACATEK
#define LCD_ON           (0x0C)      // Zapnuti displeje (bez kurzoru).
#define LCD_OFF          (0x08)      // Vypnuti displeje.
#define LCD_CLR          (0x01)      // Smazani displeje, navrat kurzoru na 0. radek a 0. sloupec.
#define LCD_CUR_ON       (0x0E)      // Zapnuti kurzoru bez blikani (vcetne zapnuti displeje).
#define LCD_CUR_OFF      LCD_ON      // Vypnuti kurzoru (displej zustane zapnuty).
#define LCD_CUR_BLINK    (0x0F)      // Zapnuti blikajiciho kurzoru (vcetne zapnuti displeje).
#define LCD_CUR_NO_BLINK LCD_CUR_ON  // Vypnuti blikajiciho kurzoru (vcetne zapnuti displeje).
#define LCD_CUR_HOME     (0x03)      // Navrat kurzoru na prvni pozici prvniho radku.
#define LCD_SL           (0x18)      // Rotace displeje vlevo.
#define LCD_SR           (0x1C)      // Rotace displeje vpravo.
#define LCD_LINE0        (0x80)      // Nulty (nejvyssi) radek prvni pozice  (0x00 + DDRAM = 0x80).
#define LCD_LINE1        (0xC0)      // Prvni            radek prvni pozice	(0x40 + DDRAM = 0xC0).
#define LCD_LINE2        (0x94)      // Druhy            radek prvni pozice  (0x14 + DDRAM = 0x94).
#define LCD_LINE3        (0xD4)      // Treti (nejnizsi) radek prvni pozice  (0x54 + DDRAM = 0xD4).
//#=== Makra pro LCD - KONEC
//#================================================================================================

const uint16_t LCD_RESOLUTION = (LCD_COLS*100) + LCD_ROWS;    // Rozliseni displeje jako jedna hodnota.

//#================================================================================================
//#=== Rutiny pro rizeni LCD - ZACATEK
/**
 * @brief  Umele pozdrzeni, pro vykonani instrukce LCD
 *
 */
void LCD_busy(void) { delay(10); } // Doba, kdy by mel LCD radic mit prikaz zpracovan a busy flag volny (kontrola stavu tak neni nutna).

/**
 * @brief  Zapis nibble informace (vyuziti 4bit komunikace, prikazy jsou vsak 8bit).
 *
 * @param  nibble Hodnota v rozmezi 0 - F.
 *
 */
void LCD_write_nibble(uint16_t nibble){
	uint16_t x;
  
  GPIOE->BSRR = ( (1UL << (4+16)) |   // R/W=0
                  (1UL << (5+16))     // E=0
                );
  
  delay(1);                           // 1ms
  
  GPIOE->BSRR = (1UL << 5);           // E=1  (clk)
  
  nibble &= 0x0F;
  nibble = nibble << 6;
  
  x = GPIOE->ODR & 0xFC3F;            // Nuluj data
  GPIOE->ODR = nibble | x;            // Pridej data
	
  delay(1);                           // 1ms
  GPIOE->BSRR = (1UL << (5+16));      // E=0
  delay(1);                           // 1ms
}

/**
 * @brief  Funkce pro rizeni/nastaveni LCD.
 *
 * @param  cmd Kod pro ridici prikaz.
 *
 */
void LCD_set(uint8_t cmd) {
  LCD_busy(); // Casova prodleva pro zpracovani ridicich prikazu.
  
  GPIOE->BSRR = (1UL << (3+16));      // RS=0
  GPIOE->BSRR = (1UL << (4+16));      // R/W=0
  
  LCD_write_nibble(cmd >> 4);         // Poslani 4 hornich bitu na zapis
  LCD_write_nibble(cmd);              // Poslani 4 dolnich bitu na zapis
}

/**
 * @brief  Pocatecni nastaveni pro LCD.
 *
 */
void LCD_setup(void) {
  uint8_t i;
  
  // 1. Aktivace CLK na portu E
  RCC->AHB1ENR |= (1UL << 4);
  
  // 2. Nastaveni pinu pro LCD - ZACATEK
  for (i = 3; i < 11; i++) {
    GPIOE->MODER   &= ~(3UL << 2*i);  // Reset; INPUT
    GPIOE->MODER   |=  (1UL << 2*i);  // Nastaveni pinu jako OUTPUT
    
    GPIOE->OTYPER  &= ~(1UL << 1*i);  // Push-pull (dvojcinny vystup)
    
    GPIOE->OSPEEDR &= ~(3UL << 2*i);  // Reset; Low speed
    GPIOE->OSPEEDR |=  (2UL << 2*i);  // High speed
    
    GPIOE->PUPDR   &= ~(3UL << 2*i);  // Reset; No pull-up/pull-down
  }
  // 2. Nastaveni pinu a portu - KONEC
  
  // 3. Nastaveni/inicializace LCD - ZACATEK
  LCD_set(0x03);  // 1) Reset LCD
  LCD_set(0x03);
  LCD_set(0x02);

  LCD_set(0x28);  // 2) Nastaveni komunikace, poctu radku a rozliseni: 4bit ; 2 radky ; 5x8 bodu
  LCD_set(0x0F);  // 3) Aktivace displeje: zapnuti displeje a blikajiciho kurzoru
  LCD_set(0x06);  // 4) Chovani displeje pri vypisu znaku: inkrementace adresy a posun kurzoru vpravo po vypsani znaku na LCD
  LCD_set(0x01);  // 5) Smazani displeje
  // 3. Nastaveni/inicializace LCD - KONEC
}
//#=== Rutiny pro rizeni LCD - KONEC
//#================================================================================================


//#================================================================================================
//#=== Rutiny pro praci s LCD - ZACATEK

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
 * @param  col pro cislo sloupce, row pro cislo radku (hodnoty zacinaji od 0).
 *
 */
void LCD_setCursor(uint8_t col, uint8_t row) {
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

/**
 * @brief  Funkce pro vypis 1 znaku na LCD.
 *
 * @param  data Kod pro vypisovany znak, pripadne konkretni znak.
 *
 */
void LCD_put(uint8_t data) {
  LCD_busy(); // Casova prodleva pro zpracovani ridicich prikazu.
  
  GPIOE->BSRR = (1UL << 3);       // RS=1
  GPIOE->BSRR = (1UL << (4+16));  // R/W=0
  
  LCD_write_nibble(data >> 4);    // Horni 4bity
  LCD_write_nibble(data & 0x0F);  // Dolni 4bity
}

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
//#=== Rutiny pro praci s LCD - KONEC
//#================================================================================================

#endif  /* ARM_KIT_LCD */
