#pragma once

#include <list>
#include <memory>

class Observer;

class Subject {
public:
    void subscribe(std::shared_ptr<Observer> observer);
    void notify();
private:
    std::list<std::shared_ptr<Observer>> _observers;
};
