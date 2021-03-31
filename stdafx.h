#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <cstring>
#include <cstdio>
#include "Log.h"
#include <iostream>
// #include <algorithm>

using std::string;
using std::cout;
using std::to_string;
using std::thread;
using std::mutex;
using std::vector;
// using std::fill;