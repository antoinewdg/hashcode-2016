//
// Created by antoinewdg on 2/11/16.
//

#include <list>
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


vector<vector<Drone::LoadCommand>> Simulation::locateObjects(Order o) {
    vector<vector<Drone::LoadCommand>> commands;
    vector<Warehouse> wares(warehouses);
    sort(wares.begin(), wares.end(), [&o](Warehouse w1, Warehouse w2) {
        double dist1 = pow((w1.r - o.r), 2) + pow(w1.c - o.c, 2);
        double dist2 = pow((w2.r - o.r), 2) + pow(w2.c - o.c, 2);

        return dist1 < dist2;
    });

    bool finished = false;
    while (!finished) {
        vector<Drone::LoadCommand> command;

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
                    Drone::LoadCommand lc;
                    takeInWarehouse(w, o, lc, i, numb, charge);
                    command.push_back(lc);
                }
            }
        }
        for (int i = 0; i < n_products; i++) {
            if (o.product_quantities[i] != 0) {
                finished = false;
                break;
            }
            else {
                finished = true;
            }
        }
        commands.push_back(command);
    }
    return commands;
}

void Simulation::processOrders() {
    vector<Order> toDo(orders);
    vector<vector<Drone::LoadCommand>> commands;

    for (Order o: toDo) {
        vector<vector<Drone::LoadCommand>> temp = locateObjects(o);
        for (vector<Drone::LoadCommand> c: temp) {
            commands.push_back(c);
        }
    }

    int c = 0;
    for (int t = 0; t < t_max; t++) {

        list<Drone *> availableDrones = available_drones();


        for (Drone *d: availableDrones) {
            d->give_instruction(commands[c], t);
            c++;
        }

//        for (vector<int> command: commands) {
//            Order o = orders[command[0]];
//
//            for (int w = 0; w < command.size() / 3; w++) {
//                Warehouse ware = warehouses[command[w * 3 + 1]];
//                Product p = products[command[w * 3 + 2]];
//                int number = command[w * 3 + 3];
//
//                int time = time_for_operation(o.r, o.c, ware.r, ware.c);
//
//
//
//
//            }
//        }

        update_drones();
    }

    ofstream file("files/out/test.out");

    for (Drone d : drones) {
        d.write_history(file);
    }

    file.close();

}

bool Simulation::droneAvailable() {
    for (Drone d : drones) {
        if (d.unavailable_for == 0) {
            return true;
        }
    }

    return false;
}


list<Drone *> Simulation::available_drones() {

    list<Drone *> available;


    for (Drone &d : drones) {
        if (d.unavailable_for == 0) {
            available.push_back(&d);
        }
    }
    return available;
}

void Simulation::update_drones() {
    for (Drone d : drones) {
        if (d.unavailable_for > 0) {
            d.unavailable_for--;
        }
    }
}

int Simulation::time_for_operation(int r1, int c1, int r2, int c2) {
    double temp = sqrt(pow(r1 - r2, 2) + pow(c1 - c2, 2));
    return floor(temp) + 2;
}
