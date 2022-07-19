///// @Jollu
// Least Recently Used

#include <list>
#include <array>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

template<typename Key, typename Value>
class LRUCache {
    typedef typename std::pair<Key, Value> KeyValuePair;
    typedef typename std::list<KeyValuePair>::iterator ListIterator;
public:
    explicit LRUCache(std::size_t maxSize) : maxSize_(maxSize) {}

    void put(const Key &key, const Value &value) noexcept;

    const Value &get(const Key &key);

    bool tryGet(const Key &key, const Value &value) noexcept;

    bool exists(const Key &key) const noexcept;

    std::size_t size() const noexcept;

private:
    const std::size_t maxSize_;
    std::list<KeyValuePair> elements_;
    std::unordered_map<Key, ListIterator> searchTable_;
};

template<typename KeyType, typename ValueType>
void LRUCache<KeyType, ValueType>::put(const KeyType &key, const ValueType &value) noexcept {
    auto iterator = searchTable_.find(key);
    if (iterator == searchTable_.end()) {
        if (elements_.size() == maxSize_) {
            KeyValuePair tpmElement = elements_.back();
            elements_.pop_back();
            searchTable_.erase(tpmElement.first);
        }
    } else {
        elements_.erase(searchTable_[key]);
    }

    elements_.push_front(KeyValuePair(key, value));
    searchTable_[key] = elements_.begin();
}

template<typename KeyType, typename ValueType>
const ValueType &LRUCache<KeyType, ValueType>::get(const KeyType &key) {
    auto iterator = searchTable_.find(key);
    if (iterator == searchTable_.end())
        throw std::invalid_argument("Cache does not contain element with current key.");

    elements_.splice(elements_.begin(), elements_, iterator->second);
    return iterator->second->second;
}

template<typename Key, typename Value>
bool LRUCache<Key, Value>::tryGet(const Key &key, const Value &value) noexcept {
    auto iterator = searchTable_.find(key);
    if (iterator == searchTable_.end())
        return false;

    elements_.splice(elements_.begin(), elements_, iterator->second);
    value = iterator->second->second;
    return true;
}

template<typename Key, typename Value>
bool LRUCache<Key, Value>::exists(const Key &key) const noexcept {
    return searchTable_.find(key) != searchTable_.end();
}

template<typename Key, typename Value>
std::size_t LRUCache<Key, Value>::size() const noexcept {
    return elements_.size();
}

int main() {
    std::uint8_t cacheSize = 6;
    std::array<int, 10> testKeys = {10,12,13,1,4,17,18,4,3,5};
    LRUCache<int, std::string> cache(cacheSize);
    for (auto key: testKeys) {
        if (cache.exists(key)) {
            const std::string &element = cache.get(key);
            std::cout << "Element with key: " << key << " was got from the cache" << std::endl;
        } else {
            cache.put(key, "Some data");
            std::cout << "Element with key: " << key << " is absent in the cache." << std::endl;
        }
    }


}