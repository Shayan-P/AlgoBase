/////////////////////// FWHT //////////////////////////////
// change the mods 
void txor(int *a,int tw,bool inv){
    for(int ln=1;(2*ln)<=tw;ln*=2){
	for(int l=0;l<tw;l+=ln+ln){
	    for(int i=0;i<ln;i++){
		int x=a[l+i],y=a[l+ln+i];
		a[l+i]=x+y; /// 
		a[l+ln+i]=x-y; ///
	    }
	}
    }
    if(inv){
	for(int i=0;i<tw;i++)
	    a[i]/=tw; ///
    }
}


/////////////////////// FFT with vector //////////////////////////////
typedef long double ld;
typedef pair<ld,ld> pld;

const ld pi=acos(-1);

pld operator +(pld a,pld b) {return {a.F+b.F,a.S+b.S};}
pld operator -(pld a,pld b) {return {a.F-b.F,a.S-b.S};}
pld operator *(pld a,pld b) {return {a.F*b.F-a.S*b.S,a.F*b.S+a.S*b.F};}
void operator/=(pld &a,ld b) { a.F/=b;a.S/=b;}

void fft(vector<pld> &a,bool rev){
    if(a.empty()) return;
    int n=32-__builtin_clz(sz(a));
    if(sz(a)==(1<<(n-1))) --n;
    a.resize((1<<n));
    
    for(int i=1;i<(1<<n);i++){
	int x=0;
	for(int j=0;j<n;j++)
	    if(bit(i,j)) x+=(1<<(n-1-j));
	if(i<x) swap(a[i],a[x]);
    }
    int N=(1<<n);
    for(int ln=0,Ln1=1,Ln2=2;ln<n;ln++,Ln1<<=1,Ln2<<=1){
	for(int start=0;start<N;start+=Ln2){
	    ld alpha=(rev?-1:1)*2*pi/Ln2;
	    pld w={cos(alpha),sin(alpha)},nw={1,0};
	    for(int i=start;i<start+Ln1;i++){
		pld &A=a[i],&B=a[i+Ln1],x=B*nw;
		nw=nw*w;
		B=A-x;A=A+x;
		if(rev)	B/=2,A/=2;
	    }
	}
    }
}

// ~858 ms for 2e6
// ~1850 ms for 4e6

int main(){
    vector<pld> A(2000000);
    fft(A,0);
    fft(A,1);
}


/////////////////////// NTT //////////////////////////////
// this is for mod 998...
// change the primitive root and mod
// you can precompute w array

int w[2][maxn];

void fft(int *arr, int n, bool rev){
    int N = __builtin_ctz(n);
    for(int i = 0; i < n; i++){
	int x = 0;
	for(int j = 0; j < N; j++)
	    x += bit(i, j) << (N- 1- j);
	if(x < i)
	    swap(arr[x], arr[i]);
    }

    w[0][0] = 1;
    w[0][1] = Pow( 3, ( mod -1 ) >> (N) );
    for(int i = 2; i < n; i++)
	w[0][i] = 1ll * w[0][i-1] * w[0][1] %mod;
    w[1][0] = 1;
    w[1][1] = Pow( w[0][1], mod - 2 );
    for(int i = 2; i < n; i++)
	w[1][i] = 1ll * w[1][i-1] * w[1][1] %mod;
    
    for(int stpid = 0; stpid < N; stpid++){
	int stp = 1<<stpid;
	for(int l = 0; l < n; l+= stp + stp){
	    for(int i = 0; i < stp; i++){
		int &A = arr[l + i], &B = arr[l + stp + i], C = 1ll * B * w[rev][i << (N - stpid -1)] %mod;
		B = ( A - C ) %mod;
		A = ( A + C ) %mod;
	    }
	}
    }

    if(rev){
	int rv = Pow( n, mod - 2 );
	for(int i = 0; i < n; i++)
	    arr[i] = 1ll * arr[i] * rv %mod;
    }
}
