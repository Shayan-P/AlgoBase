#include "AlgoBase/utils.h"
#include "AlgoBase/data_structure/segment.h"
#include "AlgoBase/data_structure/interval.h"
#include "AlgoBase/data_structure/groups.h"

template<typename T>
void test_for_group(int n, int q) {
    data_structure::SegmentTreeSimple<T> segment(n);
    data_structure::Interval<T, T> interval(n);

    while(q--) {
        int t = rand() % 3;
        int l = rand() % n;
        int r = rand() % n;
        if(l > r)
            swap(l, r);
        int pos = rand() % n;
        T val = rand();

        if(t == 0) {
            segment.add(pos, val);
            interval.add(pos, val);
        }
        if(t == 1) {
            auto seg_val = segment.ask(l, r).val;
            auto int_val = interval.ask(l, r).val;
            assert(seg_val == int_val);
        }
        if(t == 2) {
            segment.set(pos, val);
            interval.set(pos, val);
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
