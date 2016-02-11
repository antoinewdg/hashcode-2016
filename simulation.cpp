//
// Created by antoinewdg on 2/11/16.
//

#include "simulation.h"

Simulation::Simulation(string filename) {
    ifstream file(filename);
    string line, token;
    vector<float> res;
    stringstream ss(line);

    getline(file, line);
    ss = stringstream(line);
    getline(ss, token, ' ');
    rows = atoi(token);
    getline(ss, token, ' ');
    cols = atoi(token);
    getline(ss, token, ' ');
    drones = atoi(token);
    getline(ss, token, ' ');
    t_max = atoi(token);
    getline(ss, token, ' ');
    payload = atoi(token);


    getline(file, line);
    n_products = atoi(line);

    getline(file, line);
    ss = stringstream(line);
    products = vector<Product>(n_products);
    int i = 0;
    while (getline(ss, token, ' ')) {
        products[i] = Product(atoi(token));
        i++;
    }

    getline(file, line);
    n_warehouses = atoi(line);
    warehouses = vector<Warehouse>(n_warehouses);
    i = 0;

    while (getline(file, line)) {
        ss = stringstream(line);
        getline(ss, token, ' ');
        while (getline(ss, token, ' ')) {
            warehouses[i] = Product(atoi(token));
            i++;
        }
    }


    while (getline(file, line)) {
        ss(line);
        while (getline(ss, token, ' ')) {
            res.push_back(float(atof(token.c_str())));
        }
//        cout << line << endl;
    }

    for (float f : res) {
        cout << f << " ";
    }
}
