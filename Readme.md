# Dokumentation MsgApplication

## Prinzip des Programmes
Das Prinzip des Programmes ist, das der Benutzter einen Text eingeben kann, welcher mit der RSA-Verschlüsselung verschlüsselt wird.

## Benutzte Klassen
### Auflistung aller benutzten Klassen in dem Programm

- MsgApplication.cpp
- generateKey.cpp
- calcW.cpp
- endecrypt.cpp
- window.cpp

## Erkl�rung der einzelnen Klassen

### MsgApplication.cpp
Main Klasse. Das Programm startet hier und ruft die anderen Klassen auf.

`thread t3(&generateKey::newThreadToCheck, &keyget);`
Erstellt einen neuen Thread, welcher parallel zum Main Thread das Schl�sselpaar generiert.

`window.create();`
Ruft die Funktion von window.cpp �void create()� auf. Diese sorgt f�r die Erstellung des Fensters.

### generateKey.cpp
Klasse, die ausschlie�lich am Anfang des Programms aufgerufen wird, um die Schl�ssel zu erstellen.

`void generateKey::newThreadToCheck()`
Diese Funktion wird vom neu erstellten Thread aus MsgApplication aufgerufen. Sie pr�ft, ob schon ein Schl�ssel vorliegt. Sollte dies nicht der Fall sein, wird ein neues Schl�sselpaar erstellt (bisher wird der generierte Schl�ssel noch nicht gespeichert).
Sollte kein Schl�ssel vorliegen (kann es noch gar nicht), wird die Funktion generate() aufgerufen.
Anschlie�end werden die generierten Werte in die Funktion der Klasse endecrypt()

`void generateKey::generate()`
Wird von der Funktion newThreadToCheck

### calcW.cpp
Klasse 