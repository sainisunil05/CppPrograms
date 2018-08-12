#include <iostream>

using namespace std;

class test
{
	public:
	int val;
	test(int i = 10) : val (i){}
	~test()
	{
		cout << "test destructor" << endl;
	}
};

template<typename T> class uniq_ptr
{
	T* data;
	public:
	uniq_ptr()
	{
		data = nullptr;
	}
	uniq_ptr(T* ptr)
	{
		data = ptr;
	}
	
	T* get()
	{
		return data;
	}
	
	void reset()
	{
		data = nullptr;
	}
	
	T& operator*()
	{
		return *data;
	}
	
	T* operator->()
	{
		return data;
	}
	
	uniq_ptr(const uniq_ptr& ref) = delete;
	uniq_ptr& operator=(const uniq_ptr& ref) = delete;
	uniq_ptr& operator=(uniq_ptr&& ref)
	{
		cout << "move assignment   " << endl;
		if(data == ref.get())
			cout << "self move " << endl;
		
		delete data;
		data = ref.get();
		ref.reset();
		
	}
	uniq_ptr(uniq_ptr&& ref)
	{
		cout << "move constructor  " << endl;
		data = ref.get();
		ref.reset();
	}
	
	~uniq_ptr()
	{
		delete data;
	}
};

int main()
{
	uniq_ptr<test> ptr(new test(22));
	
	cout << (*ptr).val << endl;
	cout << ptr->val << endl;
	
	uniq_ptr<test> tmp(move(ptr));
	
	cout << (*tmp).val << endl;
	cout << tmp->val << endl;
	
	ptr = move(tmp);
	
	cout << (*ptr).val << endl;
	cout << ptr->val << endl;	
}
