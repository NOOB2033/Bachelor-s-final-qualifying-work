#ifndef BACHELOR_S_FINAL_QUALIFYING_WORK_UTILS_HPP
#define BACHELOR_S_FINAL_QUALIFYING_WORK_UTILS_HPP


#include "../dependencies/dependencies.hpp"


template <typename T>
class sorted_list {
public:

    bool operator==(const sorted_list<T>& other) const {
        return list == other.list;
    }

    bool operator<(const sorted_list<T>& other) const {
        return list < other.list;
    }

    void push(T value) {
        if (list.begin() == list.end()) {
            list.push_back(std::move(value));
            return;
        }
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (value <= *it) {
                list.insert(it, std::move(value));
                return;
            }
        }
        list.push_back(std::move(value));
    }

    bool find(T value) {
        for (auto&& n : list) {
            if (n == value) {
                return true;
            }
        }
        return false;
    }

    size_t size() const {
        return list.size();
    }

    typename std::list<T>::iterator begin() {
        return list.begin();
    }

    typename std::list<T>::iterator end() {
        return list.end();
    }

private:

    std::list<T> list;
};


#endif //BACHELOR_S_FINAL_QUALIFYING_WORK_UTILS_HPP
