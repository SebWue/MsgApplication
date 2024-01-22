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
Genauere Erkl�rung in [window.cpp](#window.cpp)

### generateKey.cpp
Klasse, die ausschlie�lich am Anfang des Programms aufgerufen wird, um die Schl�ssel zu erstellen.

`void generateKey::newThreadToCheck()`
Diese Funktion wird vom neu erstellten Thread aus MsgApplication aufgerufen. Sie pr�ft, ob schon ein Schl�ssel vorliegt. Sollte dies nicht der Fall sein, wird ein neues Schl�sselpaar erstellt (bisher wird der generierte Schl�ssel noch nicht gespeichert).
Sollte kein Schl�ssel vorliegen (kann es noch gar nicht), wird die Funktion generate() aufgerufen.
Anschlie�end werden die generierten Werte in die Funktion der Klasse endecrypt()

`void generateKey::generate()`
Wird von der Funktion `newThreadToCheck()` aufgerufen, sollte kein Schl�ssel gefunden worden sein. Sie generiert ein Schl�sselpaar, welches im weitern Verlauf des Programmes zum Ver- und Entschl�sseln genutzt wird.
Das Schl�sselpaar wird von zwei zuf�llig ausgew�hlten Primzahlen `UINT q, p` aus Liste `vector<UINT>primes`, diese wird jeden Programmstart neu errechnet, ausgew�hlt. Die beiden Primzahlen werden anschlie�end miteinenannder Multipliziert, sodass man die Variable `UINT n` erh�lt.
Um nun die Variable `UINT m` zu erhalten subtrahiert man die einzelen werte `p, q` mit 1, sodass man die Operation `m = (p - 1) * (q - 1);` bekommt. 
Jetzt hat man alle Werte welche man ben�tigt um die Variable `UINT e` zu brerechnen, welche in diesem Programm der �ffentliche Schl�ssel ist.
Die Kriterien die man beachten muss bei der generierung von `e` ist, das `e` Teilerfremd zu und kleiner als `m` sein muss. Dazu erstellen wir erst ein Vektor, welcher alle Teiler von m speichert. Diesen f�llen wir, indem das Programm eine Tempor�re Variable `mcurr` welche gleich `m` gesetzt wird in einer for-Schleife durch den Wert von der Z�hler-Variable `i` geteilt wird, sollte der Modulo von `m % i == 0` sein. Sollte dies der Fall sein, wird `mcurr` nun also durch `i` geteilt und `i` wird in dem Vektor `partofm` gespeichert. Wichtig ist es zu beachten, dass die Z�hlervariable `i` mit 2 startet, da sonst der Vektor mit dem Wert 1 geflutet wird, da dieser 1 bei einer Divison immer einen Rest von 0 hat.
Um nun `e` tats�chlich bestimmen zu k�nnen, w�hlen wir Zuf�llig aus dem Vekor eine Primzahl aus, und gucken ob die Kriterien auf sie zutreffen.

Nun fehlt uns nur noch der Wert `UINT d`, welcher hier der private Schl�ssel ist.

### calcW.cpp
Selbst erstellte Klasse zum Rechnen gro�en Zahlen mit Hilfe von Vektoren.

`vector<int> calcW::turninttoarray(int a)`
Schreibt einen Integer in einen Vektor, indem die Zahl modulo 10 (a % 10) gerechnet wird um die letzte (kleinste noch vorhandene Zahl) in den Vektor zu schreiben

### endecrypt.cpp

### window.cpp
