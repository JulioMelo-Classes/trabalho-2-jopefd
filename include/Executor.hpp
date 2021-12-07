#ifndef CONCORDO_EXECUTOR_H_
#define CONCORDO_EXECUTOR_H_

#include <istream>
#include <ostream>
#include <sstream>

#include "Sistema.hpp"

class Executor {
 private:
  Sistema *sistema;

  std::stringstream ss;

  bool sair = false;

 public:
  Executor(Sistema &sistema);

  void iniciar(istream &in, ostream &out);

  std::string processarLinha(std::string linha);
};

#endif
