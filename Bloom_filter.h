
#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <vector>
#include <string>


class BloomFilter {
private:
    std::vector<bool> bit_array;  // Bit array 
    size_t size;                  // Size 
    int num_hashes;              // Number of hash functions

    // Hash function using a seed to simulate multiple hash functions
    size_t hash_i(const std::string &item, int i) const;

public:
    BloomFilter(size_t size, int num_hashes); // Constructor

    void insert(const std::string &item);     // Adding an item to the filter
    bool possiblyContains(const std::string &item) const; // Checking membership
};

#endif
