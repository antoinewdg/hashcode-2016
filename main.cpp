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



    return 0;
}