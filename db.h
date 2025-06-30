
#ifndef DB_H
#define DB_H

#include <unordered_map>
#include <string>


class SimulatedDB {
private:
    std::unordered_map<std::string, std::string> db; 

public:
    SimulatedDB();
    void insert(const std::string &key, const std::string &value); // Insert key-value pair
    bool contains(const std::string &key) const;                   // Check if key exists
    std::string get(const std::string &key) const;                 // Retrieving value by key
};

#endif
