/* optimized variant:
 * Switching from vectors and maps to arrays        - 0.05
 * Using scanf instead of getline and stringstream  - 0.11
 * Changing from int to short (negligible)          - 0.03
 * A 2x increase in speed, from 0.259 to 0.139
 */

#include <iostream>
#include <array>
#include <stdio.h>

using namespace std;

struct Card { char rank, suit; };
struct Suit { 
    short count = 0;
    bool isStopped = false;
};

static char suits[] = { 'S', 'H', 'D', 'C' };

short getSuitIdx(char c) {
    for (short i = 0; i < 4; i++) 
        if (suits[i] == c) return i;
    return -1;
}

int main()
{
    while (!feof(stdin)) {
        Card card;
        array<Card, 13> cards;
        array<Suit, 4> suitCount;
        short points = 0; // <- does not include points from rule 5,6,7
        short rule567points = 0;
        
        for (short i = 0; i < 13; i++) {
            scanf("%c%c ", &card.rank, &card.suit);
            suitCount[getSuitIdx(card.suit)].count++;
            cards[i] = card;
        }
        
        // we can assert that the minimum count for a suit in suitCount
        // is at least 1, should it ever reaches the loop below
        for (auto &c : cards) {
            // note that the counts below includes the card itself
            short idx = getSuitIdx(c.suit);
            switch (c.rank) {
                case 'A': 
                    points += 4; 
                    suitCount[idx].isStopped = true;
                    break;
                case 'K': 
                    points += 3;
                    if (suitCount[idx].count >  1) suitCount[idx].isStopped = true;
                    if (suitCount[idx].count <= 1) points--;
                    break;
                case 'Q': 
                    points += 2;
                    if (suitCount[idx].count >  2) suitCount[idx].isStopped = true;
                    if (suitCount[idx].count <= 2) points--;
                    break;
                case 'J': 
                    points += 1;
                    if (suitCount[idx].count <= 3) points--; 
                    break;
            } 
        }
        
        bool isAllSuitsStopped = true;
        for (auto &s : suitCount) {
            isAllSuitsStopped &= s.isStopped;
            switch (s.count) {
                case 2: rule567points += 1; break;
                case 1: rule567points += 2; break;
                case 0: rule567points += 2; break;
            }
        }
        
        short totalPoints = points + rule567points;
        
        if (totalPoints < 14) {
            cout << "PASS" << endl;
        } else if (points >= 16 && isAllSuitsStopped) {
            cout << "BID NO-TRUMP" << endl;
        } else if (totalPoints >= 14) {
            short highest = 0;
            char suit;
            // get highest suit count, in the order S-H-D-C:
            for (short i = 0; i < 4; i++) {
                if (suitCount[i].count > highest) {
                    highest = suitCount[i].count;
                    suit    = suits[i];
                }
            }
                
            cout << "BID " << suit << endl;
        }
    }
    
    return 0;
}
