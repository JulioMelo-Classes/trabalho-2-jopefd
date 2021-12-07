#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "Executor.hpp"
#include "Sistema.hpp"

using namespace std;

int main() {
  Sistema sistema;
  Executor executor(sistema);

  executor.iniciar(cin, cout);

  return 0;
}
