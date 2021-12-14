#include <algorithm>
#include <string>

#include "canal_texto.hpp"

class Servidor {
 private:
  unsigned int id_;
  Usuario *dono_;
  std::string nome_;
  std::string descricao_;
  std::string codigo_convite_;
  std::vector<CanalTexto> canais_texto_;
  unsigned int prox_id_canal_texto_;
  std::vector<Usuario *> participantes_;

 public:
  Servidor();

  Servidor(const int &id, Usuario *dono, const std::string &nome);

  void SendMessage(const std::vector<Usuario *>::iterator &usuario_it,
                   const std::vector<CanalTexto>::iterator &canal_it,
                   const std::string &mensagem);

  /**
   * \brief Verifica se o usuario informado é dono do servidor.
   *
   * \param usuario Ponteiro para o usuário informado
   *
   * \return true, caso o usuário informado seja dono do servidor; false,
   * caso contrário
   */
  bool Owner(const std::vector<Usuario *>::iterator &usuario_it) const;

  bool IsPrivate() const;

  void AddParticipant(Usuario *usuario);

  Usuario *FindParticipant(const int &id_usuario);

  void RemoveParticipant(const std::vector<Usuario *>::iterator &usuario_it);

  void AddChannel(const std::vector<Usuario *>::iterator &dono_it,
                  const std::string &nome_canal);

  bool Exists(const std::vector<CanalTexto>::iterator &canal_it) const;

  std::vector<CanalTexto>::iterator FindChannel(const std::string &nome_canal);

  std::vector<CanalTexto>::iterator FindChannel(const int &id_canal);

  void RemoveChannel(const std::vector<CanalTexto>::iterator &canal_it);

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

  std::vector<CanalTexto> get_canais_texto() const;

  std::size_t get_prox_id_canal_texto();

  std::vector<Usuario *> get_participantes();
};