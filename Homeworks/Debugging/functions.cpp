#include <stdexcept>
#include <iostream>

int Largest(int a, int b, int c) {
  int d = INT32_MIN;
  if (a > d) {
    d = a;
  } 
  if (b > d) {
    d = b;
  } 
  if (c > d) {
    d = c;
  }
  return d;
}

bool SumIsEven(int a, int b) {
  if( (a+b) % 2 == 0) {
    return true;
  }
  else {
    return false;
  }
}

int BoxesNeeded(int apples) {
  if (apples <= 0) {
    return 0;
  }
  else if ((apples % 20 != 0)) {
    return (apples/20) + 1;
  }
  return apples/20;
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) {
  if (A_correct < 0 || A_total <= 0 || B_correct < 0 || B_total <= 0 || A_correct > A_total || B_correct > B_total) {
    throw std::invalid_argument("Invalid input");
  }
  return ((static_cast<double>(A_correct)/A_total) > (static_cast<double>(B_correct)/B_total));
}

bool GoodDinner(int pizzas, bool is_weekend) {
  if (is_weekend && pizzas >= 10) {
    return true;  
  }
  if (pizzas >= 10 && pizzas <= 20) {
    return true;
  }
  return false;
}

int SumBetween(int low, int high) {
  if (high < low) {
    throw std::invalid_argument("Low and High are out of order");
  }
  int value = 0;

  if (low < 0 && high > 0) {
    if (low < -high) {
      high = -high - 1;
    }
    else if (-low < high) {
      low = -low + 1;
    }
  }
  if (low == high) {
    return low;
  }
  if (low == -high) {
    return 0;
  }

  for (int n = low; n <= high; n++) {
    if ((n > 0 && value > INT32_MAX - n) || (n < 0 && value < INT32_MIN - n)) {
      throw std::overflow_error("Overflow");
    }
    value += n;
  }
  return value;
}

int Product(int a, int b) {
  if ((a > 0 && b > 0 && INT32_MAX / a < b) || (a > 0 && b < 0 && INT32_MIN / a > b) || 
      (a < 0 && b > 0 && INT32_MIN / b > a) || (a == INT32_MIN && b == INT32_MIN) || (a < 0 && b < 0 && INT32_MAX / a > b)) {
    throw std::overflow_error("Overflow");
  }
  return a * b;
}
