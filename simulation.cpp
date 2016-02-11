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
    rows = atoi(token.c_str());
    getline(ss, token, ' ');
    cols = atoi(token.c_str());
    getline(ss, token, ' ');
    n_drones = atoi(token.c_str());
    getline(ss, token, ' ');
    t_max = atoi(token.c_str());
    getline(ss, token, ' ');
    payload = atoi(token.c_str());


    getline(file, line);
    n_products = atoi(line.c_str());

    getline(file, line);
    ss = stringstream(line);
    products = vector<Product>(n_products);
    for (int i = 0; i < n_products; i++) {
        getline(ss, token, ' ');
        products[i].weight = atoi(token.c_str());
    }

    getline(file, line);
    n_warehouses = atoi(line.c_str());
    warehouses = vector<Warehouse>(n_warehouses);

    for (int i = 0; i < n_warehouses; i++) {
        getline(file, line);
        ss = stringstream(line);
        getline(ss, token, ' ');
        warehouses[i].r = atoi(token.c_str());
        getline(ss, token, ' ');
        warehouses[i].c = atoi(token.c_str());

        warehouses[i].product_quantities = vector<int>(n_products);
        getline(file, line);
        ss = stringstream(line);
        for (int j = 0; j < n_products; j++) {
            getline(ss, token, ' ');
            warehouses[i].product_quantities[j] = atoi(token.c_str());
        }
    }

    getline(file, line);
    n_orders = atoi(line.c_str());
    orders = vector<Order>(n_orders);

    for (int i = 0; i < n_orders; i++) {
        getline(file, line);
        ss = stringstream(line);
        getline(ss, token, ' ');
        orders[i].r = atoi(token.c_str());
        getline(ss, token, ' ');
        orders[i].c = atoi(token.c_str());

        getline(file, line);
        int product_number = atoi(line.c_str());
        getline(file, line);
        ss = stringstream(line);
        orders[i].product_quantities = vector<int>(n_products);
        for (int j = 0; j < product_number; j++) {
            getline(ss, token, ' ');
            orders[i].product_quantities[atoi(token.c_str())]++;
        }
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
