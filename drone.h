//
// Created by antoinewdg on 2/11/16.
//

#ifndef HASH_CODE_DRONE_H
#define HASH_CODE_DRONE_H

struct Drone {
    int id;
    int r, c;
    bool available;

    Drone() : available(true) { }
};

#endif //HASH_CODE_DRONE_H
