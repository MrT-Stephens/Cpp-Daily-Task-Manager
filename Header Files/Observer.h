#pragma once

#include "../Header Files/Task.h"
#include "../Header Files/Vector.h"

class Observer 
{
public:
    virtual ~Observer() {}
    virtual void Update(const mrt::Vector<Task>& tasks) = 0;
};