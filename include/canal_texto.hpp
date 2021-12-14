#include <ctime>
#include <iomanip>
#include <string>
#include <vector>

#include "mensagem.hpp"

class CanalTexto {
 private:
  unsigned int id_;

  std::string nome_;

  Usuario* dono_;

  std::vector<Mensagem> mensagens_;

  std::size_t prox_id_mensagem_;

 public:
  CanalTexto();

  CanalTexto(const unsigned int& id, const std::string& nome,
             const std::vector<Usuario*>::iterator& dono_it);

  void SendMessage(const std::vector<Usuario*>::iterator& usuario_it,
                   const std::string& mensagem);

  unsigned int get_id() const;

  void set_id(const unsigned int& id);

  std::string get_nome() const;

  void set_nome(const std::string& nome);

  Usuario* get_dono() const;

  void set_dono(Usuario* dono);

  std::vector<Mensagem> get_mensagens() const;

  void set_mensagens(const std::vector<Mensagem>& mensagens);
};