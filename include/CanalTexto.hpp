#include <string>
#include <vector>

#include "Mensagem.hpp"
#include "Usuario.hpp"

class CanalTexto {
 private:
  unsigned int id_;

  std::string nome_;

  Usuario* dono_;

  std::vector<Mensagem> mensagens_;

 public:
  unsigned int get_id() const;

  void set_id(const unsigned int& id);

  std::string get_nome() const;

  void set_nome(const std::string& dono);

  Usuario* get_dono() const;

  void set_dono(const Usuario* dono);

  std::string get_mensagens() const;

  void set_mensagens(const std::string& mensagens);
};