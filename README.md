README
Opis programu:
Program rysuje figury na canvasie ASCII zgodnie ze specyfikacją podaną w pliku konfiguracyjnym. Obsługiwane figury to: koło (Circle), prostokąt (Rectangle) oraz kwadrat (Square). Wynik jest zapisywany do pliku tekstowego, gdzie figury są przedstawione za pomocą różnych symboli.

Format pliku konfiguracyjnego:
Plik konfiguracyjny zawiera informacje o wymiarach canvasu, pliku wyjściowym oraz specyfikacji figur do narysowania. Struktura pliku konfiguracyjnego jest następująca:

    1)Wymiary canvasu: szerokość i wysokość (np. 20 10)

    2)Nazwa pliku wyjściowego (np. output.txt)

    3)Symbol oznaczający piksel nienależący do żadnej figury (np. ' ')

    4)Lista figur do narysowania, gdzie każda figura jest opisana linią tekstu w formacie:
        Koło (Circle): Circle x y radius symbol
            x - współrzędna X środka koła
            y - współrzędna Y środka koła
            radius - promień koła
            symbol - symbol użyty do narysowania koła
        Prostokąt (Rectangle): Rectangle x y width height symbol
            x - współrzędna X lewego górnego rogu prostokąta
            y - współrzędna Y lewego górnego rogu prostokąta
            width - szerokość prostokąta
            height - wysokość prostokąta
            symbol - symbol użyty do narysowania prostokąta
        Kwadrat (Square): Square x y side symbol
            x - współrzędna X lewego górnego rogu kwadratu
            y - współrzędna Y lewego górnego rogu kwadratu
            side - długość boku kwadratu
            symbol - symbol użyty do narysowania kwadratu
            
Kompilacja i uruchomienie programu:
Aby skompilować program, użyj kompilatora C++: g++ -o draw draw.cpp
Program uruchamia się, przekazując plik konfiguracyjny jako argument: ./draw config.txt
