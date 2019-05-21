#include <systemc>
#include <iostream>

SC_MODULE(EventSys)
{
public:
    sc_core::sc_event s0, s1, s2, s3, s4;

    SC_CTOR(EventSys)
    {
        SC_THREAD(proc0);
        SC_THREAD(proc1);
        SC_THREAD(proc2);
        SC_THREAD(proc3);
        SC_THREAD(proc4);
        dont_initialize();
        sensitive << s4;
    }

    void proc0();
    void proc1();
    void proc2();
    void proc3();
    void proc4();
    void print(int id);
    void hello(int id);
};

void EventSys::hello(int id)
{
    std::cout << "Hello from process " << id << " at " <<
		sc_core::sc_time_stamp() << std::endl;
}

void EventSys::print(int id)
{
    std::cout << "Process " << id << " at " <<
		sc_core::sc_time_stamp() << std::endl;
}

void EventSys::proc0()
{
    hello(0);
    wait(sc_core::SC_ZERO_TIME);
    s1.notify();
    while(true)
    {
        wait(s0);
        print(0);
        s1.notify(sc_core::SC_ZERO_TIME);
        s4.notify();
        s3.notify();
		wait(1, sc_core::SC_NS);
    }
}

void EventSys::proc1()
{
    hello(1);
    while(true)
    {
        wait(s1);
        print(1);
        s2.notify(1, sc_core::SC_NS);
    }
}

void EventSys::proc2()
{
    hello(2);
    while(true)
    {
        wait(s2);
        print(2);
        s0.notify(1, sc_core::SC_NS);
    }
}

void EventSys::proc3()
{
    hello(3);
    while(true)
    {
        wait(s3);
        print(3);
    }
}

void EventSys::proc4()
{
    hello(4);
    while(true)
    {
        wait(s4);
        s4.notify();
        print(4);
    }
}

int sc_main(int argc, char* argv[])
{
    EventSys uut("UUT");

    sc_core::sc_start(10, sc_core::SC_NS);

    return 0;
}
