#include "AlgoBase/utils.h"
#include "AlgoBase/data_structure/segment.h"
#include "AlgoBase/data_structure/interval.h"
#include "AlgoBase/data_structure/groups.h"


template<typename T, template<typename> class G1, template<typename> class G2>
void test_for_group(int n, int q) {
    data_structure::SegmentTreeGenericModification<G1<T>, data_structure::WithSet<T, G2>> segment(n);
    data_structure::Interval<G1<T>, G2<T>> interval(n);

    while(q--) {
        int t = rand() % 5;
        int l = rand() % n;
        int r = rand() % n;
        if(l > r)
            swap(l, r);
        int pos = rand() % n;
        T val = rand() % 2;
        // data_structure::WithSet<T, G2> set_val(G2<T>(val));
        // data_structure::WithSet<T, G2> opp_val(std::optional<T>(val));
        data_structure::WithSet<T, G2> opp_val = data_structure::WithSet<T, G2>::fromOpp(G2<T>(val));
        data_structure::WithSet<T, G2> set_val = data_structure::WithSet<T, G2>::fromSet(val);

        if(t == 0) {
            segment.add(pos, opp_val);
            interval.add(pos, val);
            // cout << "add pos " << pos << " " << val << endl;
        }
        if(t == 1) {
            segment.add(l, r, opp_val);
            interval.add(l, r, val);
            // cout << "add interval " << l << " " << r << " " << val << endl;
        }
        if(t == 2) {
            auto seg_val = segment.ask(l, r).val;
            auto int_val = interval.ask(l, r).val;
            // cout << "ask interval " << l << " " << r << endl;
            // std::cout << seg_val << " " << int_val << std::endl;
            // if(seg_val != int_val) {
            //     cout << "segment: " << endl;
            //     segment.print();
            //     cout << "interval " << endl;
            //     interval.print();
            // }
            assert(seg_val == int_val);
        }
        if(t == 3) {
            // cout << "set pos " << pos << " " << val << endl;
            segment.add(pos, set_val);
            interval.set(pos, val);
        }
        if(t == 4) {
            // cout << "set segment " << l << " " << r << " " << val << endl;
            segment.add(l, r, set_val);
            interval.set(l, r, val);
        }

        // cout << "segment: " << endl;
        // segment.print();
        // cout << "interval " << endl;
        // interval.print();
        // assert(segment.ask(0, n).val == interval.ask(0, n).val);
    }
    std::cout << typeid(data_structure::SegmentTreeGenericModification<G1<T>, data_structure::WithSet<T, G2>>).name() << " : " << "passed!" << std::endl;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int n = 4;
    int q = 100000;

    test_for_group<ll, data_structure::SumGroup, data_structure::SumGroup>(n, q);
    test_for_group<ll, data_structure::MinGroup, data_structure::SumGroup>(n, q);
    test_for_group<ll, data_structure::MaxGroup, data_structure::MaxGroup>(n, q);
}
