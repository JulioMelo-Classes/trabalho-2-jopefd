#ifndef CONCORDO_SISTEMA_H_
#define CONCORDO_SISTEMA_H_

#include <cstddef>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "servidor.hpp"

class Sistema {
 private:
  /** Lista de servidores do sistema */
  std::vector<Servidor> servidores_;

  /** Variável que guarda o id do próximo servidor a ser cadastrado */
  std::size_t prox_id_servidor_;

  /** Lista de usuário(a)s do sistema */
  std::vector<Usuario *> usuarios_;

  /** Variável que guarda o id do próximo usuário(a) a ser cadastrado(a) */
  std::size_t prox_id_usuario_;

  /** Mapa do id de usuário(a) para os ids dos servidor e canal logados */
  std::map<int, std::pair<unsigned int, unsigned int>> usuarios_logados_;

 private:
  /**
   * \brief
   *
   * \param usuario_it
   *
   * \return
   */
  bool Exists(const std::vector<Usuario *>::iterator &usuario_it) const;

  /**
   * \brief
   *
   * \param servidor_it
   *
   * \return
   */
  bool Exists(const std::vector<Servidor>::iterator &servidor_it) const;

  /**
   * \brief
   *
   * \param servidor_it
   * \param canal_it
   *
   * \return
   */
  bool Exists(const std::vector<Servidor>::iterator &servidor_it,
              const std::vector<CanalTexto>::iterator &canal_it) const;

  /**
   * \brief Busca por um usuário via id.
   *
   * \param id Id de usuário informado
   *
   * \return Ponteiro para o usuário informado, caso seja encontrado; nullptr,
   * caso contrário
   */
  std::vector<Usuario *>::iterator FindUser(const int &id_usuario);

  /**
   * \brief Busca por um usuário via email.
   *
   * \param email Email de usuário informado
   *
   * \return Ponteiro para o usuário informado, caso seja encontrado; nullptr,
   * caso contrário
   */
  std::vector<Usuario *>::iterator FindUser(const std::string &email);

  /**
   * \brief Verifica se o usuário informado está logado.
   *
   * \param id_usuario Id de usuário informado
   * \return true, caso o usuário informado está logado; false, caso
   * contrário.
   */
  bool Logged(const std::vector<Usuario *>::iterator &usuario_it) const;

  /**
   * \brief Verifica se o usuário informado está logado.
   *
   * \param usuario Ponteiro para o usuário informado
   *
   * \return true, caso o usuário informado está logado; false, caso
   * contrário.
   */
  bool Logged(const Usuario *usuario) const;

  /**
   * \brief
   *
   * \param id_usuario
   *
   * \return Servidor*
   */
  std::vector<Servidor>::iterator FindServer(
      const std::vector<Usuario *>::iterator &usuario_it);

  /**
   * \brief
   *
   * \param id_servidor
   * \return std::vector<Servidor>::iterator
   */
  std::vector<Servidor>::iterator FindServer(const int &id_servidor);

  /**
   * \brief Busca por um servidor via nome.
   *
   * \param nome_servidor Nome do servidor a ser buscado
   *
   * \return Ponteiro para o servidor informado, caso seja encontrado;
   * nullptr, caso contrário
   */
  std::vector<Servidor>::iterator FindServer(const std::string &nome_servidor);

  /**
   * \brief Adiciona um servidor ao sistema.
   *
   * Este método atualiza o vetor servidores_ e o contador prox_id_servidor_.
   *
   * \param servidor Servidor a ser adicionado ao sistema
   */
  void AddServer(const std::string &nome_servidor,
                 const std::vector<Usuario *>::iterator &usuario_it);

  void EraseServer(const std::vector<Servidor>::iterator &servidor_it);

  /**
   * \brief Adiciona um usuário ao sistema.
   *
   * \param nome Nome do usuário a ser adicionado ao sistema
   * \param email Email do usuário a ser adicionado ao sistema
   * \param senha Senha do usuário a ser adicionado ao sistema
   */
  void AddUser(const std::string &nome, const std::string &email,
               const std::string &senha);

  /**
   * \brief
   *
   * \param usuario_it
   */
  void AddLoggedUser(const std::vector<Usuario *>::iterator &usuario_it);

  /**
   * \brief
   *
   * \param id_usuario
   */
  void RemoveLoggedUser(const int &id_usuario);

  /**
   * \brief
   *
   * \param usuario_it
   */
  void RemoveLoggedUser(const std::vector<Usuario *>::iterator &usuario_it);

  /**
   * \brief
   *
   * \param id_usuario
   * \param servidor
   * \param codigo_convite
   */
  void AddParticipant(const int &id_usuario, Servidor *servidor,
                      const std::string &codigo_convite);

  /**
   * \brief
   *
   * \param id_usuario
   * \param servidor
   */
  void RemoveParticipant(const int &id_usuario, Servidor *servidor);

  /**
   * \brief
   *
   * \param servidor_it
   */
  void PrintParticipants(
      const std::vector<Servidor>::iterator &servidor_it) const;

  /**
   * \brief
   *
   * \param canais_texto
   */
  void PrintChannels(const std::vector<Servidor>::iterator &servidor_it) const;

  /**
   * \brief
   *
   * \param canal_it
   */
  void PrintMessages(const std::vector<CanalTexto>::iterator &canal_it) const;

  /**
   * \brief
   *
   * \param senha
   * \param usuario_it
   * \return true
   * \return false
   */
  bool CorrectPassword(
      const std::string &senha,
      const std::vector<Usuario *>::iterator &usuario_it) const;

  /**
   * \brief
   *
   */
  void PrintServers() const;

  /**
   * \brief
   *
   * \param codigo_convite
   * \param servidor_it
   * \return true
   * \return false
   */
  bool CorrectInviteCode(
      const std::string &codigo_convite,
      const std::vector<Servidor>::iterator &servidor_it) const;

  /**
   * \brief
   *
   * \param servidor_it
   * \param usuario_it
   */
  void AddParticipant(std::vector<Servidor>::iterator &servidor_it,
                      std::vector<Usuario *>::iterator &usuario_it);
  /**
   * \brief
   *
   * \param usuario_it
   * \param servidor_it
   * \return true
   * \return false
   */
  bool Participant(const std::vector<Usuario *>::iterator &usuario_it,
                   const std::vector<Servidor>::iterator &servidor_it) const;

  /**
   * \brief
   *
   * \param usuario_it
   * \param servidor_it
   */
  void RemoveParticipant(const std::vector<Usuario *>::iterator &usuario_it,
                         const std::vector<Servidor>::iterator &servidor_it);

  /**
   * \brief
   *
   * \param servidor_it
   * \param usuario_it
   * \return true
   * \return false
   */
  bool Owner(const std::vector<Servidor>::iterator &servidor_it,
             const std::vector<Usuario *>::iterator &usuario_it) const;

  /**
   * \brief Set the Description object
   *
   * \param servidor_it
   * \param descricao
   */
  void SetDescription(const std::vector<Servidor>::iterator &servidor_it,
                      const std::string &descricao);

  /**
   * \brief Set the Invite Code object
   *
   * \param servidor_it
   * \param codigo_convite
   */
  void SetInviteCode(const std::vector<Servidor>::iterator &servidor_it,
                     const std::string &codigo_convite);

  /**
   * \brief
   *
   * \param servidor_it
   * \param nome_canal
   * \return std::vector<CanalTexto>::iterator
   */
  std::vector<CanalTexto>::iterator FindChannel(
      const std::vector<Servidor>::iterator &servidor_it,
      const std::string &nome_canal);

  std::vector<CanalTexto>::iterator FindChannel(
      const std::vector<Servidor>::iterator &servidor_it,
      const std::vector<Usuario *>::iterator &usuario_it);

  void AddChannel(const std::vector<Servidor>::iterator &servidor_it,
                  const std::vector<Usuario *>::iterator &usuario_it,
                  const std::string &nome_canal);

  void DeleteUser(const std::vector<Usuario *>::iterator &usuario_it);

  std::string Name(const std::vector<Usuario *>::iterator &usuario_it) const;

  void LeaveChannel(const std::vector<Usuario *>::iterator &usuario_it);

  void SendMessage(const std::vector<Usuario *>::iterator &usuario_it,
                   const std::vector<Servidor>::iterator &servidor_it,
                   const std::vector<CanalTexto>::iterator &canal_it,
                   const std::string &mensagem);

 public:
  /**
   * \brief Construct a new Sistema object
   */
  Sistema();

  /*! Encerra o funcionamento do Concordo, o programa termina ao executar
     este comando.
      @return uma string com a mensagem "Saindo.."
  */
  std::string Quit();

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

  /*! Remove um servidor da lista de servidores, retornando uma mensagem de
     sucesso ou de erro em caso de falha.
      @param id  um id válido de algum usuário cadastrado e logado no sistema.
      @param nome um nome válido de um servidor cadastrado no sistema.
      @return "Servidor <nome> removido com sucesso" ou uma mensagem de erro
     em caso de falha.
  */
  /**
   * \brief
   *
   * \param id_usuario
   * \param nome_servidor
   * \return std::string
   */
  std::string RemoveServer(const int &id_usuario,
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

  /*!
      @param id um id válido de um usuário logado no sistema.
      @param nome um nome válido de um servidor cadastrado no sistema.
      @param codigo um código de acordo com o comando set-server-invite-code.
      @return "Código de convite modificado com sucesso" ou uma mensagem de
     erro em caso de falha.
  */

  /**
   * \brief Modifica o código de convite do servidor no sistema.
   *
   * \param id_usuario
   * \param nome_servidor
   * \param codigo_convite
   *
   * \return Retorna uma  mensagem de sucesso ou de erro em caso de falha.
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

  /**
   * \brief
   *
   * \param id_usuario
   * \return std::string
   */
  std::string ListServers(const int &id_usuario);

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

  /**
   * \brief
   *
   * \param id_usuario
   * \param nome_servidor
   * \param codigo_convite
   * \return std::string
   */
  std::string EnterServer(const int &id_usuario,
                          const std::string &nome_servidor,
                          const std::string &codigo_convite);

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

  /**
   * \brief
   *
   * \param id_usuario
   * \param nome_servidor
   * \return std::string
   */
  std::string LeaveServer(const int &id_usuario,
                          const std::string &nome_servidor);

  /*! Lista os participantes presentes no servidor que o usuário com o id
     passado está visualizando. Retorna uma string vazia em caso de sucesso ou
     uma mensagem de erro em caso de falha.
          @param id um id válido de algum usuário cadastrado e logado no
     sistema.
          @return Uma string vazia em caso de sucesso ou uma mensagem de erro
     em caso de falha.
  */

  /**
   * \brief
   *
   * \param id_usuario
   * \return std::string
   */
  std::string ListParticipants(const int &id_usuario);

  /*!	Lista os canais do servidor que o usuário com o id passado está
     vizualizando. Retorna uma string vazia em caso de sucesso o uma mensagem
     de erro no caso de falha.
          @param id um id válido de algum usuário cadastrado e logado no
     sistema.
          @return uma string vazia em caso de sucesso ou uma mensagem de erro
     em caso de falha.
  */

  /**
   * \brief
   *
   * \param id_usuario
   * \return std::string
   */
  std::string ListChannels(const int &id_usuario);

  /**
   * \brief Cria um canal em um servidor em um dado servidor.
   *
   * O canal criado é do tipo dado (voz ou texto) de acordo com o comando
   * create-channel.
   *
   * \param id_usuario Id de um usuário cadastrado e logado no sistema
   * \param nome_canal Nome do canal o qual o usuário solicita criar
   *
   * \return A mensgem "Sucesso: canal " + nome_canal + " criado!", em caso de
   * sucesso; uma mensagem de erro, caso contrário
   */
  std::string CreateChannel(const int &id_usuario,
                            const std::string &nome_canal);

  /**
   * \brief Adiciona o usuário com um dado id em um canal
   *
   * \param id_usuario Id de um usuário cadastrado e logado no sistema
   * \param nome_canal Nome do canal no qual o usuário solicita entrar
   *
   * \return std::string
   */
  std::string EnterChannel(const int &id_usuario,
                           const std::string &nome_canal);

  /**
   * \brief Retira o usuário com um dado id saia do canal que está sendo
   * visualizado atualmente.
   *
   * Ao sair de um canal o sistema deve atualizar o atributo
   * Sistema::usuarios_logados_ de forma que o usuário não esteja mais
   * vizualizando qualquer canal.
   *
   * \param id Id de um usuário cadastrado e logado no sistema que está
   * visualizando um canal
   *
   * \return A mensagem "Sucesso: usuário(a) " + email_usuario + " saiu do canal
   * " + nome_canal + "!", em caso de sucesso; uma mensagem de erro, caso
   * contrário
   */
  std::string LeaveChannel(const int &id);

  /**
   * \brief Remove um canal do sistema, se ele existir.
   *
   * \param id_usuario Um id válido de algum usuário cadastrado e logado no
   * sistema.
   * \param nome_canal O nome do canal a ser removido
   *
   * \return A mensagem "Sucesso: canal " + nome_canal + " removido!" em caso
   * de sucesso; uma mensagem de erro, caso contrário
   */
  std::string RemoveChannel(const int &id_usuario,
                            const std::string &nome_canal);

  /**
   * \brief
   *
   * \param servidor_it
   * \param canal_it
   * \return std::string
   */
  void RemoveChannel(const std::vector<Servidor>::iterator &servidor_it,
                     const std::vector<CanalTexto>::iterator &canal_it);

  /**
   * \brief Envia uma mensagem no canal em que o usuário com id passado está
   * visualizando.
   *
   * \param id_usuario Um id válido de algum usuário cadastrado e logado no
   * sistema.
   * \param mensagem A mensagem que deve ser enviada
   *
   * \return Uma string vazia em caso de sucesso; uma mensagem de erro em caso
   * de falha
   */
  std::string SendMessage(const int &id_usuario, const std::string &mensagem);

  /**
   * \brief Lista as mensagem no canal que o usuário com id passado está
   * visualizando.
   *
   * \param id_usuario Um id válido de algum usuário cadastrado e logado no
   * sistema
   *
   * \return Uma string vazia em caso de sucesso ou uma mensagem de erro em caso
   * de falha.
   */
  std::string ListMessages(const int &id_usuario);
};

#endif
