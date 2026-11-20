#ifndef DISASTER_H
#define DISASTER_H

#include <string>

struct Disaster {
    enum Status {
        PENDING,
        ASSIGNED,
        COMPLETED
    };

    int id;
    int affected;
    int injured;
    int trapped;
    int resourceId;

    std::string type;
    std::string zone;

    Status status;

    Disaster(int n, std::string t, int a, int i, int tr, std::string z)
        : id(n),
          affected(a),
          injured(i),
          trapped(tr),
          resourceId(-1),
          type(t),
          zone(z),
          status(PENDING) {
    }

    int priority() const {
        if (trapped >= 50 || injured >= 100 || affected >= 1000) {
            return 4;
        }

        if (trapped >= 20 || injured >= 50 || affected >= 500) {
            return 3;
        }

        if (trapped >= 5 || injured >= 10 || affected >= 100) {
            return 2;
        }

        return 1;
    }

    std::string severity() const {
        switch (priority()) {
            case 4:
                return "CRITICAL";
            case 3:
                return "HIGH";
            case 2:
                return "MEDIUM";
            default:
                return "LOW";
        }
    }
};

#endif
