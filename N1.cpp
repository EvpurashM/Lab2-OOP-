#include <iostream>

using namespace std;

int compute_expression(int a, int b, int c, int d) {
    int term1 = (b << 5) + b;  // 33 * b
    int term2 = (((d << 3) + (d << 2) + (d << 1) + d) + ((a << 3) + (a << 2))) >> 9;  // (d * 15 + 12 * a) / 512
    int term3 = (c << 6) + c;  // 65 * c
    int term4 = (d << 3) + (d << 2) + (d << 1);  // d * 14

    return term1 + term2 - term3 + term4;
}

int main() {
    int a, b, c, d;
    
    cout << "Enter values for a, b, c, d: ";
    cin >> a >> b >> c >> d;

    int result = compute_expression(a, b, c, d);
    
    cout << "Computed result: " << result << endl;
    
    return 0;
}
