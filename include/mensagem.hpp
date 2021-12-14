#include <string>

#include "usuario.hpp"

class Mensagem {
 private:
  unsigned int id_;

  std::string data_hora_;

  Usuario* enviada_por_;

  std::string conteudo_;

 public:
  Mensagem();

  Mensagem(const int& id, const std::string& data_hora, Usuario* usuario,
           const std::string& conteudo);

  unsigned int get_id() const;

  void set_id(const unsigned int& id);

  std::string get_data_hora() const;

  void set_data_hora(const std::string& data_hora);

  Usuario* get_enviada_por() const;

  void set_enviada_por(const Usuario*& enviada_por);

  std::string get_conteudo() const;

  void set_conteudo(const std::string& conteudo);
};