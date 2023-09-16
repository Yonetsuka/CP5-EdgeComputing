# Sprint 3 Challenge IBM
# Membros:
- Allan Von Ivanov RM: 98705
- Cássio Yonetsuka RM: 99678
- Guilherme Braziolli RM: 98237
- Lourenzo Ramos RM: 99951
- Matheus Cavasini RM: 97722

# IOT e Fiware
A palavra IOT vem de Internet of Things, que por sua vez significa internet das coisas. Esse conceito se refere auma rede de objetos fisicos, dispositivos, máquinas e outros itens que estão conectados a internet coletar, transmitir e trocar dados entre si e com outros sistemas de computação. Quanto ao Fiware, ele é uma plataforma com o código aberto para ajudar inegrar e gerenciar dados IOT. Seus componentes mais importantes são Context Broker e o IOT agent. O Broker serve para armazenar e gerenciar os dados enquanto o IOT agent facilitam a comunicação com os dispositivos, podendo usar vários protocolos no processo, como o MQTT e o ORION.

# Objetivo do repositório
Neste repositório, estará sendo mostrado o como subir um servidor utilizando o dockers e o repositório do professor Fabio Cabrini. Haverá duas formas, sendo uma com o auxilio do VMware e a outra utilizando a máquina local.

# Guia para Implantação de Contêineres Docker e Execução de Health Check **(Máquina Virtual/VMware)**
Este repositório fornece instruções passo a passo sobre como implantar contêineres Docker em uma máquina virtual e como executar um health check usando o Postman.

*Observação: Devido a problemas técnicos, foi utilizado em uma maquina local para instalação do dockers e do git*

## Passo 1

Instale a maquina virtual VMware e imagem do ubunto 22.04 LTS

## Passo 2

Abrir o VMware e criar uma maquina virtual nova usando a imagem do ubuntu.(Não esqueçer de deixar a conexão bridged)

## Passo 3

Instalar o software do postman

## Passo 4

Fazer o download dos comando do github fiware descomplicado pelo Fabio Caprini e importar para o postman

## Passo 5

Executar a máquina virtual e abrir o terminal de comando

## Passo 6

Ao abrir o terminal, executar os comandos:  
- **Comandos para pegar o ip da máquina virtual e instalar o git**
  - sudo apt-get install net-tools
  - ifconfifg
  - sudo apt install git
- **Comandos para instalar o docker**
  - sudo apt update && apt upgrade
  - sudo apt install apt-transport-https curl gnupg-agent ca-certificates software-properties-common -y
  - curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
  - sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu focal stable"
  - sudo apt install docker-ce docker-ce-cli containerd.io -y  
- **Comandos para subir os containers**
  - git clone https://github.com/fabiocabrini/fiware
  - cd fiware
  - sudo docker compose up -d
  - sudo docker stats

## Passo 7

Ao subir os containers, abrir o postman e executar o comando de health check, colocando o IP da máquina virtual no url. Ao fazer isso, o postman irá receber uma mensagem sinalizando que os containers está ativo.

# Guia para Implantação de Contêineres Docker e Execução de Health Check **(Máquina Local)**

## Passo 1

Tenha o gitBash, o software do postman e o docker desktop instalados e funcionando no seu computador

## Passo 2
Abra o prompt de comando e selecione a pasta que deseja utilizar

## Passo 3
Execute os seguintes comandos:
- git clone https://github.com/fabiocabrini/fiware
- cd fiware
- docker compose up -d

## Passo 4
Após isso, vá até o repositório do fiware do professor Cabrini e baixe a collection do postman importe para o software

## Passo 5
Por fim, abra as três pastas e procure a opção de Health Check, substitual URL por localhost (isso só funcionará caso o postman esteja baixado) e execute. Ao fazer isso, o postman irá receber uma mensagem sinalizando que os containers está ativo.
