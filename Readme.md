# Dokumentation MsgApplication

## Prinzip des Programmes
Das Prinzip des Programmes ist, das der Benutzter einen Text eingeben kann, welcher mit der RSA-Verschlüsselung verschlüsselt wird.

## Benutzte Klassen
### Auflistung aller selbstgeschriebenen und benutzten Klassen in dem Programm

- MsgApplication.cpp
- generateKey.cpp
- calcW.cpp
- endecrypt.cpp
- window.cpp

## Importierte Funktionen/Libaries und DatenTypen

- windows.h -> benutzt für das Fenster und Windows eigene Datentypen (UINT, TCHAR, ...)
- thread -> benutzt für die Gleichzeitige Erstellung von dem Fenster und dem Schüssel
- iostream -> "Standart" Bibilotek, vereinfacht die Ausgabe von Text, Variablen, usw...; Viele andere Bibiloteken bauen auf ihr auf
- vector -> auch Liste genannt, dynamisches Array, was die Handhabung von Arrays einfacher macht (keine statische Größe, mehr möglichkeiten mit den daten zu interagieren(.push_back(); .size(); .clear(); ...), ...)
- chrono -> benutzt um die Ausführungszeit eines Programmabschnittes zu bekommen
- math.h -> nur für pow(x,y) benutzt
- WindowsX.h -> Benutzt um die X und Y Koordinaten aus der System-Nachicht zu bekommen, welche bei einem Mausklick abgeschickt wird (GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam))

## Erklärung der einzelnen Klassen (chronoligisch)

### MsgApplication.cpp
Main Klasse. Das Programm startet hier und ruft die anderen Klassen auf.

`thread t3(&generateKey::newThreadToCheck,&keyget);`
Erstellt einen neuen Thread, welcher parallel zum Main Thread das Schlüsselpaar generiert.

`window.create();`

Ruft die Funktion von window.cpp “void create()” auf. Diese sorgt für die Erstellung des Fensters.
Genauere Erklärung in [window.cpp](#window.cpp)

### generateKey.cpp
Klasse, die ausschließlich am Anfang des Programms aufgerufen wird, um die Schlüssel zu erstellen.

`void generateKey::newThreadToCheck()`
Diese Funktion wird vom neu erstellten Thread aus MsgApplication aufgerufen. Sie prüft, ob schon ein Schlüssel vorliegt. Sollte dies nicht der Fall sein, wird ein neues Schlüsselpaar erstellt (bisher wird der generierte Schlüssel noch nicht gespeichert).
Sollte kein Schlüssel vorliegen (kann es noch gar nicht), wird die Funktion generate() aufgerufen.
Anschließend werden die generierten Werte in die Funktion der Klasse endecrypt()

`void generateKey::generate()`
Wird von der Funktion `newThreadToCheck()` aufgerufen, sollte kein Schlüssel gefunden worden sein. Sie generiert ein Schlüsselpaar, welches im weitern Verlauf des Programmes zum Ver- und Entschlüsseln genutzt wird.
Das Schlüsselpaar wird von zwei zufällig ausgewählten Primzahlen `UINT q, p` aus Liste `vector<UINT>primes`, diese wird jeden Programmstart neu errechnet, ausgewählt. Die beiden Primzahlen werden anschließend miteinenannder Multipliziert, sodass man die Variable `UINT n` erhält.
Um nun die Variable `UINT m` zu erhalten subtrahiert man die einzelen werte `p, q` mit 1, sodass man die Operation `m = (p - 1) * (q - 1);` bekommt. 
Jetzt hat man alle Werte welche man benötigt um die Variable `UINT e` zu brerechnen, welche in diesem Programm der öffentliche Schlüssel ist.
Die Kriterien die man beachten muss bei der generierung von `e` ist, das `e` Teilerfremd zu und kleiner als `m` sein muss. Dazu erstellen wir erst ein Vektor, welcher alle Teiler von m speichert. Diesen füllen wir, indem das Programm eine Temporäre Variable `mcurr` welche gleich `m` gesetzt wird in einer for-Schleife durch den Wert von der Zähler-Variable `i` geteilt wird, sollte der Modulo von `m % i == 0` sein. Sollte dies der Fall sein, wird `mcurr` nun also durch `i` geteilt und `i` wird in dem Vektor `partofm` gespeichert. Wichtig ist es zu beachten, dass die Zählervariable `i` mit 2 startet, da sonst der Vektor mit dem Wert 1 geflutet wird, da dieser 1 bei einer Divison immer einen Rest von 0 hat.
Um nun `e` tatsächlich bestimmen zu können, wählen wir Zufällig aus dem Vekor eine Primzahl aus, und gucken ob die Kriterien auf sie zutreffen.

Nun fehlt uns nur noch der Wert `UINT d`, welcher hier der private Schlüssel ist.

### calcW.cpp
Selbst erstellte Klasse zum Rechnen großen Zahlen mit Hilfe von Vektoren.

`vector<int> calcW::turninttoarray(int a)`
Schreibt einen Integer in einen Vektor, indem die Zahl modulo 10 (a % 10) gerechnet wird um die letzte (kleinste noch vorhandene Zahl) in den Vektor zu schreiben

### endecrypt.cpp

### window.cpp
