#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    map<string, size_t> counter;
    
    size_t n;
	cin >> n;
    cin.get(); // remove '\n' in the input buffer
    
    while (n-- > 0) {
        char country[75];
        cin.getline(country, 75, ' ');
        cin.ignore(75, '\n');
        
        counter[country]++;
    }
    
    for (auto &kv : counter) cout << kv.first << " " << kv.second << endl;
}
