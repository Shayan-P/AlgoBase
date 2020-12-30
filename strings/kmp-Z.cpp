namespace StrAlgo{
    // 1 base
    vector<int> Kmp(string s){
	int n = sz(s);
	vector<int> ans(n + 1);
	for(int i = 2; i <= n; i++){
	    ans[i] = ans[i-1];
	    while(ans[i] > 0 && s[ans[i]] != s[i-1])
		ans[i] = ans[ans[i]];
	    ans[i]+= s[ans[i]] == s[i-1];
	}
	return ans;
    }
    vector<int> Z(string s){
	int n = sz(s);
	vector<int> ans(n + 1);
	int L = -1, R = -1;
	// [L R)
	// ans[1] is 0
	for(int i = 2; i <= n; i++){
	    if(i < R)
		ans[i] = min(ans[i-L+1], R-i);
	    else
		L = i, R = i;
	    while(i + ans[i] <= n && s[i-1 + ans[i]] == s[ans[i]])
		ans[i]++;
	    if(i + ans[i] > R)
		L = i, R = i + ans[i];
	}
	return ans;
    }
};
