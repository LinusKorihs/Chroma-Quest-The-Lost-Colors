# Styleguide für ChromaQuest

## Allgemeine Regeln und Richtlinien:

Sprache für Kommentare: Englisch

Vor jedem Build: Ein 20 Minütiges Gebet an Sergey Dmitriev, Eugene Belyaev und Valentin Kipiatkov

## Formatierung und Einrückung:
### Klammernposition:

Nach Schleifen wird die öffnende Klammer "{" in die nächste Zeile geschrieben

Der Codeblock innerhalb der Klammer wieder in die darauffolgende Zeile geschrieben

#### Beispiel:
``` c++
for (int i = 0; i < 10; ++i)
{
    std::cout << i << std::endl;
}
```

### Leerzeichen:

"Space" nach und vor Kommata, Operatoren, Doppelpunkten, Semikolon, Rechnungen

Kein "Space" bei Klammern (zb: if()) 

Kein "Space" vor "!"

#### Beispiel:
``` c++
for (int i = 0; i < 10; ++i)
{
    std::cout<<i<<std::endl;
}
```

### Einrückung: 
Bei Teilen, die im Code nicht unmittelbar zusammenhängen, wird 1 line bis zum nächsten Code freigelassen

Pro Schleife eine Einrückung

#### Beispiel:
``` c++
int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}
```

## Namensvergebung:
### Variablen/Funktionen:
Namen sinnhaft und verständlich

Möglichst kurze Namen

#### Beispiel:
``` c++
int number1 = 5;
int number2 = 3;
int result = add(number1, number2);
```

### Pointer:

Pointer werden mit "_p" am Ende benannt

#### Beispiel:
``` c++
std::shared_ptr<TileMap> tile_p;
shape* shape_p;
```

###Enums, Klassen, Namespaces, Structs:

Name wird Groß geschrieben

#### Beispiel:
``` c++
enum class Fruit { Banana };
class FruitBasket {};
```

Klassenfunktionen werden klein geschrieben:

#### Beispiel:
``` c++
class Player
{
  public:
    void draw(); // Funktion klein geschrieben
};
```

## Kommentare:

Bei nicht trivialem Code sollten Kommentare hinzugefügt werden

#### Beispiel:
``` c++
int sum(int a, int b)
{
  // Explanation: The sum of both numbers will be calculated and returned
  return a + b;
}
```

## Code-Struktur:

Code sollte so klein wie möglich gehalten werden

Möglichst viel in Funktionen auslagern

#### Beispiel:
``` c++
int calculateSum(const std::vector<int>& nums)
{
  int sum = 0;
  for (int num : nums)
  {
    sum += num;
  }
  return sum;
}
```

Code in der "Main.cpp" soll so wenig anderer Code wie möglich beinhalten

Es soll hauptsächlich Klassenfunktionen beinhalten

#### Beispiel:
``` c++
#include "MyClass.h"
int main()
{
  MyClass myObject;
  myObject.classFunction(); // Call of function, nothing else
  return 0;
}
```

## Klassen und Objekte:

Klassen verwenden immer Public, Protected und Private

Es muss in einer Klasse einen Konstruktor geben

Destruktor sind nicht verpflichtend, aber erwünscht

Der Konstruktor wird als erstes in einer Klasse aufgeschrieben

#### Beispiel:
``` c++
class Player
{
  public:
    Player(); // Konstruktor an 1. Stelle
  
    void draw(); // Funktion klein geschrieben
  
    ~Player(); // Destruktor an letzter Stelle in public
  
  protected:
    int playerX; // Variable klein geschrieben
};
```

Alle von Klassen erstellten Objekte haben den gleichen Namensaufbau

#### Beispiel:
``` c++
Class1 myClass1;
Class2 myClass2;
```

## Includes:

### Reihenfolge:

Am Anfang des Codes immer "#pragma once" in .h Dateien

Danach ".h und ".cpp" Dateien in alphabetischer Reihenfolge

#### Beispiel:
``` c++
#pragma once

#include "xy.h"
#include "algorithm"
#include "barrier"
#include "cstdio"
```

## Qualität des Codes:

Nur funktionierender Code wird committed/gepusht

Keine Klasse für komplett verschiedene Funktionen/Objekte erstellen
