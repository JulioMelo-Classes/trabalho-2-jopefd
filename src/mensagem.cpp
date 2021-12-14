#include "mensagem.hpp"

using std::string;

Mensagem::Mensagem() {}

Mensagem::Mensagem(const int& id, const std::string& data_hora,
                   Usuario* usuario, const std::string& conteudo)
    : id_(id),
      data_hora_(data_hora),
      enviada_por_(usuario),
      conteudo_(conteudo) {}

string Mensagem::get_conteudo() const { return conteudo_; }