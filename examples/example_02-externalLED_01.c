/**
  *************************************************************************************************
  * @file       example_02-externalLED_01.c
  * @author     SPSE Havirov
  * @version    1.0.0
  * @date       26-February-2023 [v0.1]
  * @history    Viz CHANGELOG.md
  * @brief      Blikani externi LED v nekonecne smycce.
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

#define STEP  500                             // Krok blikani LED.
#define LED   12                              // Cislo pinu LED.

#include "chrono.h"                           // Pripojeni driveru pro praci s CLK.

volatile uint8_t out;                         // Pro Debug.

int main(void) {
  RCC->AHB1ENR |= (1UL << 4);                 // 1. Aktivace CLK na portu E (PE).
  
  GPIOE->MODER &= ~(3UL << LED*2);            // 2. Reset smeru PINu.
  GPIOE->MODER |= (1UL << LED*2);             //    Nastaveni smeru PINu jako OUTPUT.
  
  while (1) {
    GPIOE->ODR |= (1 << LED);                 // 3. Zhasnuti LED.
    
    out = 0x00;                               // V Debug (Logic Analyzer) hodnota na min.
    
    cekej(STEP);                              // Umele pozdrzeni programu.
    
    GPIOE->ODR &= ~(1 << LED);                // 4. Rozsviceni LED.
    
    out = 0xFF;                               // V Debug (Logic Analyzer) hodnota na max.
    
    cekej(STEP);
  }

  return 0;                                   // Tento krok nebude nikdy vykonan z duvodu pouziti nekonecne smycky vyse (viz varovani pri kompilaci).
}
