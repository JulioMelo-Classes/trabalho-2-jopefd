#include <string>

class Usuario {
 private:
  unsigned int id_;

  std::string nome_;

  std::string email_;

  std::string senha_;

 public:
  Usuario();

  Usuario::Usuario(const unsigned int &id, const std::string &nome,
                   const std::string &email, const std::string &senha);

  unsigned int get_id() const;

  void set_id(const unsigned int &id);

  std::string get_nome() const;

  void set_nome(const std::string &nome);

  std::string get_email() const;

  void set_email(const std::string &email);

  std::string get_senha() const;

  void set_senha(const std::string &senha);
};