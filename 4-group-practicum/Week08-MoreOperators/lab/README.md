# Още оператори

## Задача 1 :clock3:
Да се реализира клас `Time`, който има член-данни `hour` и `minute` от целочислен тип. Да се предефинират необходимите оператори за реализиране на следните видове изрази: 

```Time t1, t2, t3, t4, t5;```

* `t3 = t1 + t2`
* `t4 = t1 + 5` (добавя 5 часа)
* `t5 = 6 + t1` (добавя 6 часа)
* `++t3` (добавя 1 час)
* `t4++` (добавя 1 час)
* `t1 < t2`

## Задача 2 :musical_note:
Реализирайте константна и неконстантна версия на оператора `[]` за плейлиста, който реализирахте преди няколко седмици.

## Задача 3 (Music playlist V2) :musical_score::microphone:	

Реализирайте клас `Song`, състоящ се от име, жанр и продължителност (в секунди). Името и жанрът трябва да са непразни низове, заделени в динамичната памет, продължителността трябва да е цяло положително число, по-малко от 600. Класът трябва да има подходящи методи за достъп до член-данните си.

Песните ще участват в плейлист, затова всяка песен "трябва да знае" коя песен е следваща. Помислете как да реализирате това.

Реализирайте клас `Playlist`, пазещ в себе си само и единствено първата си песен. Класът трябва да има:
 - подходящ оператор за достъп на песен по индекс
 - подходящ оператор за достъп на песен по име
 - подходящ оператор за добавяне на песен в края на прейлиста
 - подходящ оператор за премахване на песен (запазващ относителния ред на песните)
 - подходящи оператори, даващи следното поведение:
```c++
Playlist p;

...

if (p)
{
    std::cout << "The playlist is empty\n"; 
}
else
{
    std::cout << "The playlist is not empty\n";
    p(); // отпечатва последователно имената на песните в плейлиста
}
 ```
 - метод, даващ информация за общата продължителност на плейлиста
 - метод, даващ информация колко песни съдържа плейлистът.

В `main` създайте плейлист от поне 5 песни и демонстрирайте работата на горните оператори.

Навсякъде, където мислите, че е редно, хвърлете подходящо изключение. Не забравяйте също така да обработите всяко хвълено изключение по подходящ начин.
