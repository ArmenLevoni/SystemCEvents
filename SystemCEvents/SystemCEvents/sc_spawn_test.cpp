//
//  sc_spawn_test.cpp
//  SystemCEvents
//
//  Created by Armen Khachatryan on 29/09/2019.
//  Copyright © 2019 Armen Khachatryan. All rights reserved.
//

#include <stdio.h>

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <systemc.h>

int function_method(double d)
{
  cout << endl << sc_time_stamp() << ", "
       << sc_get_curr_process_handle()->name()
       << ": function_method sees " << d << endl;
  return int(d);
}

class module1 : public sc_module
{
private:
  sc_event& ev;
public:

  SC_HAS_PROCESS(module1);

  module1(sc_module_name name, sc_event& event) : sc_module(name),
    ev(event)
  {
    int r;
    SC_THREAD(main);
    cout << endl << sc_time_stamp() << ": CTOR, Before spawning function_method" << endl;
    sc_spawn_options o1;
    o1.spawn_method();
    o1.dont_initialize();
    o1.set_sensitivity(&ev);
    sc_process_handle h4 = sc_spawn(&r, sc_bind(&function_method, 1.2345), "event_sensitive_method", &o1);

  }

  void main()
  {
    sc_event e1, e2, e3, e4;

    cout << endl << sc_time_stamp() << ", "
    << sc_get_curr_process_handle()->name()
    << ": main thread, Before spawning round robin threads."
    << endl << endl;

    e1.notify(100, SC_NS);

    // Spawn several threads that co-operatively execute in round robin order

    SC_FORK
      sc_spawn(
        sc_bind(&module1::round_robin, this, "1", sc_ref(e1), sc_ref(e2), 3), "1") ,
      sc_spawn(
        sc_bind(&module1::round_robin, this, "2", sc_ref(e2), sc_ref(e3), 3), "2") ,
      sc_spawn(
        sc_bind(&module1::round_robin, this, "3", sc_ref(e3), sc_ref(e4), 3), "3") ,
      sc_spawn(
        sc_bind(&module1::round_robin, this, "4", sc_ref(e4), sc_ref(e1), 3), "4") ,
    SC_JOIN

    cout << endl << sc_time_stamp() << ", "
         << sc_get_curr_process_handle()->name()
         << ": Done main thread." << endl;
  }

  void round_robin(const char *str, sc_event& receive, sc_event& send, int cnt)
  {
    while (--cnt >= 0)
    {
      wait(receive);
      cout << sc_time_stamp() << ": " << sc_get_curr_process_handle()->name()
           << ": Round robin thread " << str << endl;
      wait(10, SC_NS);
      send.notify();
    }
  }

};

int sc_main_3 (int argc , char *argv[])
{
  sc_event event1;
  event1.notify(55, SC_NS);

  module1 mod1("mod1", event1);
  sc_start(500, SC_NS);
  return 0;
}
