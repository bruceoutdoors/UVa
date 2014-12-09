#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

struct searchResult {
    size_t idx;
    list<int>::iterator it;
};

vector< list<int> > blockWorld;

// prototypes:
void printBlockWorld();
void returnInitialPosition(searchResult r);
searchResult findBlock(int k);

int main()
{
    string com1, com2;
    int a, b, size;

    // first line gets the size
    cin >> size;
    blockWorld.reserve(size);

    // initial setup:
    for (int i = 0; i < size; i++) {
        list<int> k;
        k.push_back(i);
        blockWorld.push_back(k);
    }
    
    while (true) {
        cin >> com1;
        if (com1 == "quit") break;
        cin >> a >> com2 >> b;
        
        if (a == b) continue;
        
        searchResult aLoc = findBlock(a);
        searchResult bLoc = findBlock(b);
        
        if (aLoc.idx == bLoc.idx) continue;
        
        // return blocks to initial positions, if any... 
        if        (com1 == "move" && com2 == "onto") {
            returnInitialPosition(aLoc);
            returnInitialPosition(bLoc);
        } else if (com1 == "move" && com2 == "over") {
            returnInitialPosition(aLoc);
        } else if (com1 == "pile" && com2 == "onto") {
            returnInitialPosition(bLoc);
        } 
        
        // ...then pile/move them:
        if (com1 == "pile") {
            blockWorld[bLoc.idx].splice(blockWorld[bLoc.idx].end(), 
                                        blockWorld[aLoc.idx], 
                                        aLoc.it, 
                                        blockWorld[aLoc.idx].end());
        } else if (com1 == "move") {
            blockWorld[bLoc.idx].splice(blockWorld[bLoc.idx].end(), 
                                        blockWorld[aLoc.idx], 
                                        aLoc.it);
        }
        
        // debug information, uncomment to toggle:
        //~ cout << "\n-----=> " << com1 << " " << a << " " 
             //~ << com2 << " " << b << "\n\n";
        //~ printBlockWorld();
    }
    
    printBlockWorld();
    
    return 0;
}

void printBlockWorld()
{
    for (size_t i = 0; i < blockWorld.size(); i++) {
        cout << i << ":";
        for (auto p : blockWorld[i]) cout << " " << p;
        
        cout << endl;
    }
}

searchResult findBlock(int k)
{
    searchResult result;
    for (size_t i = 0; i < blockWorld.size(); i++) {
        for (list<int>::iterator it = blockWorld[i].begin(); 
                it != blockWorld[i].end(); it++) {
            if (*it == k) {
                result = { i, it };
                return result;
            }
        }
    }
    
    return result;
}

// return all blocks stacked above this block to their initial positions
void returnInitialPosition(searchResult r)
{
    if (r.it == blockWorld[r.idx].end()) return;
    
    list<int>::iterator itr;
            
    itr = r.it;
    while (++itr != blockWorld[r.idx].end()) 
        blockWorld[*itr].push_back(*itr);
    
    itr = r.it;
    blockWorld[r.idx].erase(++itr, blockWorld[r.idx].end());
}
