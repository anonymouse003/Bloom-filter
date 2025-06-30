#include <iostream>
#include <fstream>
#include <algorithm>       
#include "Bloom_filter.h"
#include "db.h"

/*
 It checks if a key exists in the database using the Bloom Filter first.
 If Bloom Filter says "no", we skip querying the DB.
 If Bloom Filter says "yes", we query DB to confirm (may be a false positive).
*/

int main() {
    BloomFilter bloom(10000, 7);    // Bloom Filter with 10,000 bits and 7 hash functions
    SimulatedDB db;                 

    // Insert sample 
    db.insert("user123", "rahul");
    db.insert("admin456", "sumit");
    db.insert("guest789", "deepak");
    db.insert("user323", "raman");
    db.insert("admin444", "lakshita");
    db.insert("guest788", "muskan");

    // Add same keys to Bloom Filter
    bloom.insert("user123");
    bloom.insert("admin456");
    bloom.insert("guest789");
    bloom.insert("user323");
    bloom.insert("admin444");
    bloom.insert("guest788");

    // Setup logging file to record results
    std::ofstream log("query_log.csv");
    if (!log.is_open()) {
        std::cerr << "Error: Could not open query_log.csv for writing\n";
        return 1;
    }
    log << "Query,InBloom,InDB,Result\n";

    int totalQueries = 0, dbHits = 0, optimizedSkips = 0, falsePositives = 0;
    std::string query;

    std::cout << "Enter key to search (type 'exit' to quit):\n";
    while (true) {
        std::getline(std::cin, query);

        // Removing whitespace from query 
        query.erase(std::remove_if(query.begin(), query.end(), ::isspace), query.end());

        if (query == "exit") break;

        ++totalQueries;
        bool inBloom = bloom.possiblyContains(query);
        bool inDB = db.contains(query);

        if (!inBloom) {
            ++optimizedSkips;
            std::cout << "[Optimized] Key definitely not in DB.\n";
            log << query << ",0,0,Optimized Skip\n";
            log.flush();
        } else {
            if (inDB) {
                ++dbHits;
                std::cout << "[DB Lookup] Found: " << db.get(query) << "\n";
                log << query << ",1,1,DB Hit\n";
                log.flush();
            } else {
                ++falsePositives;
                std::cout << "[False Positive] Key not in DB.\n";
                log << query << ",1,0,False Positive\n";
                log.flush();
            }
        }
    }

    log.close();

    std::cout << "\n--- Statistics ---\n";
    std::cout << "Total Queries: " << totalQueries << "\n";
    std::cout << "Optimized Skips: " << optimizedSkips << "\n";
    std::cout << "DB Hits: " << dbHits << "\n";
    std::cout << "False Positives: " << falsePositives << "\n";

    return 0;
}
