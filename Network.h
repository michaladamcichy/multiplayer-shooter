#pragma once
#include "stdafx.h"
#include "Config.h"

class RemotePC {
    public:
        int socket;
        sockaddr_in addr;
    public:
        RemotePC() {}
        // RemotePC(string address, int port) {
        //     addr.sin_family = PF_INET;
        //     addr.sin_port = htons(port);
        //     addr.sin_addr.s_addr = inet_addr(address.c_str());
        // }

        RemotePC(int socket, sockaddr_in addr) {
            this->socket = socket;
            this->addr = addr;
        }

        string getIp() {
            return string(inet_ntoa(addr.sin_addr));
        }

        int getPort() {
            return addr.sin_port;
        }

    private:
};

class Network {
    public:
        int fd;
        sockaddr_in addr;
        socklen_t SOCKADDR_SIZE = sizeof(sockaddr);
        socklen_t SOCKADDR_IN_SIZE = sizeof(sockaddr_in);

    public:
        Network(int port = 0) {
            if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                Log::print("Cannot create socket!");
                //return false;
            } 
            memset(&addr, 0, SOCKADDR_IN_SIZE);
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = htonl(INADDR_ANY);
            addr.sin_port = htons(port);

            if(bind(fd, ( sockaddr*) &addr, SOCKADDR_SIZE) < 0) {
                Log::print(pair<string, int> ("Cannot bind socket to port", port));
                //return false;
            }

            int option  = 1;
            if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int)) < 0) {
                //Log::print("Cannot make the socket reusable"); //ALERT NIE DZIALA
            };

            if(listen(fd, Config::maxPlayersCount) < 0) {
                Log::print("Cannot set queue size");
            }
            //return true;
        }

        ~Network() {
            close(fd);
        }

        RemotePC waitForClient() {
            sockaddr_in addr;

            int clientSocket = accept(fd, (struct sockaddr*)&addr, &SOCKADDR_SIZE);

            if(clientSocket < 0) {
                Log::print("Cannot create connection");
            }

            return RemotePC(clientSocket, addr);
        }

        // bool connect(RemotePC& remotePC) {
        //     if(sendto(fd, nullptr, 0, 0, ( sockaddr*) &remotePC.addr, SOCKADDR_SIZE) < 0) {
        //        Log::print("Cannot connect"); 

        //        return false;
        //     }

        //     return true;
        // }

template<class T>
        void send(RemotePC& remotePC, T& data) {
            sendto(remotePC.socket, &data, sizeof(T), 0, ( sockaddr*) &remotePC.addr, SOCKADDR_SIZE);
        }

template<class T>
        T receive(RemotePC& remotePC) {
            T data;
            if(recv(remotePC.socket, &data, sizeof(T), 0) < 0) {
                Log::print("Cannot receive message");
                Log::print(to_string(errno));
            }

            return data;
        }

template<class T>
		void sendArray(RemotePC& remotePC, T* data, int size) {
			sendto(remotePC.socket, data, size * sizeof(T), 0, (sockaddr*)& remotePC.addr, SOCKADDR_SIZE);
		}

		template<class T>
		T* receiveArray(RemotePC& remotePC, int size) {
			T* data = new T[size];
			recvfrom(fd, data, size *sizeof(T), 0, (sockaddr*)& remotePC.addr, &SOCKADDR_SIZE);

			return data;
		}

    private:

};
