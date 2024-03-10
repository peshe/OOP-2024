# Структури. Разположение в паметта. Битови полета. Разделна компилация.

> Количествените натрупвания водят до качествени изменения.
>
> &mdash; Георг Вилхелм Фридрих Хегел

## Съдържание на темата
![Alt text](./assets/image-8.png)

## Въведение

В началото нещата, за които говорим най-вероятно ще са неясни, моят съвет е все пак да се прочетат, ще правят смисъл в ретроспекция.

Досега, по УП учихме как да създаваме променливи с типове от самия език - `int`, `double`, `bool`, `char` и т.н.

Фокусът ни от тук нататък е да използваме тези типове и да ги надградим, като започнем да създаваме **наши типове**. 
![Alt text](./assets/image-1.png)

Чрез добре измислени наши типове, имаме силата да моделираме отделните части на произволно сложен проблем, както и да моделираме как тези отделни части си взаимодействат. Това ще ни позволи да пишем четим, качествен код.

### Типове данни, дадени от езика

Tиповете данни, дадени от езика, са ни познати. Наричаме ги **primitive data types** и сме създавали не малко променливи с тях:

<small><b>Пример 1: Примитивни типове данни.</b></small>

```c++
#include <iostream>

int main() {
    int number = 42; // <-- int
    int numbers[100] = {0}; // <-- array
    char initial = 'A'; // <-- char

    return 0;
}
```

### Типове данни, създадени от нас

Има и друга "категория" типове данни, те са типовете данни, които ние можем да денифинираме. Вече сме виждали енумерациите(`enum`), които спадат в тази категория.

<small><b>Пример 2: Енумерация - дефиниране, инстанциране и сравнение.</b></small>

```c++
#include <iostream>

enum DayOfWeek {
	Monday = 0,
	Tuesday = 1,
	Wednesday = 2,
	Thursday = 3,
	Friday = 4,
	Saturday = 5,
	Sunday = 6,

};

int main() {
	DayOfWeek today = Monday; // <-- DayOfWeek, defined by us.

	if (today == Saturday || today == Sunday) {
		std::cout << "It's the weekend!";
	}
	else {
		std::cout << "It's a weekday.";
	}

	return 0;
}

```

<br/>

Структурите (`struct`) които ще разгледаме в тази тема също спадат в тази категория на типове, които ние дефинираме.

---

## Структури

Целта на една структура е да групира концептуално даден набор от данни.

Ако трябва да моделираме точка от двумерното пространство чрез код, бихме направили променливи `pointX` и `pointY`.
Структурите ни позволяват да обединим тези променливи в наш собствен тип, който можем да наречем `Point`, групирайки `x` и `y`.

<small><b>Пример 3: Моделиране на точка от пространството. Чрез променливи. Чрез структура.</b></small>
![Alt text](./assets/image-3.png)

<small><b>Пример 4: Структура - дефиниране, инстанциране и достъп до **полета(fields)**.</b></small>

```c++
#include <iostream>

struct Point {
    double x;
    double y;
};

void printPoint(Point p);

int main() {
    Point point = { 3.5, 2.5 };

    printPoint(point);

    return 0;
}

void printPoint(Point p) {
    std::cout << "Point coordinates: (" << p.x << ", " << p.y << ")" << std::endl;
}
```

Дефинираните в `Point`, `x` и `y`, отсега нататък ще наричаме **полета**.

Имайки новия тип `Point`, вече можем да го използваме като всеки друг тип, например във функцията `printPoint`, той е параметър, в картинката по-долу са показани разликите:
 1. Декларацията на функцията се промени, вместо 2 параметъра `x` и `y`, очаква само един от тип `Point` на име `p`.
 2. Самата имплементация също се променя, за да достъпим стойностите на `x` и `y`, които вече са част от структурата `Point`, трябва да използваме "оператор точка" на самия обект `p` --> `p.x`, `p.y`.

<small><b>Пример 5: Визуализация на разлики между методи приемащи параметри с примитивни типове и структури, групиращи ги. </b></small>
![Alt text](./assets/image-4.png)

### Операции със структури
Ще разгледаме различни операции със структури, за пример ще използваме структурата `Student`, която ще дефинираме по-долу.

Нека да решим следната задача:

<small><b>Задача 1: структура `Student`.</b></small>
Създайте програма на C++, която дефинира структура `Student`, съдържаща следните полета: 
 1. име (низ с дължина до 100 символа),
 2. факултетен номер (целочислен тип) и 
 3. среден успех (десетично число). 
 
В програмата трябва да извършите следните стъпки:

1. Дефинирайте структурата `Student`.
2. Инстанцирайте обект от тип `Student`, като прочетете от конзолата името, факултетния номер и средния успех на студента.
3. Напишете функция `updateGPA`, която приема обект от тип `Student` по референция и променя неговия среден успех, като също прочетете новата стойност от конзолата.
4. Напишете функция `printStudent`, която приема обект от тип `Student` и отпечатва информация за студента в конзолата.
5. В `main` функцията, след като инстанцирате и модифицирате обекта `Student`, извикайте `printStudent`, за да отпечатате актуализираната информация за студента.

#### 1. Дефиниране на структура

<small><b>Пример 6: Визуализация на дефиниране на структура `Student`. </b></small>
![alt text](./assets/image-5.png)

Преди да можем да създаваме променливи от тип `Student`, трябва да дефинираме този тип.

За да го дефинираме:
 1. Използваме ключовата дума `struct`,
 2. последвана от името на структурата, в случая `Student`
 3. в къдрави скоби дефинираме отделните полета на структурата, по същия начин както дефинираме променливи
 4. Не забравяме да добавим `;` след затварящата къдрава скоба

<small><b>Пример 7: Дефиниране на структура `Student`.</b></small>

```c++
#include <iostream>

struct Student { // <----
	char name[100];
	unsigned int facultyNumber;
	double gradePointAverage; // GPA.
};

int main() {

	return 0;
}

```

##### Какво са полета?
Полетата в една структура са отделните компоненти, които тя обединява. В случая `name`, `facultyNumber` и `gradePointAverage` са полета, които структурата `Student` обединява.

#### 2а. Създаване на обект от тип `Student`

<small><b>Пример 7: Визуализация на дефиниране на структура `Student` и създаване на обекти от този тип.</b></small>
![alt text](./assets/image-6.png)

Имайки вече дефинирам типа `Student`, можем да започнем да създаваме променливи от този тип. 
Това действие наричаме "инстанциране на обект от тип `Student`" или "създаване на обект от тип `Student`", къде обектите са различните променливи от този тип.
Когато говорим за обекти мислим за "нещо, съдържащо други неща".

<small><b>Пример 8: Създаване на обект от тип `Student`.</b></small>

```c++
#include <iostream>

struct Student {
	char name[100];
	unsigned int facultyNumber;
	double gradePointAverage; // GPA.
};

int main() {
	Student student; // <----

	return 0;
}
```

Създаваме обект от тип `Student`, както бихме създали досега позната променлива -> `Student student`.

C++ автоматично заделя памет за обекта `student` и дава случайните стойности на тези адреси в паметта на отделните полета, които са останали от последното използване на тази памет от предишни програми.
 Затова е много важно преди да използваме даден обект да въведен правилни данни в него.

<small><b>Пример 9: Случайните стойности на полетата за обект от тип `Student` при създаването му.</b></small>
![alt text](./assets/image.png)

#### 2b. Четене на данни за обект от тип `Student` от конзолата
Работим по абсолютно същия начин както бихме работим с трите променливи `name`, `facultyNumber` и `gradePointAverage`, единствената разлика е, че за да ги достъпим, трябва да използваме обектът `student` и оператор точка - `student.name`, `student.facultyNumber` и `student.gradePointAverage`.

<small><b>Пример 10: Четене и попълване на полета на обект от тип `Student`.</b></small>

```c++
#include <iostream>

using namespace std;

struct Student {
	char name[100];
	unsigned int facultyNumber;
	double gradePointAverage; // GPA.
};

int main() {
	Student student;

	cout << "Please enter up to 100 characters for your name:" << endl;
	cin.getline(student.name, 100);

	cout << "Please enter your faculty number:" << endl;
	cin >> student.facultyNumber;

	cout << "Please enter your grade point average:" << endl;	
	cin >> student.gradePointAverage;

	return 0;
}

```
<small><b>Пример 11: Стойности на полетата за обекта `student` след четене от конзолата.</b></small>
![alt text](./assets/image-2.png)

#### 3. Декларираме и дефиниране на функция, която приема обект от тип `Student` и го променя
Можем да създаваме функции, които приемат параметри от тип `Student`. В зависимост от това дали искаме да запазим промените, които сме направили в дадената функция или не, можем да изберем да приемаме параметрите по референция(`Student& student`) или по стойност(`Student student`). 

<small><b>Пример 12: Декларация и дефиниция на функция `updateGPA`, приемаща параметър от тип `Student`.</b></small>

```c++
#include <iostream>

using namespace std;

struct Student {
	char name[100];
	unsigned int facultyNumber;
	double gradePointAverage; // GPA.
};

void updateGPA(Student& student); // Function declaration.

int main() {
	Student student;

	cout << "Please enter up to 100 characters for your name:" << endl;
	cin.getline(student.name, 100);

	cout << "Please enter your faculty number:" << endl;
	cin >> student.facultyNumber;

	cout << "Please enter your grade point average:" << endl;
	cin >> student.gradePointAverage;

	updateGPA(student);

	return 0;
}


void updateGPA(Student& student) { // Function definition.
	double newGPA;

	cout << "Please enter your new GPA:" << endl;
	cin >> newGPA;

	student.gradePointAverage = newGPA;
}
```

#### 4. Декларираме и дефиниране на функция, която приема обект от тип `Student` и не го променя
Знаем че функцията `printStudent`, която трябва да напишем, няма да променя параметъра `student`, затова параметъра задаваме като `const Student& student`,
подаваме го по референция `Student&`, за да не правим излишни копирания и го правим константен `const Student`, за да не можем да го променяме в тялото на функцията.

<small><b>Пример 13: Декларация и дефиниция на функция `updateGPA`, приемаща параметър от тип `Student`, която не променя неговите стойности.</b></small>

```c++
#include <iostream>

using namespace std;

struct Student {
	char name[100];
	unsigned int facultyNumber;
	double gradePointAverage; // GPA.
};

void printStudent(const Student& student);

int main() {
	Student student;

        // ...read input from console and update GPA.

	printStudent(student);

	return 0;
}

void printStudent(const Student& student) {
	cout << "Student information below." << endl;
	cout << "Name: " << student.name << endl;
	cout << "Faculty number: " << student.facultyNumber << endl;
	cout << "GPA: " << student.gradePointAverage << endl;
}
```

#### 5. Пълното решение на задачата

<small><b>Пример 14: Пълно решение на задача 1.</b></small>

```c++
#include <iostream>

using namespace std;

struct Student {
	char name[100];
	unsigned int facultyNumber;
	double gradePointAverage; // GPA.
};

void updateGPA(Student& student);
void printStudent(const Student& student);

int main() {
	Student student;

	cout << "Please enter up to 100 characters for your name:" << endl;
	cin.getline(student.name, 100);

	cout << "Please enter your faculty number:" << endl;
	cin >> student.facultyNumber;

	cout << "Please enter your grade point average:" << endl;
	cin >> student.gradePointAverage;

	updateGPA(student);
	printStudent(student);

	return 0;
}

void updateGPA(Student& student) {
	double newGPA;

	cout << "Please enter your new GPA:" << endl;
	cin >> newGPA;

	student.gradePointAverage = newGPA;
}

void printStudent(const Student& student) {
	cout << "Student information below." << endl;
	cout << "Name: " << student.name << endl;
	cout << "Faculty number: " << student.facultyNumber << endl;
	cout << "GPA: " << student.gradePointAverage << endl;
}
```

#### 6. Добри практики. Подобрение на кода.
Текущото решение има 2 основни пропуска:
1. Има магически числа(magic numbers) за максималния размер на `name` -> винаги изкарваме магическите числа в константи!
2. Кодът в `main()` не се чете лесно, тъй като правим запълването на данни от конзолата в него - изнасяме свързаните блокове код в отделни функции и ги използваме, дори да ни трябват само веднъж!

<small><b>Пример 15: Подобрения на финалното решение на задача 1. Добри практики.</b></small>

```c++
#include <iostream>

using namespace std;

const int MAX_NAME_LENGTH = 100;

struct Student {
	char name[MAX_NAME_LENGTH];
	unsigned int facultyNumber;
	double gradePointAverage; // GPA.
};

void readStudentFromConsole(Student& student);
void updateGPA(Student& student);
void printStudent(const Student& student);

int main() {
	Student student;

	readStudentFromConsole(student);
	updateGPA(student);
	printStudent(student);

	return 0;
}
void readStudentFromConsole(Student& student) {
	cout << "Please enter up to " << MAX_NAME_LENGTH << " characters for your name : " << endl;
	cin.getline(student.name, MAX_NAME_LENGTH);

	cout << "Please enter your faculty number:" << endl;
	cin >> student.facultyNumber;

	cout << "Please enter your grade point average:" << endl;
	cin >> student.gradePointAverage;
}

void updateGPA(Student& student) {
	double newGPA;

	cout << "Please enter your new GPA:" << endl;
	cin >> newGPA;

	student.gradePointAverage = newGPA;
}

void printStudent(const Student& student) {
	cout << "Student information below." << endl;
	cout << "Name: " << student.name << endl;
	cout << "Faculty number: " << student.facultyNumber << endl;
	cout << "GPA: " << student.gradePointAverage << endl;
}
```

##### Подобрения
1. Вече кодът в `main()` метода се чете като текст на аглийски:
    1. Създай студент
    2. Прочети го от конзолата
    3. Промени му оценката
    4. Принтирай го на конзолата

2. При нужда от промяна на размера на масива `name`, промяната се случва само на едно място, в `MAX_NAME_LENGTH`, всичката останала част от кода работи както трябва, включително и `cout` съобщението към потребителя на нашата програма.

##### В какви случаи са полезни структурите - кога да ги използваме
Едно от предизвикателствата, пред което сме представени когато работим по реален проект е неяснотата.
Често се случва да не е добре описано какво се очаква от нас да направим и то най-вече описано от гледна точка на потребителя на нашето приложение,
с други думи наша е задачата да разберем какъв проблем трябва да бъде решен, да го моделираме най-добре и да го решим.

Структурите влизат в употреба когато имаме имаме дадени данни, които искаме да групираме, това ще направи кода ни по-четим и лесен за разбиране.

---

## Задачи за структури

### 1. Room
![Alt text](assets/room.png)
1. Разгледайте стаята, в която сте или стаята от снимката по-горе и изберете 5 предмета. Моделирайте тези предмети като структури, за всяка структура:
   1. Добавете поне 4-5 полета, максимално 10. Не бягайте от масиви, засега нека да **не** използват динамична памет.
   1. Дефинирайте структурата.
   1. Създайте функция `read`, която да чете данни за структурата от конзолата.
   1. Създайте функция `print`, която да показва информацията в структурата.
   1. Създайте функция `createDefault`, която връща "празен" обект от дадената структура.
2. Създайте нова структура `Room`, която съдържа всички останали структури, в зависимост от структурите ви, може да съдържа масиви от или повече от едно поле.
   1. Създайте функция `read`, която преизползва `read` функциите на останалите структури
   1. Създайте функция `print`, която преизползва `print` функциите на останалите структури
3. Създайте обект от тип `Room` и го прочетете от конзолата, после го покажете информацията за него в конзолата.


PRO TIP 1: напишете си входа в един тексов файл и paste в конзолата, това ще ви спести писането на многото входни данни при всяко изпълнение на програмата

PRO TIP 2: Използвайте debugger + breakpoints, за да намерите грешки и пропуски, ако програмата ви има неочаквано поведение

### Допълнение 1 към Room
Оптимизирайте структурите си, за да заемат минимална памет и да имат минимален padding, следвайте alignment requirements. 

За всяка структура добавете коментар, който показва броят байтове, които един обект от този тип заема в паметта.

Колко е потенциалния padding, ако обектите бяха част от масив?

### Допълнение 2 към Room
Разделете кода си по файлове на `header` и `source` файлове, спрямо добрите практики, разделете структурите, декларациите и дефинициите. Нека `main()` функцията се чете като текст на английски.


### Въпроси

###### Какво са структурите? С какво са полезни?
<details>
<summary>Отговор. Моля, първо отговори на въпроса преди да гледаш отговора.</summary>
Структурите са потребителски дефинирани типове данни в C++, които позволяват съхранението на данни от различни типове под един общ идентификатор. Те са полезни за групиране на свързани данни по удобен за използване начин.
</details>

###### Какво е декларация на функция?
<details>
<summary>Отговор. Моля, първо отговори на въпроса преди да гледаш отговора.</summary>
Декларацията на функция в C++ задава името на функцията, връщаемия тип и параметрите ѝ, без да включва тялото (дефиницията) на функцията. Тя информира компилатора за съществуването на функцията и как може да бъде извикана.
</details>

###### Какво е дефиниция на функция?
<details>
<summary>Отговор. Моля, първо отговори на въпроса преди да гледаш отговора.</summary>
Дефиницията на функция в C++ включва декларацията ѝ, както и тялото на функцията - блокът от код, който се изпълнява, когато функцията е извикана. Дефиницията предоставя конкретната реализация на функцията.
</details>

###### Какво е инстанция/обект на структура?
<details>
<summary>Отговор. Моля, първо отговори на въпроса преди да гледаш отговора.</summary>
Инстанция на структура е конкретно създаден обект от даден структурен тип. Всяка инстанция съдържа свой собствен набор от стойности за съответстващите полета, дефинирани в структурата.
</details>

###### Какво е поле на структура?
<details>
<summary>Отговор. Моля, първо отговори на въпроса преди да гледаш отговора.</summary>
Поле на структура е променлива, дефинирана в рамките на структурата. Полетата дефинират данните, които структурата съхранява, и могат да бъдат от всякакъв тип данни.
</details>

###### Какво е инициализиращ списък?
<details>
<summary>Отговор. Моля, първо отговори на въпроса преди да гледаш отговора.</summary>
Инициализиращият списък в C++ се използва за инициализация на полетата на обект при неговото създаване. Той позволява присвояването на начални стойности на полетата на обекта в момента на дефинирането му.

```c++
#include <iostream>

struct Point3D {
    double x;
    double y;
    double z;
};

int main() {
    // Create an object using initializer list.
    Point3D p = {1.23, 2.24, 15.53};

    return 0;
}

```
</details>

---

## Разположение на структурите в паметта при създаване на обекти
Когато стартираме нашата програма, операционната система заделя част от RAM паметта, която имаме на нашата машина. 

Можем да си представим, че нашата рам памет е една много дълга редица от байтове, от която заделяме дадена част при изпълнението на нашата програма.

<small><b>Пример 16: Визуализация на RAM паметта. Заделяне и използване при изпълнение на програми.</b></small>
![Alt text](./assets/image-10.png)

### Как променливи от примитивни типове са разположение в паметта

Засега знаем, че обикновено:
 1. `bool` заема 1 байт
 2. `char` заема 1 байт
 3. `int` заема 4 байта
 4. `double` заема 8 байта


<small><b>Пример 17: Създаване на променливи с примитивни типове данни.</b></small>

```c++
#include <iostream>
using namespace std;

int main() {
    bool myBool = true;         
    char myChar = 'A';          
    int myInt = 123;            
    double myDouble = 123.456; 

    return 0;
}

```

Примерно заделяне на паметта може да изглежда така. 


<small><b>Пример 18: Визуализация на заделяне на памет за различните променливи спрямо техните размери.</b></small>
![Alt text](./assets/image-9.png)

Не е задължително променливите да са една до друга в паметта. Може да бъде разположено и така.

<small><b>Пример 19: Друго възможно заделяне на паметта.</b></small>
![Alt text](./assets/image-11.png)

### Как обекти от тип структура дефинирана от нас са разположени в паметта
Когато създаваме обект от даден тип структура, самият обект заема място в паметта по строго определени правила. Знаейки тези правила, можем да дефинираме оптимални структури.

Нека разгледаме следната структура:

<small><b>Пример 20: Дефиниция на структура `WeatherData`. Създаване на обект от тип `WeatherData`.</b></small>

```c++
#include <iostream>

struct WeatherData {
    char temperatureCategory; // Category code for the temperature ('H' for hot, 'C' for cold, 'M' for moderate)
    char condition; // Condition code ('S' for sunny, 'R' for rainy, 'C' for cloudy, 'W' for windy)
    double temperatureInCelsius; // Temperature reading in degrees Celsius
    int timestamp; // Unix timestamp representing the date and time of the reading
};

int main() {
    WeatherData currentWeather = {'M', 'S', 22.5, 1617123456}; // initializer list.

    return 0;
}
```

Потелнциална първичната идея за разпределение в паметта на обекта `currentWeather` от тип `WeatherData`, би била:

<small><b>Пример 21: Примерно заделяне на памет за обект от тип `WeatherData`. (ГРЕШНО!).</b></small>
![Alt text](./assets/image-13.png)

Тази идея е грешна поради следното правило

### Изисквания за подравняване за структури (Alignment requirements)

> << Бележка след семинар II на 26.02.2024 >>
> Когато изчисляваме колко памет би заела една структура, големината на масивите влиза в изчисленията крайните, но само типът влиза при изчисленията за изискванията за подравняване относно кратност на адресите. 
(Виж задачите за по-подробни обяснения)

За оптимален достъп от операционната система, всяко едно от полетата на дадена структура **изискват да са подравнени на адрес кратен на размера на типа на даденото поле**.

<small><b>integers - 4 байта</b></small>
Това означава, че полето `timestamp`, може да започва само на адреси кратни на 4, тъй като обикновено `int` заема 4 байта в паметта. Тоест, `0x0`, `0x4`, `0x8`, `0x12` и т.н.

<small><b>chars and booleans - 1 байт</b></small>
Това важи за всяко едно поле на структурата. Обикнове с типове като `bool` и `char` нямаме проблем, тъй като те обикновено са заемат 1 байт, което означава че могат да започват на всеки адрес - `0x0`, `0x1`, `0x2`, `0x3` и т.н.

<small><b>double - 8 байта</b></small>
Както останалите типове, `double` също има свойте изисквания за подравняване, кратни на 8 - `0x0`, `0x8`, `0x16`, `0x24` и т.н.

Тъй като double има най-специфични изисквания, всички останалите полета се нареждат по него. 

Компилаторът подпълна обекта с празни байтове:

<small><b>Пример 22: Примерно заделяне на памет за обект от тип `WeatherData` спрямо спецификите на правилата за подравняване на отделните полета.</b></small>
![Alt text](./assets/image-15.png)

1. `temperatureCategory` е с размер 1, затова може на всеки адрес кратен на 1, т.е всеки адрес
2. Същото важи за `condition`
3. `temperatureInCelcius` e `double`, може на всеки адрес кратен на 8, първият такъв в случая е `0x8`
4. `timestamp` е `int`, може на всеки адрес кратен на 4, първият такъв в случая е `0x16`, непосредствено след `temperatureInCelcius`
5. Компилаторът на C++ подпълва паметта от `0x2` до `0x6` с празни байтове, за да изпълни изискванията на `double temperatureInCelcius`
6. Възможно е да има и padding за последните 4 байта, от `0x20` до `0x23`. Този padding се добавя когато имаме масив от обекти на дадената структура, за да има и подравняване между елементите на самия масив.

Един обект от структурата заема общо 24 байта в паметта.

### Как да създаване структури оптимални по памет
**Слагаме полетата с най-специфични изисквания в началото на структурата.**

Дали полето е масив или не, няма значение, интересуваме се само от типа. 

Указателите са отделен тип и те заемат 4 или 8 байта, в зависимост от операционната система(32 или 64 битова).

<small><b>Пример 23: Подобрена структура `WeatherData` чрез по-добра подредба на полетата.</b></small>

```c++
struct WeatherData {
    double temperatureInCelsius; // Temperature reading in degrees Celsius
    int timestamp;               // Unix timestamp for the date and time of the reading
    char temperatureCategory;    // Category code for the temperature ('H', 'C', 'M')
    char condition;              // Condition code ('S', 'R', 'C', 'W')
    // Potential padding here to align the structure for array access.
};
```

Съотвеното заделяне на памет вече е:

<small><b>Пример 24: Визуализация на заделяне на памет за подобрената структура `WeatherData`.</b></small>
![Alt text](./assets/image-16.png)

1. `temperatureInCelcius` e `double`, може на всеки адрес кратен на 8, първият такъв в случая е `0x0`
2. `timestamp` е `int`, може на всеки адрес кратен на 4, първият такъв в случая е `0x8`, непосредствено след `temperatureInCelcius`
3. `temperatureCategory` е с размер 1, затова може на всеки адрес кратен на 1, т.е всеки адрес, затова заема непосредствено `0x12`
4. Същото важи за `condition` - `0x13`
5. Възможно е да има и padding за последните 2 байта, от `0x14` и `0x15`. Този padding се добавя когато имаме масив от обекти на дадената структура, за да има и подравняване между елементите на самия масив.

Обект от тази структура вече заема максимално 16 байта в паметта.

---

## Задачи за разположение на структируте в паметта

### Задача 1: Потребителски профил

```c++
struct UserProfile {
    char username[11];
    bool isActive;
    unsigned int loginCount;
    double lastLoginTime;
};
```

<small><b>Въпрос 1</b></small> 
Колко памет би заела тази структура на 32-битова система?
<details>
<summary>Отговор. Моля, първо реши задачата преди да гледаш решението.</summary>
1b * 11 + 1b + 4b + 8b = 24b;
Изискванията за подравняване на всяко поле са изпълнени и няма padding.

</details>
<br/>

<small><b>Въпрос 2</b></small> 
Как би могла да бъде оптимизирана?
<details>
<summary>Отговор. Моля, първо реши задачата преди да гледаш решението.</summary>

Дадената структура е оптимизирана, тъй като `unsigned int loginCount` има 12 байта преди себе и неговите изисквания за подравняване са изпълнени, същото важи за полето `double lastLoginTime`, което има 16 байта преди себе си.

Все пак, за да следваме добрите практики е по-добре да променим структурата като пренаредим полетата:

```c++
struct UserProfile {
    double lastLoginTime;
    unsigned int loginCount;
    char username[15];
    bool isActive;
};
```

</details>
<br/>

### Задача 2: Данни за автомобил

```c++
struct CarData {
    double engineVolume;
    char brand[10];
    int yearOfManufacture;
    bool isElectric;
};
```

<small><b>Въпрос 1</b></small> 
Колко памет би заела тази структура на 64-битова система?
<details>
<summary>Отговор. Моля, първо реши задачата преди да гледаш решението.</summary>
8b + 1b * 10 + 2BP + 4b + 1b + 7BP = 32b;

BP = bytes padding.

+2BP, за да може `int yearOfManufacture` да се подравни четно на 4, т.е 20.

+7BP, защото имаме `double engineVolume`, който изисква допълване до число четно на 8 -> 32. 
</details>
<br/>

<small><b>Въпрос 2</b></small> 
Как би могла да бъде оптимизирана?
<details>
<summary>Отговор. Моля, първо реши задачата преди да гледаш решението.</summary>

```c++
struct CarData {
    double engineVolume;
    int yearOfManufacture;
    char brand[10];
    bool isElectric;
};
```
8b + 4b + 1b * 10 + 1 + 1BP = 24b;
</details>
<br/>

### Задача 3: Сензор за температура

```c++
struct TemperatureSensor {
    char id[8];
    double currentTemperature;
    bool isCalibrated;
    char unit; // 'C' for Celsius and 'F' for Fahrenheit
};
```


<small><b>Въпрос 1</b></small> 
Колко памет би заела тази структура на 64-битова система?
<details>
<summary>Отговор. Моля, първо реши задачата преди да гледаш решението.</summary>
1b * 8 + 8b + 1b + 1b + 6BP = 24b;

</details>
<br/>

<small><b>Въпрос 2</b></small> 
Как би могла да бъде оптимизирана?
<details>
<summary>Отговор. Моля, първо реши задачата преди да гледаш решението.</summary>

Структурата вече е оптимизирана, но следвайки добрите практики:

```c++
struct TemperatureSensor {
    double currentTemperature;
    char id[8];
    char unit; // 'C' for Celsius and 'F' for Fahrenheit
    bool isCalibrated;
};
```

</details>
<br/>


### Задача 4: Студентски регистър

```c++
struct StudentRecord {
    unsigned int studentID;
    char name[24];
    double gradeAverage;
    bool hasScholarship;
};
```


<small><b>Въпрос 1</b></small> 
Колко памет би заела тази структура на 64-битова система?
<details>
<summary>Отговор. Моля, първо реши задачата преди да гледаш решението.</summary>
4b + 1b * 24 + 4BP + 8b + 1b + 7BP = 48;

`double gradeAverage` изисква байтове четни на 8 преди себе си, в случая 32, затова имаме 4 байта padding, както и цялата структура да е кратна на 8, което значи +7BP в края.

</details>
<br/>

<small><b>Въпрос 2</b></small> 
Как би могла да бъде оптимизирана?
<details>
<summary>Отговор. Моля, първо реши задачата преди да гледаш решението.</summary>

```c++
struct StudentRecord {
    double gradeAverage;
    unsigned int studentID;
    char name[24];
    bool hasScholarship;
};
```
8b + 4b + 24b + 1b + 3BP = 40b;

</details>
<br/>

### Задача 5: Контактна Информация


```c++
struct ContactInfo {
    char phoneNumber[15]; 
    int birthYear;        
    float accountBalance; 
    bool hasNegativeBalance;
    char* name;           
    bool isFavorite;      
};
```

<small><b>Въпрос 1</b></small> 
Колко памет би заела тази структура на 64-битова система?
<details>
<summary>Отговор. Моля, първо реши задачата преди да гледаш решението.</summary>

1b * 15 + 1BP + 4b + 4b + 1b + 7BP + 8b + 1b + 7BP = 48b;

</details>
<br/>


<small><b>Въпрос 2</b></small> 
Колко памет би заела тази структура на 32-битова система?
<details>
<summary>Отговор. Моля, първо реши задачата преди да гледаш решението.</summary>

1b * 15 + 1BP + 4b + 4b + 1b + 3BP + 4b + 1b + 3BP = 36b;

</details>
<br/>

<small><b>Въпрос 3</b></small> 
Как би могла да бъде оптимизирана?
<details>
<summary>Отговор. Моля, първо реши задачата преди да гледаш решението.</summary>

```c++
struct ContactInfo {
    char* name;           
    int birthYear;        
    float accountBalance; 
    char phoneNumber[15]; 
    bool hasNegativeBalance;
    bool isFavorite;      
};
```

При 64 битови системи:
8b + 4b + 4b + 15b + 1b + 1b + 7BP = 40b;

При 32 битови системи:
4b + 4b + 4b + 15b + 1b + 1b + 3BP = 32b;

</details>
<br/>

---

## Битови полета


```c++
struct S
{
    // will usually occupy 2 bytes:
    unsigned char b1 : 3; // 1st 3 bits (in 1st byte) are b1
    unsigned char    : 2; // next 2 bits (in 1st byte) are blocked out as unused
    unsigned char b2 : 6; // 6 bits for b2 - doesn't fit into the 1st byte => starts a 2nd
    unsigned char b3 : 2; // 2 bits for b3 - next (and final) bits in the 2nd byte
};
 
```

---

## Задачи за Битови полета

TODO: Задачи за Битови полета

---

## Разделна компилация. Използване на отделни файлове за смислово разграничение

В практиката едно от най-големите предизвикателства е сложността, която се получава от самите мащаби на кода, който пишем. Дадени проекти могат да достигнат стотици хиляди, милиони редове код.

В по-малки мащаби имаме опит с решението на този проблем - функции. Те ни позволяват да разделяме кода си на отделни части и да мислим за тях по отделно, а след това да ги комбинираме, за да решаваме по-сложни проблеми.

Следващата стъпка е да започнем да разделяме кода си не само на функции, а и на повече от един файл.

Какво слагаме в отделните файлове? Различните структури и функции свързани с тях.

<small><b>Пример x: Визуализация на разделяне на примерен `main.cpp` на отделни файлове.</b></small>
![Alt text](./assets/image-17.png)

### Създаване и смисъл на Header файл (.hpp)
TODO: 

#### Header guards

```c++
#ifndef _HERO_HEADER_INCLUDED_
#define _HERO_HEADER_INCLUDED_

// ...code

#endif
```

### Създаване и смисъл на Source code файл (.cpp)
TODO: 

### Разделна компилация
TODO: 

---

### Задачи

- Направете структура `Address`, която включва отделни полета за държава, град, улица, блок + вход + етаж. + четене от конзола + писане в конзола, сравняване на 2 адреса дали са еднакви.
- Triangle struct - perimeter, area, methods?
- Разделяне на решената задача на повече от един файл. Методи.
