#include <iostream>
#include <vector>

using namespace std;

inline void increment(int k, vector<int> &v) {
    if (v[k] != -1) v[k]++;
}

int main()
{
    int row, col;
    char t;
    int field_num = 0;

    while (true) {
        // first line has row col:
        cin >> row >> col;
        if (row == 0 && col == 0) break;

        if (field_num++ != 0) cout << endl;
        cout << "Field #" << field_num << ":" << endl;

        int total_cells = row * col;
        vector<int> field(total_cells);

        // store input to vector, swap input for either 0 or -1:
        for (int i = 0; i < total_cells; i++) {
            cin >> t;
            t == '*' ? field[i] = -1 : field[i] = 0;
        }

        for (int i = 0; i < total_cells; i++) {
            if (field[i] == -1) {
                // increment right cell:
                if (!((i+1) % col == 0)) { // unless end of row
                    increment(i+1, field);
                    // increment top right cell:
                    int tr = i+1-col;
                    if (tr >= 0) increment(tr, field);

                    // increment bottom right cell:
                    int br = i+1+col;
                    if (br < total_cells) increment(br, field);
                }

                // increment left cell:
                if (!(i % col == 0)) { // unless first in row
                    // either 0 or multiple of col
                    increment(i-1, field);
                    // increment top left cell:
                    int tl = i-1-col;
                    if (tl >= 0) increment(tl, field);

                    // increment bottom left cell:
                    int bl = i-1+col;
                    if (bl < total_cells) increment(bl, field);
                }
                // increment bottom cell:
                int b = i+col;
                if (b < total_cells) increment(b, field);

                // increment top cell:
                int t = i-col;
                if (t >= 0) increment(t, field);
            }
        }

        // print mine field
        for (int i = 0; i < total_cells; i++) {
            if (field[i] == -1) {
                cout << "*";
            } else {
                cout << field[i];
            }
            // print new line at end of row
            if ((i+1) % col == 0) cout << endl;
        }
    }
    return 0;
}

