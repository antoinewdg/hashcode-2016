//
// Created by antoinewdg on 2/11/16.
//

#include "simulation.h"

Simulation::Simulation(string filename) {
    ifstream file(filename);
    string line, token;
    vector<float> res;

    {
        getline(file, line);
        stringstream ss(line);
        getline(ss, token, ' ');
        rows = atoi(token.c_str());
        getline(ss, token, ' ');
        cols = atoi(token.c_str());
        getline(ss, token, ' ');
        n_drones = atoi(token.c_str());
        getline(ss, token, ' ');
        t_max = atoi(token.c_str());
        getline(ss, token, ' ');
        payload = atoi(token.c_str());
    }


    getline(file, line);
    n_products = atoi(line.c_str());
    {
        getline(file, line);
        stringstream ss(line);
        products = vector<Product>(n_products);
        for (int i = 0; i < n_products; i++) {
            getline(ss, token, ' ');
            products[i].weight = atoi(token.c_str());
            products[i].id = i;
        }
    }
    getline(file, line);
    n_warehouses = atoi(line.c_str());
    warehouses = vector<Warehouse>(n_warehouses);

    for (int i = 0; i < n_warehouses; i++) {
        {
            warehouses[i].id = i;
            getline(file, line);
            stringstream ss(line);
            getline(ss, token, ' ');
            warehouses[i].r = atoi(token.c_str());
            getline(ss, token, ' ');
            warehouses[i].c = atoi(token.c_str());
        }
        {
            warehouses[i].product_quantities = vector<int>(n_products);
            getline(file, line);
            stringstream ss(line);
            for (int j = 0; j < n_products; j++) {
                getline(ss, token, ' ');
                warehouses[i].product_quantities[j] = atoi(token.c_str());
            }
        }
    }

    getline(file, line);
    n_orders = atoi(line.c_str());
    orders = vector<Order>(n_orders);

    for (int i = 0; i < n_orders; i++) {
        orders[i].id = i;
        getline(file, line);
        {
            stringstream ss(line);
            getline(ss, token, ' ');
            orders[i].r = atoi(token.c_str());
            getline(ss, token, ' ');
            orders[i].c = atoi(token.c_str());
        }
        getline(file, line);
        int product_number = atoi(line.c_str());
        getline(file, line);
        {
            stringstream ss(line);
            orders[i].product_quantities = vector<int>(n_products);
            for (int j = 0; j < product_number; j++) {
                getline(ss, token, ' ');
                orders[i].product_quantities[atoi(token.c_str())]++;
            }
        }
    }

    drones = vector<Drone>(n_drones);
    for (int i = 0; i < n_drones; i++) {
        drones[i].id = i;
        drones[i].r = warehouses[0].r;
        drones[i].c = warehouses[i].c;
    }

//    cout << getline(file, line) << endl;
}

ostream &operator<<(ostream &os, const Simulation &s) {
    os << s.rows << " " << s.cols << " " << s.n_drones << " " << s.t_max << " " << s.payload << " " << endl;
    os << s.n_products << endl;
    for (Product p : s.products) {
        os << p.weight << " ";
    }
    os << endl;

    os << s.n_warehouses << endl;

    for (Warehouse w : s.warehouses) {
        os << w.r << " " << w.c << endl;
        for (int q : w.product_quantities) {
            os << q << " ";
        }
        os << endl;
    }

    os << s.n_orders << endl;
    for (Order o : s.orders) {
        os << o.r << " " << o.c << endl << endl;
        for (int q : o.product_quantities) {
            os << q << " ";
        }
        os << endl;
    }


    return os;
}


vector<vector<int>> Simulation::locateObjects(Order o) {
    vector<vector<int>> commands;
    vector<Warehouse> wares(warehouses);
    sort(wares.begin(), wares.end(), [&o](Warehouse w1, Warehouse w2) {
        double dist1 = pow((w1.r - o.r), 2) + pow(w1.c - o.c, 2);
        double dist2 = pow((w2.r - o.r), 2) + pow(w2.c - o.c, 2);

        return dist1 < dist2;
    });

    bool finished = false;
    while (!finished) {
        vector<int> command;
        int charge = 0;
        for (Warehouse w: wares) {
            for (int i = 0; i < n_products; i++) {

                int numb = o.product_quantities[i];
                int weight = products[i].weight;

                numb = min(numb, (payload - charge) / weight);

                if (numb == 0 || w.product_quantities[i] == 0) {
                    continue;
                }
                else {
                    takeInWarehouse(w, o, command, i, numb, charge);
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
