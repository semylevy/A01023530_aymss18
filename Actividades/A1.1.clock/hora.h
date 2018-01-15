#ifndef HORA
#define HORA

#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class Clock {
private:
    static Clock* instance;
    Clock () {
        cout << "Constr\n";
    }
    ~Clock () { }
public:
    static Clock* getInstance() {
        if(instance == NULL) {
            instance = new Clock;
        }
        return instance;
    }
    static bool deleteInstance() {
        if(instance != NULL) {
            delete instance;
            return true;
        }
        return false;
    }
    string getTime() {
        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        return asctime(timeinfo);
    }
};

Clock* Clock::instance = NULL;

#endif
