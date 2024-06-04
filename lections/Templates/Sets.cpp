#include <iostream>
#include "array.hpp"

template<typename Type>
class Set
{
public:
    virtual ~Set() {}
    virtual bool isMember(const Type& x) const = 0;
    virtual Set<Type>* clone() const = 0;
};

template<typename Type>
class ArraySet : public Set<Type>
{
public:
    ArraySet(Array<Type> data) : data(std::move(data)){}
    virtual bool isMember(const Type& x) const override
    {
        return data.find(x) >= 0;
    }
    virtual ArraySet<Type>* clone() const override
    {
        return new ArraySet<Type>(*this);
    }
private:
    Array<Type> data;
};

template <typename Type, typename Predicate>
class PredicateSet : public Set<Type>
{
public:
    PredicateSet(const Predicate& p) : pred(p) {}
    virtual bool isMember(const Type& x) const override
    {
        return pred(x);
    }
    virtual Set<Type>* clone() const override
    {
        return new PredicateSet<Type, Predicate>(*this);
    }
private:
    const Predicate& pred;
};

template <typename Type, bool All>
class OperationSet : public Set<Type>
{
public:
    OperationSet(const Set<Type>* s1, const Set<Type>* s2)
    {
        if (!s1 || !s2) throw std::invalid_argument("Bad sets!");
        this->s1 = s1->clone();
        try {
            this->s2 = s2->clone();
        }
        catch (...) {
            delete s1;
            throw;
        }
    }

    OperationSet(const OperationSet& other) :
        OperationSet(other.s1, other.s2) {}

    OperationSet& operator= (const OperationSet & other)
    {
        if (this != &other) {
            OperationSet copy(other);
            std::swap(s1, copy.s1);
            std::swap(s2, copy.s2);
        }
        return *this;
    }

    ~OperationSet() noexcept
    {
        delete s1;
        delete s2;
    }

    virtual Set<Type>* clone() const override
    {
        return new OperationSet<Type, All>(*this);
    }

    virtual bool isMember(const Type& x) const override {
        if (All) {
            return s1->isMember(x) && s2->isMember(x);
        }
        else {
            return s1->isMember(x) || s2->isMember(x);
        }
    }
private:
    const Set<Type>* s1, * s2;
};

template <typename Type>
using AllSet = OperationSet<Type, true>;

template <typename Type>
using AnySet = OperationSet<Type, false>;

struct EverySecond
{
    bool operator()(int) const{return (cnt++) % 2 == 0; }
private: 
    mutable int cnt = 0;
};


#if 0
int main()
{
    auto lambda = [](int x) {return x % 2 == 1; };
    EverySecond es;
    PredicateSet<int, decltype(lambda)> p(lambda);
    PredicateSet<int, EverySecond> ps(es);
    ArraySet<int> as({ 1, 2, 3, 4, 5 });

    const Set<int>* ptr1 = &p;
    const Set<int>* ptr2 = &ps;

    AllSet<int> all(ptr1, ptr2);
    AnySet<int> any(&as, &all);

    for (int i = 0; i < 20; ++i) {
        std::cout << i << ':' << any.isMember(i) << ", ";
    }
    return 0;
}
#endif