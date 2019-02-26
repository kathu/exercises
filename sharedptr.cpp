#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>

template <typename T>
class sharedpointer
{
    T* _ptr;
    size_t* _refcount;
    
public:
    sharedpointer(T* ptr) : _ptr(ptr)
    {
        _refcount = new size_t(0);
        ++_refcount;
    }
    
    sharedpointer(const sharedpointer<T>& sp)
    {
        _ptr = sp._ptr;;
        _refcount = sp._refcount;
        ++_refcount;
    }
    
    sharedpointer<T>& operator=(const sharedpointer<T>& sp)
    {
        if (this == &sp)
            return *this;
        
        _ptr = sp.operator->();
        _refcount = sp._refcount;
        ++_refcount;
        
        return *this;
    }
    
    sharedpointer(sharedpointer<T>&& sp)
    {
        _ptr = sp._ptr;
        _refcount = sp._refcount;
        sp._ptr = nullptr;
        sp._refcount = 0;
    }
    
    sharedpointer<T>& operator=(sharedpointer<T>&& sp)
    {
        if (this == &sp)
            return *this;
        
        _ptr = sp._ptr;
        _refcount = sp._refcount;
        
        sp._ptr = nullptr;
        sp._refcount = 0;
        
        return *this;
    }
    
    T* operator->()
    {
        return _ptr;
    }
    
    T& operator*()
    {
        return *_ptr;
    }
    
    ~sharedpointer()
    {
        --_refcount;
        if (_refcount == 0)
            delete _ptr;
    }
};

int main()
{
    sharedpointer<int> A(new int(9));
    *A = 10;
    
    sharedpointer<int> B(A);
    
    *B = 11;
    
    auto C = std::move(A);
    
    std::cout << *C;
}
