//
//  Testbench.cpp
//  SystemCEvents
//
//  Created by Armen Khachatryan on 17/11/2019.
//  Copyright © 2019 Armen Khachatryan. All rights reserved.
//

#include "Testbench.hpp"

int sc_main_s(int argc, char* argv[])
{
  Top top("top");
  sc_start();
  return 0;
}
