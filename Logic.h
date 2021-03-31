#include "stdafx.h"
#include "Utils.h"
#include "myGeometry.h"

class Logic {
    private:
        static double dot(vec2 a, vec2 b) {
            return a.x * b.x + a.y * b.y;
        }
        static bool playerHurtsPlayer(Player& shooter, Player& victim) {
            if(shooter.aimingDirection.x == 0 && shooter.aimingDirection.z == 0) return false;

            //if(dot(vec2(shooter.position.x -victim.position.x, shooter.position.y - victim.position.y), vec2(shooter.aimingDirection.x, shooter.aimingDirection.z)) <= 0) return false;

            float distance = perpendicularDistance(shooter.position, vec2(shooter.aimingDirection.x, shooter.aimingDirection.z), victim.position); 
            return distance < 2.0;
        }
    public:
        static void handleShots(Player* players, int size) {
            for(int i = 0; i<size; i++) {
                players[i].isHurt = false;
            }

            for(int i = 0; i<size; i++) {

                if(players[i].isShooting) {
                    for(int k = 0; k<size; k++) {
                        if(i != k && playerHurtsPlayer(players[i], players[k])) {
                            players[k].isHurt = true;
                            Log::print("HURT");
                        }
                    }
                }
            }
        }
    private:
};