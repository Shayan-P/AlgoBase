#include<bits/stdc++.h>

using namespace std;

template<typename Input_Type, typename Return_Type>
struct My_Iter {
  using iterator_category = std::forward_iterator_tag;
  using difference_type = Input_Type;
  using value_type = Return_Type;
  using pointer = value_type*;
  using reference = value_type&;
  
  Input_Type x;
  
  My_Iter(Input_Type x): x(x) {}

  value_type operator * () const {
    // to be implemented
  }
  difference_type operator - (const My_Iter &other) const {
    return other.x - x;
  }
  My_Iter operator + (Input_Type dist) const {
    return My_Iter(x+dist);
  }
  void operator ++ () { ++x; }
  void operator -- () { --x; }
  bool operator == (const My_Iter &other) const {
    return other.x == x;
  }
  bool operator != (const My_Iter &other) const {
    return other.x != x;
  }
};

using ll = long long;

struct Impl : public My_Iter<ll, ll> {
  using My_Iter::My_Iter;
  ll operator * () const {
    return 2*x;
  }
};


int main() {
  Impl start(-1ll * 1000000000000000);
  Impl end(1ll * 1000000000000000000);
  cout << lower_bound(start, end, 32).x << endl;
  cout << upper_bound(start, end, 32).x << endl;
}
