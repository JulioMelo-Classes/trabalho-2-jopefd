#include "executor.hpp"

#include <iostream>
#include <istream>
#include <ostream>
#include <queue>
#include <sstream>

using namespace std;

// Função de apoio que recebe um istringstream e
// ler todo texto restante até o fim da linha
string RestoDe(istringstream &ss) {
  string resto;
  getline(ss, resto, '\0');  // ler o resto da linha
  if (resto != "" && (resto[0] == ' ' || resto[0] == '\t')) {
    resto = resto.substr(1);  // o primeiro caractere é um espaço, descartar
  }
  return resto;
}

// Construtor. Recebe uma referência ao sistema que vai operar
// Guarda o seu endereço para executar as operações.
Executor::Executor(Sistema &sistema) {
  this->sair = false;
  this->sistema = &sistema;
}

// Inicia o processamento dos comentos.
// Esse método recebe por exemplo o "cin" e o "cout" no main
// Dessa forma ele faz o necessário para ler 1 comando por linha e
// o processar corretamente, colocando no stream de saída o resultado de cada
// um.
void Executor::iniciar(istream &inputStream, ostream &outputStream) {
  string linha, saida;
  this->sair = false;
  while (!this->sair) {
    if (std::getline(inputStream, linha)) {
      saida = processarLinha(linha);
      outputStream << saida << endl;
    }
  }
}

// Método responsável por processar cada linha, capturando o nome do comando
// e seus parâmetros em variáveis e executar o método correspondente no sistema
string Executor::processarLinha(string linha) {
  istringstream buf(linha);
  string nomeComando;
  buf >> nomeComando;

  if (nomeComando.empty()) {
    return "Comando Inválido <vazio>";
  }

  if (nomeComando == "quit") {
    this->sair = true;
    return sistema->Quit();
  }

  else if (nomeComando == "create-user") {
    string email, senha, nome;
    buf >> email;
    buf >> senha;
    nome = RestoDe(buf);
    return sistema->CreateUser(nome, email, senha);
  }

  else if (nomeComando == "delete-user") {
    string email, senha;
    buf >> email;
    buf >> senha;
    return sistema->DeleteUser(email, senha);
  }

  else if (nomeComando == "login") {
    string email, senha;
    buf >> email;
    buf >> senha;
    return sistema->Login(email, senha);
  }

  int id;
  if (buf >> id) {
    if (nomeComando == "disconnect") {
      return sistema->Disconnect(id);
    }

    else if (nomeComando == "create-server") {
      string nome;
      buf >> nome;
      return sistema->CreateServer(id, nome);
    }

    else if (nomeComando == "set-server-desc") {
      string nome, descricao;
      buf >> nome;
      descricao = RestoDe(buf);
      return sistema->SetServerDesc(id, nome, descricao);
    }

    else if (nomeComando == "set-server-invite-code") {
      string nome, codigo;
      buf >> nome;
      buf >> codigo;
      return sistema->SetServerInviteCode(id, nome, codigo);
    }

    else if (nomeComando == "list-servers") {
      return sistema->ListServers(id);
    }

    else if (nomeComando == "remove-server") {
      string nome;
      buf >> nome;
      return sistema->RemoveServer(id, nome);
    }

    else if (nomeComando == "enter-server") {
      string nome, codigo;
      buf >> nome;
      buf >> codigo;
      return sistema->EnterServer(id, nome, codigo);
    }

    else if (nomeComando == "leave-server") {
      string nome;
      buf >> nome;
      return sistema->LeaveServer(id, nome);
    }

    else if (nomeComando == "list-participants") {
      return sistema->ListParticipants(id);
    }

    else if (nomeComando == "list-channels") {
      return sistema->ListChannels(id);
    }

    else if (nomeComando == "create-channel") {
      string nome;
      buf >> nome;
      return sistema->CreateChannel(id, nome);
    }

    else if (nomeComando == "remove-channel") {
      string nome;
      buf >> nome;
      return sistema->RemoveChannel(id, nome);
    }

    else if (nomeComando == "enter-channel") {
      string nome;
      buf >> nome;
      return sistema->EnterChannel(id, nome);
    }

    else if (nomeComando == "leave-channel") {
      return sistema->LeaveChannel(id);
    }

    else if (nomeComando == "send-message") {
      string mensagem;
      mensagem = RestoDe(buf);
      return sistema->SendMessage(id, mensagem);
    }

    else if (nomeComando == "list-messages") {
      return sistema->ListMessages(id);
    } else {
      return "Comando não reconhecido [" + nomeComando + "]";
    }
  } else {
    return "Comando precisa ser precedido de um id [" + nomeComando + "]";
  }
}
