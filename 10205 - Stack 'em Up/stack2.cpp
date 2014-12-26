/* a simpler variant forked off algorithm from
 * https://github.com/marioyc/Online-Judge-Solutions/blob/master/UVA/Contest%20Volumes/10205%20-%20Stack%20'em%20Up.cpp
 */

#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <stdlib.h> //atoi

using namespace std;

#define CARD_COUNT 52

typedef array<int, CARD_COUNT> Sequence;

const array<string, 4> suits  = {"Clubs", "Diamonds", "Hearts", "Spades"};
const array<string, 13> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

inline void resetSequence(Sequence &seq) { for (int i = 0; i < CARD_COUNT; i++) seq[i] = i; }

int main()
{
    array<string, CARD_COUNT> cards;
    int itr = 0;
    for (auto &suit : suits) {
        for (auto &rank : ranks) {
            cards[itr++] = rank + " of " + suit;
        }
    }
    
    int testCases;
    cin >> testCases;
    cin.get(); // ignore newline after testCase count
    cin.get(); // ignore empty line
    
    while(testCases-- > 0) {
        vector<Sequence> shuffles;
        Sequence sequence;
        resetSequence(sequence);
        int kCount;
        cin >> kCount;
        
        while (kCount-- > 0) {
            Sequence shuffle;
            for (int i = 0; i < CARD_COUNT; i++) {
                cin >> shuffle[i];
                shuffle[i]--; // sequences start from 1, but array idx starts from 0
            }
            shuffles.push_back(shuffle);
        }
        
        cin.get(); // ignore newline
        char input[10];
        while (true) {
            cin.getline(input, 10);
            int k = atoi (input);
            // we assume that k-th sequence always start with 1,
            // ergo invalid conversion will be definitely be 0:
            if (k == 0) break;
            
            Sequence nextSeq;
            for (int i = 0; i < CARD_COUNT; i++) nextSeq[i]  = sequence[shuffles[k-1][i]];
            for (int i = 0; i < CARD_COUNT; i++) sequence[i] = nextSeq[i];
        }
        
        for (int i = 0; i < CARD_COUNT; i++) 
            cout << cards[sequence[i]] << endl;
            
        if (testCases != 0) cout << endl;
    }
    
    return 0;
}
