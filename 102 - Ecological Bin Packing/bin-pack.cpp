#include <iostream>

using namespace std;

#define B 0
#define G 1
#define C 2
// consts
const int COLOR_NUM = 3;

// globals
int bin1[COLOR_NUM], bin2[COLOR_NUM], bin3[COLOR_NUM];

// prototypes
int getMoveCount(char order[COLOR_NUM]);
int getIdx(char code);

int main()
{
	const int PERMUTES  = 6;
    
    while (cin >> bin1[B] >> bin1[G] >> bin1[C]
               >> bin2[B] >> bin2[G] >> bin2[C]
               >> bin3[B] >> bin3[G] >> bin3[C]) {
        int leastMoves = 999999999;
        int least_idx;
        // if BGC:
        char seq[PERMUTES][COLOR_NUM+1] = {
            "BCG", "BGC", "CBG",
            "CGB", "GBC", "GCB"
        };
        for (int i = 0; i < PERMUTES; i++) {
            int moves = getMoveCount(seq[i]);
            //~ cout << seq[i] << " " << moves << endl;
            if (moves < leastMoves) {
                leastMoves = moves;
                least_idx = i;
            }
        }
        
        cout << seq[least_idx] << " " << leastMoves << endl;
    }
    
	return 0;
}

int getMoveCount(char order[COLOR_NUM])
{
    return bin2[getIdx(order[0])] + bin3[getIdx(order[0])] +
           bin1[getIdx(order[1])] + bin3[getIdx(order[1])] +
           bin1[getIdx(order[2])] + bin2[getIdx(order[2])];
}

int getIdx(char code)
{
    switch(code) {
        case 'B': return B;
        case 'G': return G;
        case 'C': return C;
    }
    
    return -1;
}
