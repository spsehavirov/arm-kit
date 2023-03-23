/**
  *************************************************************************************************
  * @file       example_03-userButton_01-controlLED.c
  * @author     SPSE Havirov
  * @version    1.0.0
  * @date       26-February-2023 [v0.1]
  * @history    Viz CHANGELOG.md
  * @brief      Pri stisku tlacitka se rozsviti vestavena LED, jinak nesviti.
  *
  *************************************************************************************************
  * @attention
  *
  *   Uzivatelske tlacitko (modre) je umisteno na PA0.
  *     LOG '1' = stisknuto
  *     LOG '0' = nestisknuto
  *
  *************************************************************************************************
  * @copyright  Copyright SPSE Havirov (c) 2023 *
  ***********************************************
*/
#include "stm32f4xx.h"                        // Device header

#define LED   12                              // Cislo pinu LED.

volatile uint8_t out;                         // Pro Debug.

int main(void) { 
  RCC->AHB1ENR |= (1UL << 0);                 // 1. Aktivace CLK na portu A (PA).
  RCC->AHB1ENR |= (1UL << 3);                 //    Aktivace CLK na portu D (PD).
  
  GPIOD->MODER &= ~(3UL << LED*2);            // 2. Reset smeru PINu.
  GPIOD->MODER |= (1UL << LED*2);             //    Nastaveni smeru PINu jako OUTPUT.
  
  while (1) {
    if (GPIOA->IDR & (1UL << 0)) {            // 3. Kontrola stavu tlacitka, vyuzito maskovani.
      GPIOD->ODR = (1 << LED);                // Rozsviceni LED.
    } else {
      GPIOD->ODR &= ~(1 << LED);              // Zhasnuti LED.
    }
  }

  return 0;                                   // Tento krok nebude nikdy vykonan z duvodu pouziti nekonecne smycky vyse (viz varovani pri kompilaci).
}
