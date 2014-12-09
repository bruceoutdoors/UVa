#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#define INCORRECT_PENALTY_TIME 20

using namespace std;

struct input {
    int playerId; 
    int problem; 
    int time; 
    char L;  
};

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

vector<player*> players;

// default comparable cannot be used as sort algorithm sorts by reference
bool comparePlayerPtr(player* a, player* b) 
{ 
    if (a->problemsSolved.size() == b->problemsSolved.size()) {
        if (a->timePenalty == b->timePenalty) {
            return a->id < b->id;
        }
        return a->timePenalty < b->timePenalty;
    }
    
    return a->problemsSolved.size() > b->problemsSolved.size();
}

player* getPlayer(int id) 
{
    for (player *p : players) {
        if (p->id == id) return p;
    }
    
    // if cannot found, create, add and return one
    player *p = new player(id);
    players.push_back(p);
    return p;
}

bool hasProblemSolved(int prob, player *p)
{
    return (p->problemsSolved.find(prob) == p->problemsSolved.end()) ?
            false : true;
}

int main()
{
    int testCases;
    string line;
    istringstream iss;
    vector<input> inputs;
    
    cin >> testCases;
    cin.get(); // ignore newline after testCase count
    getline(cin, line); // ignore empty line
    
    while(testCases-- > 0) {
        do { // add to input container
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
            
            input inp = { playerId, problem, time, L };
            inputs.push_back(inp);
        } while (line != "");
        
        for (auto &inp : inputs) {
            player *pl = getPlayer(inp.playerId);
            
            // proceeding submissions after a correct submission is skipped
            if (hasProblemSolved(inp.problem, pl)) continue;
            
            if (inp.L == 'I') {
                pl->incorrectCount[inp.problem]++;
            } else if (inp.L == 'C') {
                pl->timePenalty += 
                    (pl->incorrectCount[inp.problem] * INCORRECT_PENALTY_TIME) + 
                    inp.time;
                pl->problemsSolved.insert(inp.problem);
            }
        }
        
        sort(players.begin(), players.end(), comparePlayerPtr);
        
        // print scoreboard 
        for (player *p : players) {
            cout << p->id << " " 
                 << p->problemsSolved.size() << " " 
                 << p->timePenalty << endl;
        }
        
        // cleanups:
        inputs.clear();
        for (player *pl : players) delete pl;
        players.clear();
    
        // make sure there is only ONE blank line 
        // at the end of output (IMPORTANT!):
        if (testCases != 0) cout << endl;
    }
}
