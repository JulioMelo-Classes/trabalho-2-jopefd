#include <string>

#include "Usuario.hpp"

class Mensagem {
 private:
  unsigned int id_;

  std::string data_hora_;

  Usuario* enviada_por_;

  std::string conteudo_;

 public:
  unsigned int get_id() const;

  void set_id(const unsigned int& id);

  std::string get_data_hora() const;

  void set_data_hora(const std::string& data_hora);

  Usuario* get_enviada_por() const;

  void set_enviada_por(const Usuario*& enviada_por);

  std::string get_conteudo() const;

  void set_conteudo(const std::string& conteudo);
};