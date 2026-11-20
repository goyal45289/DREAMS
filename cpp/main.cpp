#include <iostream>
#include <string>

#include "DisasterManager.h"

int main() {
    DisasterManager aidris;
    int choice = 0;

    do {
        std::cout << "\nAIDRIS DISASTER RESPONSE\n"
                  << "1. Register demo incident\n"
                  << "2. Show incidents (default)\n"
                  << "3. Show resources\n"
                  << "4. Complete mission\n"
                  << "5. Show incidents sorted by severity\n"
                  << "0. Exit\n"
                  << "Choice: ";

        std::cin >> choice;

        if (choice == 1) {
            std::string type;
            std::string zone;
            int affected;
            int injured;
            int trapped;

            std::cout << "Type (Fire/Flood/Earthquake/Medical Emergency): ";
            std::cin >> type;

            std::cout << "Zone (A/B/C/D): ";
            std::cin >> zone;

            std::cout << "Affected injured trapped: ";
            std::cin >> affected >> injured >> trapped;

            aidris.report(type, affected, injured, trapped, "Zone " + zone);
        } else if (choice == 2) {
            aidris.showDisasters();
        } else if (choice == 3) {
            aidris.showResources();
        } else if (choice == 5) {
            aidris.showDisastersSorted();
        } else if (choice == 4) {
            int id;
            std::cout << "Incident ID: ";
            std::cin >> id;
            aidris.complete(id);
        }
    } while (choice != 0);

    return 0;
}
