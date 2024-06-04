#pragma once
#ifndef __AUTO_PTR_HEADER_INCLUDED_
#define __AUTO_PTR_HEADER_INCLUDED_

#include <stdexcept>

template <typename Type>
struct DefaultDeleter
{
    void free(Type* ptr) { delete ptr; }
};

template <typename Type, typename Deleter = DefaultDeleter<Type>>
class AutoPtr
{
public:
    AutoPtr() noexcept : ptr(nullptr) {}
    explicit AutoPtr(Type* ptr) noexcept : ptr(ptr) {}
    ~AutoPtr() noexcept { del.free(ptr); }

    AutoPtr(AutoPtr&& other) noexcept
        : AutoPtr()
    {
        std::swap(other.ptr, ptr);
    }

    AutoPtr& operator=(AutoPtr&& other) noexcept
    {
        std::swap(this->ptr, other.ptr);
        return *this;
    }

    AutoPtr& operator=(Type* ptr)
    {
        if (ptr != this->ptr)
        {
            del.free(this->ptr);
            this->ptr = ptr;
        }
        return *this;
    }

    AutoPtr(const AutoPtr&) = delete;
    AutoPtr& operator=(const AutoPtr&) = delete;

public:
    operator bool()const noexcept
    {
        return ptr != nullptr;
    }

    Type operator*()
    {
        if (!ptr) throw std::runtime_error("Null pointer reference");
        return *ptr;
    }

    const Type operator*() const
    {
        if (!ptr) throw std::runtime_error("Null pointer reference");
        return *ptr;
    }

    Type* operator->()
    {
        if (!ptr) throw std::runtime_error("Null pointer reference");
        return ptr;
    }

    const Type* operator->() const
    {
        if (!ptr) throw std::runtime_error("Null pointer reference");
        return ptr;
    }

    void reset(Type* newPtr)
    {
        del.free(ptr);
        ptr = newPtr;
    }
    
    Type* release() noexcept
    {
        Type* t = ptr;
        ptr = nullptr;
        return t;
    }

    void exchange(Type*& other) noexcept
    {
        std::swap(ptr, other);
    }

private:
    Type* ptr;
    Deleter del;
};


template <typename Type, typename Deleter = DefaultDeleter<Type>>
class CountingPtr
{
public:
    explicit CountingPtr(Type* ptr = nullptr) : control(nullptr) 
    {
        if (ptr) control = new control_block{ ptr, 1 };
    }
    CountingPtr(const CountingPtr& other) noexcept : control(other.control) 
    { 
        if (control)
            ++control->count;
    }
    CountingPtr(CountingPtr&& other) noexcept : control(other.control)
    {
        other.control = nullptr;
    }
    
    ~CountingPtr() noexcept 
    { 
        release(); 
    }

    CountingPtr& operator=(const CountingPtr& other) noexcept
    {
        if (this != &other) {
            release();
            control = other.control;
            if (control) ++control->count;
        }
        return *this;
    }

    CountingPtr& operator=(CountingPtr&& other) noexcept
    {
        if (this != &other) {
            release();
            control = other.control;
            other.control->ptr = nullptr;
        }
        return *this;
    }

    const Type& operator*() const
    {
        if (!control || !control->ptr) throw std::runtime_error("Null pointer reference");
        return *control->ptr;
    }

    Type& operator*()
    {
        if (!control || !control->ptr) throw std::runtime_error("Null pointer reference");
        return *control->ptr;
    }

    const Type* operator->() const
    {
        if (!control || !control->ptr) throw std::runtime_error("Null pointer reference");
        return control->ptr;
    }

    Type* operator->()
    {
        if (!control || !control->ptr) throw std::runtime_error("Null pointer reference");
        return control->ptr;
    }

    operator bool() const noexcept
    {
        return control && control->ptr;
    }

    void reset(Type* ptr = nullptr)
    {
        release();
        control = ptr ? new control_block{ ptr, 1 } : nullptr;
    }

private:

    void release() noexcept
    {
        if (control && --control->count == 0) {
            control->del.free(control->ptr);
            delete control;
        }
    }

    struct control_block
    {
        Type* ptr = nullptr;
        size_t count = 0;
        Deleter del{};
    }* control;
};


#endif //AUTO_PTR_HEADER_INCLUDED_
