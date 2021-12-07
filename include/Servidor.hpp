#include <string>

#include "Usuario.hpp"

class Servidor {
 private:
  unsigned int id_;
  Usuario *dono_;
  std::string nome_;
  std::string descricao_;
  std::string codigo_convite_;

 public:
  Servidor();

  Servidor(const int &id, Usuario *dono, const std::string &nome);

  /**
   * \brief Verifica se o usuario informado é dono do servidor.
   *
   * \param usuario Ponteiro para o usuário informado
   *
   * \return true, caso o usuário informado seja dono do servidor; false, caso
   * contrário
   */
  bool IsDono(const Usuario *usuario) const;

  unsigned int get_id() const;

  void set_id(const unsigned int &id);

  Usuario *get_dono() const;

  void set_dono(Usuario *dono);

  std::string get_nome() const;

  void set_nome(const std::string &nome);

  std::string get_descricao() const;

  void set_descricao(const std::string &descricao);

  std::string get_codigo_convite() const;

  void set_codigo_convite(const std::string &codigo_convite);
};