#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <memory>

#define INCORRECT_PENALTY_TIME 20

using namespace std;

struct player {
    int id; 
    set<int> problemsSolved;
    map<int, int> incorrectCount; // <question num, count>
    int timePenalty;
    
    player(int id) {
        this->id = id;
        timePenalty = 0;
    }
};

typedef shared_ptr<player> playerPtr;

vector<playerPtr> players;

// default comparable cannot be used as sort algorithm sorts by reference
bool comparePlayerPtr(playerPtr a, playerPtr b) 
{ 
    if (a->problemsSolved.size() == b->problemsSolved.size()) {
        if (a->timePenalty == b->timePenalty) {
            return a->id < b->id;
        }
        return a->timePenalty < b->timePenalty;
    }
    
    return a->problemsSolved.size() > b->problemsSolved.size();
}

playerPtr getPlayer(int id) 
{
    for (auto p : players) {
        if (p->id == id) return p;
    }
    
    // if cannot found, create, add and return one
    playerPtr p(new player(id));
    players.push_back(p);
    return p;
}

bool hasProblemSolved(int prob, playerPtr p)
{
    return (p->problemsSolved.find(prob) == p->problemsSolved.end()) ?
            false : true;
}

int main()
{
    int testCases;
    string line;
    istringstream iss;
    
    cin >> testCases;
    cin.get(); // ignore newline after testCase count
    cin.get(); // ignore empty line
    
    while(testCases-- > 0) {
        do {
            // retrieve input:
            getline(cin, line);
            istringstream iss(line);
            
            int playerId; 
            int problem; 
            int time; 
            char L;  
            
            iss >> playerId;
            iss >> problem;
            iss >> time;
            iss >> L;
            
            playerPtr pl = getPlayer(playerId);
            
            // proceeding submissions after a correct submission is skipped
            if (hasProblemSolved(problem, pl)) continue;
            
            if (L == 'I') {
                pl->incorrectCount[problem]++;
            } else if (L == 'C') {
                pl->timePenalty += 
                    (pl->incorrectCount[problem] * INCORRECT_PENALTY_TIME) + time;
                pl->problemsSolved.insert(problem);
            }
        } while (line != "");
        
        sort(players.begin(), players.end(), comparePlayerPtr);
        
        // print scoreboard 
        for (auto pl : players) {
            cout << pl->id << " " 
                 << pl->problemsSolved.size() << " " 
                 << pl->timePenalty << endl;
        }
        
        // cleanups:
        players.clear();
    
        // make sure there is only ONE blank line 
        // at the end of output (IMPORTANT!):
        if (testCases != 0) cout << endl;
    }
}
