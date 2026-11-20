#ifndef RESOURCE_ALLOCATOR_H
#define RESOURCE_ALLOCATOR_H

#include <string>
#include <vector>

#include "Resource.h"
#include "Disaster.h"
#include "CityGraph.h"

class ResourceAllocator {
public:
    int choose(
        Disaster& disaster,
        std::vector<Resource>& resources,
        const CityGraph& graph,
        std::vector<std::string>& path,
        int& kilometres
    ) {
        std::string requiredType =
            disaster.type == "Fire"
                ? "Fire Truck"
                : disaster.type == "Medical Emergency"
                    ? "Ambulance"
                    : "Rescue Team";

        int bestIndex = -1;
        int bestDistance = 1000000;

        for (int i = 0; i < static_cast<int>(resources.size()); ++i) {
            if (resources[i].available && resources[i].type == requiredType) {
                std::vector<std::string> candidatePath;
                int distance;

                if (graph.route(
                        resources[i].zone,
                        disaster.zone,
                        candidatePath,
                        distance
                    ) &&
                    distance < bestDistance) {
                    bestIndex = i;
                    bestDistance = distance;
                    path = candidatePath;
                }
            }
        }

        if (bestIndex >= 0) {
            resources[bestIndex].assign(disaster.id);
            disaster.resourceId = resources[bestIndex].id;
            kilometres = bestDistance;
        }

        return bestIndex;
    }
};

#endif
