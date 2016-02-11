//
// Created by antoinewdg on 2/11/16.
//

#ifndef HASH_CODE_WAREHOUSE_H
#define HASH_CODE_WAREHOUSE_H

#include <vector>

using namespace std;

struct Warehouse {
    int r, c;
    int id;

    vector<int> product_quantities;
};

#endif //HASH_CODE_WAREHOUSE_H
