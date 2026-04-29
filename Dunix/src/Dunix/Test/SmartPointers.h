#pragma once
#include <atomic>

template <typename T>
class UniquePointerDX
{
public:
    UniquePointerDX() : ptr(nullptr)
    {
    }
    
    UniquePointerDX(UniquePointerDX&& InOther)
        : ptr(std::move(InOther.Get()))
    {
    }
    
    UniquePointerDX(const UniquePointerDX& InUniquePtr) = delete;
    UniquePointerDX& operator=(const UniquePointerDX& InUniquePtr) = delete;
    
    UniquePointerDX(T* InPtr)
      : ptr(std::move(InPtr))
    {
    }
    
    ~UniquePointerDX()
    {
        delete ptr;
    }
    
    T* Get()
    {
        return ptr;
    }
    
private:
    T* ptr;
};

template <typename T>
class SharedPointerDX
{
public:
    SharedPointerDX() = default;
    
    SharedPointerDX(T* InPtr)
    {
        ptr = InPtr;
        PtrCount = new std::atomic<int>(1);
    }
    
    SharedPointerDX(SharedPointerDX& InSharedPtr)
    {
        ptr = InSharedPtr.Get();
        PtrCount->fetch_add(1);
        return *this;
    }
    
    SharedPointerDX(const SharedPointerDX& InUniquePtr) = delete;
    
    ~SharedPointerDX()
    {
        if (PtrCount->fetch_sub(1) == 1) delete ptr;
    }
    
    SharedPointerDX& operator=(const SharedPointerDX& InPointer)
    {
        ptr = InPointer.Get();
        PtrCount = InPointer.PtrCount;
        PtrCount->fetch_add(1);
        
        return *this;
    }
    
    T* Get()
    {
        return ptr;
    }
    
private:
    std::atomic<int>* PtrCount = nullptr;
    T* ptr;
};

template <typename T>
class WeakPointerDX
{
public:
    WeakPointerDX() = default;
    
    WeakPointerDX(T* InPtr)
    {
        ptr = InPtr;
        PtrCount = new std::atomic<int>(1);
    }
    
    WeakPointerDX(WeakPointerDX& InSharedPtr)
    {
        ptr = InSharedPtr.Get();
        PtrCount->fetch_add(1);
        return *this;
    }
    
    WeakPointerDX(const WeakPointerDX& InUniquePtr) = delete;
    
    ~WeakPointerDX()
    {
        if (PtrCount->fetch_sub(1) == 1) delete ptr;
    }
    
    WeakPointerDX& operator=(const WeakPointerDX& InPointer)
    {
        ptr = InPointer.Get();
        PtrCount = InPointer.PtrCount;
        PtrCount->fetch_add(1);
        
        return *this;
    }
    
    T* Get()
    {
        return ptr;
    }
    
private:
    std::atomic<int>* PtrCount = nullptr;
    T* ptr;
};