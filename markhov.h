#include <iostream>
#include <cstddef>

template<class T>

class Markhov
{
	private:
	typedef struct mkv 
	{
		T value;
		struct mkv *next;
		struct mkv *back;
	} mkv;

	size_t _size;
	size_t _steps;
	
	mkv *_start;
	mkv *_end;
	mkv *_state;

	public:
	
	Markhov()
	{
		_size = 0;
		_start = 0;
		_end = 0;
		_steps = 0;
	}
	
	~Markhov()
	{
		while(!empty())
		{
			pop_back();
		}
	}
	// empty	
	bool empty() const
	{
		return (_start == 0 && _end == 0);
	}

	// front
	T& start()
	{
		return _start -> value;
	}

	// back
	T& end()
	{
		return _end -> value;
	}
	
	// size
	size_t size()
	{
		return _size;
	}
	
	//steps	
	size_t steps()
	{
		return _steps;
	}
	
	//state
	T&  state()
	{
		return _state->value;
	}

	//reset
	void reset()
	{
		_state = _start;		
		_steps = 0;
	}

	//push_back
	void push_back(const T& value)
	{
		mkv *newEndItem = new mkv;
		newEndItem -> value = value;
		newEndItem -> back  = _end;
		newEndItem -> next = 0;
		
		if (_end != 0)
		{
			_end -> next = newEndItem;
		}		
		if (_start == 0)
		{
			_start = newEndItem;
			_state = _start;
		}
	
		_end = newEndItem;
		_size++;
	}

	//pop_back
	void pop_back()
	{
		mkv *saveEnd = _end;
		_end = _end -> back;
		
		if (_end)
		{
			_end -> next = _end -> next -> next;
		}
		else 
		{
			_start = 0;
		}
		
		delete saveEnd;
		_size--;	
	}

	
	// testing
	void test(T& val)
	{
		mkv *ptr = _state;
		
		if (val > 49)
		{
			ptr = ptr -> next;
			_steps++;
		}
		else
		{
			if (ptr -> back == 0)
			{
				;
			}
			else
			{
				ptr = ptr -> back;
				_steps++;
			}
		}
		_state = ptr;
	}
		
	void print() 
	{
		mkv *temp = _start;
		while (temp != 0)
		{
			std::cout << temp -> value << " ";
			temp = temp -> next;
		}
		std::cout << std::endl;
	}
};
