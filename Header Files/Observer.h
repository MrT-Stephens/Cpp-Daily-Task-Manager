#pragma once

#include "../Header Files/Task.h"
#include "../Header Files/Vector.h"

/// <summary>
/// Interface for the Observer pattern
/// </summary>
class Observer 
{
public:
    virtual ~Observer() {}
    virtual void Update(const mrt::Vector<Task>& tasks) = 0;
};