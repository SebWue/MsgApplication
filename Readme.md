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

## Erklärung der einzelnen Klassen (chronoligisch)

### MsgApplication.cpp
Main Klasse. Das Programm startet hier und ruft die anderen Klassen auf.

`thread t3(&generateKey::newThreadToCheck, &keyget);`
Erstellt einen neuen Thread, welcher parallel zum Main Thread das Schlüsselpaar generiert.

`window.create();`
Ruft die Funktion von window.cpp “void create()” auf. Diese sorgt für die Erstellung des Fensters.

### generateKey.cpp
Klasse, die ausschließlich am Anfang des Programms aufgerufen wird, um die Schlüssel zu erstellen.

`void generateKey::newThreadToCheck()`
Diese Funktion wird vom neu erstellten Thread aus MsgApplication aufgerufen. Sie prüft, ob schon ein Schlüssel vorliegt. Sollte dies nicht der Fall sein, wird ein neues Schlüsselpaar erstellt (bisher wird der generierte Schlüssel noch nicht gespeichert).
Sollte kein Schlüssel vorliegen (kann es noch gar nicht), wird die Funktion generate() aufgerufen.
Anschließend werden die generierten Werte in die Funktion der Klasse endecrypt()

`void generateKey::generate()`
Wird von der Funktion newThreadToCheck aufgerufen, sollte kein Schlüssel gefunden worden sein. Sie generiert ein Schlüsselpaar, weches im weitern Verlauf des Programmes zum Ver- und Entschlüsseln genutzt wird.


### calcW.cpp
Klasse 