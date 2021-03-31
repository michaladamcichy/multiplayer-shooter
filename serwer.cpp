#include "stdafx.h"
#include "struktury.h"
#include "Network.h"
#include "Player.h"
#include "Utils.h"
#include "Logic.h"

int main() {
    vector <Player*> players;
    mutex playersMutex;
    
    vector <thread> playerHandlers;
    mutex playerHandlersMutex;

    Network network(1500);
    Network network2(1600);

    thread listener([&network, &network2, &playerHandlers, &playerHandlersMutex, &players, &playersMutex]() -> void {
        while(true) {
            //usleep(10000);
            Log::print("Waiting for players...");
            RemotePC client = network.waitForClient();

            Player* player = new Player(client);
            //cout << "PLAYERMUTEX P\n";
            playersMutex.lock();
            players.push_back(player);
            player->id = players.size(); //ALERT
            playersMutex.unlock();

            network.send<int>(client, player->id);
    
            Log::print("New player!");
            cout << player->getIp() << ":" << player->getPort() << "\n";
            //cout << "PLAYERMUTEX V\n";

            //cout << "PLAYERHANDLERMUTEX P\n";
            //playerHandlersMutex.lock();
            // playerHandlers.push_back(thread(
            //     [player, &network2] () mutable {
            //         while(true) {
                        
            //             //usleep(10000);
            //         }
            //     }
            // ));
           //playerHandlersMutex.unlock();
            //cout << "PLAYERHANDLERMUTEX V\n";
        }
    });

    // int w = 0;
    // thread watchdog([&w]() mutable {
    //     while(true) {
    //         w++;
    //         sleep(2);
    //         cout<< w << '\n';
    //     }
    // });

    while(true) {
        //cout << "*\n";

        //cout << "PLAYERMUTEX P\n";
        playersMutex.lock();

        Player* playersArray = new Player[Config::maxPlayersCount];
        int arraySize = players.size();
        for(unsigned int i = 0; i < players.size(); i++) {
            playersArray[i] = *players[i];
            //Log::print(to_string(rawPlayers[i].id));
        }
        playersMutex.unlock();


        for(int i=0; i<arraySize; i++) {
            RemotePC client = (RemotePC) (playersArray[i]);
            Player updatedPlayer = network2.receive<Player>(client);
            
            playersArray[i].position = updatedPlayer.position;
            playersArray[i].aimingDirection = updatedPlayer.aimingDirection;
            playersArray[i].isShooting = updatedPlayer.isShooting;
        }

        Logic::handleShots(playersArray, arraySize);
    
        //Utils::printPlayersArray(playersArray, arraySize);
        for(int i=0; i<arraySize; i++) {
            RemotePC client = (RemotePC) playersArray[i];
            network.sendArray<Player>(client, playersArray, Config::maxPlayersCount);
        }
        //cout << "PLAYERHANDLERMUTEX V\n";

        delete[] playersArray;

    }

    listener.join();
    for(auto& playerHandler : playerHandlers) {
        playerHandler.join();
    }

    //watchdog.join();
    return 0;
}