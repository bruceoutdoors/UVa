// from 0.042 to 0.028, not much, but still fun to do (:
// changed string to char array and remove need to copy any cards over

#include <array>
#include <string>
#include <stdlib.h> //atoi
#include <cstdio>

using namespace std;

typedef char Card[3];

inline int findVal(const Card card) {
    int rank = atoi(&card[0]);
    return rank == 0 ? 10 : rank;
}

int main()
{
	int testCases;
    scanf("%i", &testCases);
    
    for (int t = 1; t <= testCases; t++) {
        array<Card, 52> pile;
        
        for (auto &card : pile) scanf("%s", card);
        
        int topPile = 26, Y = 0;
        for (int i = 0; i < 3; i++) {
            int X = findVal(pile[topPile]);
            Y += X; 
            topPile -= ((10 - X) + 1);
        }
        
        printf("Case %i: %s\n", t, Y < topPile ? pile[Y-1] : pile[26+(Y-topPile-1)]);
    }
    
	return 0;
}
