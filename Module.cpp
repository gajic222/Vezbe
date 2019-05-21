#include "Module.hpp"
#include <cstdlib>
#include <ctime>

using namespace sc_core;
using namespace std;

Module::Module(sc_core::sc_module_name name)
{
	srand(time(NULL));
	SC_THREAD(fibogen);
 	SC_THREAD(respond);
	dont_initialize();
	sensitive << foo;
}

void Module::fibogen()
{
	int n=0;
	while(true)
	{
		
		int val = rand()%90;
		wait(10+val, SC_NS);
		fiboQ.push_back(fibo(n));
		std::cout << "Generated number " << fiboQ.back() <<", @" << sc_time_stamp() << std::endl;
		foo.notify(5,sc_core::SC_NS);	
		n++;
		n=n%64;
	}
	
}

void Module::respond()
{
	while(true){
		long unsigned int num=fiboQ.front();
		fiboQ.pop_front();
		std::cout << "Displayed number " << num <<", @" << sc_time_stamp() << std::endl;
		wait(foo);
	}
}

long unsigned int Module::fibo(int n)
{
	long unsigned int f[n];
	f[0]=1;
	f[1]=1;
	for(int i=2;i<=n;i++)
		f[i]=f[i-1]+f[i-2];
	return f[n];
}
