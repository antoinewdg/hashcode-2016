#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "simulation.h"

using namespace std;

void parse_file(string filename) {
    ifstream file(filename);
    string line, token;
    vector<float> res;

    while (getline(file, line)) {
        stringstream ss(line);
        while (getline(ss, token, ' ')) {
            res.push_back(float(atof(token.c_str())));
        }
//        cout << line << endl;
    }

    for (float f : res) {
        cout << f << " ";
    }
}

int main() {
//    cout << "Hello, World!" << endl;
    Simulation sim("files/in/busy_day.in");
//    cout << sim;

    vector<vector<int>> commands = sim.locateObjects(sim.orders[50]);

    for(int i = 0; i < sim.orders[50].product_quantities.size(); i++) {
        if(sim.orders[50].product_quantities[i] != 0) {
            cout << i << " " << sim.orders[50].product_quantities[i] << " " << sim.products[i].weight << endl;
        }
    }
    cout << endl;
    for(int i = 0; i < commands.size(); i++) {
        for(int j = 0; j < commands[i].size(); j++) {
            cout << commands[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}