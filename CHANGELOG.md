# Změny a vývoj projektu

## [next]:

## [1.0.5] - 2023-03-31

Uprava repozitáře tak, aby umožňoval automatizaci
pomocí GitHub Actions. Přechod na formát keepachangelog 1.1.0.

### Added:
 - (#0807930) Přidání podpory pro doxygen dokumentaci (WIP #3)
 - (#8cf349e, #3e81e90) Automatický release na github

### Modified
 - (#20f8b62) formatování a malé úpravy souborů

## [1.0.0] - 2023-03-23

- `Del`: Odstranění historie ze všech driverů a ukázkových zdrojových kódů.
- `Mod`:
  - CHANGELOG.md doplněn o odstraněnou historii.
  - Drobná úprava všech hlavních komentářů.
- `Add`: Upload projektu na GitHub a jeho zveřejnění.


## [0.5][19-March-2023]:

- `Mod`: U všech ukázkových zdrojových kódů:
  - Zpřehlednění a zjednodušení kódu.
    - Odebrání nepotřebných funkcí, zaměření pouze na jednoduchou ukázku použití.
  - Revize dílčích komentářů a jejich přesun na pravou stranu v kódu.
  - Drobná revize hlavního komentáře a popisu programu.
- `Add`: Všem driverům přidána direktiva pro ošetření jejich opětovného vložení.
- `example_03-userButton.c_01-controlLED.c`
  - Drobná revize historie.
- `KPAD.h`
  - Přejmenování driveru `KeyPad.h` na `KPAD.h`.
  - Změna názvu funkcí `KeyPad_***()` na `KPAD_***()`.
  - Rozšíření o 4. sloupec (pro KeyPad 4x4)
    - Úprava masky pro aktivaci sloupce.
    - Úpravy hodnot pro zachycení klávesy (hodnoty pro case).
  - `KPAD_getKey()`: Zobecnění funkce.
- `LCD.h`
  - Revize všech LCD maker a hlavního komentáře.
  - Změna číslování řádků a sloupců LCD včetně přejmenování příslušných maker:
    - `LCD_LINE1` změněno na `LCD_LINE0` apod.
  - Přidání konstanty `LCD_RESOLUTION`, která je generována z uživatelem definovaného rozložení LCD.
  - Změna časování na milisekundy, místo mikrosekund.
    - `delay_us()` nahrazena univerzální `delay()`.


## [0.4][05-March-2023]:

- `Mod`: Změna názvu projektu na `arm-kit`.
- `chrono.h`
  - Funkce `delay()` přejmenována na `cekej()` (funkčnost zachována).
    - Jako jediná je česky a slouží pro umělé pozdržení programu.
  - Odstranění funkcí `delay_ms()` a `delay_us()`.
  - Přepracovaná funkce `delay()` využívající nyní `SysTick Timer`.
    - Na základě jeho konfigurace pozdrží program v rámci mikro/milisekund.
  - Odstranění souboru chrono.md, jeho obsah přesunut zpět do driveru chrono.h a revidován.
  - Přidáno defaultně vytvářené makro `CLK_DIV` - dělička CLK, využívána při konfiguraci `SysTick Timer`.
- `example_01-builtinLED.c` a `example_02-externalLED.c`
  - Přidání názvů barev pro vestavěné LED do hlavního komentáře.
  - Vyčlenění práce se SysTick Timer do samostatných ukázkových zdrojových kódů.
- `example_03-userButton.c`
  - Změna popisu programu.
- Změna názvů všech ukázkových zdrojových kódů, pro snadnější orientaci a budoucí rozšíření:
  | Ukázkové zdrojové kody                | Popis                                               |
  |---------------------------------------|-----------------------------------------------------|
  | example_01-builtinLED_01.c            | Blikání vestavěných LED [bez využití časovače]      |
  | example_01-builtinLED_02-SysTick.c    | Blikání vestavěných LED [s využitím SysTick Timer]  |
  | example_02-externalLED_01.c           | Blikaní externích LED [bez využití časovače]        |
  | example_02-externalLED_02-SysTick.c   | Blikaní externích LED [s využitím SysTick Timer]    |
  | example_03-userButton_01-controlLED.c | Podle stavu tlačítka svítí vestavěné/externí LED    |
  | example_04-LCD_01.c                   | HW test LCD                                         |
  | example_04-Keypad_01.c                | HW test KeyPad                                      |


## [0.3][02-March-2023]:

- `LCD.h`
  - Změna názvu funkce `LCD_symbol()` na `LCD_put()` (funkčnost zachována).
  - Nové funkce:
    - `LCD_setCursor()` pro nastavení pozice kurzoru na LCD.
    - `LCD_clear()` pro smazání zobrazeného obsahu.


## [0.2][28-February-2023]:

- `Mod`: Všechny ukázkové zdrojové kódy rozšířeny o reset módu PINu, při jeho nastavování.
- `example_01-builtinLED.c`, `example_02-externalLED.c` a `example_03-userButton.c`
  - Přidání drobného popisu k práci s LED respektive tlačítkem.
  - Rozšířeny o použití driveru chrono.h.
- `chrono.h`
  - Vyčlenění popisu a ukázek do externího soboru chrono.md.


## [0.1][26-February-2023]:

- První verze projektu `ARM`.
- První verze driverů:
  - `chrono.h` pro práci s CLK u F407, včetně popisu a ukázek.
  - `LCD.h` obsahující základní rutiny pro práci s řadičem LCD `HD44780`.
  - `KeyPad.h` obsahující základní rutiny pro práci s klávesnicí 3x4.

| Ukázkové zdrojové kody    | Popis                                             |
|---------------------------|---------------------------------------------------|
| example_01-builtinLED.c   | Blikání vestavěných LED                           |
| example_02-externalLED.c  | Blikaní externích LED                             |
| example_03-userButton.c   | Podle stavu tlačítka svítí vestavěné/externí LED  |
| example_04-LCD.c          | HW test LCD                                       |
| example_04-KeyPad.c       | HW test KeyPad                                    |

