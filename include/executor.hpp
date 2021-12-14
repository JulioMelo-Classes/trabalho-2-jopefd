#ifndef CONCORDO_EXECUTOR_H_
#define CONCORDO_EXECUTOR_H_

#include <istream>
#include <ostream>
#include <sstream>

#include "sistema.hpp"

class Executor {
 private:
  Sistema *sistema;

  std::stringstream ss;

  bool sair = false;

 public:
  /**
   * \brief Construct a new Executor object
   *
   * \param sistema
   */
  Executor(Sistema &sistema);

  /**
   * \brief
   *
   * \param in
   * \param out
   */
  void iniciar(std::istream &in, std::ostream &out);

  /**
   * \brief
   *
   * \param linha
   * \return std::string
   */
  std::string processarLinha(std::string linha);
};

#endif
