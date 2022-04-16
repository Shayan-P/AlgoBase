#include<bits/stdc++.h>

using namespace std;

template <typename T>
constexpr auto type_name() {
    std::string_view name, prefix, suffix;
#ifdef __clang__
    name = __PRETTY_FUNCTION__;
  prefix = "auto type_name() [T = ";
  suffix = "]";
#elif defined(__GNUC__)
    name = __PRETTY_FUNCTION__;
    prefix = "constexpr auto type_name() [with T = ";
    suffix = "]";
#elif defined(_MSC_VER)
    name = __FUNCSIG__;
  prefix = "auto __cdecl type_name<";
  suffix = ">(void)";
#endif
    name.remove_prefix(prefix.size());
    name.remove_suffix(suffix.size());
    return name;
}

template<int T> void func() {
    cout << __PRETTY_FUNCTION__  << endl;
}

int main() {
    cout << type_name<decltype(declval<vector<int>>().size())>() << endl;
    vector<int> v;
    decltype(v) other_v = {1, 2, 3, 4}; // type of other_v is vector<int>
    cout << type_name<decltype(other_v)>() << endl;
}