#pragma once

#include <type_traits>
#include <iostream>
#include <limits>
#include <algorithm>

namespace data_structure {
    // template<typename T>
    // typename std::enable_if<std::is_arithmetic<T>::value, T>::type initialize_ans(T& ans) {
    //     ans = 0;
    // }

    // template<typename T>
    // typename std::enable_if<!std::is_arithmetic<T>::value, void>::type initialize_ans(T& ans) {
    //     ans.reset();
    // }

    template<typename T>
    struct Group {
        T val;
        Group(const T &val): val(val) {}
        void operator = (const T &_val) { val = _val; }
    };

    template<typename T> 
    struct SumGroup: public Group<T> {
        SumGroup() : Group<T>(0) {}
        SumGroup(const T &val): Group<T>(val) {}
        void reset() { this->val = 0; }
        void operator += (const SumGroup<T> &other) {
            this->val += other.val;
        }
    };

    template<typename T>
    struct MinGroup: public Group<T> {
        MinGroup() : Group<T>(std::numeric_limits<T>::max()) {}
        MinGroup(const T &val): Group<T>(val) {}
        void reset() { this->val = std::numeric_limits<T>::max(); }
        void operator += (const MinGroup<T> &other) {
            this->val = std::min(this->val, other.val);
        }
    };

    template<typename T>
    struct MaxGroup: public Group<T> {
        MaxGroup() : Group<T>(std::numeric_limits<T>::min()) {}
        MaxGroup(const T &val): Group<T>(val) {}
        void reset() { this->val = std::numeric_limits<T>::min(); }
        void operator += (const MaxGroup<T> &other) {
            this->val = std::max(this->val, other.val);
        }
    };

    template<typename T, typename Compare = std::less<T>>
    struct SortGroup: public Group<std::vector<T>> {
        static std::vector<T> buffer;

        SortGroup() : Group<std::vector<T>>({}) {}
        SortGroup(const std::vector<T> &val): Group<std::vector<T>>(val) {
            std::sort(this->val.begin(), this->val.end(), Compare()); // is it bad for time complexity?
        }
        void reset() { this->val.clear(); }
        void operator += (const SortGroup<T> &other) {
            int N = this->val.size() + other.val.size();
            if(buffer.size() < N)
                buffer.resize(N);
            std::merge(this->val.begin(), this->val.end(), other.val.begin(), other.val.end(), buffer.begin());
            this->val.resize(N);
            std::move(this->buffer.begin(), this->buffer.begin() + N, this->val.begin()); 
        }
    };
    template<typename T, typename Compare>
    std::vector<T> SortGroup<T, Compare>::buffer;


    template<typename T>
    inline void sum_aggregate(SumGroup<T> &data, SumGroup<T> &applier, int count) {
        data += SumGroup<T>{applier.val * count};
    }    
    template<typename T>
    inline void set_aggregate(SumGroup<T> &data, SumGroup<T> &applier, int count) {
        data = SumGroup<T>{applier.val * count};
    }

    template<typename T>
    inline void sum_aggregate(MinGroup<T> &data, MinGroup<T> &applier, int count) {
        data += applier;
    }
    template<typename T>
    inline void set_aggregate(MinGroup<T> &data, MinGroup<T> &applier, int count) {
        data = applier;
    }

    template<typename T>
    inline void sum_aggregate(MaxGroup<T> &data, MaxGroup<T> &applier, int count) {
        data += applier;
    }
    template<typename T>
    inline void set_aggregate(MaxGroup<T> &data, MaxGroup<T> &applier, int count) {
        data = applier;
    }
}
