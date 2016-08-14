#include <algorithm>
#include <memory>

using std::shared_ptr;
using std::find;

#include "observer.h"
#include "subject.h"

void Subject::subscribe(shared_ptr<Observer> observer) {
    _observers.push_back(observer);
}

void Subject::unsubscribe(std::shared_ptr<Observer> observer) {
    auto fid = find(_observers.begin(), _observers.end(), observer);
    if (fid != _observers.end()) _observers.erase(fid);
}

void Subject::notify() {
    for (auto obs : _observers)
        obs->update();
}
