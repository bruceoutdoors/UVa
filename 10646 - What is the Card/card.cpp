#include <iostream>
#include <array>
#include <string>
#include <stdlib.h> //atoi

using namespace std;

int findVal(const string card) {
    int rank = atoi(&card[0]);
    return rank == 0 ? 10 : rank;
}

int main()
{
	int testCases;
    cin >> testCases;
    
    for (int t = 1; t <= testCases; t++) {
        array<string, 52> pile;
        
        for (auto &card : pile) cin >> card;
        
        int topPile = 26, Y = 0;
        for (int i = 0; i < 3; i++) {
            int X = findVal(pile[topPile]);
            Y += X; 
            
            // Put this card and the top (10-X) cards of the pile away
            topPile -= ((10 - X) + 1);
        }
        
        // we don't have to place all 25 cards back; just the ones to get Y-th:
        int stop = 26 + (Y - topPile);
        for (int i = 27; i < stop; i++) pile[++topPile] = pile[i];
        
        // Y starts from 0 here, so the Y-th card is in the idx Y-1
        cout << "Case " << t << ": " << pile[Y-1] << endl;
    }
    
	return 0;
}
