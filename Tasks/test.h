#ifndef TESTS_H
#define TESTS_H

#include "service.h"
#include <cassert>

class Tests
{
public:

    Tests() = default;

    // Functie de test pentru domain
    void test_domain();

    // Functie de test pentru repo
    void test_repo();

    // Functie de test pentru service
    void test_service();

    // Functie de rulat toate testele
    void test_all();
};

#endif // TESTS_H
