/**
  *************************************************************************************************
  * @file       KPAD.h
  * @author     SPSE Havirov
  * @version    1.0.0
  * @date       26-February-2023 [v0.1]
  * @history    Viz CHANGELOG.md
  * @brief      Driver pro praci s KeyPad 3x4 nebo 4x4.
  *
  *************************************************************************************************
  * @attention
  *
  *   Podporovane desky:
  *     STM32F4-DISCOVERY (STM32F407VGTx)   -   skolni pripravek
  *       CLK:
  *               16MHz   HSI
  *       KEYPAD:
  *               COL0    PD0
  *               COL1    PD1
  *               COL2    PD2
  *               COL3    PD3     (skolni pripravek ma keypad pouze 3x4, domaci pripravky maji keypad 4x4)
  *
  *               ROW0    PD6
  *               ROW1    PD7
  *               ROW2    PD8
  *               ROW3    PD9
  *
  *************************************************************************************************
  * @copyright  Copyright SPSE Havirov (c) 2023 *
  ***********************************************
*/

#ifndef ARM_KIT_KPAD
#define ARM_KIT_KPAD

#include "chrono.h"                         // Pripojeni driveru pro praci s CLK.

#ifndef KPAD_STEP
  #define KPAD_STEP 250                     // Prodleva mezi dalsim snimanim klaves
#endif

/**
 * @brief  Funkce pro zisteni stisknute klavesy.
 *
 * @return  Pokud neni stisknuta zadna klavesa vraci 0, jinak prislusny znak, dle zadefinovaneho rozlozeni pro KeyPad.
 */
uint8_t KPAD_getKey(void) {
  uint16_t readout = 0;
  uint8_t i;
  
  delay(KPAD_STEP);
  
  for (i = 0; i < 4; i++) {
    GPIOD->ODR &= ~(0x0F << 6);             // Deaktivace vsech radku.
    GPIOD->ODR |= (~(1UL << i) << 6);       // Aktivace radku.
    
    readout = GPIOD->IDR & 0x0F;            // Vymaskovani sloupcu.
    
    switch(readout) {                       // Kontrola, zda nebylo stisknuto tlacitko ve vybranem radku a sloupci
      case 0x0E: return KPAD_KeyMap[i][0];
      case 0x0D: return KPAD_KeyMap[i][1];
      case 0x0B: return KPAD_KeyMap[i][2];
      case 0x07: return KPAD_KeyMap[i][3];
    }
  }

  return 0;	
}

/**
 * @brief  Pocatecni nastaveni pro KeyPad.
 *
 */
void KPAD_setup(void) {
  uint8_t i;
  
  // 1. Aktivace CLK na portu D
  RCC->AHB1ENR |= (1UL << 3);
  
  // 2. Nastaveni pro radky - ZACATEK
  for (i = 6; i < 10; i++) {
    GPIOD->MODER   &= ~(3UL << 2*i);  // Reset; INPUT
    GPIOD->MODER   |=  (1UL << 2*i);  // Nastaveni pinu jako OUTPUT
    
    GPIOD->OTYPER  &= ~(1UL << 1*i);  // Push-pull (dvojcinny vystup)
    
    GPIOD->OSPEEDR &= ~(3UL << 2*i);  // Reset; Low speed
    GPIOD->OSPEEDR |=  (2UL << 2*i);  // High speed
    
    GPIOD->PUPDR   &= ~(3UL << 2*i);  // Reset; No pull-up/pull-down
  }
  // 2. Nastaveni pro radky - KONEC
  
  
  // 3. Nastaveni pro sloupce - ZACATEK
  for (i = 0; i < 4; i++) {
    GPIOD->MODER &= ~(3UL << 2*i);    // Reset; INPUT
    
    GPIOD->PUPDR &= ~(3UL << 2*i);    // Reset; No pull-up/pull-down
    GPIOD->PUPDR |=  (1UL << 2*i);    // Pull-up
  }
  // 3. Nastaveni pro sloupce - KONEC                          
}

#endif  /* ARM_KIT_KPAD */
