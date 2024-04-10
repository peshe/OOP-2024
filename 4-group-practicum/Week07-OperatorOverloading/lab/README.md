# Разделна компилация. Предефиниране на оператори.

## Задача 1 :calendar:

Да се реализира клас **Date**, който пази в себе си информация за следните променливи:

* Дата - `std::uint8_t`
* Месец - `std::uint8_t`
* Година - `std::uint16_t`

Класът да има следния интерфейс:

* Класът НЕ ТРЯБВА да има конструктор по подразбиране
* `Date(unsigned int day, unsigned int month, unsigned int year)` - конструктор, създаващ нов обект за дата и проверяващ с `assert` валидността й
* `unsigned int day() const`
* `unsigned int month() const`
* `unsigned int year() const`
* `bool operator==(const Date& rhs) const`
* `bool operator<(const Date& rhs) const`

## Задача 2 :heavy_dollar_sign:

Да се реалзира изброим тип **Currency**, който ще има следните стойности:

* BGN
* USD
* EUR

## Задача 3 :currency_exchange:

Напишете структура **ConversionRate**, която ще съдържа следната информация:

* Обменен курс - `double`
* Стара валута - `Currency`
* Нова валута - `Currency`

## Задача 4 :money_mouth_face:

Да се реализира клас `Money`, който да пази в себе си следната информация:

* Сума пари - `double`
* Вид валута - `Currency`

Класът да има следния интерфейс:

* Класът НЕ ТРЯБВА да има конструктор по подразбиране
* `Money(double startingMoney, Currency currency)`
* Метод, който ще връща парите
* Метод, който ще връща валутата
* **Не искаме директни сетъри за парите и валутата!**
* `Money softConvert(const ConversionRate& convertion) const` - Не променя стойностите на класа, но променя копие на класа и връща него*
* `void hardConvert(const ConversionRate& newCurrency)` - Променя самия клас
* Предефинирайте операторите `+, +=, -, -=` да работят с реални числа (левове)
* Предефинирайте операторитете `+, +=, -, -=` да работят с обекти от тип `Money`, като в debug режим `assert`-вайте, че валутите са едни и същи.
* Предефинирайте оператор `-`, така че като е поставен пред обекта, да обръща неговата стойност: m (5, BGN) => -m (-5, BGN)
* Предефинирайте операторите за сравнение `==, !=, <, >, <= , >=`

## Задача 5 :man_beard:

Да се реализира клас **Client**, който да пази в себе си следната информация:

* Име - низ с точен размер
* ЕГН - низ с точно **10** символа
* Рожден ден - обект от тип `Date`
* Пари - обект от тип `Money`

Класът да има следния интерфейс:

* `Client(const char* name, const char* identificationNumber, const Date& birthday, const Money& money)`
* Реализирайте нужните гетъри и сетъри

## Задача 6 :bank:

Да се реализира клас **Bank**, който да пази в себе си следната информация:

* Име на банката - низ с точен размер
* Потребители - саморазширяващ се масив от `Client`
* Големина на потребителите - `std::size_t`
* Капацитет на потребителите - `std::size_t`
* Обменни курсове - масив от точно 6 обекта от тип **ConversionRate**. Трябва да има обменен курс от всяка валута към всяка друга.

Класът да има следния интерфейс:

* Класът НЕ ТРЯБВА да има конструктор по подразбиране
* `Bank(const char* name, ConversionRate rates[6])`
* `void addClient(const Client& client)`
* `bool removeClient(const char* identificationNumber)`
* `int getClientIndex(const char* identificationNumber) const`
* `bool deposit(const char* identificationNumber, const Money& toDeposit)`
* `bool withdraw(const char* identificationNumber, const Money& toWithdraw)`
* `bool transfer(const char* sourceClientIdentificationNumber, const char* destinationClientIdentifinationNumber, Money moneyToTransfer)` - Първо трябва да се провери дали съществуват клиентите, после дали source клиентът има достатъчно пари да прехвърли към destionation клиента. После маха парите от source и ги дава на destination. При различни валути може да се наложи конвертиране на парите
* `bool convertClientMoney(const char* identificationNumber, Currency newCurrency)`
