
#include "db.h"

// Constructor: nothing needed for std::unordered_map
SimulatedDB::SimulatedDB() {}

// Insert a key-value pair
void SimulatedDB::insert(const std::string &key, const std::string &value) {
    db[key] = value;
}

// Checking if a key exists or not
bool SimulatedDB::contains(const std::string &key) const {
    return db.find(key) != db.end();
}

// Retrieving a value by key
std::string SimulatedDB::get(const std::string &key) const {
    auto it = db.find(key);
    return (it != db.end()) ? it->second : "";
}
