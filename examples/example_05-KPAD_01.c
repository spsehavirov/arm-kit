/**
  *************************************************************************************************
  * @file       example_05-KPAD_01.c
  * @author     SPSE Havirov
  * @version    1.0.0
  * @date       26-February-2023 [v0.1]
  * @history    Viz CHANGELOG.md
  * @brief      Testovaci program pro KeyPad 3x4 nebo 4x4.
  *
  *************************************************************************************************
  * @attention
  *
  *   Pripojeni KPAD viz driver "KPAD.h".
  *
  *************************************************************************************************
  * @copyright  Copyright SPSE Havirov (c) 2023 *
  ***********************************************
*/

#include "stm32f4xx.h"                        // Device header

#define STEP        1000                      // Krok v ms pro pozdrzeni programu.
#define CLK_DIV     1000                      // Hodnota pro upravu CLK, viz hl. popisek v driveru pro praci s CLK.

#define LCD_COLS    8                         // Pocet sloupcu pouziteho displeje.
#define LCD_ROWS    2                         // Pocet radku pouziteho displeje.

#define KPAD_COLS   4                         // Pocet sloupcu pouziteho KPAD.
#define KPAD_ROWS   4                         // Pocet radku pouziteho KPAD.

static uint8_t
  KPAD_KeyMap[KPAD_ROWS][KPAD_COLS] = {       // Defaultni rozlozeni pro KPAD 4x4.
  '1', '2', '3', 'A',
  '4', '5', '6', 'B',
  '7', '8', '9', 'C',
  '*', '0', '#', 'D'
};

#include "chrono.h"                           // Pripojeni driveru pro praci s CLK.
#include "LCD.h"                              // Pripojeni driveru pro praci s LCD.
#include "KPAD.h"                             // Pripojeni driveru pro praci s KPAD.

int main() {
  uint8_t mark;                               // Pro nacitany znak.
  
  SystemCoreClockUpdate();                    // Do SystemCoreClock se nahraje frekvence jadra, viz hl. popisek v driveru pro praci s CLK.
  SysTick_Config(SystemCoreClock / CLK_DIV);  // Konfigurace SysTick timeru, viz hl. popisek v driveru pro praci s CLK.
  
  LCD_setup();                                // Pocatecni nastaveni LCD, nutne pro dalsi praci s LCD.
  KPAD_setup();                               // Pocatecni nastaveni KPAD, nutne pro dalsi praci s KPAD.
  
  while(1) {
    LCD_clear();                              // Smazani displeje.
    LCD_setCursor(0, 0);                      // Nastaveni pozice kurzoru.
    LCD_set(LCD_CUR_BLINK);                   // Zapnuti blikani kurzoru.
    
    do {
      mark = KPAD_getKey();                   // Nacteni stisknute klavesy.
    } while(!mark);                           // Kontrola, zda doslo ke stisku klavesy. Pokud ne, je vracena 0, jinak prislusny znak.
    
    LCD_put(mark);                            // Pro zmacknutou klavesu se vypise prislusny znak.
    
    LCD_set(LCD_CUR_OFF);                     // Vypnuti kurzoru.
    delay(STEP);                              // Pozdrzeni programu.
  }
  
  return 0;                                   // Tento krok nebude nikdy vykonan z duvodu pouziti nekonecne smycky vyse (viz varovani pri kompilaci).
}
