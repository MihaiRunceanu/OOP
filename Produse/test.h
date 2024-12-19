#pragma once
#include "gui.h"

class Test{
public:
    Test(){
        test_domain();
        test_repo();
        test_service();
        cout<<"Testele au fost verificate cu succes\n";
    };

    void test_domain();

    void test_service();

    void test_repo();
};

