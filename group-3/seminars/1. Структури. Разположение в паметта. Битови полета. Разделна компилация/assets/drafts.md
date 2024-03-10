# Въведение в структури

Започваме с ООП-то, разликите с това, което познаваме досега (УП) са много и трудни за обяснение и разбиране преди да натрупаме малко опит. За да не говорим неразбираема теория ще започнем със създаване на практическа идея за различните концепции, след като натрупаме знания, постепенно ще ги обединим в едно общо цялостно разбиране за материала.

Обектното-ориентирано програмине ни дава възможността да решаваме реални проблеми. Задачите които решаваме ще стават по-големи като условия, обем код и ще започват повече и повече да приличат на реални проблеми, които срещат хората.

Едно от най-големите предизвикателства е в промяната в мисленето, което трябва да направим. Досега в нашия код имаше типове като `int`, `double`, `bool`, `char`, `int[]` и т.н.

Напред освен тези типове ще имаме и типове, които ние дефинираме спрямо проблемите, които се опитваме да решим(моделираме). Една от задачите ни ще е да моделираме истинския свят възможно най-близко. Например, ако правим система свързана с обучение на студенти, може да имаме типове като `Person`, `Student`, `Course`, `Teacher`, `Address`, `Exam`, `Homework`, `Project` и т.н.

Едно от най-големите предизвикателства е в промяната в мисленето, което трябва да направим. Досега в нашия код имаше типове като `int`, `double`, `bool`, `char`, `int[]` и т.н.

Напред освен тези типове ще имаме и типове, които ние дефинираме спрямо проблемите, които се опитваме да решим(моделираме). Една от задачите ни ще е да моделираме истинския свят възможно най-близко. Например, ако правим система свързана с обучение на студенти, може да имаме типове като `Person`, `Student`, `Course`, `Teacher`, `Address`, `Exam`, `Homework`, `Project` и т.н.

Въпросът, който изниква веднага е "Откъде идват тези типове?". Отговорът е, че **ние ги създаваме**.


- дефиниране на структури в отделни файлове, excalidraw this + the include in vs
- 1 file - 1 class, 1 struct - folder structure should convey what the codebase contains clearly. There are cases where you can break this convention, for now follow it.
- define guards for double inclusion

TODO: theory practice questions
TODO: Simple tasks for understanding the syntax

- create struct
- print struct
- create a method inside the struct
- create a function that accepts the struct
- some

TODO: задачи + решения

TODO: Possibly? Show operator overload, first do it with a method add for example. Operator overload for <>?
TODO: намали размера на снимките с chatGPT
TODO: user input validation.


- масив от структури
- структура с масиви - окей, но без динамична памет
  TODO: Пример за char[] в структура



TODO: Кога използваме структури?
TODO: array vs struct
TODO: array of struct
TODO: array of structs with nested structs
TODO: Nesting structures: Triangle -> area, perimeter,

example for showing useful structs -> array of points, function that prints them, function that finds the furthest point from the center
todo: nail & hammer metaphor for oop forward and the modelling part -> read problem statement -> model the problem through user defined types - enum + struct, etc. (no dynamic memory, that's for classes)

todo: modelling part -> bad naming of Point -> Point2D, Point3D
- \*\* Задача със структура в структурата
- ** Въпроси, чиито отговори не са в текста по-горе **

# Task list (for Yasen)

TODO: spell check.
TODO: Добри практики


 - hpp files -> C++ header files - contain declarations and definitions of structs, functions
 - cpp files -> C++ source files -> contain function definitions
 - hpp files have guards and are imported
 - cpp files only import hpp files
 - 1 file combo per struct


