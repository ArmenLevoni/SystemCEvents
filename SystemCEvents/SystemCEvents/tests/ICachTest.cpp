//
//  ICachTest.cpp
//  SystemCEvents
//
//  Created by Armen Khachatryan on 03/10/2019.
//  Copyright © 2019 Armen Khachatryan. All rights reserved.
//

#include "ICachTest.hpp"
#include "icache.hpp"

SC_MODULE (ICACHTEST) {
    
    ICache ic;

    SC_CTOR(ICACHTEST) :
        ic("ICache")
    {
        ic.addShaderFromList(0, {"A"});
        cout << ic.getInstrucion(0,0).getInstructionName() << endl;
        SC_THREAD(proc);
    }

    
    void proc () {
        cout << "Starting the process" << endl;
        //Instruction i = ic.getDelayedInstruction(0, 0);
        //cout << i.getInstructionName() << endl;
        wait(10, SC_NS);
        cout << "Ending the process" << endl;

    }
};


int sc_main_2 (int, char *[]) {
    ICACHTEST test("ICACHTEST");
    sc_start();
    cout << "INFO: Finishing the simulation: " << sc_time_stamp()<< endl;
    return 0;
}
