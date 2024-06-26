# Шаблони

## Задача 1 :page_with_curl:
Да се направи темплейтен клас `MyDummyList`, който има следните функционалности:

* съдържа произволен брой **уникални** елементи
* да се добавят нови елементи; при нарушаване на уникалността да се хвърля подходящо изключение
* да се премахва елемент на определена позиция; при невалиден индекс да се хвърля подходящо изключение
* да се достъпват елементите във вида list[3]; при невалиден индекс да се хвърля подходящо изключение
* да дава информация за броя елементи
* да дава информация дали е празен
* да има функции за писане и четене от поток

### Задача 2 :couch_and_lamp::house:
Даден е следният интерфейс:
```c++
template <class T, class ID>
class CrudRepository
{
public:
    virtual void create(const T& object) = 0;
    virtual const T& read(ID id) const = 0;
    virtual void update(ID id, const T& newObject) = 0;
    virtual void delete_(ID id) = 0;

    virtual ~CrudRepository() = default;
};
```

Включете го в йерархия с някой от класовете - саморазширяващи се масиви, които сте писали през семестъра.
