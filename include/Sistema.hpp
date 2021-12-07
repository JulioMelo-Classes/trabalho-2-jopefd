#ifndef CONCORDO_SISTEMA_H_
#define CONCORDO_SISTEMA_H_

#include <cstddef>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Servidor.hpp"
#include "Usuario.hpp"

// Sistema deve concentrar todas as operações do Concordo
class Sistema {
 private:
  std::vector<Usuario *> usuarios_;

  std::vector<Servidor> servidores_;

  std::map<int, std::pair<unsigned int, unsigned int>> usuarios_logados_;

  std::size_t prox_id_servidor_;

  std::size_t prox_id_usuario_;

  /**
   * \brief Busca por um usuário via email.
   *
   * \param email Email de usuário informado
   *
   * \return Ponteiro para o usuário informado, caso seja encontrado; nullptr,
   * caso contrário
   */
  Usuario *FindUser(const std::string &email);

  /**
   * \brief Busca por um usuário via id.
   *
   * \param id Id de usuário informado
   *
   * \return Ponteiro para o usuário informado, caso seja encontrado; nullptr,
   * caso contrário
   */
  Usuario *FindUser(const int &id);

  /**
   * \brief Verifica se o usuário informado está logado.
   *
   * \param id_usuario Id de usuário informado
   * \return true, caso o usuário informado está logado; false, caso
   * contrário.
   */
  bool IsLogged(const int &id_usuario) const;

  /**
   * \brief Verifica se o usuário informado está logado.
   *
   * \param usuario Ponteiro para o usuário informado
   *
   * \return true, caso o usuário informado está logado; false, caso
   * contrário.
   */
  bool IsLogged(const Usuario *usuario) const;

  /**
   * \brief Busca por um servidor via nome.
   *
   * \param nome_servidor Nome do servidor a ser buscado
   *
   * \return Ponteiro para o servidor informado, caso seja encontrado;
   * nullptr, caso contrário
   */
  Servidor *FindServer(const std::string &nome_servidor);

  /**
   * \brief Adiciona um servidor ao sistema.
   *
   * Este método atualiza o vetor servidores_ e o contador prox_id_servidor_.
   *
   * \param servidor Servidor a ser adicionado ao sistema
   */
  void AddServer(Usuario *dono, const std::string &nome_servidor);

  void EraseServer(const Servidor *servidor);

  /**
   * \brief Adiciona um usuário ao sistema.
   *
   * \param nome Nome do usuário a ser adicionado ao sistema
   * \param email Email do usuário a ser adicionado ao sistema
   * \param senha Senha do usuário a ser adicionado ao sistema
   */
  void AddUser(const std::string &nome, const std::string &email,
               const std::string &senha);

  void AddLoggedUser(const Usuario *usuario);

  void RemoveLoggedUser(const int &id_usuario);

  void RemoveLoggedUser(const Usuario *usuario);

 public:
  Sistema();

  /*! Encerra o funcionamento do Concordo, o programa termina ao executar
     este comando.
      @return uma string com a mensagem "Saindo.."
  */
  std::string quit();

  /**
   * \brief Cria um usuário e retorna uma string de erro/sucesso.
   *
   * \param email O email do usuário informado no comando create-user
   * \param senha A senha passada ao comando create-user
   * \param nome O nome do usuário (com espaços) passado ao comando
   * create-user
   *
   * \return Uma string contendo uma mensagem de erro ou "Usuário criado!"
   */
  std::string CreateUser(const std::string &email, const std::string &senha,
                         const std::string &nome);

  /**
   * \brief Remove as informações do cadastro de um usuário do sistema.
   *
   * Só deve ser possível se o usuário não estiver logado, demais
   * especificidades deste método, veja o documento de especificação.
   *
   * \param email O email do usuário, passado no comando login
   * \param senha A senha correspondente àquele usuário
   *
   * \return Uma string contendo uma mensagem de erro ou "Usuário(a) <email>
   * removido(a) do sistema!"
   */
  std::string DeleteUser(const std::string &email, const std::string &senha);

  /**
   * \brief Realiza o login do usuário com email e senha.
   *
   * Retorna uma string de erro ou uma mensagem login bem sucedido. Quando um
   * usuário loga o sistema deve adicionar o usuário na tabela
   * Sistema::usuariosLogados.
   *
   * \param email O email do usuário, passado no comando login
   * \param senha A senha correspondente àquele usuário
   *
   * \return Uma string contendo uma mensagem de erro ou "Logado como
   * <email>!"
   */
  std::string Login(const std::string &email, const std::string &senha);

  /**
   * \brief Desconecta um usuário do sistema pelo seu id.
   *
   * \param id Um id válido de um usuário logado no sistema
   *
   * \return A mensagem "Sucesso: usuário desconectado!", caso a operação seja
   * realizada, ou "Erro ao desconectar: usuário não logado!", caso contrário.
   */
  std::string Disconnect(const int &id_usuario);

  /*! Cria um novo servidor no sistema e o adiciona na lista de servidores.
      @param id
      @param nome o nome do servidor de acordo com o comando create-server.
      @return "Servidor <nome> criado" quando o servidor for criado ou uma
     mensagem de erro em caso de falha.
  */

  /**
   * \brief Cria um novo servidor no sistema.
   *
   * A função deve retornar uma string "Servidor <nome> criado" ou uma
   * mensagem de erro caso o servidor não possa ser criado por algum motivo.
   *
   * \param id_usuario Um id válido de um usuário logado no sistema
   * \param nome O nome do servidor de acordo com o comando create-server.
   *
   * \return A mensagem "Sucesso: servidor criado!", caso a operação seja
   * realizada, ou "Erro ao desconectar: <causa>", caso contrário.
   */
  std::string CreateServer(const int &id_usuario,
                           const std::string &nome_servidor);

  /**
   * \brief Modifica a descrição do servidor informado.
   *
   * A função deve retornar "Descrição do servidor <nome> modificada!" ou uma
   * mensagem de erro em caso de falha.
   *
   * \param id_usuario Id do dono do servidor
   * \param nome_servidor Nome do servidor
   * \param descricao Nova descrição
   *
   * \return A mensagem "Sucesso: descrição do servidor alterada!", caso a
   * operação seja realizada, ou "Erro ao mudar descrição do servidor:
   * <causa>", caso contrário.
   */
  std::string SetServerDesc(const int &id_usuario,
                            const std::string &nome_servidor,
                            const std::string &descricao);

  /*! Modifica o código de convite do servidor no sistema. Retorna uma
     mensagem de sucesso ou de erro em caso de falha.
      @param id um id válido de um usuário logado no sistema.
      @param nome um nome válido de um servidor cadastrado no sistema.
      @param codigo um código de acordo com o comando set-server-invite-code.
      @return "Código de convite modificado com sucesso" ou uma mensagem de
     erro em caso de falha.
  */
  std::string SetServerInviteCode(const int &id_usuario,
                                  const std::string &nome_servidor,
                                  const std::string &codigo_convite);

  /*! Lista os servidores cadastrados no sistema, retorna uma string contendo
     uma mensagem de erro ou uma string vazia no caso de não haver erros.
      @param id_usuario um id válido de algum usuário cadastrado e logado no
     sistema.
      @return uma string vazia ou a string de erro "Usuário não está logado".
  */
  std::string ListServers(const int &id_usuario) const;

  /*! Remove um servidor da lista de servidores, retornando uma mensagem de
     sucesso ou de erro em caso de falha.
      @param id  um id válido de algum usuário cadastrado e logado no sistema.
      @param nome um nome válido de um servidor cadastrado no sistema.
      @return "Servidor <nome> removido com sucesso" ou uma mensagem de erro
     em caso de falha.
  */
  std::string RemoveServer(const int &id_usuario,
                           const std::string &nome_servidor);

  /*! Faz com que o usuário logado com o id dado entre no servidor de nome com
     a senha fornecida (se necessário). Retorna uma mensagem de erro em caso
     de falha ou uma mensagem de sucesso caso contrário. Esse método atualiza
     a tabela Sistema::usuariosLogados com a informação do servidor que o
     usuário com o id está conectado.
      @param id  um id válido de algum usuário cadastrado e logado no sistema.
      @param nome um nome válido de um servidor cadastrado no sistema.
      @param codigo um código de convite para o servidor se necessário ou uma
     string vazia, caso o comando tenha vindo sem código. Veja o comando
     enter-server para mais detalhes.
      @return "Entrou no servidor <nome>" em caso de sucesso ou uma mensagem
     de erro caso contrário.
  */
  std::string EnterServer(const int &id, const std::string &nome,
                          const std::string &codigo);

  /*! Faz com oque o usuário conectado em algum servidor saia do mesmo. Deve
     retornar uma string com uma mensagem de sucesso ou uma mensagem de erro
     caso contrário. No caso que o servidor passado como agumento para este
     método é o mesmo que o servidor em que o usuário está visualizando
     atualmente (usando o valor guardado em Sistema::usuariosLogados) este
     método deve atualizar a tabela Sistema::usuariosLogados, sinalizando que
     o usuário não está mais visualizando aquele servidor.
          @param id um id válido de algum usuário cadastrado e logado no
     sistema.
          @param nome um nome válido de um servidor cadastrado no sistema.
          @return "Saiu do servidor <nome>" ou uma mensagem de erro em caso de
     falha.
  */
  std::string LeaveServer(const int &id, const std::string &nome);

  /*! Lista os participantes presentes no servidor que o usuário com o id
     passado está visualizando. Retorna uma string vazia em caso de sucesso ou
     uma mensagem de erro em caso de falha.
          @param id um id válido de algum usuário cadastrado e logado no
     sistema.
          @return Uma string vazia em caso de sucesso ou uma mensagem de erro
     em caso de falha.
  */
  std::string ListParticipants(const int &id) const;

  /*!	Lista os canais do servidor que o usuário com o id passado está
     vizualizando. Retorna uma string vazia em caso de sucesso o uma mensagem
     de erro no caso de falha.
          @param id um id válido de algum usuário cadastrado e logado no
     sistema.
          @return uma string vazia em caso de sucesso ou uma mensagem de erro
     em caso de falha.
  */
  std::string ListChannels(const int &id) const;

  /*! Cria um canal em um servidor com o nome passado. O canal criado é do
     tipo dado (voz ou texto) de acordo com o comando create-channel. Retorna
     uma mensa
          @param id um id válido de algum usuário cadastrado e logado no
     sistema.
          @param o nome do novo canal, de acordo com o comando create-channel
          @return "Canal <nome> criado!" ou uma mensagem de erro em caso de
     falha.
  */
  std::string CreateChannel(const int &id, const std::string &nome);

  /*! Faz com que o usuário com id dado entre em um canal específico(com seu
     nome e tipo) ao entrar em um canal o sistema deve atualizar a tabela
     Sistema::usuariosLogados com a informação de que o usuário está
     vizualizando o canal em que entrou. Retorna uma mensagem de sucesso ou de
          erro em caso de falha.
          @param id um id válido de algum usuário cadastrado e logado no
     sistema.
          @param o nome do canal que deseja entrar,
          @return "Usuário <email.do.usuario> entrou no canal <nome>" ou uma
     mensagem de erro em caso de falha.
  */
  std::string EnterChannel(const int &id, const std::string &nome);

  /*! Faz com que o usuário com id dado saia do canal que está visualizando
     atualmente. Ao sair de um canal o sistema deve atualizar o attributo
     Sistema::usuariosLogados de forma que o usuário não esteja mais
     vizualizando qualquer canal. A função deve retornar mensagem de sucesso
     ou de erro em caso de falha
          @param id um id válido de algum usuário cadastrado e logado no
     sistema. que o usuário está visualizando, de acordo com o atributo
     Sistema::usuariosLogados.
          @return "Usuário <email.do.usuario> saiu no canal <nome>" ou uma
     mensagem de erro em caso de falha.
  */
  std::string LeaveChannel(const int &id);

  /*! Remove um canal do sistema, se ele existir. Para maiores especificações
     veja o documento do trabalho
      @param id um id válido de algum usuário cadastrado e logado no sistema.
      @param o nome do canal a ser removido
      @return "Canal <nome> removido!" ou uma mensagem de erro em caso de
     falha.
  */
  std::string RemoveChannel(const int &id, const std::string &nome);

  /*! Envia uma mensagem no canal em que o usuáiro com id passado está
     visualizando.
          @param id um id válido de algum usuário cadastrado e logado no
     sistema.
          @param mensagem a mensagem que deve ser enviada.
          @return uma string vazia em caso de sucesso ou uma mensagem de erro
     em caso de falha.
  */
  std::string SendMessage(const int &id, const std::string &mensagem);

  /*! Lista as mensagem no canal que o usuário com id passado está
     visualizando.
          @param id um id válido de algum usuário cadastrado e logado no
     sistema.
          @return uma string vazia em caso de sucesso ou uma mensagem de erro
     em caso de falha.
  */
  std::string ListMessages(const int &id) const;
};

#endif
