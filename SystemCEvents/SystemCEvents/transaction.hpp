//
//  transaction.hpp
//  SystemCEvents
//
//  Created by Armen Khachatryan on 03/10/2019.
//  Copyright © 2019 Armen Khachatryan. All rights reserved.
//

#ifndef transaction_hpp
#define transaction_hpp

#include <stdio.h>

template <typename T>
class Transaction {

public:
    Transaction () {
        curr = 0;
    }
    
    T data;
    
    void advance() { curr++; }

    void setID (unsigned int id) {
        ID = id;
    }
    
    unsigned int getID () const {
        return ID;
    }

private:
    int curr;
    unsigned int ID;
    
};
#endif /* transaction_hpp */
