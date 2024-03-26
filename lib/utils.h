#include<bits/stdc++.h>
#include "io.h"
#include "data_structure/groups.h"

typedef long long ll;

using namespace std;

template<typename T, template<typename> class G, typename Iterator>
G<T> aggregate(Iterator first, Iterator last) {
    G<T> ans;
    while(first != last) {
        ans += *first;
        first++;
    }
    return ans;
}
