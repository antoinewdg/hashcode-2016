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


vector<vector<int>> Simulation::locateObjects(Order o) {
    vector<vector<int>> commands;
    vector<Warehouse> wares(warehouses);
    sort(wares.begin(), wares.end(), [](Warehouse w1, Warehouse w2) {
        double dist1 = pow((w1.r - o.r), 2) + pow(w1.c - o.c, 2);
        double dist2 = pow((w2.r - o.r), 2) + pow(w2.c - o.c, 2);

        return dist1 < dist2;
    });

    bool finished = false;
    while (!finished) {
        vector<int> command;
        int charge = 0;
        for (Warehouse w: wares) {
            command.push_back(w.id);
            for (int i = 0; i < n_products; i++) {

                int numb = o.product_quantities[i];
                int weight = products[i];

                numb = min(numb, (payload - charge) / weight);

                if (numb == 0 || w.product_quantities[i] == 0) {
                    continue;
                }
                else {
                    if (w.product_quantities[i] >= numb) {
                        w.product_quantities[i] -= numb;
                        o.product_quantities[i] -= numb;
                        command.push_back(w.id);
                        command.push_back(i);
                        command.push_back(numb);
                        charge += numb * weight;
                    }
                    else {
                        o.product_quantities[i] -= w.product_quantities[i];
                        command.push_back(w.id);
                        command.push_back(i);
                        command.push_back(w.product_quantities[i]);
                        charge += w.product_quantities[i] * weight;
                        w.product_quantities[i] = 0;
                    }
                }
            }
        }
        commands.push_back(command);
        for (int i = 0; i < n_products; i++) {
            if (o.product_quantities[i] != 0) {
                finished = false;
                break;
            }
            else {
                finished = true;
            }
        }
    }
    return commands;
}
