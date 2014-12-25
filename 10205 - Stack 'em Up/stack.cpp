#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <stdlib.h> //atoi
#include <set>
#include <stack>

using namespace std;

#define CARD_COUNT 52

typedef array<int, CARD_COUNT> Sequence;

const array<string, 4> suits  =  {"Clubs", "Diamonds", "Hearts", "Spades"};
const array<string, 13> ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
array<string, CARD_COUNT> cards;

int findVal(Sequence &seq, int val, int idx)
{
    if (val == seq[idx]) {
        swap(seq[val], seq[idx]);
        return idx;
    }
    
    return findVal(seq, val, seq[idx]);
}

void applyShuffle(Sequence &seq, const Sequence &other)
{
    Sequence otherCopy(other);
    stack<int> swapStack;

    // the loop below sorts a copy of the sequence,
    // pushing required swaps into a stack:
    for (int i = 0; i < CARD_COUNT; i++) {
        if (i != otherCopy[i]) {
            int idx = findVal(otherCopy, i, otherCopy[i]);
            swapStack.push(i);
            swapStack.push(idx);
        }
    }
    
    // the swap is then executed in descending order:
    while (!swapStack.empty()) {
        int idx = swapStack.top();
        swapStack.pop();
        swap(seq[idx], seq[swapStack.top()]);
        swapStack.pop();
        
        //~ cout << "swap " << idx+1 << " with " << swapStack.top()+1 << endl;
    }
    
    //~ for (int i = 0; i < CARD_COUNT; i++)  cout << seq[i]+1 << " ";
    //~ cout << endl;
}

inline void resetSequence(Sequence &seq) { for (int i = 0; i < CARD_COUNT; i++) seq[i] = i; }

int main()
{
    // init:
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
            
            applyShuffle(sequence, shuffles[k-1]);
        }
        
        for (int i = 0; i < CARD_COUNT; i++) 
            cout << cards[sequence[i]] << endl;
            
        if (testCases != 0) cout << endl;
    }
    
    return 0;
}
