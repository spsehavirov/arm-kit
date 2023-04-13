/**
  *************************************************************************************************
  * @file       example_04-LCD_02-customChar.c
  * @author     SPSE Havirov
  * @version    1.0.0
  * @date       11-April-2023 [v0.1]
  * @history    Viz CHANGELOG.md
  * @brief      Testovaci program pro zobrazeni vlastniho znaku na LCD s radicem HD44780.
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

#define STEP        500                       // Krok v ms pro pozdrzeni programu.
#define CLK_DIV     1000                      // Hodnota pro upravu CLK, viz hl. popisek v driveru pro praci s CLK.

#define LCD_COLS    8                         // Pocet sloupcu pouziteho LCD.
#define LCD_ROWS    2                         // Pocet radku pouziteho LCD.

#include "chrono.h"                           // Pripojeni driveru pro praci s CLK.
#include "LCD.h"                              // Pripojeni driveru pro praci s LCD.

#include "LCD_customChar_table.h"             // Pripojeni tabulky s vlastnimi znaky.

int main() {
  SystemCoreClockUpdate();                    // Do SystemCoreClock se nahraje frekvence jadra, viz hl. popisek v driveru pro praci s CLK.
  SysTick_Config(SystemCoreClock / CLK_DIV);  // Konfigurace SysTick timeru, viz hl. popisek v driveru pro praci s CLK.
  
  LCD_setup();                                // Pocatecni nastaveni LCD, nutne pro dalsi praci s LCD.
  
  LCD_customChar_write(0, batteryFull);       // Ulozeni noveho znaku na zadanou pozici do CGRAM.
  
  LCD_customChar_read(0);                     // Zobrazeni vlastniho znaku ze zadane pozice v pameti.
  
  return 0;                                   // Tento krok nebude nikdy vykonan z duvodu pouziti nekonecne smycky vyse (viz varovani pri kompilaci).
}
