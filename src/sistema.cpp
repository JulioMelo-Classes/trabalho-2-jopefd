#include "sistema.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::find_if;
using std::map;
using std::nullptr_t;
using std::pair;
using std::string;
using std::vector;

/*******************************************************************************
 * PRIVATE METHODS
 ******************************************************************************/

vector<Usuario *>::iterator Sistema::FindUser(const int &id_usuario) {
  return find_if(
      usuarios_.begin(), usuarios_.end(),
      [id_usuario](const Usuario *u) { return id_usuario == u->get_id(); });
}

vector<Usuario *>::iterator Sistema::FindUser(const string &email) {
  return find_if(usuarios_.begin(), usuarios_.end(),
                 [email](const Usuario *u) { return email == u->get_email(); });
}

vector<Servidor>::iterator Sistema::FindServer(const int &id_servidor) {
  return find_if(
      servidores_.begin(), servidores_.end(),
      [id_servidor](const auto &s) { return id_servidor == s.get_id(); });
}

vector<Servidor>::iterator Sistema::FindServer(const string &nome_servidor) {
  return find_if(
      servidores_.begin(), servidores_.end(),
      [nome_servidor](const auto &s) { return nome_servidor == s.get_nome(); });
}

vector<Servidor>::iterator Sistema::FindServer(
    const vector<Usuario *>::iterator &usuario_it) {
  auto it = usuarios_logados_.find((*usuario_it)->get_id());
  return FindServer(it->second.first);
}

bool Sistema::Exists(const vector<Usuario *>::iterator &usuario_it) const {
  return usuario_it != usuarios_.end();
}

bool Sistema::Exists(const vector<Servidor>::iterator &servidor_it) const {
  return servidor_it != servidores_.end();
}

bool Sistema::Exists(const vector<Servidor>::iterator &servidor_it,
                     const vector<CanalTexto>::iterator &canal_it) const {
  return servidor_it->Exists(canal_it);
}

bool Sistema::Logged(const vector<Usuario *>::iterator &usuario_it) const {
  return usuarios_logados_.find((*usuario_it)->get_id()) !=
         usuarios_logados_.end();
}

void Sistema::AddServer(const string &nome_servidor,
                        const vector<Usuario *>::iterator &usuario_it) {
  servidores_.push_back(
      Servidor(prox_id_servidor_++, *usuario_it, nome_servidor));
}

void Sistema::EraseServer(const vector<Servidor>::iterator &servidor_it) {
  servidores_.erase(servidor_it);
}

void Sistema::AddUser(const string &nome, const string &email,
                      const string &senha) {
  usuarios_.push_back(new Usuario(prox_id_usuario_++, nome, email, senha));
}

void Sistema::AddLoggedUser(const vector<Usuario *>::iterator &usuario_it) {
  usuarios_logados_.insert({(*usuario_it)->get_id(), {0, 0}});
}

void Sistema::RemoveLoggedUser(const vector<Usuario *>::iterator &usuario_it) {
  usuarios_logados_.erase((*usuario_it)->get_id());
}

bool Sistema::CorrectPassword(
    const string &senha, const vector<Usuario *>::iterator &usuario_it) const {
  return senha == (*usuario_it)->get_senha();
}

void Sistema::PrintServers() const {
  for (const auto &s : servidores_) cout << s.get_nome() << endl;
}

bool Sistema::CorrectInviteCode(
    const string &codigo_convite,
    const vector<Servidor>::iterator &servidor_it) const {
  return codigo_convite == servidor_it->get_codigo_convite();
}

void Sistema::AddParticipant(vector<Servidor>::iterator &servidor_it,
                             vector<Usuario *>::iterator &usuario_it) {
  servidor_it->AddParticipant(*usuario_it);
}

bool Sistema::Participant(const vector<Usuario *>::iterator &usuario_it,
                          const vector<Servidor>::iterator &servidor_it) const {
  auto it = usuarios_logados_.find((*usuario_it)->get_id());
  if (it->second.first == servidor_it->get_id()) return true;
  return false;
}

void Sistema::RemoveParticipant(const vector<Usuario *>::iterator &usuario_it,
                                const vector<Servidor>::iterator &servidor_it) {
  servidor_it->RemoveParticipant(usuario_it);
  auto it = usuarios_logados_.find((*usuario_it)->get_id());
  it->second = {0, 0};
}

bool Sistema::Owner(const vector<Servidor>::iterator &servidor_it,
                    const vector<Usuario *>::iterator &usuario_it) const {
  return servidor_it->Owner(usuario_it);
}

void Sistema::SetDescription(const vector<Servidor>::iterator &servidor_it,
                             const string &descricao) {
  servidor_it->set_descricao(descricao);
}

void Sistema::SetInviteCode(const vector<Servidor>::iterator &servidor_it,
                            const string &codigo_convite) {
  servidor_it->set_codigo_convite(codigo_convite);
}

vector<CanalTexto>::iterator Sistema::FindChannel(
    const vector<Servidor>::iterator &servidor_it, const string &nome_canal) {
  return servidor_it->FindChannel(nome_canal);
}

vector<CanalTexto>::iterator Sistema::FindChannel(
    const vector<Servidor>::iterator &servidor_it,
    const vector<Usuario *>::iterator &usuario_it) {
  auto it = usuarios_logados_.find((*usuario_it)->get_id());
  auto id_canal = it->second.second;
  return servidor_it->FindChannel(id_canal);
}

void Sistema::RemoveChannel(const vector<Servidor>::iterator &servidor_it,
                            const vector<CanalTexto>::iterator &canal_it) {
  servidor_it->RemoveChannel(canal_it);
}

void Sistema::PrintChannels(
    const vector<Servidor>::iterator &servidor_it) const {
  const auto canais = servidor_it->get_canais_texto();
  for (const auto &c : canais) cout << c.get_nome() << endl;
}

void Sistema::PrintMessages(
    const vector<CanalTexto>::iterator &canal_it) const {
  const auto mensagens = canal_it->get_mensagens();
  for (const auto &m : mensagens) cout << m.get_conteudo() << endl;
}

void Sistema::AddChannel(const vector<Servidor>::iterator &servidor_it,
                         const vector<Usuario *>::iterator &usuario_it,
                         const string &nome_canal) {
  servidor_it->AddChannel(usuario_it, nome_canal);
}

void Sistema::DeleteUser(const vector<Usuario *>::iterator &usuario_it) {
  usuarios_.erase(usuario_it);
  delete *usuario_it;
}

string Sistema::Name(const vector<Usuario *>::iterator &usuario_it) const {
  return (*usuario_it)->get_nome();
}

void Sistema::LeaveChannel(const vector<Usuario *>::iterator &usuario_it) {
  auto it = usuarios_logados_.find((*usuario_it)->get_id());
  it->second.second = 0;
}

void Sistema::SendMessage(const std::vector<Usuario *>::iterator &usuario_it,
                          const std::vector<Servidor>::iterator &servidor_it,
                          const std::vector<CanalTexto>::iterator &canal_it,
                          const std::string &mensagem) {
  servidor_it->SendMessage(usuario_it, canal_it, mensagem);
}

void Sistema::PrintParticipants(
    const vector<Servidor>::iterator &servidor_it) const {
  const auto participantes = servidor_it->get_participantes();
  for (const auto p : participantes) cout << p->get_nome() << endl;
}

/*******************************************************************************
 * PUBLIC METHODS
 ******************************************************************************/

Sistema::Sistema() : prox_id_servidor_(1), prox_id_usuario_(1) {}

string Sistema::Quit() { return "Saindo..."; }

string Sistema::CreateUser(const string &nome, const string &email,
                           const string &senha) {
  auto u = FindUser(email);

  if (Exists(u)) {
    return "Erro ao criar usuário(a): usuário(a) já existe!";
  } else {
    AddUser(nome, email, senha);
  }

  return "Sucesso: usuário(a) " + email + " criado(a)!";
}

string Sistema::DeleteUser(const string &email, const string &senha) {
  auto u = FindUser(email);

  if (not Exists(u)) {
    return "Erro ao deletar usuário(a): usuário(a) não existe!";
  } else if (Logged(u)) {
    return "Erro ao deletar usuário(a): usuário(a) está logado(a)!";
  } else if (not CorrectPassword(senha, u)) {
    return "Erro ao deletar usuário(a): senha incorreta!";
  } else {
    DeleteUser(u);
  }

  return "Sucesso: usuário(a) " + email + " deletado!";
}

string Sistema::Login(const string &email, const string &senha) {
  auto u = FindUser(email);

  if (not Exists(u)) {
    return "Erro ao logar usuário(a): usuário(a) não existe!";
  } else if (not CorrectPassword(senha, u)) {
    return "Erro ao logar usuário(a): senha incorreta!";
  } else {
    AddLoggedUser(u);
  }

  return "Sucesso: usuário(a) " + email + " logado(a)!";
}

string Sistema::Disconnect(const int &id_usuario) {
  const auto u = FindUser(id_usuario);

  if (not Exists(u)) {
    return "Erro ao desconectar usuário(a): usuário(a) não existe!";
  } else if (not Logged(u)) {
    return "Erro ao desconectar usuário(a): usuário(a) está desconectado(a)!";
  } else {
    RemoveLoggedUser(u);
  }

  return "Sucesso ao desconectar usuário(a)!";
}

string Sistema::CreateServer(const int &id_usuario,
                             const string &nome_servidor) {
  const auto s = FindServer(nome_servidor);
  const auto u = FindUser(id_usuario);

  if (Exists(s)) {
    return "Erro ao criar servidor: servidor já existe!";
  } else if (not Exists(u)) {
    return "Erro ao criar servidor: usuário(a) não existe!";
  } else if (not Logged(u)) {
    return "Erro ao criar servidor: usuário(a) não está logado!";
  } else {
    AddServer(nome_servidor, u);
  }

  return "Sucesso ao criar servidor!";
}

string Sistema::RemoveServer(const int &id_usuario,
                             const string &nome_servidor) {
  const auto s = FindServer(nome_servidor);
  const auto u = FindUser(id_usuario);

  if (not Exists(s)) {
    return "Erro ao remover servidor: servidor não existe!";
  } else if (not Exists(u)) {
    return "Erro ao remover servidor: usuário(a) não existe!";
  } else if (not Logged(u)) {
    return "Erro ao remover servidor: usuário(a) não está logado(a)!";
  } else {
    EraseServer(s);
  }

  return "Sucesso ao remover servidor!";
}

string Sistema::ListServers(const int &id_usuario) {
  const auto u = FindUser(id_usuario);

  if (not Exists(u)) {
    return "Erro ao listar servidores: usuário(a) não existe!";
  } else if (not Logged(u)) {
    return "Erro ao listar servidores: usuário(a) não está logado(a)!";
  } else {
    PrintServers();
  }

  return "";
}

string Sistema::EnterServer(const int &id_usuario, const string &nome_servidor,
                            const string &codigo_convite) {
  auto s = FindServer(nome_servidor);
  auto u = FindUser(id_usuario);

  if (not Exists(s)) {
    return "Erro ao entrar em servidor: servidor não existe!";
  } else if (not CorrectInviteCode(codigo_convite, s)) {
    return "Erro ao entrar em servidor: código de convite "
           "incorreto!";
  } else if (not Exists(u)) {
    return "Erro ao entrar em servidor: usuário(a) não existe!";
  } else if (not Logged(u)) {
    return "Erro ao entrar em servidor: usuário(a) não logado(a)!";
  } else {
    AddParticipant(s, u);
  }

  return "Sucesso: usuário entrou no servidor " + nome_servidor + "!";
}

string Sistema::LeaveServer(const int &id_usuario,
                            const string &nome_servidor) {
  const auto s = FindServer(nome_servidor);
  const auto u = FindUser(id_usuario);

  if (not Exists(s)) {
    return "Erro ao deixar servidor: servidor não existe!";
  } else if (not Exists(u)) {
    return "Erro ao deixar servidor: usuário(a) não existe!";
  } else if (not Logged(u)) {
    return "Erro ao deixar servidor: usuário(a) não logado(a)!";
  } else if (not Participant(u, s)) {
    return "Erro ao deixar servidor: usuário(a) não é participante!";
  } else {
    RemoveParticipant(u, s);
  }

  return "Sucesso: usuário deixou servidor!";
}

string Sistema::SetServerDesc(const int &id_usuario,
                              const string &nome_servidor,
                              const string &descricao) {
  const auto s = FindServer(nome_servidor);
  const auto u = FindUser(id_usuario);

  if (Exists(s)) {
    return "Erro ao alterar descrição de servidor: servidor não existe!";
  } else if (not Exists(u)) {
    return "Erro ao alterar descrição de servidor: usuário(a) não existe!";
  } else if (not Logged(u)) {
    return "Erro ao alterar descrição de servidor: usuário(a) não logado(a)!";
  } else if (not Owner(s, u)) {
    return "Erro ao alterar descrição de servidor: usuário(a) não é dono(a)!";
  } else {
    SetDescription(s, descricao);
  }

  return "Sucesso ao alterar descrição de servidor!";
}

string Sistema::SetServerInviteCode(const int &id_usuario,
                                    const string &nome_servidor,
                                    const string &codigo_convite) {
  const auto s = FindServer(nome_servidor);
  const auto u = FindUser(id_usuario);

  if (Exists(s)) {
    return "Erro ao alterar código de convite: servidor não existe!";
  } else if (not Exists(u)) {
    return "Erro ao alterar código de convite: usuário(a) não existe!";
  } else if (not Logged(u)) {
    return "Erro ao alterar código de convite: usuário(a) não logado(a)!";
  } else if (not Owner(s, u)) {
    return "Erro ao alterar código de convite: usuário(a) não é dono(a)!";
  } else {
    SetInviteCode(s, codigo_convite);
  }

  return "Sucesso ao alterar código de convite de servidor!";
}

string Sistema::ListParticipants(const int &id_usuario) {
  const auto s = FindServer(id_usuario);
  const auto u = FindUser(id_usuario);

  if (not Exists(s)) {
    return "Erro ao listar participantes: usuário(a) fora de um servidor!";
  } else if (not Exists(u)) {
    return "Erro ao listar participantes: usuário(a) não existe!";
  } else if (not Logged(u)) {
    return "Erro ao listar participantes: usuário(a) não logado(a)!";
  } else {
    PrintParticipants(s);
  }

  return "";
}
string Sistema::CreateChannel(const int &id_usuario,
                              const std::string &nome_canal) {
  const auto u = FindUser(id_usuario);
  const auto s = FindServer(u);

  if (not Logged(u)) {
    return "Erro ao criar canal: usuário(a) não logado(a)!";
  } else if (not Exists(s)) {
    return "Erro ao criar canal: usuário(a) fora de um servidor!";
  } else {
    AddChannel(s, u, nome_canal);
  }

  return "Sucesso: canal " + nome_canal + " criado!";
}

string Sistema::RemoveChannel(const int &id_usuario, const string &nome_canal) {
  const auto u = FindUser(id_usuario);
  const auto s = FindServer(u);
  const auto c = FindChannel(s, nome_canal);

  if (not Exists(u)) {
    return "Erro ao remover canal: usuário(a) não existe!";
  } else if (not Logged(u)) {
    return "Erro ao remover canal: usuário(a) não logado(a)!";
  } else if (not Exists(s)) {
    return "Erro ao remover canal: usuário(a) fora de um servidor!";
  } else if (not Exists(s, c)) {
    return "Erro ao remover canal: canal não existe!";
  } else {
    RemoveChannel(s, c);
  }

  return "Sucesso: canal " + nome_canal + " removido!";
}

string Sistema::ListChannels(const int &id_usuario) {
  const auto u = FindUser(id_usuario);
  const auto s = FindServer(u);

  if (not Exists(u)) {
    return "Erro ao remover canal: usuário(a) não existe!";
  } else if (not Logged(u)) {
    return "Erro ao listar canais: usuário(a) não logado(a)!";
  } else if (not Exists(s)) {
    return "Erro ao listar canais: usuário(a) fora de m servidor!";
  } else {
    PrintChannels(s);
  }

  return "";
}

string Sistema::EnterChannel(const int &id_usuario, const string &nome_canal) {
  const auto u = FindUser(id_usuario);
  const auto s = FindServer(u);
  const auto c = FindChannel(s, nome_canal);

  if (not Exists(u)) {
    return "Erro ao entrar em canal: usuário(a) não existe!";
  } else if (not Logged(u)) {
    return "Erro ao entrar em canal: usuário(a) não logado(a)!";
  } else if (not Exists(s)) {
    return "Erro ao entrar em canal: usuário(a) fora de um servidor!";
  } else if (not Exists(s, c)) {
    return "Erro ao entrar em canal: canal não existe!";
  } else {
    auto it = usuarios_logados_.find(id_usuario);
    it->second.second = c->get_id();
  }

  return "Sucesso: " + Name(u) + " entrou no canal " + nome_canal + "!";
}

string Sistema::LeaveChannel(const int &id_usuario) {
  const auto u = FindUser(id_usuario);
  const auto s = FindServer(u);
  const auto c = FindChannel(s, u);

  if (not Exists(u)) {
    return "Erro ao deixar canal: usuário(a) não está cadastrado(a)!";
  } else if (not Logged(u)) {
    return "Erro ao deixar canal: usuário(a) não está logado(a)!";
  } else if (not Exists(s)) {
    return "Erro ao deixar canal: usuário(a) não está nenhum servidor!";
  } else if (not Exists(s, c)) {
    return "Erro ao deixar canal: usuário(a) não está nenhum canal!";
  } else {
    LeaveChannel(u);
  }

  return "Sucesso: " + Name(u) + " deixou o canal!";
}

string Sistema::SendMessage(const int &id_usuario, const string &mensagem) {
  const auto u = FindUser(id_usuario);
  const auto s = FindServer(u);
  const auto c = FindChannel(s, u);

  if (not Exists(u)) {
    return "Erro ao enviar mensagem: usuário(a) não existe!";
  } else if (not Logged(u)) {
    return "Erro ao enviar mensagem: usuário(a) não logado(a)!";
  } else if (not Exists(s)) {
    return "Erro ao enviar mensagem: usuário(a) fora de um servidor!";
  } else if (not Exists(s, c)) {
    return "Erro ao enviar mensagem: usuário(a) fora de um canal!";
  } else {
    SendMessage(u, s, c, mensagem);
  }

  return "";
}

string Sistema::ListMessages(const int &id_usuario) {
  const auto u = FindUser(id_usuario);
  const auto s = FindServer(u);
  const auto c = FindChannel(s, u);

  if (not Exists(u)) {
  } else if (not Logged(u)) {
    return "Erro ao listar mensagens: usuário(a) não logado(a)!";
  } else if (not Exists(s)) {
    return "Erro ao listar mensagens: usuário(a) fora de um servidor!";
  } else if (not Exists(s, c)) {
    return "Erro ao listar mensagens: usuário(a) fora de um canal!";
  } else {
    PrintMessages(c);
  }

  return "";
}
