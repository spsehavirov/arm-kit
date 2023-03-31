# SPŠE ARM kit

<!-- ## Obecné informace o projektu -->

Projekt pro výuku základů programování MCU (registry) ve 3. ročníku.

## Organizace projektu

| Adresář               | Popis                                                           |
|-----------------------|-----------------------------------------------------------------|
| `docs/`               | Dokumentace k projektu (stažená zvlášť - git modul).            |
| `examples/`           | Ukázkové zdrojové kódy (HW testy).                              |
| `include/`            | Drivery nejen pro použité periférie.                            |
|                       |    chrono.h  [driver pro práci s CLK]                           |
|                       |    KPAD.h    [driver pro práci s KPAD]                          |
|                       |    LCD.h     [driver pro práci s LCD]                           |
| `src/`                | Zdrojové kódy pro vlastní úlohy.                                |
|                       |    assignments_for_better_practice.txt [zadání pro procvičení]  |
|                       |    main.c [základní kostra programu]                            |

## Podpora

Projekt pro správnou funkci potřebuje (minimálně) následující balíčky podpory (DFP):

| Platforma (deska)     | Balíček s podporu                                               |
|-----------------------|-----------------------------------------------------------------|
| F407                  | `Keil.STM32F4xx_DFP.2.7.0.pack`                                 |

Testováno s `ARM Keil uVision 5.18.0.0`.

#### Copyright SPSE Havirov (c) 2023
