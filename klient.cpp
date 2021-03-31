#include "stdafx.h"
#include "struktury.h"
#include "Network.h"
#include "Player.h"

int main(int argc, char** args) {
    Network::init();

    RemotePC host("127.0.0.1", 1500);
    Network::connect(host);


    int size = 1000;

    RawPlayer* array = Network::receiveArray<RawPlayer>(host, size * sizeof(RawPlayer));

    for(int i=0; i<size; i++) {
        Log::print(to_string(array[i].id));
    }
    
    // vector<int> v = Network::receiveArray<int>(host, 5);
    // Log::print("KLIENT: " + to_string(v[0]));
    
    Network::cleanUp();

    return 0;
}
