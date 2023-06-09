#!/bin/bash

echo "Actualizando linux..."
sudo apt update
echo "Instalando Consul ..."
echo "Primera parte ..."
wget -O- https://apt.releases.hashicorp.com/gpg | sudo gpg --dearmor -o /usr/share/keyrings/hashicorp-archive-keyring.gpg
echo "Primera parte Completada"
echo "deb [signed-by=/usr/share/keyrings/hashicorp-archive-keyring.gpg] https://apt.releases.hashicorp.com $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/hashicorp.list
echo "Segunda parte Completada"
echo "Instalando Consul Ultimo ..."
sudo apt update && sudo apt install consul
echo "Consul Intalado Completado"
consul -v
echo "-------PARTE CONSUL INSTALADA------------"
echo "-------INICIA INSTALACION LXD------------"
sudo apt-get install lxd-installer -y
newgrp lxd
echo "------fin instalacion LXD------------"
echo "inicializando lxd ....."
lxd init --auto
echo "Instalación de servidores de backend corriendo apache"
lxc launch ubuntu:18.04 web1
echo "Web 1 completo"
lxc launch ubuntu:18.04 web2
echo "Web 2 completo"
echo "Ingresando a shell web1"
echo "Creando haproxy"
lxc launch ubuntu:18.04 haproxy
echo "Creacion haproxy completa"

#echo "Arrancando un agente de cónsul"
#consul agent -ui -dev -bind=192.168.100.6 -client=0.0.0.0 -data-dir=.


