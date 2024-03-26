#include "AlgoBase/utils.h"
#include "AlgoBase/data_structure/fenwick.h"
#include "AlgoBase/data_structure/interval.h"
#include "AlgoBase/data_structure/groups.h"

template<typename T>
void test_for_group(int n, int q) {
    data_structure::FenwickTree<T> fen(n);
    data_structure::Interval<T, T> interval(n);

    while(q--) {
        int t = rand() % 2;
        int pos = rand() % n;
        T val = rand();

        if(t == 0) {
            fen.add(pos, val);
            interval.add(pos, val);
        }
        if(t == 1) {
            auto fen_res = fen.ask(pos).val;
            auto int_res = interval.ask(0, pos+1).val;

            assert(fen_res == int_res);
        }
    }
    std::cout << typeid(T).name() << " : " << "passed!" << std::endl;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int n = 100;
    int q = 100000;

    test_for_group<data_structure::SumGroup<ll>>(n, q);
    test_for_group<data_structure::MaxGroup<ll>>(n, q);
    test_for_group<data_structure::MinGroup<ll>>(n, q);
}
