/**
  *************************************************************************************************
  * @file       example_04-LCD_I2C-01.c
  * @author     SPSE Havirov
  * @version    1.0.0
  * @date       18-January-2025
  * @history    Viz CHANGELOG.md
  * @brief      Testovaci program pro LCD s radicem HD44780, pripojenym k I2C pomoci prevodniku.
  *
  *************************************************************************************************
  * @attention
  *
  *   Pripojeni LCD viz driver "LCD_I2C.h".
  *
  *************************************************************************************************
  * @copyright  Copyright SPSE Havirov (c) 2025 *
  ***********************************************
*/

#include "stm32f4xx.h"                        // Device header



#define STEP          1000                    // Krok v ms pro pozdrzeni programu.
#define CLK_DIV       1000                    // Hodnota pro upravu CLK, viz hl. popisek v driveru pro praci s CLK.

#define LCD_COLS      20                      // Pocet sloupcu pouziteho LCD.
#define LCD_ROWS      4                       // Pocet radku pouziteho LCD.

#define LCD_ADDR      0x4E                    // Defaultni adresa LCD I2C - nutno zjistit pro kazde LCD I2C a pripadne zmenit

#define SDA_PIN       7                       // PIN pro datovy vodic I2C sbernice.
#define SCL_PIN       6                       // PIN pro CLK vodic I2C sbernice.

//void TIM4_ms_delay(uint16_t);

#include "chrono.h"                           // Pripojeni driveru pro praci s CLK.
#include "LCD_I2C.h"                          // Pripojeni driveru pro praci s LCD_I2C.

int main() {
  SystemCoreClockUpdate();                    // Do SystemCoreClock se nahraje frekvence jadra, viz hl. popisek v driveru pro praci s CLK.
  SysTick_Config(SystemCoreClock / CLK_DIV);  // Konfigurace SysTick timeru, viz hl. popisek v driveru pro praci s CLK.
  
  I2C_GPIO_init();                            // Pocatecni inicializace PINu pro I2C.
  I2C_init();                                 // Pocatecni inicializace I2C sbernice
  
  LCD_init();                                 // Pocatecni inicializace LCD I2C
  
  while(1) {
    LCD_set(LCD_CUR_ON);                      // Zapnuti kurzoru.
    delay(STEP);                              // Pozdrzeni programu.
    
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
    
    LCD_setCursor(0, 0);                      // Nastaveni pozice kurzoru.
    
    LCD_print("World!");                      // Vypis retezce.
    delay(STEP);
    
    LCD_clear();                              // Smazani displeje.
  }
  
  return 0;                                   // Tento krok nebude nikdy vykonan z duvodu pouziti nekonecne smycky vyse (viz varovani pri kompilaci).
}
