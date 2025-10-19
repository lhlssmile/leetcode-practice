#include<iostream>
using namespace std;
const int N=100005;
int t,n;
long long b[N];
int a[N],val;
// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     cin>>t;
//     while(t--){
//         cin>>n;
//         for(int i=1;i<=n;i++)cin>>b[i];
//         val=1;
//         a[1]=val++;
//         for(int i=2;i<=n;i++){
//             long long d=b[i]-b[i-1];
//             int p=i-d;
//             if(p==0){
//                 a[i]=val++;
//             }else{
//                 a[i]=a[p];
//             }
//         }
//         for(int i=1;i<=n;i++){
//             cout<<a[i]<<" ";
//         }
//         cout<<"\n";
//     }
//     return 0;
// }
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> b[i];
        val = 1;
        a[1] = val++;
        for (int i = 2; i <= n; i++ ) {
            int d = b[i] - b[i - 1];
            int p = i - d;
            if (p == 0) {
                a[i] = val++;
            }else {
                a[i] = a[p];
            }
        }
        for (int i = 1; i <= n; i++) {
            cout << a[i] << " ";
        }
        cout << "\n";
    }
}