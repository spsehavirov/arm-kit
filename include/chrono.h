/**
  *************************************************************************************************
  * @file       chrono.h
  * @author     SPSE Havirov
  * @version    1.0.0
  * @date       26-February-2023 [v0.1]
  * @history    Viz CHANGELOG.md
  * @brief      Driver pro praci s CLK.
  *
  *************************************************************************************************
  * @attention
  *
  *   SysTick Timer:
  *     Dekrementujici casovac pracujici po restartu s frekvenci 16MHz (HSI).
  *     Do promenne "SystemCoreClock" je nahrana hodnota 16 0000 0000 (ekvivalent pro def. CLK F407).
  *
  *     Do vlastniho projektu vlozit nasledujici 2 radky:
  *       SystemCoreClockUpdate();                    // Do SystemCoreClock se nahraje frekvence jadra, viz hl. popisek v driveru pro praci s CLK.
  *       SysTick_Config(SystemCoreClock / CLK_DIV);  // Konfigurace SysTick timeru, viz hl. popisek v driveru pro praci s CLK.
  *
  *     Priklady pouziti a volani casovych funkci:
  *       SysTick_Config(SystemCoreClock);            // Konfigurace SysTick Timer na periodu 1000ms.
  *         delay(1);                                 // 1000ms
  *         delay(10);                                // 10000ms  (10s)
  *
  *       SysTick_Config(SystemCoreClock / 10);       // Konfigurace SysTick Timer na periodu 100ms.
  *         delay(1);                                 // 100ms
  *         delay(10);                                // 1000ms
  *
  *       SysTick_Config(SystemCoreClock / 100);      // Konfigurace SysTick Timer na periodu 10ms.
  *         delay(1);                                 // 10ms
  *         delay(10);                                // 100ms
  *
  *       SysTick_Config(SystemCoreClock / 1000);     // Konfigurace SysTick Timer na periodu 1ms.
  *         delay(1);                                 // 1ms
  *         delay(10);                                // 10ms
  *
  *       SysTick_Config(SystemCoreClock / 10000);    // Konfigurace SysTick Timer na periodu 0.1ms.
  *         delay(1);                                 // 0.1ms    (100us)
  *         delay(10);                                // 1ms
  *
  *************************************************************************************************
  * @copyright  Copyright SPSE Havirov (c) 2023 *
  ***********************************************
*/

#ifndef ARM_KIT_CHRONO
#define ARM_KIT_CHRONO

//#================================================================================================
//#=== Casove funkce - ZACATEK

#ifndef CLK_DIV
  #define CLK_DIV 1000          // Hodnota pro upravu CLK, viz hl. popisek.
#endif

static volatile uint32_t Ticks; // Vyuzito pro SysTick k nacitani Ticku pri podteceni.

/**
 * @brief  Rutina pro obsluhu preruseni SysTick.
 */
void SysTick_Handler(void) { Ticks++; }

/**
 * @brief  Funkce pro pozdrzeni programu s vyuzitim SysTick Timeru.
 *         Zalezi na nastaveni SysTick_Config(), viz hl. komentar.
 *
 * @param  value Hodnota odpovidajici poctu casovych jednotek pozdrzeni.
 */
void delay(uint32_t value) {
  uint32_t start = Ticks;

  while ((Ticks - start) < value) {
    /* cekani na ubehnuti casu */
  }
}

/**
 * @brief Funkce pro umele pozdrzeni programu.
 *
 * @param[in] value Hodnota v rozmezi 0 - 65535.
 */
void cekej(uint16_t value) {
  uint16_t i, j;

  for (i = 0; i < value; i++) {
    for (j = 0; j < value; j++) {
      /* __NOP(); */
    }
  }
}

//#=== Casove funkce - KONEC
//#================================================================================================

#endif  /* ARM_KIT_CHRONO */
