#include <bits/stdc++.h>

using namespace std;

struct PrettyBinary {
    unsigned x;
    int count;
    PrettyBinary(unsigned x, int count=32): x(x), count(count) {}
};

ostream& operator << (ostream& out, const PrettyBinary &b) {
    for(int i = 0; i < b.count; i++)
        out << ((b.x >> i) & 1);
    return out;
}


template <size_t N>
struct simple_bitset {
    uint32_t data[(N>>5)+2], n; // the end should alwaye be 0,  at least + 2 because of equal_range function

    simple_bitset() {
        memset(data, 0, sizeof data);
    }

    void set(unsigned pos, bool val) {
        if(val)
            data[pos>>5] |= 1<<(pos&31);
        else
            data[pos>>5] &= ~(1<<(pos&31));
    }
    bool get(unsigned pos) const {
        return data[pos>>5] & (1<<(pos & 31));
    }
    int find_first() const {
        unsigned pt = 0;
        while((pt << 5) < N) {
            if(data[pt])
                return (pt<<5) + __builtin_ctz(data[pt]);
            pt++;
        }
        return N;
    }
    int find_next(int pos) const {
        unsigned pt = pos>>5, r = pos & 31;
        unsigned x = data[pt]>>(r+1);
        if(x)
            return (pt<<5) + __builtin_ctz(x) + r+1;
        pt++;
        while((pt << 5) < N) {
            if(data[pt])
                return (pt<<5) + __builtin_ctz(data[pt]);
            pt++;
        }
        return N;
    }
    size_t size() {
        return N;
    }

    template<size_t M>
    bool equal_range(simple_bitset<M> &other, int start) const {
        if(start + M > N)
            return false;
        const int r = start&31;
        for(unsigned pos_me = start, index_me = start>>5, index_other = 0, pos_other = 0; pos_other < M; pos_me += 32, pos_other += 32, index_me++, index_other++) {
            uint32_t me;
            if(r == 0)
                me = data[index_me];
            else 
                me = (data[index_me] >> r) | (data[index_me+1] << (32-r));
            if(me != other.data[index_other]) {
                int rest = min((size_t)32, M-pos_other);
                if(rest == 32)
                    return false;
                int mask = (1<<rest)-1;
                return ((me & mask) == (other.data[index_other] & mask));
            }
        }
        return true;
    }
};

template <size_t N>
ostream& operator << (ostream& out, const simple_bitset<N> &bs) {
    for(unsigned i = 0; i < N; i++)
        out << bs.get(i);
    return out;
}


int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    simple_bitset<30> big;
    simple_bitset<3> small;
    big.set(3, true);
    big.set(5, true);
    small.set(0, true);
    small.set(2, true);

    cout << "small: "<< small << endl;
    cout << "big: " << big << endl;
    cout << "Check if matches: " << endl;
    for(int i = 0; i < 30; i++) {
        cout << big.equal_range(small, i);
    }
    cout << endl;
}