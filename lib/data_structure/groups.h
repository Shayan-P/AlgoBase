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
        SumGroup<T>& operator += (const SumGroup<T> &other) {
            this->val += other.val;
            return *this;
        }
    };

    template<typename T>
    struct MinGroup: public Group<T> {
        MinGroup() : Group<T>(std::numeric_limits<T>::max()) {}
        MinGroup(const T &val): Group<T>(val) {}
        void reset() { this->val = std::numeric_limits<T>::max(); }
        MinGroup<T>& operator += (const MinGroup<T> &other) {
            this->val = std::min(this->val, other.val);
            return *this;
        }
        MinGroup<T>& operator += (const SumGroup<T> &other) {
            this->val += other.val;
            return *this;
        }
    };

    template<typename T>
    struct MaxGroup: public Group<T> {
        MaxGroup() : Group<T>(std::numeric_limits<T>::min()) {}
        MaxGroup(const T &val): Group<T>(val) {}
        void reset() { this->val = std::numeric_limits<T>::min(); }
        MaxGroup<T>& operator += (const MaxGroup<T> &other) {
            this->val = std::max(this->val, other.val);
            return *this;
        }
        MaxGroup<T>& operator += (const SumGroup<T> &other) {
            this->val += other.val;
            return *this;
        }
    };

    // this adds set modifier to the group
    template<typename T, template<typename> class G>
    struct WithSet: public Group<std::pair<G<T>, std::optional<T>>> {
        using GroupParams = std::pair<G<T>, std::optional<T>>;

        WithSet(const G<T> &g, std::optional<T> opt) : Group<GroupParams>({g, opt}) {}
        WithSet(const G<T> &g) : WithSet(g, {}) {}
        WithSet(std::optional<T> opt) : WithSet(G<T>(), opt) {}
        WithSet() : WithSet(G<T>(), {}) {}

        static WithSet<T, G> fromOpp(const G<T>& g) {
            return WithSet<T, G>(g, {});
        }
        static WithSet<T, G> fromSet(const T &val) {
            return WithSet<T, G>(G<T>(), {val});
        }

        inline const G<T>& mutator() const { return this->val.first; }
        inline const std::optional<T>& to_set() const { return this->val.second; }

        void reset() { this->val.first.reset(), this->val.second = {}; }

        WithSet<T, G>& operator += (const WithSet<T, G> &other) {
            if(other.to_set().has_value())
                return *this = other;            
            this->val.first += other.mutator();
            return *this;
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
        SortGroup<T>& operator += (const SortGroup<T> &other) {
            int N = this->val.size() + other.val.size();
            if(buffer.size() < N)
                buffer.resize(N);
            std::merge(this->val.begin(), this->val.end(), other.val.begin(), other.val.end(), buffer.begin());
            this->val.resize(N);
            std::move(this->buffer.begin(), this->buffer.begin() + N, this->val.begin()); 
            return *this;
        }
    };
    template<typename T, typename Compare>
    std::vector<T> SortGroup<T, Compare>::buffer;


    // sum_aggregate : what is the aggregation of data after applying applier to all elements
    template<typename T>
    inline void sum_aggregate(SumGroup<T> &data, const SumGroup<T> &applier, int count) {
        data += SumGroup<T>{applier.val * count};
    }    
    template<typename T>
    inline void set_aggregate(SumGroup<T> &data, const SumGroup<T> &applier, int count) {
        data = SumGroup<T>{applier.val * count};
    }

    template<typename T>
    inline void sum_aggregate(MinGroup<T> &data, const MinGroup<T> &applier, int count) {
        data += applier;
    }
    template<typename T>
    inline void set_aggregate(MinGroup<T> &data, const MinGroup<T> &applier, int count) {
        data = applier;
    }

    template<typename T>
    inline void sum_aggregate(MaxGroup<T> &data, const MaxGroup<T> &applier, int count) {
        data += applier;
    }
    template<typename T>
    inline void set_aggregate(MaxGroup<T> &data, const MaxGroup<T> &applier, int count) {
        data = applier;
    }

    template<typename T>
    void sum_aggregate(MinGroup<T> &mg, const SumGroup<T> &sg, [[gnu::unused]] int cnt) {
        mg.val += sg.val;
    }

    template<typename T>
    void sum_aggregate(MaxGroup<T> &mg, const SumGroup<T> &sg, [[gnu::unused]] int cnt) {
        mg.val += sg.val;
    }

    template<typename T, template<typename> class G_data, template<typename> class G_applier>
    inline void sum_aggregate(G_data<T> &data, const WithSet<T, G_applier> &applier, int count) {
        if(applier.to_set().has_value())
            set_aggregate(data, G_data<T>(applier.to_set().value()), count);        
        sum_aggregate(data, applier.mutator(), count);
    }

    template<typename T, template<typename> class G_data, template<typename> class G_applier>
    inline G_data<T> operator += (G_data<T> &data, const WithSet<T, G_applier> &applier) {
        if(applier.to_set().has_value())
            data = G_data{applier.to_set().value()};       
        return data += applier.mutator();
    }

    // // Check if T is derived from Group
    // template<typename T>
    // struct IsDerivedFromGroup {
    // private:
    //     template<typename U>
    //     static std::true_type test(const Group<U>*);
    //     static std::false_type test(...);
    // public:
    //     static constexpr bool value = decltype(test(std::declval<T*>()))::value;
    // };

    // template<typename T, template<typename> class G>
    // auto operator+(const G<T>& lhs, const G<T>& rhs)
    //     ->  std::enable_if_t<
    //             IsDerivedFromGroup<G<T>>::value,
    //             decltype(std::declval<G<T>>() += std::declval<G<T>>())
    //     >
    // {
    //     G<T> result = lhs;
    //     return result += rhs;
    // }
}
