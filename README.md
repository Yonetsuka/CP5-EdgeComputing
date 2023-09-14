# Guia para Implantação de Contêineres Docker e Execução de Health Check
Este repositório fornece instruções passo a passo sobre como implantar contêineres Docker em uma máquina virtual e como executar um health check usando o Postman.

*Observação: Devido a problemas técnicos, foi utilizado em uma maquina local para instalação do dockers e do git*

# Passo 1

Instale a maquina virtual VMware e imagem do ubunto 22.04 LTS

# Passo 2

Abrir o VMware e criar uma maquina virtual nova usando a imagem do ubuntu.(Não esqueçer de deixar a conexão bridged)

# Passo 3

Instalar o software do postman

# Passo 4

Fazer o download dos comando do github fiware descomplicado pelo Fabio Caprini e importar para o postman

# Passo 5

Executar a máquina virtual e abrir o terminal de comando

# Passo 6

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

# Passo 7

Ao subir os containers, abrir o postman e executar o comando de health check, colocando o IP da máquina virtual no url. Ao fazer isso, o postman irá receber uma mensagem sinalizando que os containers está ativo.
