//
//  fifo.cpp
//  SystemCEvents
//
//  Created by Armen Khachatryan on 29/09/2019.
//  Copyright © 2019 Armen Khachatryan. All rights reserved.
//
#include <systemc.h>
#include "fifo.hpp"

class write_if : virtual public sc_interface
{
   public:
     virtual void write(char) = 0;
     virtual void reset() = 0;
};

class read_if : virtual public sc_interface
{
   public:
     virtual void read(char &) = 0;
     virtual int num_available() = 0;
};

class fifo : public sc_channel, public write_if, public read_if
{
   public:
     fifo(sc_module_name name) : sc_channel(name), num_elements(0), first(0) {}

     void write(char c) {
       if (num_elements == max)
         wait(read_event);

       data[(first + num_elements) % max] = c;
       ++ num_elements;
       write_event.notify();
     }

     void read(char &c){
       if (num_elements == 0)
         wait(write_event);

       c = data[first];
       -- num_elements;
       first = (first + 1) % max;
       read_event.notify();
     }

     void reset() { num_elements = first = 0; }

     int num_available() { return num_elements;}

   private:
     enum e { max = 10 };
     char data[max];
     int num_elements, first;
     sc_event write_event, read_event;
};

class producer : public sc_module
{
   public:
     sc_port<write_if> out;

     SC_HAS_PROCESS(producer);

     producer(sc_module_name name) : sc_module(name)
     {
       SC_THREAD(main);
     }

     void main()
     {
       const char *str =
         "Visit www.accellera.org and see what SystemC can do for you today!\n";

       while (*str)
         out->write(*str++);
     }
};

class consumer : public sc_module
{
   public:
     sc_port<read_if> in;
     sc_time t;

     SC_HAS_PROCESS(consumer);

     consumer(sc_module_name name) : sc_module(name)
     {
       SC_THREAD(main);
     }

     void main()
     {
       char c;
       cout << endl << endl;

       while (true) {
         in->read(c);
         cout << c << flush << endl;
         t = sc_time_stamp();
         cout <<"Value of time "<< t.to_string() << endl;
         if (in->num_available() == 1)
       cout << "<1>" << flush;
         if (in->num_available() == 9)
       cout << "<9>" << flush;
        //wait(1);
       }
     }
};

class top : public sc_module
{
   public:
     fifo *fifo_inst;
     producer *prod_inst;
     consumer *cons_inst;

     top(sc_module_name name) : sc_module(name)
     {
       fifo_inst = new fifo("Fifo1");

       prod_inst = new producer("Producer1");
       prod_inst->out(*fifo_inst);

       cons_inst = new consumer("Consumer1");
       cons_inst->in(*fifo_inst);
         sc_start(0, SC_NS);
         sc_start(1, SC_NS);
     }
};



template <typename T>
class Transaction {

public:
    Transaction (){}
    void advance() { curr++; }
    T data;
    unsigned int ID;
    
    void setID(unsigned int id) {
        ID = id;
    }
    
    unsigned int getID  () const {
        return ID;
    }

private:
    //static Route route;
    //Route::iterator curr;
    int curr;
};

class Data {
    
public:
    double x;
    double y;
        
};


template<
    typename Transaction,
    template <typename> class InPort,
    template <typename> class OutPort
    >
class StageInterface {
public:
    InPort<Transaction> in;
    OutPort<Transaction> out;
};

struct TimedPolicy {
    inline static void wait(int t) { ::wait(t, SC_NS); }
};
struct UntimedPolicy {
    inline static void wait(int t) { }
};
template <class Transaction,
        class Function,
        class DelayModel,
        class PortInterface>
class Resource :
    public sc_module,
    public Function,
    public DelayModel,
    public PortInterface {
 
    SC_HAS_PROCESS(Resource);

public:
    Resource(sc_module_name  name) :sc_module(name) { SC_THREAD(process); }
            
    void process() {
        cout << "INFO: Starting top process in Resource..." << endl;
        while(1) {
            cout << "Starting reading: " << sc_time_stamp() <<endl;
            Transaction t = in.read();
            cout << "Processing transacion: " << t.getID() <<endl;
            t.data = f(t.data);
            wait(1);
            t.advance();
            out.write(t);
        }
    }

public:
    using PortInterface::in;
    using PortInterface::out;
    using Function::f;
    using DelayModel::wait;
};

//typedef Transaction<std::pair<double, double> > MyTransaction;
typedef Transaction<Data> MyTransaction;

template<typename T>
struct TwoSqr {
    static inline T f(T p) {
    //p.second = p.second + 2*sqr(p.first);
    return p;
    }
};

typedef TwoSqr<Data> MyFunction;
typedef StageInterface<MyTransaction, sc_fifo_in, sc_fifo_out> FIFOInterface;

class Threading{
    
};



typedef Resource<MyTransaction, MyFunction, TimedPolicy, FIFOInterface> MyResource;


    
SC_MODULE(Top)
{
    
    sc_fifo<MyTransaction> q1;
    sc_fifo<MyTransaction> q2;
    
    MyResource r;
    
    
    void before_end_of_elaboration() {
       r.in.bind(q1);
       r.out.bind(q2);
    }
    

    SC_CTOR(Top)
        :q1("q1",1)
        ,q2("q2",11)
        ,r("r2")
    {
        SC_THREAD(process);
    }
    
    void process() {
        cout << "INFO: Starting top process in top..." << endl;
        MyTransaction t ;
        for(int i=0; i<10; i++) {
            cout <<endl<< "INFO: Sending transaction: " << i*11 << " "<<  sc_time_stamp()<< endl;
            
            t.data.x = 1+i;
            t.data.y = 2+i;
            t.setID(i*11);
            q1.write(t);
            //wait(1, SC_NS);
        }
    }
    
};


int sc_main_4 (int, char *[]) {
    Top top("top");

    sc_start();
    cout << "INFO: Finishing the simulation: " << sc_time_stamp()<< endl;
    return 0;
}
