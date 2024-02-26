# Структури. Битови полета

## Задача 1 :microphone:
Гошо е най-големият купонджия в Студентски град - за него е по-важно да посещава редовно участията на любимите си изпълнители по дискотеките, отколкото да посещава лекции и упражнения (*на кого са му притрябвали ООП и Алгебра...*). Гошо иска да си направи систематизиран график за текущата седмица, с помощта на който никога няма да пропусне участие (*ако някога случайно изтърве участие на Галена, няма да може да си го прости*). Помогнете му, като реализирате структура `Performance`, която съдържа име на изпълнител и място на участието (символни низове, заделени с точна големина), както и ден от седмицата, в който ще бъде участието. За да представите деня от седмицата, създайте подходящ изброим тип.

**Бонус:** Създайте масив от участия за текущата седмица и го сортирайте според деня от седмицата.

## Задача 2 :red_circle::green_circle::large_blue_circle:
Реализирайте структура от битови полета `RGB`, съдържаща три полета, репрезентиращи трите основни цвята - червено, зелено и синьо. Полетата трябва да бъдат целочислени, приемащи стойности от 0 до 255. Създайте инстанция на структурата, представяща цвета жълто `(255, 255, 0)`.

## Задача 3 :open_file_folder:
Реализирайте структура от битови полета `FilePermissions`, даваща информация за правата на ползване върху файл или директория в операционната система. Тя трябва да съдържа по три полета (права за четене, писане и изпълнение) за текущия потребител, за групата и за всички останали. От стандартния вход прочете символен низ (с дължина 9), даващ информация за правата на ползване на някакъв файл, и според тази информация запълнете инстанция на вашата структура и изведете битовите маски на екрана.
```
Вход:
rwxr-xr-x

Обяснение:
Текущият потребител има право да чете, да пише и да изпълнява файла.
Групата има право за чете и да го изпълнява, но няма права да пише във файла.
Всички останали имат същите права като на групата.

Изход: (отпечатване на всички полета на структурата)
Owner permissions: 111
Group permissions: 101
Others permissions: 101
```

## Задача 4 - Geometry Helper :triangular_ruler:

### 3D Вектор

Първото нещо, с което сте се сблъскали в курса по **Геометрия**, е **векторът**. Един от начините за представяне на вектор е чрез координати. Понеже всичко е *по-забавно* :clown_face: в 3-мерното пространсво, векторът в нашата задача ще се характеризира с **3 координати** - *x, y, z*. За целта създайте структура `Vector3D`, съдържаща в себе си нужната информация за един тримерен вектор.

Имплементирайте следните функции, свързани с вектори:

```c++
/**
 * @brief Function to return the length of a vector
 * 
 * @param vector the vector itself
 * @return the vector length
 */
double getVectorLength(const Vector3D& vector);


/**
 * @brief Function to return the scalar products of two vectors
 * 
 * @param first the first vector
 * @param second the second vector
 * @return the scalar product of the vectors
 */
double getScalarProduct(const Vector3D& first, const Vector3D& second);

/**
 * @brief Function to check if two vectors are perpendicular
 * 
 * @param first the first vector
 * @param second the second vector
 * @return if the vectors are perpendicular
 */
bool arePerpendicular(const Vector3D& first, const Vector3D& second);

/**
 * @brief Function to return the vector product of two vectors
 * 
 * @param first the first vector
 * @param second the second vector
 * @return a new Vector3D instance for the vector product
 */
Vector3D getVectorProduct(const Vector3D& first, const Vector3D& second);

/**
 * @brief Function to return the scalar triple product of two vectors
 * 
 * @param first the first vector
 * @param second the second vector
 * @param third the third vector
 * @return the scalar triple product of the vectors 
 */
double getScalarTripleProduct(const Vector3D& first, const Vector3D& second, const Vector3D& third);
```

### 2D Точка

След всичките тези вектори, нека слезем на земята или иначе казано - в равнината. :woozy_face: Нека дефинираме най-малката единица, а именно - точката. В равнината сме, т.е. ще са ни необходими само две координати. Вземете това предвид и създайте структура `Point2D`, която би свършила работа за представяне на такава точка.

Имплементирайте следните функции, свързани с точки:

```c++
/**
 * @brief Function to return the midpoint of two points
 * 
 * @param first the first point
 * @param second the second point
 * @return a new Point2D instance for the midpoint
 */
Point2D getMidpoint(const Point2D& first, const Point2D& second);

/**
 * @brief Function to return the distance between two points
 * 
 * @param first the first point
 * @param second the second point
 * @return the distance between the points
 */
double getDistance(const Point2D& first, const Point2D& second);
```

### Права (Бонус)

Освен точки, в равнината има и прави. Всяка права се характеризира с т. нар. **уравнение на права**, което наричаме уравнение от вида: `Ax + By + C = 0`. Създайте функция, която намира уравнението на права по дадени две точки. Помислете от какви структури се нуждаете и как ще изглежда сигнатурата на функцията.

### Определения

За съжаление, в геометрията освен задачи, има и теория, мноооого теория... :cry: Едно от най-важните неща за взимане на теоретичния изпит са определенията. Напишете структура `Definition`, която представлява определение. Всяко определение се състои от име (напр. "вектор") и дефиниция (напр. "насочена отсечка, която ...")

> Забележкa: Текстовите полета трябва да са с точен размер

Създайте функция със следната сигнатура:

```c++
/**
 * @brief Function to initialize a new Definition instance from the console
 * 
 * @return a new dynamically allocated Definition instance
 */
Definition* createDefinition();
```

Помислете за подходящо реализиране на функцията така, че потребителят да разбира какво се очаква от него да направи.

### Мини изпит

Щракваме с пръсти и се пренасяме директно в лятната сесия :sparkles: - изпитът по геометрия и по-точно частта с определенията. Ще симулираме мини изпит, който изисква правилното написване на няколко определения. За тази цел създайте структура `MiniExam`, която вътре в себе си пази масив от определения с максимален размер 10.

Създайте функция, която добавя ново определение към мини изпит:

```c++
/**
 * @brief Function to add a new definition to an existing mini exam
 * 
 * @param exam the exam to which we're adding questions
 * @param definition the definition to be added
 */
void addDefinition(MiniExam& exam, const Definition* definition);
```

Помислете как ще следите колко определения имате в момента и дали не са възможни някакви проблеми при добавяне - например добавяне на определение, което е вече добавено?

### Оценяване (Бонус)

Разбира се, за да бъде оценен един студент, той трябва да напише собствена дефиниция на дадено определение. Проверяващият мини изпита в нашата задача е изключително педантичен и признава едно определение за вярно дефинирано само ако то е *1:1* съвпадащо с неговата дефиниция. Помогнете на преподавателя, като напишете функция `gradeDefinitions`, която да приема вече създаден мини изпит, както и дефинициите на студент, който прави изпита, и връща резултат - число, показващо броя на верните определения. Помислете за правилна сигнатура на функцията. Покажете действието на функцията в кратка конзолна програма.

### :warning: Забележки

- Погрижете се за правилното използване на динамична памет и не допускайте memory leaks
- Целете се към максимално спазване на чист код
- Не е позволено използването на `std::string`
- Позволено е използването на библиотеките `<cstring>` и `<cmath>`