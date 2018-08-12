#include <iostream>

using namespace std;


class test
{
	public:
    test()
    {
        cout << "default constructor " << endl;
    }
    
	test(const test& t)
    {
        cout << "copy constructor " << endl;
    }
    
	~test()
    {
        cout << "destructor " << endl;
    }
};

template<typename T> class sharedPtr
{
    T* data;

    public:
    mutable int* count;
	
    int getCount()
    {
        return *count;
    }
	
    sharedPtr(T* data)
    {
        this->data = data;
        count = new int(1);
    }
	
    T& operator*()
    {
        return *data;
    }

    T* operator->()
    {
        return data;
    }
	
    T* get() const
    {
        return data;
    }
	
    sharedPtr(const sharedPtr& ptr)
    {

        data = ptr.get();
        (*ptr.count)++;
        count = ptr.count;
    }

    sharedPtr& operator=(const sharedPtr& ptr)
    {
        data = ptr.get();
        (*ptr.count)++;
        if((*count) > 0)
            (*count)--;
        count = ptr.count;
    }
	
    ~sharedPtr()
    {
        (*count)--;
        if((*count) == 0)
		{
             delete data;
		}
	}
};


int main()
{
    sharedPtr<test> ptr1(new test());
    sharedPtr<test> ptr2(new test());

    sharedPtr<test> ptr3(ptr1);
    sharedPtr<test> ptr4(ptr2);

    sharedPtr<test> ptr5 = ptr1;

    ptr5 = ptr2;

    cout << ptr1.getCount() << " ";
	cout << ptr2.getCount() << " ";
	cout << ptr3.getCount() << " ";
	cout << ptr4.getCount() << " ";
	cout << ptr5.getCount() << endl;
}

