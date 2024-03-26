#pragma once

namespace data_structure {
    template<typename T>
    class FenwickTree {
        std::vector<T> data;
        int n;

    public:
        FenwickTree(int _n): data(_n+1), n(_n) {}

        void add(int pos, T val) {
            for(pos+= 1; pos <= n; pos+= (pos & -pos)) {
                auto tmp = val;
                tmp += data[pos];
                data[pos] = tmp; // in order for this to handle Non Abelian Groups
            }
        }

        T ask(int pos) {
            T ans;
            if(std::is_arithmetic<T>::value) ans = 0;
            for(pos+= 1; pos > 0; pos-= (pos & -pos))
                ans += data[pos];
            return ans;
        }

        void reset(int _n) {
            n = _n;
            if(data.size() < n+1)
                data.resize(n+1);
            T emp;
            if(std::is_arithmetic<T>::value) emp = emp;            
            fill(data.begin(), data.begin()+n+1, emp);
        }
    };
}