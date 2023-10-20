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

# MyMqtt
Este é um aplicativo para celular que usa o protocolo mqtt, e pode ser usado para enviar e receber mensagens em uma porta de um endereço de broker, broker este que funciona como servidor que gerencia a troca de mensagens. Ele será usado no projeto como uma forma de estabelecer uma comunicação entre o usuário e o esp 32 desde que possua internet

# Explicando o código cp
Primeiro, deve se importar as bibliotecas WiFi e PubSubClient.
Depois se define os tópicos, que é a principal forma para o publisher e o subscriber trocarem mensagens. Também será necessário definir uma id no código (no caso, 112). 
Em seguida, se coloca o nome da rede e senha que deseja conectar o esp, junto com o endereço e porta do broker. Também deve se criar o objeto Esp e instanciar o MQTT passando o objeto do ESP como parâmetro.
Na função de setup,  se coloca funções que irão fazer o Esp se conectar a internet, identificar o broker e também se inicia o dht.
Na função loop, foram passadas funções que irão pegar os valores dos sensores de umidade, temperatura e luminosidade que irão converte-los para string e então serão publicados nos tópicos. Também será passada uma função que irá verificar constantemente se o esp não perdeu conexão com o broker ou a internet.

# Montagem do ESP
Ao montar o esp, conectou-se 5, 4 e 23 com os leds Verde, Amarelo e Vermelho. O LCD teve as portas sda e scl conectadas nas portas 21 e 22 e o gnd e vcc no terra e no 3.3v. O DHT foi conectado a porta 15 e ao terra e 3.3v também. O fotoresistor foi conectado ao terra, o 3.3 volts e a porta 2. O buzzer foi conectado ao terra e porta 25.

## No final da montagem, ele deverá ficar parecido com isso (Imagem pega do Wokwi)
![Imagem do Esp montado](https://user-images.githubusercontent.com/127115211/277034184-6a5be623-f8e3-4121-8caa-e30206cbec09.png)

### Links usados 

- Link de video ensinando a subir na máquina local: https://www.youtube.com/watch?v=MFZwQOKKtlI
- Link do gitbash: https://git-scm.com/downloads
- Link do VMware : https://www.vmware.com/br/products/workstation-player.html
- Link do Ubuntu: https://ubuntu.com/download/desktop
- Link do docker: https://www.docker.com/products/docker-desktop/
- Link do repositório do professor: https://github.com/fabiocabrini/fiware
- Link do Wokwi: https://wokwi.com/projects/378106750832946177
