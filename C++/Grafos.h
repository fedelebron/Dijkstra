#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <limits>
#define forsn(i, s, n) for(int i = (s); i < (n); ++i)
#define forn(i, n) forsn(i, 0, n)
#define forall(it, c) for(typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define INFINITO (numeric_limits<double>::infinity())
#define DBG(s) cout << s
using namespace std;

typedef int nodo;
typedef vector<bool> vbool;