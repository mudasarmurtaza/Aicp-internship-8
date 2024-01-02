#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct Boat {
    bool isAvailable;
    int returnTime;
};

int main() {
    const int OPENING_HOUR = 10;
    const int CLOSING_HOUR = 17;
    const double HOURLY_RATE = 20.0;
    const double HALF_HOUR_RATE = 12.0;
    const int NUM_BOATS = 10;

    std::vector<Boat> boats(NUM_BOATS, {true, OPENING_HOUR});

    int totalHoursHired = 0;
    double totalMoneyTaken = 0.0;

    cout << "Boat rental service is open from 10:00 to 17:00." << endl;

    while (true) {
        int startHour, endHour;
        char hireType;

        cout << "Enter the starting hour of boat hire (10-17): ";
        cin >> startHour;

        // Check if the service is open at the specified starting hour
        if (startHour < OPENING_HOUR || startHour > CLOSING_HOUR) {
            cout << "Boat rental service is closed at that hour. Please choose a valid hour." << endl;
            continue;
        }

        // Find the next available boat
        int availableBoatIndex = -1;
        for (int i = 0; i < NUM_BOATS; ++i) {
            if (boats[i].isAvailable) {
                availableBoatIndex = i;
                break;
            }
        }

        if (availableBoatIndex == -1) {
            // No boats are available, find the earliest return time
            int earliestReturnTime = CLOSING_HOUR + 1;
            for (const Boat& boat : boats) {
                if (boat.returnTime < earliestReturnTime) {
                    earliestReturnTime = boat.returnTime;
                }
            }

            cout << "No boats are currently available. Earliest available time is: " << earliestReturnTime << ":00" << endl;
            continue;
        }

        cout << "Enter the type of hire (H for hourly, M for half-hourly): ";
        cin >> hireType;

        double rate = (hireType == 'H' || hireType == 'h') ? HOURLY_RATE : HALF_HOUR_RATE;

        cout << "Enter the ending hour of boat hire (10-17): ";
        cin >> endHour;

        // Check if the service is open at the specified ending hour
        if (endHour < OPENING_HOUR || endHour > CLOSING_HOUR) {
            cout << "Boat rental service is closed at that hour. Please choose a valid hour." << endl;
            continue;
        }

        int hoursHired = endHour - startHour;

        // Update total hours hired, money taken, and boat status
        totalHoursHired += hoursHired;
        totalMoneyTaken += hoursHired * rate;

        boats[availableBoatIndex].isAvailable = false;
        boats[availableBoatIndex].returnTime = endHour;

        cout << "Boat " << availableBoatIndex + 1 << " hired successfully for " << hoursHired << " hours. Rate: $" << rate
                  << " per hour. Total: $" << std::fixed << std::setprecision(2) << hoursHired * rate << endl;

        char anotherHire;
        cout << "Do you want to hire another boat? (Y/N): ";
        cin >> anotherHire;

        if (anotherHire != 'Y' && anotherHire != 'y') {
            break;  // Exit the loop if the user does not want to hire another boat
        }
    }

    // Output total money taken and hours hired at the end of the day
    cout << "End of the day summary:" << endl;
    cout << "Total money taken: $" << std::fixed << std::setprecision(2) << totalMoneyTaken << endl;
    cout << "Total hours hired: " << totalHoursHired << " hours" << endl;

    return 0;
}
