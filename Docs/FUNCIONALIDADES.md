# 📘 Documentação Técnica - Simulador de Terminal Rodoviário

Este documento complementa o README principal, trazendo detalhes sobre as **funções implementadas** e os **dados iniciais para teste**.

---

## 🔧 Funções do sistema

### 🚌 Funções de Motoristas
- `cadastrarMotorista()`  
  Cadastra um novo motorista no sistema e salva seus dados no arquivo binário `motoristas.bin`.  
  Dados armazenados: nome, CPF, telefone, número da CNH, etc.  

- `listarMotoristas()`  
  Lê o arquivo `motoristas.bin` e exibe na tela todos os motoristas cadastrados.  

- `buscarMotoristaPorCPF()`  
  Faz a busca de um motorista específico com base no CPF informado.  

- `loginMotorista()`  
  Valida o acesso de um motorista à área restrita, pedindo CPF e senha cadastrada.  

---

### 🚍 Funções de Viagens
- `cadastrarViagem()`  
  Permite registrar uma nova viagem, associando a um motorista já existente.  
  Dados armazenados: destino, data, horário, número do ônibus, etc.  

- `listarViagens()`  
  Exibe todas as viagens cadastradas no arquivo `viagens.bin`.  

- `buscarViagemPorCodigo()`  
  Procura uma viagem específica a partir de um código ou identificador.  

---

### 🎟️ Funções de Passagens
- `reservarPassagem()`  
  Permite que o usuário reserve uma poltrona em uma viagem.  
  Verifica se a poltrona já está ocupada antes de confirmar.  

- `listarPassagens()`  
  Exibe todas as reservas realizadas para uma determinada viagem.  

- `cancelarReserva()`  
  Cancela uma reserva existente e libera a poltrona.  

---

### 👨‍💻 Funções de Interface (Menus)
- `menuPrincipal()`  
  Exibe o menu inicial do sistema com opções como cadastrar motorista, reservar passagem e acessar a área do motorista.  

- `menuMotorista()`  
  Exibe o menu interno da área do motorista, com funcionalidades específicas para ele.  

---

### 🗂️ Funções de Persistência
- `salvarDadosMotoristas()`  
  Grava no arquivo binário as informações de motoristas cadastrados.  

- `salvarDadosViagens()`  
  Grava no arquivo binário as informações das viagens.  

- `salvarDadosPassagens()`  
  Grava no arquivo binário as informações das reservas.  

- `carregarDados()`  
  Verifica a existência dos arquivos binários e carrega os dados em memória.  
  Caso o arquivo não exista, pode criar um novo vazio (autoinicialização).  

---

## 🗃️ Dados iniciais de teste
O código possui **dados comentados** para facilitar os testes iniciais:  
- Motoristas fictícios já configurados.  
- Viagens de exemplo ligadas a esses motoristas.  
- Reservas iniciais para demonstrar a verificação de poltronas.  

Esses dados servem apenas como **base para testes acadêmicos** e não representam informações reais.  

---

## 📂 Estrutura do programa
- Arquivo único: `simulador_terminal.c`  
- Organização por **funções**, todas chamadas pela `main()`  
- Persistência em **arquivos binários** (`motoristas.bin`, `viagens.bin`, `passagens.bin`)  

---
