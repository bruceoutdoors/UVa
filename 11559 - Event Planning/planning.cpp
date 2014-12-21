#include <iostream>
#include <limits.h>

using namespace std;

int main()
{
    int numParticipants, budget, numHotels, numWeeks;
    
    while (cin >> numParticipants >> budget >> numHotels >> numWeeks) {
        int minCost = INT_MAX;
        bool canStay = false;
        
        while (numHotels--) {
            int price, totalCost;
            bool isEnoughBed = false;
            cin >> price;
            totalCost = price * numParticipants;
            for (int i = 0; i < numWeeks; i++) {
                int bedsAvailable;
                cin >> bedsAvailable;
                if (bedsAvailable >= numParticipants) {
                    isEnoughBed = true;
                    cin.ignore(INT_MAX, '\n');
                    break;
                }      
            }
            
            if (isEnoughBed && (totalCost <= budget) && (totalCost < minCost)) {
                minCost = totalCost;
                canStay = true;
            }
        } 
        
        if (canStay) {
            cout << minCost << endl;
        } else {
            cout << "stay home" << endl;
        }
    }
    
	return 0;
}
