#include <pthread.h>
#include "signalmgr.hpp"

SignalManager::SignalManager() {
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGTERM);
    pthread_sigmask(SIG_BLOCK, &sigset, NULL);
}

int SignalManager::wait(int* sig) {
    return sigwait(&sigset, sig);
}
