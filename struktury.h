#pragma once

#include "stdafx.h"

class vec2 {
public:
    vec2() {}
    
    vec2(float x, float y) {
        this->x = x;
        this->y = y;
    }

    float x;
    float y;
};

class vec3 {
public:
    vec3() {}

    vec3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float x;
    float y;
    float z;
};

class PlayerReport {
public:
    struct vec2 position;
    struct vec2 movingDirection;
    struct vec3 shootingDirection;

    PlayerReport() {};

    PlayerReport(vec2 position, vec2 movingDirection, vec3 shootingDirection) {
        this->position = position;
        this->movingDirection = movingDirection;
        this->shootingDirection = shootingDirection;
    }

    void print() {
        cout << to_string(position.x) << " " << to_string(position.y) << "\n" <<
            to_string(movingDirection.x) << " " << to_string(movingDirection.y) << "\n" <<
            to_string(shootingDirection.x) << " " << to_string(shootingDirection.y) << " " <<
            to_string(shootingDirection.z) << "\n\n";
    }
};

class PlayerState {
public:
    struct vec2 position;
    struct vec2 movingDirection;
    bool isShooting;

    void print() {
        cout << to_string(position.x) << " " << to_string(position.y) << "\n" <<
            to_string(movingDirection.x) << " " << to_string(movingDirection.y) << "\n" <<
            to_string(isShooting) << "\n\n";
    }
};

