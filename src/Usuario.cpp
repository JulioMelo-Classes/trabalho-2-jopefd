#include "Usuario.hpp"

using std::string;

Usuario::Usuario() {}

Usuario::Usuario(const unsigned int &id, const string &nome,
                 const string &email, const string &senha)
    : id_(id), nome_(nome), email_(email), senha_(senha) {}

unsigned int Usuario::get_id() const { return id_; }

void Usuario::set_id(const unsigned int &id) { id_ = id; }

string Usuario::get_nome() const { return nome_; }

void Usuario::set_nome(const string &nome) { nome_ = nome; }

string Usuario::get_email() const { return email_; }

void Usuario::set_email(const string &email) { email_ = email; }

string Usuario::get_senha() const { return senha_; }

void Usuario::set_senha(const string &senha) { senha_ = senha; }