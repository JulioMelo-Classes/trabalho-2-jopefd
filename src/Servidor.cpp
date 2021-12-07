#include "Servidor.hpp"

Servidor::Servidor() {}

Servidor::Servidor(const int &id, Usuario *dono, const std::string &nome)
    : id_(id), dono_(dono), nome_(nome) {}

bool Servidor::IsDono(const Usuario *usuario) const {
  return usuario->get_id() == dono_->get_id();
}

unsigned int Servidor::get_id() const { return id_; }

void Servidor::set_id(const unsigned int &id) { id_ = id; }

Usuario *Servidor::get_dono() const { return dono_; }

void Servidor::set_dono(Usuario *dono) { dono_ = dono; }

std::string Servidor::get_nome() const { return nome_; }

void Servidor::set_nome(const std::string &nome) { nome_ = nome; }

std::string Servidor::get_descricao() const { return descricao_; }

void Servidor::set_descricao(const std::string &descricao) {
  descricao_ = descricao;
}

std::string Servidor::get_codigo_convite() const { return codigo_convite_; }

void Servidor::set_codigo_convite(const std::string &codigo_convite) {
  codigo_convite_ = codigo_convite;
}