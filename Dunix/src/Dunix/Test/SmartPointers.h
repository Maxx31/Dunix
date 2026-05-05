#pragma once
#include <atomic>


template<typename T>
struct ControlBlock
{
    explicit ControlBlock(T* InPtr)
        : ptr(InPtr),
          StrongPtrCount(1),
          WeakPtrCount(0)
    {}

    T* ptr = nullptr;
    std::atomic<int> StrongPtrCount{0};
    std::atomic<int> WeakPtrCount{0};
};
template <typename T>
class UniquePointerDX
{
public:
    UniquePointerDX() = default;

    explicit UniquePointerDX(T* InPtr)
        : ptr(InPtr)
    {}

    UniquePointerDX(const UniquePointerDX&) = delete;
    UniquePointerDX& operator=(const UniquePointerDX&) = delete;

    UniquePointerDX(UniquePointerDX&& Other) noexcept
        : ptr(Other.ptr)
    {
        Other.ptr = nullptr;
    }

    UniquePointerDX& operator=(UniquePointerDX&& Other) noexcept
    {
        if (this != &Other)
        {
            delete ptr;
            ptr = Other.ptr;
            Other.ptr = nullptr;
        }

        return *this;
    }

    ~UniquePointerDX()
    {
        delete ptr;
    }

    T* Get() const
    {
        return ptr;
    }

private:
    T* ptr = nullptr;
};
template <typename T>
class SharedPointerDX
{
public:
    SharedPointerDX() = default;

    explicit SharedPointerDX(T* InPtr)
    {
        control = new ControlBlock<T>(InPtr);
    }

    SharedPointerDX(const SharedPointerDX& Other)
        : control(Other.control)
    {
        if (control)
            control->StrongPtrCount.fetch_add(1);
    }

    SharedPointerDX& operator=(const SharedPointerDX& Other)
    {
        if (this == &Other)
            return *this;

        Release();

        control = Other.control;

        if (control)
            control->StrongPtrCount.fetch_add(1);

        return *this;
    }

    ~SharedPointerDX()
    {
        Release();
    }

    T* Get() const
    {
        return control ? control->ptr : nullptr;
    }

    T* operator->() const
    {
        return Get();
    }

    explicit operator bool() const
    {
        return Get() != nullptr;
    }

private:
    void Release()
    {
        if (!control)
            return;

        if (control->StrongPtrCount.fetch_sub(1) == 1)
        {
            delete control->ptr;
            control->ptr = nullptr;

            if (control->WeakPtrCount.load() == 0)
            {
                delete control;
            }
        }

        control = nullptr;
    }

private:
    ControlBlock<T>* control = nullptr;

    template<typename U>
    friend class WeakPointerDX;
};
template <typename T>
class WeakPointerDX
{
public:
    WeakPointerDX() = default;

    WeakPointerDX(T* InPtr) = delete;

    WeakPointerDX(const SharedPointerDX<T>& Shared)
        : control(Shared.control)
    {
        if (control)
            control->WeakPtrCount.fetch_add(1);
    }

    WeakPointerDX(const WeakPointerDX& Other)
        : control(Other.control)
    {
        if (control)
            control->WeakPtrCount.fetch_add(1);
    }

    WeakPointerDX& operator=(const WeakPointerDX& Other)
    {
        if (this == &Other)
            return *this;

        Release();

        control = Other.control;

        if (control)
            control->WeakPtrCount.fetch_add(1);

        return *this;
    }

    ~WeakPointerDX()
    {
        Release();
    }

    bool IsValid() const
    {
        return control && control->StrongPtrCount.load() > 0;
    }

    SharedPointerDX<T> Lock() const
    {
        if (!control)
            return SharedPointerDX<T>();

        int count = control->StrongPtrCount.load();

        while (count > 0)
        {
            if (control->StrongPtrCount.compare_exchange_weak(count, count + 1))
            {
                SharedPointerDX<T> result;
                result.control = control;
                return result;
            }
        }

        return SharedPointerDX<T>();
    }

private:
    void Release()
    {
        if (!control)
            return;

        if (control->WeakPtrCount.fetch_sub(1) == 1 &&
            control->StrongPtrCount.load() == 0)
        {
            delete control;
        }

        control = nullptr;
    }

private:
    ControlBlock<T>* control = nullptr;
};