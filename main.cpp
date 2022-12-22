#include <iostream>
#include <exception>
#include <cmath>
#include <utility>

using namespace std;

struct complex {
  float re, im;

  friend ostream &operator<<(ostream &os, const complex &complex) {
    os << "re: " << complex.re << " im: " << complex.im;
    return os;
  }
};

complex complex_div_base( complex c, complex d ) {
  float r, p;
  complex res{};

  if(fabs(d.re) >= fabs(d.im) ) {
    r = d.im / d.re;
    p = d.re + r * d.im;
    res.re = (c.re + r * c.im) / p;
    res.im = (c.im - r * c.re) / p;

    return res;
  }

  r = d.re / d.im;
  p = d.im + r * d.re;
  res.re = (c.re * r + c.im) / p;
  res.im = (c.im * r - c.re) / p;

  return res;
}

class Empty {};
class Error
{
  private:
    string message;
  public:
    explicit Error(string message) : message(std::move(message)) {}

    string What() { return message; }
};

class E : public exception
{
  private:
    string message;
  public:
    explicit E(string message) : message(std::move(message)){}
    string What() { return message; }
};

complex complex_div1(complex c, complex d) noexcept(false) {
  if (d.re == 0 && d.im == 0)
    throw 1;

  return complex_div_base(c, d);
}

complex complex_div2(complex c, complex d) noexcept(false) {
  if (d.re == 0 && d.im == 0)
    throw 1.0;

  return complex_div_base(c, d);
}

complex complex_div3(complex c, complex d) noexcept(false) {
  if (d.re == 0 && d.im == 0)
    throw '1';

  return complex_div_base(c, d);
}

complex complex_div4(complex c, complex d) noexcept(false) {
  if (d.re == 0 && d.im == 0)
    throw Empty();

  return complex_div_base(c, d);
}

complex complex_div5(complex c, complex d) noexcept(false) {
  if (d.re == 0 && d.im == 0)
    throw Error("something went wrong");

  return complex_div_base(c, d);
}

complex complex_div6(complex c, complex d) noexcept(false) {
  if (d.re == 0 && d.im == 0)
    throw E("something went wrong");

  return complex_div_base(c, d);
}

int main() {
  try
  {
// cout << complex_div1({1, 2}, {0, 0}) << endl;
// cout << complex_div2({1, 2}, {0, 0}) << endl;
// cout << complex_div3({1, 2}, {0, 0}) << endl;
 cout << complex_div4({1, 2}, {0, 0}) << endl;
// cout << complex_div5({1, 2}, {0, 0}) << endl;
//    cout << complex_div6({1, 2}, {0, 0}) << endl;
  }
  catch (int)
  {
    cout << " catch (int) <= complex_div1()" << endl;
  }
  catch (double)
  {
    cout << " catch (double) <= complex_div2()" << endl;
  }
  catch (char)
  {
    cout << " catch (char) <= complex_div3()" << endl;
  }
  catch (Empty)
  {
    cout << " catch (Empty) <= complex_div4()" << endl;
  }
  catch (Error e) {
    cout << " catch (Error) <= complex_div5() :" << endl;
    cout << e.What() << endl;
  }
  catch (E e) {
    cout << " catch (E) <= IsVysokosny6() :" << endl;
    cout << e.What() << endl;
  }
//  catch (exception) {
//    cout << " catch (exception) <= IsVysokosny6() :" << endl;
//  }
  catch (bad_exception) {
    cout << " catch (bad_exception)" << endl;
  }

  return 0;
}
