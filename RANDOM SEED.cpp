uint64_t randomAddress() {
  char *p = new char;
  delete p;
  return uint64_t(p);
}
 
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (randomAddress() | 1);
mt19937_64 rng(SEED);
 
