#include "Sistema.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::find_if;
using std::nullptr_t;
using std::string;
using std::vector;

Usuario *Sistema::FindUser(const string &email) {
  auto it =
      find_if(usuarios_.begin(), usuarios_.end(),
              [email](const Usuario *u) { return email == u->get_email(); });
  if (it == usuarios_.end()) return nullptr;
  return *it;
}

Usuario *Sistema::FindUser(const int &id) {
  auto it = find_if(usuarios_.begin(), usuarios_.end(),
                    [id](const Usuario *u) { return id == u->get_id(); });
  if (it == usuarios_.end()) return nullptr;
  return *it;
}

bool Sistema::IsLogged(const int &id_usuario) const {
  auto it = usuarios_logados_.find(id_usuario);
  if (it == usuarios_logados_.end()) return false;
  return true;
}

bool Sistema::IsLogged(const Usuario *usuario) const {
  return IsLogged(usuario->get_id());
}

Servidor *Sistema::FindServer(const string &nome_servidor) {
  auto it = find_if(servidores_.begin(), servidores_.end(),
                    [nome_servidor](const Servidor &s) {
                      return nome_servidor == s.get_nome();
                    });
  if (it == servidores_.end()) return nullptr;
  return &(*it);
}

void Sistema::AddServer(Usuario *dono, const string &nome_servidor) {
  servidores_.push_back(Servidor(prox_id_servidor_, dono, nome_servidor));
  prox_id_servidor_++;
}

void Sistema::EraseServer(const Servidor *servidor) {
  servidores_.erase(servidor);
  prox_id_servidor_++;
}

void Sistema::AddUser(const string &nome, const string &email,
                      const string &senha) {
  usuarios_.push_back(new Usuario(prox_id_usuario_, nome, email, senha));
  prox_id_usuario_++;
}

void Sistema::AddLoggedUser(const Usuario *usuario) {
  usuarios_logados_.insert({usuario->get_id(), {0, 0}});
}

void Sistema::RemoveLoggedUser(const int &id_usuario) {
  usuarios_logados_.erase(id_usuario);
}

void Sistema::RemoveLoggedUser(const Usuario *usuario) {
  RemoveLoggedUser(usuario->get_id());
}

Sistema::Sistema() : prox_id_servidor_(0), prox_id_usuario_(0) {}

string Sistema::quit() { return "Saindo..."; }

string Sistema::CreateUser(const string &nome, const string &email,
                           const string &senha) {
  if (FindUser(email) != nullptr)
    return "Erro ao criar usuário(a): usuário(a) já cadastrado(a) no "
           "sistema";
  AddUser(nome, email, senha);
  return "Sucesso: usuário(a) criado(a)!";
}

std::string Sistema::DeleteUser(const string &email, const string &senha) {
  Usuario *u = FindUser(email);
  if (u == nullptr)
    return "Erro ao deletar usuário(a): usuário(a) não cadastrado(a) no "
           "sistema!";
  if (IsLogged(u))
    return "Erro ao deletar usuário(a): usuário(a) logado(a) no sistema!";
  //
  // FALTA TRATAR OS DEMAIS ERROS
  //
  delete u;
  return "Sucesso: usuário(a) " + email + " removido(a) do sistema!";
}

string Sistema::Login(const string &email, const string &senha) {
  Usuario *u = FindUser(email);
  if (u == nullptr) return "Erro ao logar: email inválido!";
  if (u->get_senha() != senha) return "Erro ao logar: senha inválida!";
  AddLoggedUser(u);
  return "Sucesso: usuário(a) " + email + " logado(a) no sistema!";
}

string Sistema::Disconnect(const int &id_usuario) {
  if (not IsLogged(id_usuario))
    return "Erro ao desconectar: usuário(a) não logado(a)!";
  RemoveLoggedUser(id_usuario);
  return "Sucesso: usuário(a) desconectado(a!";
}

string Sistema::CreateServer(const int &id_usuario,
                             const string &nome_servidor) {
  if (FindServer(nome_servidor) != nullptr)
    return "Erro ao criar servidor: servidor já existe!";
  if (not IsLogged(id_usuario))
    return "Erro ao criar servidor: usuário(a) não logado(a)!";
  AddServer(FindUser(id_usuario), nome_servidor);
  return "Sucesso: servidor criado!";
}

string Sistema::SetServerDesc(const int &id_usuario,
                              const string &nome_servidor,
                              const string &descricao) {
  if (not IsLogged(id_usuario))
    return "Erro ao mudar descrição do servidor: usuário(a) não logado(a)!";
  Servidor *s = FindServer(nome_servidor);
  if (s == nullptr)
    return "Erro ao mudar descrição do servidor: servidor não existe!";
  if (not s->IsDono(FindUser(id_usuario)))
    return "Erro ao mudar descrição do servidor: usuário(a) não é dono(a)!";
  s->set_descricao(descricao);
  return "Sucesso: descrição do servidor alterada!";
}

string Sistema::SetServerInviteCode(const int &id_usuario,
                                    const string &nome_servidor,
                                    const string &codigo_convite) {
  if (not IsLogged(id_usuario))
    return "Erro ao mudar código de convite: usuário(a) não logado(a)!";
  Servidor *s = FindServer(nome_servidor);
  if (s == nullptr)
    return "Erro ao mudar código de convite: servidor não existe!";
  if (not s->IsDono(FindUser(id_usuario)))
    return "Erro ao mudar código de convite: usuário(a) não é dono(a)!";
  s->set_codigo_convite(codigo_convite);
  return "Sucesso: código de convite alterado!";
}

string Sistema::ListServers(const int &id_usuario) const {
  if (not IsLogged(id_usuario))
    return "Erro ao listar servidores: usuário(a) não logado(a)!";
  for (auto &s : servidores_) cout << s.get_nome() << endl;
  return "";
}

string Sistema::RemoveServer(const int &id_usuario,
                             const string &nome_servidor) {
  if (not IsLogged(id_usuario))
    return "Erro ao remover servidor: usuário(a) não logado(a)!";
  Servidor *s = FindServer(nome_servidor);
  if (s == nullptr) return "Erro ao remover servidor: servidor não existe!";
  EraseServer(s);
  return "Sucesso: servidor " + nome_servidor + " removido!";
}

string Sistema::EnterServer(const int &id, const string &nome,
                            const string &codigo) {
  return "enter_server NÃO IMPLEMENTADO";
}

string Sistema::LeaveServer(const int &id, const string &nome) {
  return "leave_server NÃO IMPLEMENTADO";
}

string Sistema::ListParticipants(const int &id) const {
  return "list_participants NÃO IMPLEMENTADO";
}

string Sistema::ListChannels(const int &id) const {
  return "list_channels NÃO IMPLEMENTADO";
}

string Sistema::CreateChannel(const int &id, const string &nome) {
  return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::RemoveChannel(const int &id, const string &nome) {
  return "remove_channel NÃO IMPLEMENTADO";
}

string Sistema::EnterChannel(const int &id, const string &nome) {
  return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::LeaveChannel(const int &id) {
  return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::SendMessage(const int &id, const string &mensagem) {
  return "send_message NÃO IMPLEMENTADO";
}

string Sistema::ListMessages(const int &id) const {
  return "list_messages NÃO IMPLEMENTADO";
}
