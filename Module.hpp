#ifndef MODULE_H
#define MODULE_H

#include <systemc>
#include <deque>

SC_MODULE(Module)
{
public:
	SC_CTOR(Module);
	
	void fibogen();
	void respond();
	long unsigned int fibo(int n);
protected:
	std::deque<long unsigned int> fiboQ;
	sc_core::sc_event foo;
};

#endif
