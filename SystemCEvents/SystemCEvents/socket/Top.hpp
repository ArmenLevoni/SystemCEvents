//
//  Top.hpp
//  SystemCEvents
//
//  Created by Armen Khachatryan on 17/11/2019.
//  Copyright © 2019 Armen Khachatryan. All rights reserved.
//

#ifndef Top_hpp
#define Top_hpp

#include <stdio.h>
#include "Initiator.hpp"
#include "Target.hpp"

SC_MODULE(Top)
{
  Initiator *initiator;
  Memory    *memory;

  SC_CTOR(Top)
  {
    // Instantiate components
    initiator = new Initiator("initiator");
    memory    = new Memory   ("memory");

    // One initiator is bound directly to one target with no intervening bus

    // Bind initiator socket to target socket
    initiator->socket.bind( memory->socket );
  }
};

#endif /* Top_hpp */
