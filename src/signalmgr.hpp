#include <signal.h>

/**
  * C++ modules must handle SIGINT and SIGTERM. Make sure to create a sigset
  * for SIGINT and SIGTERM that can be later awaited in a thread that cleanly
  * shuts down your module. pthread_sigmask should be called near the start of
  * main so that later threads inherit the mask.
  */
class SignalManager {
    public:
    SignalManager();
    /** wait on sigset */
    int wait(int* sig);
    sigset_t sigset;
};
