#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "executor.hpp"
#include "sistema.hpp"

using std::cin;
using std::cout;

int main() {
  Sistema sistema;
  Executor executor(sistema);

  executor.iniciar(cin, cout);

  return 0;
}
