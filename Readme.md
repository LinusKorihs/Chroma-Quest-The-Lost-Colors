Grundlegend:
Sprache: Englisch

Pro Schleife eine Einrückung

Klammer {} nach Schleife eine Zeile untendrunter - weiterer Code wird wieder eine Zeile darunter geschrieben

"Space" nach und vor Kommata, Operatoren, Doppelpunkten, Semikolon, Rechnungen; Kein "Space" bei Klammern (zb: if()) kein "Space" vor "!"

Sinnabschnitte: bei Teilen, die im Code nicht unmittelbar zusammenhängen, werden 2 lines bis zum nächsten Code freigelassen

Variablen/Funktionen werden sinnhaft/verständlich benannt

Erklärende Kommentare bei nicht ganz trivialem Code

code so klein wie möglich halten, soviel wie möglich in funktionen ausarbeiten/automatisieren

enums, klassen und structs werden großgeschrieben, alle anderen variablen klein

Bei do while Schleifen wird das while nach der Klammer geschrieben, nicht in eine Extrazeile.

In der main.cpp stehen am besten nur Klassenfunktionen. So wenig anderer Code wie möglich.

Es wird nur funktionierender Code commited.

Verwendung von sinnhaften namespaces um Zusammenhänge klar sichtbar zu machen.

Nach einer if Schleife muss ein else folgen.

Pointer Benennung: x_p, y_p


Includes:
Am Anfang des Codes immer #Pragma once, danach .h und .cpp und alle includes, sortiert nach alphabetischer reihenfolge

Klassen:
In Klassen immer Verwendung von public und protected/private

enums o.ä. stehen über Klassendefinierung

Alle von Klassen erstellte Objekte haben einen gleichen Namensaufbau: (bsp) Class1 myClass1, Class2 myClass2

Klassenfunktionen werden klein geschrieben

Code Separierung - z.B. nicht eine Klasse für 3 komplett verschiedene Funktionen/Objekte

Erklärungen über Klassen: Was macht die Klasse?

Es muss in einer Klasse einen Konstruktor und einen Destruktor geben.

Bei 2 Konstruktoren muss sich der erste schließen bevor der 2. anfängt.

Der Konstruktor wird als erstes in einer Klasse geschrieben.
