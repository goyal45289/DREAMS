#ifndef PRIORITY_MANAGER_H
#define PRIORITY_MANAGER_H

#include <queue>
#include <vector>

#include "Disaster.h"

struct DisasterOrder {
    bool operator()(const Disaster& a, const Disaster& b) const {
        if (a.priority() == b.priority()) {
            return a.id > b.id;
        }

        return a.priority() < b.priority();
    }
};

class PriorityManager {
private:
    std::priority_queue<
        Disaster,
        std::vector<Disaster>,
        DisasterOrder
    > queue;

public:
    void push(const Disaster& disaster) {
        queue.push(disaster);
    }

    bool empty() const {
        return queue.empty();
    }

    Disaster pop() {
        Disaster disaster = queue.top();
        queue.pop();
        return disaster;
    }
};

#endif
