# Имплементация на Класа Book
Спомагателен `header` файл.

```c++
// book.hpp
#ifndef __BOOK_HEADER_DEFINED__
#define __BOOK_HEADER_DEFINED__

class Book {
private:
    char* title; // Динамично алокиран низ за заглавието на книгата
    char* author; // Динамично алокиран низ за автора на книгата
    int publishYear; // Година на издаване

    // Изчиства динамично заделената памет за заглавието и автора
    void clear(); 

public:
    // Конструктор по подразбиране - инициализира полетата със стандартни стойности
    Book();
    // Параметричен конструктор - задава заглавие, автор и година на издаване
    Book(const char* title, const char* author, int publishYear);
    // Копиращ конструктор - осигурява дълбоко копие
    Book(const Book& other);
    // Оператор за присвояване - осигурява дълбоко копие и изчистване на стари стойности
    Book& operator=(const Book& other);
    // Деструктор - освобождава заделената памет
    ~Book();

    // Връща автора на книгата
    const char* getAuthor() const;
    // Връща заглавието на книгата
    const char* getTitle() const;
    // Връща годината на издаване на книгата
    int getPublishYear() const;

    // Задава ново заглавие на книгата
    void setTitle(const char* newTitle);
    // Задава нов автор на книгата
    void setAuthor(const char* newAuthor);
    // Задава нова година на издаване на книгата
    void setPublishYear(int newPublishYear);

    // Отпечатва информация за книгата
    void printBook() const;
};

#endif // !__BOOK_HEADER_DEFINED__

```

## Тестване
Използвайте кода по-долу, за да тествате дали имплементацията е коректна.

```c++
#include "book.hpp"
#include <iostream>
#include <cassert>
#include <cstring>

void testBookClass() {
    // Тестване на конструктор по подразбиране
    Book defaultBook;
    assert(std::strcmp(defaultBook.getTitle(), "No title set.") == 0);
    assert(std::strcmp(defaultBook.getAuthor(), "No author set.") == 0);
    assert(defaultBook.getPublishYear() == 0);

    // Тестване на параметричен конструктор и гетъри
    Book paramBook("Title", "Author", 1999);
    assert(std::strcmp(paramBook.getTitle(), "Title") == 0);
    assert(std::strcmp(paramBook.getAuthor(), "Author") == 0);
    assert(paramBook.getPublishYear() == 1999);

    // Тестване на копиращ конструктор
    Book copyBook(paramBook);
    assert(std::strcmp(copyBook.getTitle(), "Title") == 0);
    assert(std::strcmp(copyBook.getAuthor(), "Author") == 0);
    assert(copyBook.getPublishYear() == 1999);

    // Тестване на оператора за присвояване
    Book assignBook;
    assignBook = paramBook;
    assert(std::strcmp(assignBook.getTitle(), "Title") == 0);
    assert(std::strcmp(assignBook.getAuthor(), "Author") == 0);
    assert(assignBook.getPublishYear() == 1999);

    // Тестване на self-assignment
    assignBook = assignBook;
    assert(std::strcmp(assignBook.getTitle(), "Title") == 0);
    assert(std::strcmp(assignBook.getAuthor(), "Author") == 0);
    assert(assignBook.getPublishYear() == 1999);

    // Тестване на сетъри с валидни стойности
    assignBook.setTitle("New Title");
    assignBook.setAuthor("New Author");
    assignBook.setPublishYear(2000);
    assert(std::strcmp(assignBook.getTitle(), "New Title") == 0);
    assert(std::strcmp(assignBook.getAuthor(), "New Author") == 0);
    assert(assignBook.getPublishYear() == 2000);

    // Тестване на сетъри с невалидни стойности
    try {
        assignBook.setTitle(nullptr);
    } catch (const std::invalid_argument& e) {
        std::cout << "Expected invalid_argument for setTitle with nullptr." << std::endl;
    }

    try {
        assignBook.setAuthor("");
    } catch (const std::invalid_argument& e) {
        std::cout << "Expected invalid_argument for setAuthor with empty string." << std::endl;
    }

    try {
        assignBook.setPublishYear(-1);
    } catch (const std::invalid_argument& e) {
        std::cout << "Expected invalid_argument for setPublishYear with invalid year." << std::endl;
    }

    std::cout << "All tests passed successfully." << std::endl;
}

int main() {
    testBookClass();
    return 0;
}
```

## Задачи - `class Book`
Внимавайте при управлението на динамичната памет и при валидацията на входните данни. Обработката на изключения е ключова при реализацията на конструктори и методи, които работят с ресурси.

### Задача 1: Конструктор по Подразбиране
- Имплементирайте конструктор по подразбиране за класа `Book`.
- Инициализирайте `title` и `author` като празни низове (динамично алокирани със стойност по подразбиране, например `"No author set."` и `"No title set."`, не `nullptr`) и `publishYear` с `0`.

### Задача 2: Метод за Отпечатване
- Имплементирайте метода `printBook`.
- Методът трябва да отпечатва на конзолата детайлите за книгата.

### Задача 3: Параметричен Конструктор
- Имплементирайте параметричен конструктор, който приема `title`, `author` и `publishYear`.
- Задайте получените аргументи на съответните член-променливи на класа.

### Задача 4: Копиращ Конструктор
- Имплементирайте копиращ конструктор за класа `Book`.
- Осигурете дълбоко копие на `title` и `author`.

### Задача 5: Оператор за Присвояване
- Имплементирайте оператора за присвояване.
- Реализирайте дълбоко копие на `title` и `author` и изчиствайте старите стойности преди присвояването.

### Задача 6: Деструктор
- Имплементирайте деструктор за класа `Book`.
- Освободете паметта заделена за `title` и `author`.

### Задача 7: Методи за Вземане на Стойности (Getters)
- Имплементирайте `getAuthor`, `getTitle`, и `getPublishYear`.
- Методите трябва да връщат стойностите на съответните член-променливи.

### Задача 8: Методи за Задаване на Стойности (Setters)
- Имплементирайте методите `setTitle`, `setAuthor`, и `setPublishYear`.
- Включете валидация на входните данни във всеки метод.
  - `title`: `nullptr` и `""` са невалидни стойности.
  - `author`: `nullptr` и `""` са невалидни стойности.
  - `publishYear`: 0 >= `publishYear <= 2050
- При валидационна грешка, използвайте `throw std::invalid_argument("<text>");`
- Погрижете се в `main()` функцията да хващате тези грешки и да ги обработвате по полезен за потребителя начин.

---
## Задачи - `class BookList`
Класът `BookList` представлява колекция от обекти `Book`. Той трябва да предоставя функционалности за добавяне, премахване, и извличане на книги, както и за извеждане на списък с всички книги.

### Тестова Функция за `BookList`

```cpp
#include "BookList.hpp"
#include <cassert>

void testBookList() {
    BookList list;

    // Тестване на добавяне на книга
    Book book1("Title1", "Author1", 2001);
    list.addBook(book1);
    assert(list.count() == 1);

    // Тестване на премахване на книга
    assert(list.removeBook("Title1") == true);
    assert(list.count() == 0);

    // Тестване на добавяне и получаване на книга
    list.addBook(book1);
    Book book2 = list.getBook(0);
    assert(book2.getPublishYear() == 2001);

    // Тестване на отпечатване на всички книги
    list.printAllBooks(); // Очаква се да отпечата информация за book1

    std::cout << "All BookList tests passed successfully." << std::endl;
}

int main() {
    testBookList();
    return 0;
}
```

### Задача 1: Конструктор и Деструктор
- Имплементирайте конструктор по подразбиране за `BookList`, който инициализира празен списък.
- Имплементирайте деструктор, който освобождава всички ресурси, асоциирани със списъка.

### Задача 2: Добавяне на Книга
- Имплементирайте метод `void addBook(const Book& book)`, който добавя копие на подадената книга в списъка.

### Задача 3: Премахване на Книга
- Имплементирайте метод `bool removeBook(const char* title)`, който премахва книга по зададено заглавие. Методът връща `true`, ако премахването е успешно.

### Задача 4: Получаване на Книга
- Имплементирайте метод `Book getBook(int index) const`, който връща книга на зададен индекс.

### Задача 5: Брой Книги
- Имплементирайте метод `int count() const`, който връща броя на книгите в списъка.

### Задача 6: Отпечатване на Всички Книги
- Имплементирайте метод `void printAllBooks() const`, който отпечатва информация за всички книги в списъка.

