#pragma once
#include <assert.h>
#include "domain.h"
#include "validator.h"
#include "service.h"

class Test
{
private:
    void testEntity();
    void testValidator();
    void testModificare();

public:
    Test() = default;

    void runTests();
};
