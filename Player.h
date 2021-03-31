#pragma once

#include "stdafx.h"
#include "Network.h"
#include "struktury.h"


class RawPlayer {
    public:
        int id = 0;
        vec2 position = vec2(0,0);
        vec3 aimingDirection = vec3(0,0,0);
        bool isShooting = false;
        bool isHurt = false;
	    int hp = 100;
    public:
        RawPlayer() {}
        RawPlayer(int id, vec2 position, vec3 aimingDirection, bool isShooting) {
            this->id = id;
            this->position = position;
            this->aimingDirection = aimingDirection;
            this->isShooting = isShooting;
        }
    private:
};

class Player : public RemotePC, public RawPlayer {
    public:
    public:
        Player() {}
        Player(RawPlayer rawPlayer) : RawPlayer(rawPlayer) {}
        Player(RemotePC remotePC) : RemotePC(remotePC), RawPlayer() {}
        Player(RemotePC remotePC, RawPlayer rawPlayer) : RemotePC(remotePC), RawPlayer(rawPlayer) {}
    private:
};