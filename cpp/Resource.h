#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

struct Resource {
    int id;
    std::string type;
    std::string zone;
    bool available;
    int incident;

    Resource(int n, std::string t, std::string z)
        : id(n),
          type(t),
          zone(z),
          available(true),
          incident(-1) {
    }

    void assign(int disasterId) {
        available = false;
        incident = disasterId;
    }

    void release(std::string newZone) {
        available = true;
        incident = -1;
        zone = newZone;
    }
};

#endif
