#include <memory>

using std::shared_ptr;

#include "subject.h"
#include "observer.h"


void Subject::subscribe(shared_ptr<Observer> observer) {
    _observers.push_back(observer);
}

void Subject::notify() {
    for (auto obs : _observers)
        obs->update();
}
