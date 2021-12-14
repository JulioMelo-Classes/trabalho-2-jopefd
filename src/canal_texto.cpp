#include "canal_texto.hpp"

using std::localtime;
using std::put_time;
using std::string;
using std::stringstream;
using std::time;
using std::vector;

CanalTexto::CanalTexto() {}

CanalTexto::CanalTexto(const unsigned int& id, const string& nome,
                       const vector<Usuario*>::iterator& dono_it)
    : id_(id), nome_(nome), dono_(*dono_it), prox_id_mensagem_(1) {}

void CanalTexto::SendMessage(const std::vector<Usuario*>::iterator& usuario_it,
                             const std::string& mensagem) {
  const auto tempo = std::time(nullptr);
  const auto tempo_local = *std::localtime(&tempo);
  stringstream oss;
  oss << put_time(&tempo_local, "%d/%m/%Y %H:%M");
  const string data_hora = oss.str();

  mensagens_.push_back(
      Mensagem(prox_id_mensagem_++, data_hora, *usuario_it, mensagem));
}

unsigned int CanalTexto::get_id() const { return id_; }

void CanalTexto::set_id(const unsigned int& id) { id_ = id; }

string CanalTexto::get_nome() const { return nome_; }

void CanalTexto::set_nome(const string& nome) { nome_ = nome; }

Usuario* CanalTexto::get_dono() const { return dono_; }

void CanalTexto::set_dono(Usuario* dono) { dono_ = dono; }

vector<Mensagem> CanalTexto::get_mensagens() const { return mensagens_; }

void CanalTexto::set_mensagens(const vector<Mensagem>& mensagens) {
  mensagens_ = mensagens;
}