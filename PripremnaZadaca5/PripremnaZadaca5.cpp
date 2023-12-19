#include <iostream>

using namespace std;

int fib_petlja(int n) {
  if (n <= 1)
    return n; // 0 i 1
  int pretprosli(0), prosli(1), rezultat;
  for (int i(2); i <= n; i++) {
    rezultat = pretprosli + prosli;
    pretprosli = prosli;
    prosli = rezultat;
  }
  return rezultat;
}

int fib2_0(int n, int a = 0, int b = 1) {

  if (n == 0)
    return a;
  else if (n == 1)
    return b;

  return fib2_0(n - 1, b, a + b);
}

/*int fib(int n) {
  if (n <= 1)
    return n;
  return fib(n - 1) + fib(n - 2);
}
*/

int nzd(int x, int y) {
  if (y == 0)
    return x;

  return nzd(y, x % y);
}

int main() {
  std::cout << fib_petlja(21) << "  " << fib2_0(21) << std::endl;
  std::cout << nzd(91, 73);
  return 0;
}