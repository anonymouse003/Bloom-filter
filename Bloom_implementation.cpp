
#include "Bloom_filter.h"
#include <functional>

// Constructor 
BloomFilter::BloomFilter(size_t size, int num_hashes)
    : size(size), num_hashes(num_hashes), bit_array(size, false) {}

// hash function
size_t BloomFilter::hash_i(const std::string &item, int i) const {
    std::hash<std::string> hash_fn;
    return (hash_fn(std::to_string(i) + item)) % size;
}

// Inserting item 
void BloomFilter::insert(const std::string &item) {
    for (int i = 0; i < num_hashes; ++i) {
        bit_array[hash_i(item, i)] = true;
    }
}

// Check 
bool BloomFilter::possiblyContains(const std::string &item) const {
    for (int i = 0; i < num_hashes; ++i) {
        if (!bit_array[hash_i(item, i)]) return false; // Definitely not in set
    }
    return true; // Possibly in set (may be false positive)
}
