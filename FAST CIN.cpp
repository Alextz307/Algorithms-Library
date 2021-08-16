namespace FastRead {
  const int Dim(50000);
  char ibuf[Dim];
  int ipos, ilen;

  char nc() {
    if (ipos == ilen) {
      ipos = 0;
      ilen = fread(ibuf, 1, Dim, stdin);
      if (!ilen)
        return EOF;
    }
    return ibuf[ipos++];
  }

  template<class T> void read(T& x) {
    char ch;
    int sgn = 1;
    while (!isdigit(ch = nc()))
      if (ch == '-')
        sgn = -1;
    x = ch - '0';
    while (isdigit(ch = nc()))
      x = x * 10 + (ch - '0');
    x *= sgn;
  }
}

using namespace FastRead;