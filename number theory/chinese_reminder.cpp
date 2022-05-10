#include<bits/stdc++.h>

using namespace std;

namespace Number_Theory {
    int gcd_extended(int a, int b, int& x, int& y) {
        // gcd = ax + by,  abs(x) < b, abs(y) < a
        if (a == 0) {
            x = 0, y = 1;
            return b;
        }
        int x1, y1;
        int g = gcd_extended(b % a, a, x1, y1);
        // b/a = M
        // x1 * (b-M*a) + y1 * a == g
        // a * (-M*x1+y1) + b * (x1) == g
        x = y1 - (b / a) * x1;
        y = x1;
        return g;
    }

    int inverse(int a, int m) {
        int x, y;
        int g = gcd_extended(a, m, x, y);
        if (g != 1)
            return -1;
        return (x % m + m) % m;
    }
 
    struct CHR { // MOD should be smaller than 2^31 -1
        vector<int> mods;
        vector<int> cofs;
        int MOD;

        CHR(const vector<int>& mods): mods(mods) {
            for(unsigned i = 0; i < mods.size(); i++) {
                for(unsigned j = i+1; j < mods.size(); j++) {
                    assert(__gcd(mods[i], mods[j]) == 1);
                }
            }

            MOD = 1;
            for(int p : mods) {
                MOD *= p;
            }

            for(int p: mods) {
                int mp = MOD/p;
                cofs.push_back(1ll * mp % MOD * Number_Theory::inverse(mp, p) % MOD);
            }
        }

        int reminders_to_number(const vector<int>& rs) const {
            assert(rs.size() == mods.size());
            int ans = 0;
            for(unsigned i = 0; i < mods.size(); i++)
                ans = (1ll * cofs[i] * rs[i] + ans) % MOD;
            return ans;
        }
        vector<int> number_to_reminders(int x) const {
            vector<int> ans(mods.size());
            for(unsigned i = 0; i < mods.size(); i++)
                ans[i] = x % mods[i];
            return ans;
        }
    };
}

int main() {
    Number_Theory::CHR chr({3, 4, 5});
    int res = chr.reminders_to_number({1, 0, 2});
    cout << "ans is " << res << endl;
    vector<int> rems = chr.number_to_reminders(res);
    assert(rems == vector<int>({1, 0, 2}));
}