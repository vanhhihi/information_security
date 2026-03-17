#include<iostream>
#include<string>
#include<bitset>
using namespace std;

void swap(int *a,int*b){
    int temp =*a;
    *a =*b;
    *b = temp;
}

void keystream(int *s,int key[],int sleng,int keyleng){ // hàm biến đổi s thành keystream
    int j=0;
    for(int i=0;i<sleng;i++){
        j=j+s[i]+key[i%keyleng];
        j=j%sleng;
        swap(&s[i],&s[j]);
    }
}
int *uint(string s){
    int *arr = new int[s.length()]; // Khởi tạo mảng động để lưu các số nguyên
    for (size_t i = 0; i < s.length(); i++) {
        arr[i] = static_cast<int>(s[i]); // Chuyển ký tự thành số nguyên theo bảng mã ASCII
    }
    return arr; // Trả về mảng các số nguyên
}
int XOR(int a , int b){
    // Biến đổi int a, b sang mảng 1 byte chứa các số nhị phân
    int binaryA[8], binaryB[8];
    for (int i = 7; i >= 0; i--) {
        binaryA[i] = a % 2;
        binaryB[i] = b % 2;
        a /= 2;
        b /= 2;
    }

    // Thực hiện phép XOR từng bit và lưu vào mảng c
    int binaryC[8];
    for (int i = 0; i < 8; i++) {
        binaryC[i] = binaryA[i] ^ binaryB[i];
    }

    // Biến đổi mảng nhị phân c 1 byte sang số nguyên int
    int result = 0;
    for (int i = 0; i < 8; i++) {
        result = result * 2 + binaryC[i];
    }

    return result; // Trả về số nguyên sau khi XOR
}
void cryptoRC4(string key,int *s,int sleng){
    int i=0,j=0;
    int *t = new int[key.length()];// tìm Key(t) từ key
    for(int k=0;k < key.length();k++){
        i=(i+1)%sleng;
        j=(j+s[i])%sleng;
        swap(&s[i],&s[j]);
        t[k]=s[(s[i]+s[j])%sleng];
    }
    int *keystream = new int [key.length()];// tạo keystream từ t
    int *plantext = uint(key);
    for(int k=0;k < key.length();k++){
        keystream[k] = XOR(plantext[k],t[k]);
       // cout<<keystream[k]<<" "; ////////////////////////////////////////////////###########
    }

    // Biến đổi các số nguyên trong keystream[] thành ký tự char trong bảng mã ASCII
    string result = "";
    for (int k = 0; k < key.length(); k++) {
        result += static_cast<char>(keystream[k]);
    }

    cout << "Encrypted result: " << result << endl; // Xuất kết quả mã hóa
    delete[] t;
    delete[] keystream;
}
int main(){
    string mahoa ="cybersecurity";// viết từ cần mã hóa vào đây
    string giaima="k}glwzgc}qh|y";// viết từ muốn giải mã vào đây
    int s[10]={0,1,2,3,4,5,6,7,8,9};
    int seed[4]={2,4,1,7};
    keystream(s,seed,10,4); // tìm keystream từ seed và S
    int s1[10];
    for(int i=0;i<10;i++){
        s1[i]=s[i];
    }
    cryptoRC4(mahoa,s,10); // hàm mã hóa RC4
    cryptoRC4(giaima,s1,10); // hàm giải mã RC4
return 0;
}