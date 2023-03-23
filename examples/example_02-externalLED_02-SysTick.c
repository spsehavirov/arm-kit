/**
  *************************************************************************************************
  * @file       example_02-externalLED_02-SysTick.c
  * @author     SPSE Havirov
  * @version    1.0.0
  * @date       05-March-2023 [v0.1]
  * @history    Viz CHANGELOG.md
  * @brief      Blikani externi LED v nekonecne smycce s vyuzitim SysTick Timer.
  *
  *************************************************************************************************
  * @attention
  *
  *   Externi LED jsou umisteny na PE12 - PE15 (4x red).
  *   Externi LED maji opacnou logiku nez vestavene, anoda pripojena na 3,3V.
  *     LOG '1' = LED nesviti
  *     LOG '0' = LED sviti
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
  
  RCC->AHB1ENR |= (1UL << 4);                 // 1. Aktivace CLK na portu E (PE).
  
  GPIOE->MODER &= ~(3UL << LED*2);            // 2. Reset smeru PINu.
  GPIOE->MODER |= (1UL << LED*2);             //    Nastaveni smeru PINu jako OUTPUT.
  
  while (1) {
    GPIOE->ODR |= (1 << LED);                 // 3. Zhasnuti LED
    
    out = 0x00;                               // V Debug (Logic Analyzer) hodnota na min.
    
    delay(STEP);                              // Pozdrzeni programu.
    
    GPIOE->ODR &= ~(1 << LED);                // 4. Rozsviceni LED
    
    out = 0xFF;                               // V Debug (Logic Analyzer) hodnota na max.
    
    delay(STEP);
  }

  return 0;                                   // Tento krok nebude nikdy vykonan z duvodu pouziti nekonecne smycky vyse (viz varovani pri kompilaci).
}
