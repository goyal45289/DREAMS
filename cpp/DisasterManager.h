#ifndef DISASTER_MANAGER_H
#define DISASTER_MANAGER_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Disaster.h"
#include "Resource.h"
#include "PriorityManager.h"
#include "ResourceAllocator.h"

class DisasterManager {
private:
    std::vector<Disaster> disasters;
    std::vector<Resource> resources;

    CityGraph map;
    ResourceAllocator allocator;
    int nextId = 1;

    void dispatch() {
        PriorityManager priorityQueue;

        for (auto& disaster : disasters) {
            if (disaster.status == Disaster::PENDING) {
                priorityQueue.push(disaster);
            }
        }

        while (!priorityQueue.empty()) {
            Disaster current = priorityQueue.pop();

            std::vector<std::string> path;
            int kilometres = 0;

            int resourceIndex = allocator.choose(
                current,
                resources,
                map,
                path,
                kilometres
            );

            if (resourceIndex < 0) {
                continue;
            }

            for (auto& disaster : disasters) {
                if (disaster.id == current.id) {
                    disaster.status = Disaster::ASSIGNED;
                    disaster.resourceId = resources[resourceIndex].id;
                }
            }

            std::cout << "Dispatch incident #" << current.id << " via ";

            for (const auto& zone : path) {
                std::cout << zone << " ";
            }

            std::cout << "(" << kilometres << " km)\n";
        }
    }

public:
    DisasterManager() {
        resources.emplace_back(101, "Ambulance", "Zone A");
        resources.emplace_back(102, "Fire Truck", "Zone B");
        resources.emplace_back(103, "Rescue Team", "Zone C");
    }

    void report(
        std::string type,
        int affected,
        int injured,
        int trapped,
        std::string zone
    ) {
        disasters.emplace_back(
            nextId++,
            type,
            affected,
            injured,
            trapped,
            zone
        );

        std::cout << "Reported #" << nextId - 1
                  << " severity " << disasters.back().severity() << "\n";

        dispatch();
    }

    void complete(int id) {
        for (auto& disaster : disasters) {
            if (disaster.id == id && disaster.status == Disaster::ASSIGNED) {
                for (auto& resource : resources) {
                    if (resource.id == disaster.resourceId) {
                        resource.release(disaster.zone);
                    }
                }

                disaster.status = Disaster::COMPLETED;

                std::cout << "Completed #" << id
                          << "; resource released.\n";

                dispatch();
                return;
            }
        }

        std::cout << "No assigned incident with that ID.\n";
    }

    void showDisasters() {
        for (const auto& disaster : disasters) {
            std::cout << "#" << disaster.id << " "
                      << disaster.type << " "
                      << disaster.zone << " "
                      << disaster.severity()
                      << " status="
                      << (disaster.status == 0
                              ? "PENDING"
                              : disaster.status == 1
                                  ? "ASSIGNED"
                                  : "COMPLETED")
                      << "\n";
        }
    }

    void showDisastersSorted() {
        std::vector<Disaster> sorted = disasters;

        std::sort(
            sorted.begin(),
            sorted.end(),
            [](const Disaster& a, const Disaster& b) {
                if (a.priority() == b.priority()) {
                    return a.id < b.id;
                }

                return a.priority() > b.priority();
            }
        );

        for (const auto& disaster : sorted) {
            std::cout << "#" << disaster.id << " "
                      << disaster.type << " "
                      << disaster.zone << " "
                      << disaster.severity()
                      << " status="
                      << (disaster.status == 0
                              ? "PENDING"
                              : disaster.status == 1
                                  ? "ASSIGNED"
                                  : "COMPLETED")
                      << "\n";
        }
    }

    void showResources() {
        for (const auto& resource : resources) {
            std::cout << "#" << resource.id << " "
                      << resource.type << " "
                      << resource.zone << " "
                      << (resource.available ? "AVAILABLE" : "DEPLOYED")
                      << "\n";
        }
    }
};

#endif
