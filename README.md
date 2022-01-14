# Base para a atividade 02 de LP1

Use esse esqueleto de classes para iniciar a terceira atividade.

Existe um executor que faz a interpretação dos comandos e executa o método correto do sistema.

## Para compilar

Com makefiles:
```console
mkdir build
make
```

Com cmake:
```console
mkdir build
cd build
cmake ..
cmake --build .
```

Escolha uma das duas formas de build e ignore a outra.

## Para executar
Você pode rodar o sistema e em logo depois digitar os comandos seguidos de ENTER
```console
cd build
./concordo
```

Ou pode criar um arquivo de texto com uma lista de comandos (um por linha) e executar o sistema redirecionando esse arquivo como entrada padrão:
```console
cd build
./concordo < ../data/script_comandos.txt
```

# Avaliação
## Funcionalidades
- A1.2 ok
- A1.3 25%
Aqui você precisava processar se o usuárioi está em algum canal/servidor e as mensagens enviadas por ele
- A1.4 ok
- A2.1 ok
- A2.2 ok
- A2.3 ok
- A2.4 ok
- A2.5 ok
- A2.6 50%
Aqui você precisava prrocessar usuários logados que estejam possivelmente no servidor
- A2.7 ok
- A2.8 ok
- A2.9 10%
Embora a implementação esteja muito boa, você violou a restrição do trabalho.
- B1.1 10%
Embora a implementação esteja muito boa, você violou a restrição do trabalho.
- B1.2 ok
- B1.3 ok
- B1.4 ok
- B1.5 50%
Aqui você precisava prrocessar usuários logados que estejam possivelmente no canal
- B2.1 ok
- B2.2 10%
Embora a implementação esteja muito boa, você violou a restrição do trabalho.

## Classes
- Servidor 80%
Vou tirar alguns pontos uma vez que a restrição relativa ao retorno de containers foi violada
- Canal 80%
Vou tirar alguns pontos uma vez que a restrição relativa ao retorno de containers foi violada
- Mensagem ok

## Boas Práticas
- Documentação nok
- Testes nok
Aqui a ideia era que você enviasse também um conjunto de arquivos de teste mostrando o que foi feito.
- Organização ok

## Observações
A implementação ficou muito boa como eu te falei, no entanto tente delegar um pouco mais para os objetos o trabalho de manipular seus dados. Métodos como o Sistema::PrintMessages deveria claramente ficar dentro de canal, que por sua vez deveria ser acessado por um método em servidor.