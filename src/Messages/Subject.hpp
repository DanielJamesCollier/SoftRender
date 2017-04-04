#ifndef Subject_hpp
#define Subject_hpp

#include <vector>
#include <algorithm>
#include <iostream>

template<typename Observer>
class Subject {
public:
    Subject() = default;
    ~Subject() = default;

    void attachObserver(Observer & observer) {
        if (std::find(std::begin(m_observers), std::end(m_observers), &observer) == std::end(m_observers)) {
            m_observers.push_back(&observer);
        } else {
            std::cerr << "observer allready added\n";
        }
    }

protected:
    std::vector<Observer*> m_observers;
};
#endif /* Subject_hpp */