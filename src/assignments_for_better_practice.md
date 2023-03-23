# Příklady k procvičení:
  - Pro každý příklad doporučujeme si vytvořit nový soubor a verzovat jej.
  - Příklad kostry programu včetně hlavního komentáře je pro vás připraven v "src/main.c".
  - Ukázkové zdrojové kódy (examples/example_***.c) neměňte, ani nemažte, slouží jako jednoduché HW testy periférií.

## Builtin LED:
  `a)` Postupně rozsviťte a následně zhasněte všechny LED s využitím obyčejné funkce pro pozdržení programu.
  `b)` Postupně rozsviťte a následně zhasněte všechny LED s využitím SysTick Timer.
  `c)` Místo registru ODR použijte BSRR.

## External LED:
   - Stejné zadání, jako pro builtin LED.

## User Button:
  `a)` Na základě změny stavu tlačítka střídejte svícení všech vestavěných a všech externích LED.
  `b)` Při stisku tlačítka změňte rychlost blikání vybrané LED.
  `c)` Rozblikejte jednu LED, při každém stisknutí tlačítka rozblikejte další LED.
  
## LCD:
  `a)` Zarovnejte na střed LCD vypisovaný text.
  `b)` Na základě použitého LCD (8x2, 16x2 apod.) zaplňte všechny jeho řádky a sloupce textem.
  `c)` HW test LCD: Pomocí znaku 'H', '0' nebo '#' zaplňte celé LCD (ověření všech pixelů LCD).
  
## KPAD:
  `a)` Výpis maximálně 4 znaků na LCD, poté dojde ke smazání LCD a program pojede od začátku.
  `b)` Postupně zaplňte použité LCD znaky z KPAD (znaky se mohou opakovat).
  `c)` HW test KPAD: Stisknutou klávesu (její binární hodnotu) zobrazte pomocí LED.
