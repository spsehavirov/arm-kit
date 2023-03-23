/**
  *************************************************************************************************
  * @file       example_01-builtinLED_02-SysTick.c
  * @author     SPSE Havirov
  * @version    1.0.0
  * @date       05-March-2023 [v0.1]
  * @history    Viz CHANGELOG.md
  * @brief      Blikani vestavene LED v nekonecne smycce s vyuzitim SysTick Timer.
  *
  *************************************************************************************************
  * @attention
  *
  *   Vestavene LED jsou umisteny na PD12 - PD15 (v barevnem poradi: green, orange, red, blue).
  *     LOG '1' = LED sviti
  *     LOG '0' = LED nesviti
  *
  *************************************************************************************************
  * @copyright  Copyright SPSE Havirov (c) 2023 *
  ***********************************************
*/

#include "stm32f4xx.h"                        // Device header

#define STEP      500                         // Krok blikani LED.
#define CLK_DIV   1000                        // Hodnota pro upravu CLK, viz hl. popisek v driveru pro praci s CLK.
#define LED       12                          // Cislo pinu LED.

#include "chrono.h"                           // Pripojeni driveru pro praci s CLK.

volatile uint8_t out;                         // Pro Debug.

int main(void) {  
  SystemCoreClockUpdate();                    // Do SystemCoreClock se nahraje frekvence jadra, viz hl. popisek v driveru pro praci s CLK.
  SysTick_Config(SystemCoreClock / CLK_DIV);  // Konfigurace SysTick timeru, viz hl. popisek v driveru pro praci s CLK.
  
  RCC->AHB1ENR |= (1UL << 3);                 // 1. Aktivace CLK na portu D (PD).
  
  GPIOD->MODER &= ~(3UL << LED*2);            // 2. Reset smeru PINu.
  GPIOD->MODER |= (1UL << LED*2);             //    Nastaveni smeru PINu jako OUTPUT.
  
  while (1) {
    GPIOD->ODR |= (1 << LED);                 // 3. Rozsviceni LED.
      
    out = 0xFF;                               // V Debug (Logic Analyzer) hodnota na max.
    
    delay(STEP);                              // Pozdrzeni programu.
    
    GPIOD->ODR &= ~(1 << LED);                // 4. Zhasnuti LED.
      
    out = 0x00;                               // V Debug (Logic Analyzer) hodnota na min.
    
    delay(STEP);
  }

  return 0;                                   // Tento krok nebude nikdy vykonan z duvodu pouziti nekonecne smycky vyse (viz varovani pri kompilaci).
}
