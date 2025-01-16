#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

void runServer() {
    system("./server_select");
}

void runClients(int clientCount) {
    std::vector<std::thread> clientThreads;
    for (int i = 0; i < clientCount; ++i) {
        clientThreads.emplace_back([]() { system("./client_select"); });
    }

    for (auto &t : clientThreads) {
        t.join();
    }
}

int main() {
    std::thread serverThread(runServer);

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Give server time to start

    int clientCount = 5; // Number of clients
    runClients(clientCount);

    serverThread.join();

    return 0;
}
