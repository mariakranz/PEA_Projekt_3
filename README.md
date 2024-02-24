# Implementacja i analiza efektywności algorytmu genetycznego (ewolucyjnego) dla problemu komiwojażera

Zadanie polegało na zaimplementowaniu algorytmu genetycznego rozwiązującego problem komiwojażera i zbadaniu jego wyników dla trzech rozmiarów grafów (z plików ftv47.xml, ftv170.xml, rgb403.xml).  

Zaimplementowane zostało krzyżowanie OX (Order Crossover) oraz dwa typy mutacji - Inversion Mutation oraz Swap Mutation.  

Dla każdej wielkości grafu, i osobno każdej mutacji, przeprowadzono serię pomiarów dla trzech rozmiarów popoulacji: 500/2000/5000 osobników.  
Kryterium stopu to czas podawany w sekundach.

Wyniki testów:

| Plik   | Liczba wierzchołków | Czas [s] |  Najlepsza znaleziona ścieżka (o minimalnym koszcie) / Ścieżka optymalna | Rodzaj mutacji | Wielkość populacji |
| -------|---------------------|----------|--------------------------------------------------------------------------| -------------- | -------------------|
| ftv47  |         48          |   120    |                                1790 / 1776                               |   Inversion    |        5000        |
| ftv170 |        171          |   240    |                                3417 / 2755                               |   Inversion    |        5000        |
| rgb403 |        403          |   360    |                                2497 / 2465                               |     Swap       |        500         |
