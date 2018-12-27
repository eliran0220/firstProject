#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>
#include <algorithm>
#include <string>
#include <vector>
#include <mutex>
#include <queue>
#include "StoreVarValue.h"


#define INDICATE_SPEED "/instrumentation/airspeed-indicator/indicated-speed-kt"
#define INDICATE_ALT "/instrumentation/altimeter/indicated-altitude-ft"
#define PRESSURE_ALT "/instrumentation/altimeter/pressure-alt-ft"
#define PITCH_DEG "/instrumentation/attitude-indicator/indicated-pitch-deg"
#define ROLL_DEG "/instrumentation/attitude-indicator/indicated-roll-deg"
#define IN_PITCH_DEG "/instrumentation/attitude-indicator/internal-pitch-deg"
#define IN_ROLL_DEG "/instrumentation/attitude-indicator/internal-roll-deg"
#define ENC_INDICATE_ALT "/instrumentation/encoder/indicated-altitude-ft"
#define ENC_PRESURE_ALT "/instrumentation/encoder/pressure-alt-ft"
#define GPS_ALT "/instrumentation/gps/indicated-altitude-ft"
#define GPS_GRND_SPD "/instrumentation/gps/indicated-ground-speed-kt"
#define GPS_VERTICAL_SPD "/instrumentation/gps/indicated-vertical-speed"
#define HEAD_DEG "/instrumentation/heading-indicator/indicated-heading-deg"
#define CMPS_HEAD_DEG "/instrumentation/magnetic-compass/indicated-heading-deg"
#define SLIP_SKID "/instrumentation/slip-skid-ball/indicated-slip-skid"
#define TURN_RATE "/instrumentation/turn-indicator/indicated-turn-rate"
#define SPEED_FPM "/instrumentation/vertical-speed-indicator/indicated-speed-fpm"
#define AILERON "/controls/flight/aileron"
#define ELEVATOR "/controls/flight/elevator"
#define RUDDER "/controls/flight/rudder"
#define FLAPS "/controls/flight/flaps"
#define THROTTLE "/controls/engines/current-engine/throttle"
#define RPM "/engines/engine/rpm"

using namespace std;

#define ONE 1

using namespace std;

class SymbolTable {
private:
    map<string, vector<string>> bindValue;
    map<string, StoreVarValue<double> *> valueTable;
    map<string, StoreVarValue<string> *> destTable;
    mutex mtx;
    queue<map<string, double>> needToUpdate;

public:
    SymbolTable();

    ~SymbolTable();

    void addToTable(string name);

    void updateSymbolTableValue(string name, double value);

    void updateSymbolTableDest(string name, string value);

    double getSymbolTableValue(string name);

    string getSymbolTableDest(string name);

    void varsToUpdate(string name, double value);

    bool existsInBindValueMap(string var);

    bool existsInValueTableMap(string var);

    vector<string>* getVariablesForUpdate(string &key);

    queue<map<string, double>>* getQueueToUpdate();
};


#endif
