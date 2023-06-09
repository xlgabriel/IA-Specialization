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

#echo "Arrancando un agente de cónsul"
#consul agent -ui -dev -bind=192.168.100.6 -client=0.0.0.0 -data-dir=.



