# Vor jedem Builden an Sergey Dmitriev, Eugene Belyaev und Valentin Kipiatkov beten

## Grundlegend:
Sprache: Englisch

Pro Schleife eine Einrückung

``` c++
for (int i = 0; i < 10; ++i)
{
  std::cout << i << std::endl;
}
```

Klammer {} nach Schleife eine Zeile untendrunter - weiterer Code wird wieder eine Zeile darunter geschrieben

``` c++
if (i = 5)
{
  i = i++;
}
```

"Space" nach und vor Kommata, Operatoren, Doppelpunkten, Semikolon, Rechnungen; Kein "Space" bei Klammern (zb: if()) kein "Space" vor "!"

``` c++
for (int i = 0; i < 10; ++i)
{
  std::cout<<i<<std::endl;
}
```

Sinnabschnitte: bei Teilen, die im Code nicht unmittelbar zusammenhängen, wird 1 line bis zum nächsten Code freigelassen

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

Variablen/Funktionen werden sinnhaft/verständlich benannt
``` c++
int add(int x, int y)
{
  return x + y;
}

int main()
{
  int number1 = 5;
  int number2 = 3;
    
  int result = add(number1, number2);
}
```

Erklärende Kommentare bei nicht ganz trivialem Code

``` c++
int sum(int a, int b)
{
  // Explanation: The sum of both numbers will be calculated and returned
  return a + b;
}

int main()
{
  int x = 5;
  int y = 3;

  // Explanation: The sum of both numbers will be calculated and safed in the variable result
  int result = sum(x, y);
}
```

Code so klein wie möglich halten, soviel wie möglich in funktionen ausarbeiten/automatisieren

``` c++
#include <iostream>
#include <vector>
#include <algorithm>

// Function to calculate the sum of all elements in a vector
int calculateSum(const std::vector<int>& nums)
{
  int sum = 0;
  for (int num : nums)
  {
    sum += num;
  }
  return sum;
}

int main()
{
  // A vector of numbers
  std::vector<int> numbers = {1, 2, 3, 4, 5};

  // Calculate the sum of the numbers
  int sum = calculateSum(numbers);

  // Print the result
  std::cout << "The sum of the numbers is: " << sum << std::endl;

  return 0;
}
```

Enums, Klassen, Namespaces und Structs werden großgeschrieben, alle anderen variablen klein

``` c++
#include <iostream>

// Enum 
enum class Fruit
{
  Banana
};

// Class
class FruitBasket
{
  public:
  // Constructor 
  FruitBasket(Fruit f) : fruit(f) {}

  void printFruit()
  {
    std::cout << "Banana" << std::endl;
  }
}

private:
    Fruit fruit; // Private variable
};

int main()
{
  FruitBasket basket(Fruit::Banana);
  basket.printFruit();
  return 0;
}
```

Bei do while Schleifen wird das while nach der Klammer geschrieben, nicht in eine Extrazeile.

``` c++
int main()
{
  int i = 0;
  do
  {
    std::cout << "Wert von i: " << i << std::endl;
    i++;
  } while (i < 5);

  return 0;
}
```

In der main.cpp stehen am besten nur Klassenfunktionen. So wenig anderer Code wie möglich.

``` c++
#include "MyClass.h"

int main()
{
  Class myObjectClass;
  myObjectClass.classFunction(); // Call of function, nothing else
    
  return 0;
}
```

Es wird nur funktionierender Code commited.

Verwendung von sinnhaften Namespaces um Zusammenhänge klar sichtbar zu machen.

``` c++
#include <iostream>

namespace Geometry
{
  const double PI = 3.14159265358979323846;

  double calculateCircleArea(double radius)
  {
    return PI * radius * radius;
  }
}

namespace Physics
{
  const double GRAVITY = 9.81;

  double calculateFallDistance(double time)
  {
    return 0.5 * GRAVITY * time * time;
  }
}
```

Nach einer if Schleife muss ein else folgen.
``` c++
if(xy)
{
  xy;
}
else
{
  yx;
}
```

Pointer Benennung: x_p, y_p
``` c++
std::shared_ptr<TileMap> tile_p;

oder z.B.

shape* shape_p;
```


## Includes:
Am Anfang des Codes immer #Pragma once, danach .h und .cpp und alle includes, sortiert nach alphabetischer Reihenfolge
``` c++
#pragma once

#include "xy.h"

#include "algorithm"
#include "barrier"
#include "cstdio"
```
Code Separierung - z.B. nicht eine Klasse für 3 komplett verschiedene Funktionen/Objekte

## Klassen:
In Klassen immer Verwendung von public und protected/private
``` c++
class Player {
public:
  xy;

protected:
  xy;

};

```

enums o.ä. stehen über Klassendefinierung
``` c++
typedef enum {
  NONE = 0,
  COLOR_GRAYSCALE,
  COLOR_TINT,
  PRINT_PIXEL_COLORS
} ImageProcess;

class TileMap {};
```

Alle von Klassen erstellte Objekte haben einen gleichen Namensaufbau
``` c++
Class1 myClass1;
Class2 myClass2;
```

Klassenfunktionen werden klein geschrieben

Erklärungen über Klassen: Was macht die Klasse?

Es muss in einer Klasse einen Konstruktor und einen Destruktor geben.

Bei 2 Konstruktoren muss sich der erste schließen bevor der 2. anfängt.

Der Konstruktor wird als erstes in einer Klasse geschrieben.
``` c++
/* This class is used for drawing the player...*/
class Player {
public:
  Player(); //Konstruktor an 1. Stelle

  void draw(); //Funktion klein geschrieben

  ~Player(); //Destruktor an letzter stelle in public

protected:
  int playerX; //Variable klein geschrieben

};
```

