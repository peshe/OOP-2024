/* 
 Примерен код за демонстрация на предефиниране на операторни функции 
 ФМИ, ООП 2024
*/

#pragma once

#ifndef __VECTOR_HEADER_INCLUDED_
#define __VECTOR_HEADER_INCLUDED_

#include <iostream>

namespace fmi::oop {

    using std::istream;
    using std::ostream;

    // За целта на примера ще дефинираме клас вектор, който ще има някои 
    // свойства на алгебричните вектори и някои на динамичните масиви
    class Vector
    {
        // Оператори за вход и изход - най-честият пример за приятелски оператори
        friend ostream& operator<<(ostream& out, const Vector& v);
        friend istream& operator>>(istream& in, Vector& v);

    public:
        //////////////
        //Г6

        // комплект конструктори
        Vector();                         // създава вектор с един елемент - 0
        explicit Vector(unsigned d);      // създава вектор с определен брой елементи и стойности 0
        Vector(const Vector& v);          // копиращ конструктор
        Vector(Vector&& v) noexcept;      // преместващ конструктор
        Vector(const double* data, unsigned len); // създава вектор по подаден масив от координати
        
        ~Vector() noexcept;

        Vector& operator= (const Vector& rhs);
        Vector& operator= (Vector&& rhs) noexcept;
        //////////////

        //Оператори за събиране с число - добавят числото в края на вектора
        Vector  operator+ (double d) const;     // V + d създава нов обект - реализация в класа
        Vector& operator+= (double d);          // V += d 

        Vector& operator+= (const Vector& v);   // Конкатенира два вектора V += V

        // Покомпонентно умножение с число
        Vector  operator* (double d) const;
        Vector& operator*= (double d);

        // Оператори за еквивалентност - сравняват покомпонентно двата вектора
        bool operator== (const Vector& rhs) const;
        bool operator!= (const Vector& rhs) const;

        // Оператор за декрементиране - премахва последния елемент, ако има такъв
        Vector& operator-- ();   // --V 
        Vector  operator-- (int); // V-- Забележете фиктивния аргумент, както и връщаните типове!

        // Оператори за индексиране
        double& operator[] (int index);        // Връща елемента по псевдоним - възможност за промяна (l-value)
        double  operator[] (int index) const;  // Връща елемента по стойност - не позволява промяна на обекта. 

        // Оператори () (функционални оператори)
        double operator() () const;             // Връща норма на вектора (корен от скаларен квадрат)
        void   operator() (unsigned start, unsigned len);  // Отрязва вектора до парче с даденото начало и дължина
        

        operator const char* () const;      // Преобразуване към стринг

        unsigned length() const { return len; } // Размерност на вектора
        bool empty() const { return !length(); }
        operator bool() const { return !empty(); }

        const double* begin() const { return data; }
        const double* end() const { return data + len; }

    protected: 
        // Някои помощни функции

        double* getData() { return data; } // достъп до частните данни
        void clear() { delete[] data; }    // изтрива ресурсите заделени за обекта

        void copy(const double* vals, unsigned size);     // Копира данните в ИНИЦИАЛИЗИРАН обект.
        void move(double*& vals, unsigned& size);   // открадва данните от валиден обект.

        void extend(int cnt = 1);   // Променя размера на данните с подаденото число. Позволява разпиряване и свиване

    private:
        double * data;
        unsigned len;
    };

    // Външни операторни функции

    Vector operator+ (const Vector& v1, const Vector& v2); // Конкатенация V+V
    Vector operator* (double mul, const Vector& v);        // Ляво умножение: d*V
    Vector operator/ (const Vector& v, double mul);

    double operator* (const Vector& v1, const Vector& v2);  // Скаларно произведение

    // Серия оператори за наредба - векторите се сравняват по норма.
    // Наредбата е пълна.
    bool operator<  (const Vector& v1, const Vector& v2);
    bool operator<= (const Vector& v1, const Vector& v2);
    bool operator>  (const Vector& v1, const Vector& v2);
    bool operator>= (const Vector& v1, const Vector& v2);

} // fmi::oop


#endif //__VECTOR_HEADER_INCLUDED_