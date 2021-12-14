#include "servidor.hpp"

using std::find_if;
using std::string;
using std::vector;

/*******************************************************************************
 * PUBLIC METHODS
 ******************************************************************************/

Servidor::Servidor() {}

Servidor::Servidor(const int &id, Usuario *dono, const string &nome)
    : id_(id), dono_(dono), nome_(nome), prox_id_canal_texto_(1) {}

bool Servidor::Owner(const vector<Usuario *>::iterator &usuario_it) const {
  return (*usuario_it)->get_id() == dono_->get_id();
}

bool Servidor::IsPrivate() const { return codigo_convite_.empty(); }

void Servidor::AddParticipant(Usuario *usuario) {
  participantes_.push_back(usuario);
}

Usuario *Servidor::FindParticipant(const int &id_usuario) {
  auto it = find_if(
      participantes_.begin(), participantes_.end(),
      [id_usuario](const auto &p) { return p->get_id() == id_usuario; });
  if (it == participantes_.end()) return nullptr;
  return *it;
}

void Servidor::RemoveParticipant(
    const vector<Usuario *>::iterator &usuario_it) {
  participantes_.erase(usuario_it);
}

bool Servidor::Exists(const vector<CanalTexto>::iterator &canal_it) const {
  return canal_it == canais_texto_.end();
}

void Servidor::AddChannel(const vector<Usuario *>::iterator &dono_it,
                          const string &nome_canal) {
  canais_texto_.push_back(
      CanalTexto(prox_id_canal_texto_++, nome_canal, dono_it));
}

vector<CanalTexto>::iterator Servidor::FindChannel(const string &nome_canal) {
  return find_if(
      canais_texto_.begin(), canais_texto_.end(),
      [nome_canal](const auto &c) { return nome_canal == c.get_nome(); });
}

vector<CanalTexto>::iterator Servidor::FindChannel(const int &id_canal) {
  return find_if(canais_texto_.begin(), canais_texto_.end(),
                 [id_canal](const auto &c) { return id_canal == c.get_id(); });
}

void Servidor::RemoveChannel(const vector<CanalTexto>::iterator &canal_it) {
  canais_texto_.erase(canal_it);
}

void Servidor::SendMessage(const vector<Usuario *>::iterator &usuario_it,
                           const vector<CanalTexto>::iterator &canal_it,
                           const string &mensagem) {
  canal_it->SendMessage(usuario_it, mensagem);
}

/*******************************************************************************
 * ACCESSORS AND MODIFIERS
 ******************************************************************************/

unsigned int Servidor::get_id() const { return id_; }

void Servidor::set_id(const unsigned int &id) { id_ = id; }

Usuario *Servidor::get_dono() const { return dono_; }

void Servidor::set_dono(Usuario *dono) { dono_ = dono; }

string Servidor::get_nome() const { return nome_; }

void Servidor::set_nome(const string &nome) { nome_ = nome; }

string Servidor::get_descricao() const { return descricao_; }

void Servidor::set_descricao(const string &descricao) {
  descricao_ = descricao;
}

string Servidor::get_codigo_convite() const { return codigo_convite_; }

void Servidor::set_codigo_convite(const string &codigo_convite) {
  codigo_convite_ = codigo_convite;
}

vector<CanalTexto> Servidor::get_canais_texto() const { return canais_texto_; }

vector<Usuario *> Servidor::get_participantes() { return participantes_; }