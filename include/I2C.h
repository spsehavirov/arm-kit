/**
  *************************************************************************************************
  * @file       I2C.h
  * @author     SPSE Havirov
  * @version    1.0.0
  * @date       18-January-2025
  * @history    Viz CHANGELOG.md
  * @brief      Driver pro praci s I2C sbernici.
  *
  *************************************************************************************************
  * @attention
  *
  *   Zdroj:
  *     https://ruturajn.hashnode.dev/interfacing-an-i2c-based-lcd-with-stm32f407-discovery-kit
  *     https://controllerstech.com/stm32-i2c-configuration-using-registers/
  *
  *   Podporovane desky:
  *     STM32F4-DISCOVERY (STM32F407VGTx)
  *       CLK:
  *               16MHz   HSI
  *       I2C:
  *               SDA     PB7 (I2C1 - default); PB9 (I2C1), PB11 (I2C2), PC9 (I2C3)
  *               SCL     PB6 (I2C1 - default); PB8 (I2C1), PB10 (I2C2), PA8 (I2C3)
  *
  *************************************************************************************************
  * @copyright Copyright SPSE Havirov (c) 2025 *
  **********************************************
*/

#ifndef ARM_KIT_I2C
#define ARM_KIT_I2C

#include "chrono.h"                  // Pripojeni driveru pro praci s CLK.

#ifndef STRING_H_
  #include <string.h>
#endif

//#================================================================================================
//#=== Prototypy funkci pro I2C - ZACATEK
void I2C_GPIO_init(void);
void I2C_init(void);
void I2C_start(void);
void I2C_write(uint8_t);
void I2C_send_addr(uint8_t addr);
void I2C_stop(void);
//#=== Prototypy funkci pro I2C - KONEC
//#================================================================================================

//#================================================================================================
//#=== Rutiny pro praci s I2C - KONEC
/**
 * @brief  Nastaveni PINu pro I2C.
 *
 */
void I2C_GPIO_init(void) {
  // 1. Aktivace CLK na portu B
  RCC->AHB1ENR |= (1UL << 1);
  
  // 2. Reset a nastaveni smeru PINu
  GPIOB->MODER &= ~(3UL << (SDA_PIN*2));    // Reset (input mode)
  GPIOB->MODER |= (2UL << (SDA_PIN*2));     // Alternativni rezim
  
  GPIOB->MODER &= ~(3UL << (SCL_PIN*2));    // Reset (input mode)
  GPIOB->MODER |= (2UL << (SCL_PIN*2));     // Alternativni rezim
  
  // 3. Reset a nastaveni PINu jako pull-up
  GPIOB->PUPDR &= ~(3UL << (SDA_PIN*2));    // Reset (no pull-up, no pull-down)
  GPIOB->PUPDR |= (1UL << (SDA_PIN*2));     // pull-up
  
  GPIOB->PUPDR &= ~(3UL << (SCL_PIN*2));    // Reset (no pull-up, no pull-down)
  GPIOB->PUPDR |= (1UL << (SCL_PIN*2));     // pull-up
  
  // 4. Reset a nastaveni PINu jako otevreny kolektor
  GPIOB->OTYPER &= ~(1UL << SDA_PIN);       // Reset (output push-pull)
  GPIOB->OTYPER |= (1UL << SDA_PIN);        // OUTPUT open-drain
  
  GPIOB->OTYPER &= ~(1UL << SCL_PIN);       // Reset (output push-pull)
  GPIOB->OTYPER |= (1UL << SCL_PIN);        // OUTPUT open-drain
  
  // 5. Reset a nastaveni rychlosti PINu
  GPIOB->OSPEEDR &= ~(3UL << (SDA_PIN*2));  // Reset (low speed)
  GPIOB->OSPEEDR |= (2UL << (SDA_PIN*2));   // High speed
  
  GPIOB->OSPEEDR &= ~(3UL << (SCL_PIN*2));  // Reset (low speed)
  GPIOB->OSPEEDR |= (2UL << (SCL_PIN*2));   // High speed
  
  // 6. Vyber alternativniho rezimu - jaky alternativni rezim bude pouzit (I2C, SPI, DMA, TIM, USART, ...)
  if((SDA_PIN < 8) && (SCL_PIN < 8)) {
    GPIOB->AFR[0] |= ((4UL << 28) | (4UL << 24));   // GPIOB-> AFR[0] |= 0x44000000;
  } else {
    GPIOB-> AFR[1] |= ((4UL << 0) | (4UL << 4));    // GPIOB-> AFR[1] |= 0x00000044;
  }
}

/**
 * @brief  Inicializace I2C.
 *
 */
void I2C_init(void) {
  // 1. Povoleni CLK pro I2C
  RCC->APB1ENR |= (1UL << 21);
  
  // 2. Reset I2C
  I2C1->CR1 |= (1UL << 15);   // Neni v reset stavu
  I2C1->CR1 &= ~(1UL << 15);  // Reset stav
  
  // 3. Nastaveni 16MHz pro I2C
  I2C1->CR2 |= (16UL << 0);
  
  // 4. Softwarove musi byt 14. bit drzen v log. 1
  I2C1->OAR1 |= (1UL << 14);
  
  // 5. Nastaveni SCL na 100kHz
  I2C1->CCR |= (0x50UL << 0);
  
  // 6. Nastaveni rise time na 1000ns
  I2C1->TRISE |= (17UL << 0);
  
  // 7. Zapnuti I2C
  I2C1->CR1 |= (1UL << 0);
}

/**
 * @brief  Zahajeni komunikace na I2C.
 *
 */
void I2C_start(void) {
  // 1. Povoleni ACK bitu
  I2C1->CR1 |= (1UL << 10);
  
  // 2. Aktivace Start bitu
  I2C1->CR1 |= (1UL << 8);
  
  // 3. Kontrola, zda probehlo nastaveni v poradku (SB je v log. 1)
  while(!(I2C1->SR1 & I2C_SR1_SB)) {
    // NOP
  }
}

/**
 * @brief  Zapis na I2C.
 *
 */
void I2C_write(uint8_t data) {
  // 1. Kontrola, zda je SDA v klidovem stavu
  while(!(I2C1->SR1 & I2C_SR1_TXE)) {
    // NOP
  }
  
  // 2. Vlozeni dat na I2C
  I2C1->DR = data;
  
  // 3. Kontrola BTF (Byte Transfer Finished) bitu - cekani na dokonceni prenosu dat
  while(!(I2C1->SR1 & I2C_SR1_BTF)) {
    // NOP
  }
}

/**
 * @brief  Zapis adresy na I2C.
 *
 */
void I2C_send_addr(uint8_t addr) {
  // 1. Osloveni slave zarizeni na I2C na zaklade jeho adresy
  I2C1->DR = addr;
  
  // 2. Cekani, dokud neni adresa zpracovana
  while(!(I2C1->SR1 & I2C_SR1_ADDR)) {
    // NOP
  }
  
  // 3. Smazani adresniho bitu - prectenim jeho stavu
  addr = (I2C1->SR1 | I2C1->SR2);
}

/**
 * @brief  Ukonceni komunikace na I2C.
 *
 */
void I2C_stop(void) {
    I2C1->CR1 |= (1UL << 9);   // Aktivace Stop bitu
}
//#=== Rutiny pro praci s I2C - KONEC
//#================================================================================================

#endif
