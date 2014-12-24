#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct Card { char rank, suit; };

int main()
{
    string line;
    
    // the order S-H-D-C happens to be the chars in descending order
    // so we pass a custom comparator (a lambda function) for the map 
    map<char, int, bool(*)(char, char)> suitCount([](char l, char r) { return l > r; });
    
	while (getline(cin, line)) {
        
        suitCount['S'] = 0;
        suitCount['H'] = 0;
        suitCount['D'] = 0;
        suitCount['C'] = 0;
        
        Card card;
        vector<Card> cards;
        
        set<char> stoppedSuits; 
        
        int points = 0;
        int rule567points = 0;
        istringstream iss(line);
        
        while (iss >> card.rank >> card.suit) {
            suitCount[card.suit]++;
            cards.push_back(card);
        }
        
        for (auto &c : cards) {
            // we can assert that the minimum count for a suit in 
            // suitCount is 1, should it ever reaches here
            switch (c.rank) {
                case 'A': 
                    stoppedSuits.insert(c.suit);
                    points += 4; 
                    break;
                case 'K': 
                    points += 3;
                    if (suitCount[c.suit] > 1) stoppedSuits.insert(c.suit);
                    // Subtract a point for any king of a suit in 
                    // which the hand holds 0 other cards.
                    if (suitCount[c.suit] <= 1) points--;
                    break;
                case 'Q': 
                    points += 2;
                    if (suitCount[c.suit] > 2) stoppedSuits.insert(c.suit);
                    // Subtract a point for any queen in a suit in 
                    // which the hand holds only 0 or 1 other cards.
                    if (suitCount[c.suit] <= 2) points--;
                    break;
                case 'J': 
                    points += 1;
                    // Subtract a point for any jack in a suit in 
                    // which the hand holds only 0, 1, or 2 other cards
                    if (suitCount[c.suit] <= 3) points--; 
                    break;
            } 
        }
        
        for (auto &kv : suitCount) {
            switch (kv.second) {
                case 2: rule567points += 1; break;
                case 1: rule567points += 2; break;
                case 0: rule567points += 2; break;
            }
        }
        
        int totalPoints = points + rule567points;
        
        /* Debugging code: */
        //~ for (auto &c : cards) cout << c.rank << c.suit << " ";
        //~ cout << endl;
        //~ for (auto &kv : suitCount)  cout << kv.first << " : " << kv.second << endl;
        //~ cout << "Stopped Suits: ";
        //~ for (auto &s : stoppedSuits) cout << s << " ";
        //~ cout << endl << "Points: " << totalPoints << endl << endl;
        
        if (totalPoints < 14) {
            cout << "PASS" << endl;
        } else if (points >= 16 && stoppedSuits.size() == 4) {
            cout << "BID NO-TRUMP" << endl;
        } else if (totalPoints >= 14) {
            int highest = 0;
            char suit;
            // get highest suit count:
            for (auto &kv : suitCount) {
                if (kv.second > highest) {
                    highest = kv.second;
                    suit = kv.first;
                }
            }
                
            cout << "BID " << suit << endl;
        }
        
    }
    
    // there is an empty line at the end of this output. Without it,
    // you get wrong answer without a fucking clue what went wrong
	return 0;
}
