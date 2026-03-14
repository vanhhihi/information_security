#include <iostream>
#include <iomanip>
#include <bitset>
#include <utility>
#include <cstdint>
using namespace std;

typedef uint32_t poly;

// Đa thức tối giản m(x) = x^10 + x^3 + 1
const poly M = (1 << 10) | (1 << 3) | 1;

// Lấy bậc của đa thức
int getDegree(poly p) {
    if (p == 0) return -1;
    int deg = 0;
    while (p >>= 1) deg++;
    return deg;
}

// Chia đa thức trong GF(2): Trả về {thương q, số dư r}
pair<poly, poly> poly_div(poly a, poly b) {
    poly q = 0;
    poly r = a;
    int deg_b = getDegree(b);

    while (getDegree(r) >= deg_b) {
        int shift = getDegree(r) - deg_b;
        q ^= (1 << shift);
        r ^= (b << shift);
    }
    return {q, r};
}

// Nhân đa thức trong GF(2)
poly poly_mul(poly a, poly b) {
    poly res = 0;
    for (int i = 0; i <= getDegree(a); i++) {
        if ((a >> i) & 1) res ^= (b << i);
    }
    return res;
}

// Thuật toán Euclidean mở rộng
poly extended_euclidean_inverse(poly a, poly m) {
    if (a == 0) return 0;

    poly r0 = m, r1 = a;
    poly s0 = 0, s1 = 1;

    cout << left << setw(10) << "Step" << setw(15) << "Quotient (q)" 
         << setw(15) << "Remainder (r)" << setw(15) << "s" << endl;
    cout << string(55, '-') << endl;

    int step = 0;
    while (r1 != 0) {
        auto [q, r2] = poly_div(r0, r1);
        
        // Tính s_next = s0 ^ (q * s1)
        poly s2 = s0 ^ poly_mul(q, s1);

        cout << setw(10) << step++ 
             << setw(15) << q 
             << setw(15) << r2 
             << setw(15) << s2 << endl;

        r0 = r1; r1 = r2;
        s0 = s1; s1 = s2;
    }

    return (r0 == 1) ? s0 : 0;
}

// Hàm in đa thức dưới dạng nhị phân
void printBinary(poly p) {
    cout << bitset<11>(p) << endl;
}

int main() {
    poly tests[] = {523, 1015};// nơi ghi những số cần tìm nghịch đảo

    for (poly a : tests) {
        cout << "\nFinding inverse for a = " << a << " in GF(2^10)" << endl;
        cout << "m(x) = (x^10 + x^3 + 1)" << endl;
        
        poly inv = extended_euclidean_inverse(a, M);
        
        if (inv) {
            cout << "=> Result: " << a << "^-1 = " << inv << endl;
            cout << "Binary form: ";
            printBinary(inv);
            // Kiểm tra lại: (a * inv) % m nên bằng 1
            auto [q, check] = poly_div(poly_mul(a, inv), M);
            cout << "(Check: (a * inv) mod m = " << check << ")" << endl;
        } else {
            cout << "=> No inverse found!" << endl;
        }
        cout << string(55, '=') << endl;
    }

    return 0;
}