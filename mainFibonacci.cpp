#include <systemc>
#include "Module.hpp"

int sc_main(int argc, char* argv[])
{
	Module uut("UUT");

	sc_start(10, sc_core::SC_US);

	std::cout << "Simulation finished at " << sc_core::sc_time_stamp() << std::endl;
	return 0;
}
