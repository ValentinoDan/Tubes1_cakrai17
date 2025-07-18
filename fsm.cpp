#include "fsm.hpp"

using namespace std;

uint32_t millis(){ 
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

FSM::FSM(){
    currentState = SystemState::INIT; // Membuat currentState menjadi INIT
    lastHeartbeat = 0; // Membuat lastHearbeat dan errorCount menjadi 0
    errorCount = 0;
    stateHistory.clear(); // Inisialisasi vector stateHistory ( bisa juga dengan stateHistory = {} )
}

FSM::FSM(uint32_t delay){
    currentState = SystemState::INIT;
    lastHeartbeat = 0;
    errorCount = 0;
    this->delay = delay; // Inisialisasi delay dengan delay pada parameter fungsi (this-> digunakan untuk membedakan dengan parameter)
    stateHistory.clear();
}

FSM::~FSM(){
    stateHistory.clear(); // Destructor
}

SystemState FSM::getCurrentState() const {
    return currentState; // Mengembalikkan current state
}

void FSM::transitionToState(SystemState newState) {
    currentState = newState;
    lastHeartbeat = millis();
}

void FSM::setDelay(uint32_t delay){
    this->delay = delay;
}

void FSM::getDelay(uint32_t &delay) const {
    delay = this->delay;
}

void FSM::setErrorCount(int count){
    errorCount = count;
}

int FSM::getErrorCount() const {
    return errorCount;
}

void FSM::setMoveCount(int count) {
    moveCount = count;
}

int FSM::getMoveCount() const {
    return moveCount;
}

void FSM::addStateToHistory(SystemState state, uint32_t time){
    stateHistory.emplace_back(state, time); // Menambahkan pasangan state dan waktu 
}

vector<pair<SystemState, uint32_t>> FSM::getStateHistory() const{
    return stateHistory;
}

uint32_t FSM::getLastHeartbeat() const{
    return lastHeartbeat;
}

void FSM::setLastHeartbeat(uint32_t heartbeat){
    lastHeartbeat = heartbeat;
}

void FSM::start() {
    while (true) {
        update();
        if(currentState == SystemState::STOPPED){
            break;
        }
        auto start_time = chrono::system_clock::now();
        while (chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start_time).count() < 1000) {
            // menunggu 1 detik
        }
    }
    shutdown(); // Fungsi dipanggil ketika SystemState berhenti (STOPPED)
}

void FSM::update() {
    switch (currentState) {
        case SystemState::INIT : performInit(); break;
        case SystemState::IDLE : performProcess(); break;
        case SystemState::MOVEMENT : performMovement(); break;
        case SystemState::SHOOTING : performShooting(); break;
        case SystemState::CALCULATION : performCalculation(); break;
        case SystemState::ERROR : performErrorHandling(); break;
        case SystemState::STOPPED : shutdown(); break;
    }
    lastHeartbeat = millis();
    addStateToHistory(currentState, millis());
}

void FSM::printStatus(){
    cout << "\nCurrent State : ";
    switch (currentState) {
        case SystemState::INIT : cout << "INIT"; break;
        case SystemState::IDLE : cout << "IDLE"; break;
        case SystemState::MOVEMENT : cout << "MOVEMENT"; break;
        case SystemState::SHOOTING : cout << "SHOOTING"; break;
        case SystemState::CALCULATION : cout << "CALCULATION"; break;
        case SystemState::ERROR : cout << "ERROR"; break;
        case SystemState::STOPPED : cout << "STOPPED"; break;
    }
    cout << endl;
    cout << "Last Heartbeat Time : " << lastHeartbeat << endl;
    cout << "Delay : " << delay << endl;
    cout << "Error Count : " << errorCount << endl;
}

void FSM::printStateHistory() {
    cout << "\n==== State History ====" << endl;
    for (const auto& entry : stateHistory) { // Melakukan iterasi semua elemen yang ada dalam stateHistory
        cout << "State: ";
        switch (entry.first) {
            case SystemState::INIT: cout << "INIT"; break;
            case SystemState::IDLE: cout << "IDLE"; break;
            case SystemState::MOVEMENT: cout << "MOVEMENT"; break;
            case SystemState::SHOOTING: cout << "SHOOTING"; break;
            case SystemState::CALCULATION: cout << "CALCULATION"; break;
            case SystemState::ERROR: cout << "ERROR"; break;
            case SystemState::STOPPED: cout << "STOPPED"; break;
        }
        cout << " at " << entry.second << " ms" << endl;
    }
}

void FSM::performInit(){
    setDelay(1000);
    transitionToState(SystemState::IDLE); // sama saja dengan mengubah ke state ke IDLE dan lastHeartbeat = millis()
    cout << "Initializing system...\n";
    printStatus(); 
}

void FSM::performProcess(){
    int count;
    cout << "\n==== Please choose 1 of the process below ====\n";
    cout << "1. IDLE\n";
    cout << "2. MOVEMENT\n";
    cout << "3. SHOOTING\n";
    cout << "4. CALCULATION\n";
    cout << "Please insert your choice : ";
    cin >> count;
    switch (count) {
    case 1: printStatus();
            printStateHistory();
            break;
    case 2: currentState = SystemState::MOVEMENT; // Hanya mengubah current state (tidak menggunakan transition)
            break;
    case 3: currentState = SystemState::SHOOTING;
            break;
    case 4: currentState = SystemState::CALCULATION;
            break;
    }
}

void FSM::performMovement(){
    cout << "Moving...\n";
    moveCount += 1;
    if(moveCount >= 3){
        transitionToState(SystemState::SHOOTING); 
    } else {
        transitionToState(SystemState::IDLE); // lastHeatbeat = millis() sudah ada di transitionToState
    } 
}

void FSM::performShooting(){
    cout << "Shooting...\n";
    moveCount = 0;
    transitionToState(SystemState::IDLE);
}

void FSM::performCalculation(){
    cout << "Performing calculation...\n";
    if(moveCount == 0){
        transitionToState(SystemState::ERROR);
    } else {
        transitionToState(SystemState::IDLE);
    }
}

void FSM::performErrorHandling(){
    cout << "Error occurred, performing error handling...\n";
    errorCount += 1;
    if(errorCount > 3){
        transitionToState(SystemState::STOPPED);
    } else {
        transitionToState(SystemState::IDLE);
    }
}

void FSM::shutdown(){
    cout << "System stopped, shutting down...\n";
    stateHistory.clear();
}