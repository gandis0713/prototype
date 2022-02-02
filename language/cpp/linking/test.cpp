static int a = 3;
int b = 3;
static int c;

static int func2() {
  c += a + b;
  return c;
}

int func3() {
  b += c;
  return b;
}

int func() {
  a += func2();
  a += func3();
  return a;
}