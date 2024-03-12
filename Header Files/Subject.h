#pragma once

#include "../Header Files/Observer.h"

/// <summary>
/// The Subject interface declares a set of methods for managing subscribers.
/// </summary>
class Subject 
{
public:
    virtual ~Subject() {}
    virtual void Attach(Observer* observer) = 0;
    virtual void Detach(Observer* observer) = 0;
    virtual void Notify() = 0;
};