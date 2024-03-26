#pragma once

namespace data_structure {

    template<typename ValueType>
    class Interval {
        std::vector<ValueType> data;
        int n;

    public:
        Interval(int _n): n(_n), data(_n) {}

        inline void add(int pos, ValueType val) {
            data[pos]+= val;
        }
        inline void add(int f, int s, ValueType val) {
            while(f < s)
                data[f++]+= val;
        }
        inline void set(int pos, ValueType val) {
            data[pos] = val;
        }
        inline void set(int f, int s, ValueType val) {
            while(f < s)
                data[f++] = val;
        }
        inline ValueType ask(int f, int s) {
            ValueType res; // should be zero by default
            while(f < s)
                res += data[f++];
            return res;
        }        

        void print() {
            cout << data << endl;            
        }
    };
}