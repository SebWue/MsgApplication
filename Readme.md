# Dokumentation MsgApplication

## Prinzip des Programmes
Das Prinzip des Programmes ist, das der Benutzter einen Text eingeben kann, welcher mit der RSA-Verschl�sselung verschl�sselt wird.

## Benutzte Klassen
### Auflistung aller selbstgeschriebenen und benutzten Klassen in dem Programm

- MsgApplication.cpp
- generateKey.cpp
- calcW.cpp
- endecrypt.cpp
- window.cpp

## Importierte Funktionen/Libaries und DatenTypen

- windows.h -> benutzt f�r das Fenster und Windows eigene Datentypen (UINT, TCHAR, ...)
- thread -> benutzt f�r die Gleichzeitige Erstellung von dem Fenster und dem Sch�ssel
- iostream -> "Standart" Bibilotek, vereinfacht die Ausgabe von Text, Variablen, usw...; Viele andere Bibiloteken bauen auf ihr auf
- vector -> auch Liste genannt, dynamisches Array, was die Handhabung von Arrays einfacher macht (keine statische Gr��e, mehr m�glichkeiten mit den daten zu interagieren(.push_back(); .size(); .clear(); ...), ...)
- chrono -> benutzt um die Ausf�hrungszeit eines Programmabschnittes zu bekommen
- math.h -> nur f�r pow(x,y) benutzt
- WindowsX.h -> Benutzt um die X und Y Koordinaten aus der System-Nachicht zu bekommen, welche bei einem Mausklick abgeschickt wird (GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam))

## Erkl�rung der einzelnen Klassen (chronoligisch)

### MsgApplication.cpp
Main Klasse. Das Programm startet hier und ruft die anderen Klassen auf.

`thread t3(&generateKey::newThreadToCheck,&keyget);`
Erstellt einen neuen Thread, welcher parallel zum Main Thread das Schl�sselpaar generiert.

`window.create();`

Ruft die Funktion von window.cpp �void create()� auf. Diese sorgt f�r die Erstellung des Fensters. 
Genauere Erkl�rung in [window.cpp](###window.cpp)

### generateKey.cpp
Klasse, die ausschlie�lich am Anfang des Programms aufgerufen wird, um die Schl�ssel zu erstellen.

`void generateKey::newThreadToCheck()`
Diese Funktion wird vom neu erstellten Thread aus MsgApplication aufgerufen. Sie pr�ft, ob schon ein Schl�ssel vorliegt. Sollte dies nicht der Fall sein, wird ein neues Schl�sselpaar erstellt (bisher wird der generierte Schl�ssel noch nicht gespeichert).
Sollte kein Schl�ssel vorliegen (kann es noch gar nicht), wird die Funktion generate() aufgerufen.
Anschlie�end werden die generierten Werte in die Funktion der Klasse endecrypt()

`void generateKey::generate()`
Wird von der Funktion newThreadToCheck aufgerufen, sollte kein Schl�ssel gefunden worden sein. Sie generiert ein Schl�sselpaar, weches im weitern Verlauf des Programmes zum Ver- und Entschl�sseln genutzt wird.
Das Schl�sselpaar wird von zwei `UINT q, p` zuf�llig ausgew�hlten Primzahlen aus Liste `vector<UINT>primes`, diese wird jeden Programmstart neu errechnet, ausgew�hlt. Die beiden Primzahlen werden anschlie�end miteinenannder Multipliziert, sodass man die Variable `UINT n` erh�lt.
Um die


### calcW.cpp
Selbst erstellte Klasse zum Rechnen gro�en Zahlen mit Hilfe von Vektoren.

`vector<int> calcW::turninttoarray(int a)`
Schreibt einen Integer in einen Vektor, indem die Zahl modulo 10 (a % 10) gerechnet wird um die letzte (kleinste noch vorhandene Zahl) in den Vektor zu schreiben

### endecrypt.cpp

### window.cpp
