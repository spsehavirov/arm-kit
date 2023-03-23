/**
  *************************************************************************************************
  * @file       example_04-LCD_01.c
  * @author     SPSE Havirov
  * @version    1.0.0
  * @date       26-February-2023 [v0.1]
  * @history    Viz CHANGELOG.md
  * @brief      Testovaci program pro LCD s radicem HD44780.
  *
  *************************************************************************************************
  * @attention
  *
  *   Pripojeni LCD viz driver "LCD.h".
  *
  *************************************************************************************************
  * @copyright  Copyright SPSE Havirov (c) 2023 *
  ***********************************************
*/

#include "stm32f4xx.h"                        // Device header

#define STEP        1000                      // Krok v ms pro pozdrzeni programu.
#define CLK_DIV     1000                      // Hodnota pro upravu CLK, viz hl. popisek v driveru pro praci s CLK.

#define LCD_COLS    8                         // Pocet sloupcu pouziteho LCD.
#define LCD_ROWS    2                         // Pocet radku pouziteho LCD.

#include "chrono.h"                           // Pripojeni driveru pro praci s CLK.
#include "LCD.h"                              // Pripojeni driveru pro praci s LCD.

int main() {
  SystemCoreClockUpdate();                    // Do SystemCoreClock se nahraje frekvence jadra, viz hl. popisek v driveru pro praci s CLK.
  SysTick_Config(SystemCoreClock / CLK_DIV);  // Konfigurace SysTick timeru, viz hl. popisek v driveru pro praci s CLK.
  
  LCD_setup();                                // Pocatecni nastaveni LCD, nutne pro dalsi praci s LCD.
  
  while(1) {
    LCD_set(LCD_CUR_ON);                      // Zapnuti kurzoru.
    delay(STEP);
    
    LCD_set(LCD_CUR_BLINK);                   // Zapnuti blikani kurzoru.
    delay(STEP*2);

    LCD_set(LCD_CUR_NO_BLINK);                // Vypnuti blikani kurzoru.
    delay(STEP);
    
    LCD_set(LCD_CUR_OFF);                     // Vypnuti kurzoru.
    delay(STEP);
    
    LCD_put('#');                             // Vypis jednoho znaku.
    delay(STEP);
    
    LCD_set(LCD_LINE0);                       // Nastaveni LCD, konkretne pozice kurzoru.
    
    LCD_print("Hello");                       // Vypis retezce.
    delay(STEP);
    
    LCD_setCursor(0, 1);                     // Nastaveni pozice kurzoru.
    
    LCD_print("World!");                      // Vypis retezce.
    delay(STEP);
    
    LCD_clear();                              // Smazani displeje.
  }

  return 0;                                   // Tento krok nebude nikdy vykonan z duvodu pouziti nekonecne smycky vyse (viz varovani pri kompilaci).
}
