/* 
INFORMAÇÕES PARA TESTE DO SIMULADOR
(Carregar os arquivos ".dat" enviados para que o codigo funcione corretamente.)

LOGIN MOTORISTA 
LEONAM - ID: 1003 SENHA: 1122 (Salvo no arquivo Motoristas.dat)

(Caso o arquivo Motoristas.dat não seja carregado corretamente, adicione temporariamente a chamada da função cadastrarMotoristas(); no  
início da main e cadastre um motorista antes de iniciar os testes. Isso garantirá o acesso à área do motorista. Sem o arquivo, nenhum 
motorista estará cadastrado, impossibilitando o login.)

NOMES TESTES CADASTRADOS PARA VIAGEM 
JOAO SILVA RODRIGUES ROTA: 1 POLTRONA: 20
JOAQUIM GONCALVES    ROTA: 1 POLTRONA: 15
MARIA PEREIRA VIEIRA ROTA: 2 POLTRONA: 30
JOSE SANTOS COSTA    ROTA: 3 POLTRONA: 40

(Estes passageiros já estão cadastrados no arquivo "DadosPassagem.dat" enviado. Caso o arquivo não seja carregado, nenhuma poltrona estará ocupada.  
No entanto, ao acessar a opção "Reservar Passagens", o arquivo será criado automaticamente e o sistema funcionará normalmente, sendo necessário novos 
cadastros.)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct para guardar dados das passagens
struct Viagem {
    char nomePassageiro[100];
    int poltrona;
    int rota;
    float preco;
    char codigoViagem[10];
};

// Struct para guardar dados dos motoristas
struct DadosMotoristas {
    char nomeMotorista[100];
    int id;
    int senha;
};

//Função para remover buffer de entrada
void removerBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Menu principal 
int menu() {
    int opcao;
    printf("\n\t--- Terminal Rodoviario ---\n\n");
    printf("1 -> Rotas\n");
    printf("2 -> Reservar passagem\n");
    printf("3 -> Area motoristas\n");
    printf("4 -> Sobre nos\n");
    printf("0 -> Sair\n");
    printf("Opcao:  ");
    scanf("%d", &opcao);
    removerBuffer();
    return opcao;
}

//Função para salvar passagem no arquivo
void arquivoPassagem(struct Viagem passagem) {
    FILE* arquivo = fopen("DadosPassagem.dat", "ab");
    if (arquivo == NULL) {
        printf("Falha ao criar arquivo\n");
        return;
    }
    size_t escrito = fwrite(&passagem, sizeof(struct Viagem), 1, arquivo);
    if (escrito != 1) {
        printf("Erro ao salvar a passagem\n");
    }
    fclose(arquivo);
}

//Função para verificar se a poltrona esta livre na rota escolhida
int verificarDisponibilidade(int idDaRota, int poltronaEscolhida) {
    FILE* arquivo = fopen("DadosPassagem.dat", "rb");
    if (arquivo == NULL) return 1;

    struct Viagem passagemLida;
    while (fread(&passagemLida, sizeof(struct Viagem), 1, arquivo) == 1) {
        if (passagemLida.rota == idDaRota && passagemLida.poltrona == poltronaEscolhida) {
            fclose(arquivo);
            return 0;
        }
    }
    fclose(arquivo);
    return 1;
}

//Função para mostrar poltronas ocupadas ou livres
void poltronasDisponiveis(int idDaRota) {
    int mapaDeAssentos[40] = {0};
    FILE* arquivo = fopen("DadosPassagem.dat", "rb");

    if (arquivo != NULL) {
        struct Viagem passagemLida;
        while (fread(&passagemLida, sizeof(struct Viagem), 1, arquivo) == 1) {
            if (passagemLida.rota == idDaRota) {
                if (passagemLida.poltrona >= 1 && passagemLida.poltrona <= 40) {
                    mapaDeAssentos[passagemLida.poltrona - 1] = 1;
                }
            }
        }
        fclose(arquivo);
    }

    printf("\n\t--- Poltronas ---\n");
    printf("\t[ 99 ] = Livre | [ XX ] = Ocupado\n\n");
    for (int i = 0; i < 40; i++) {
        if (mapaDeAssentos[i] == 1) {
            printf("[XX] ");
        } else {
            printf("[%02d] ", i + 1);
        }
        if ((i + 1) % 10 == 0) printf("\n");
    }
}

//Função para reservar passagem
void reservarPassagem(float preco[3], char codigoViagem[3][10]) {
    struct Viagem novaPassagem;
    int poltronaEscolhida, estaDisponivel;

    printf("\n\t--- Nova Reserva ---\n\n");
    printf("Escolha a rota desejada:\n1 - SP -> RJ\n2 - SP -> BH\n3 - SP -> VIX\nOpcao: ");
    scanf("%d", &novaPassagem.rota);
    removerBuffer();

    if (novaPassagem.rota < 1 || novaPassagem.rota > 3) {
        printf("ERRO: Rota invalida!\n");
        return;
    }

    poltronasDisponiveis(novaPassagem.rota);

    do {
        printf("Qual poltrona voce deseja reservar? ");
        scanf("%d", &poltronaEscolhida);
        removerBuffer();

        if (poltronaEscolhida < 1 || poltronaEscolhida > 40) {
            printf("ERRO: Poltrona invalida!\n");
            estaDisponivel = 0;
            continue;
        }

        estaDisponivel = verificarDisponibilidade(novaPassagem.rota, poltronaEscolhida);
        if (!estaDisponivel) {
            printf("ERRO: A poltrona %d ja esta ocupada!\n", poltronaEscolhida);
        }
    } while (!estaDisponivel);

    novaPassagem.poltrona = poltronaEscolhida;

    printf("Nome do passageiro: ");
    fgets(novaPassagem.nomePassageiro, 100, stdin);
    novaPassagem.nomePassageiro[strcspn(novaPassagem.nomePassageiro, "\n")] = 0;

    novaPassagem.preco = preco[novaPassagem.rota - 1];
    strcpy(novaPassagem.codigoViagem, codigoViagem[novaPassagem.rota - 1]);

    arquivoPassagem(novaPassagem);

    printf("\nReserva confirmada para %s na poltrona %d!\n", novaPassagem.nomePassageiro, novaPassagem.poltrona);
}

//Função para mostrar rotas de viagem
void rotas(float preco[], char codigoViagem[3][10]) {
    int opcao;
    while (1) {
        printf("\n1 - SP -> RJ\n2 - SP -> BH\n3 - SP -> VIX\n0 - Sair\nOpcao: ");
        scanf("%d", &opcao);
        removerBuffer();
        if (opcao == 0) break;

        if (opcao >= 1 && opcao <= 3) {
            printf("Valor: R$%.2f\nCodigo: %s\n", preco[opcao - 1], codigoViagem[opcao - 1]);
        } else {
            printf("ERRO: Opcao invalida!\n");
        }
    }
}

//Função para cadastrar novos motoristas
void cadastrarMotorista() {
    FILE* arquivo = fopen("Motoristas.dat", "ab");
    if (arquivo == NULL) {
        printf("Falha no sistema\n");
        return;
    }

    struct DadosMotoristas motorista;
    printf("Nome do motorista: ");
    fgets(motorista.nomeMotorista, 100, stdin);
    motorista.nomeMotorista[strcspn(motorista.nomeMotorista, "\n")] = 0;

    printf("ID (4 digitos): ");
    scanf("%d", &motorista.id);
    removerBuffer();

    printf("Senha (4 digitos): ");
    scanf("%d", &motorista.senha);
    removerBuffer();

    fwrite(&motorista, sizeof(struct DadosMotoristas), 1, arquivo);
    fclose(arquivo);
    printf("Cadastro realizado com sucesso!\n");
}

//Função para motoristas verem poltronas e passageiros de uma rota
void frotas(char* codigoDaViagem) {
    FILE* arquivo = fopen("DadosPassagem.dat", "rb");
    if (arquivo == NULL) {
        printf("Nenhuma passagem vendida ainda.\n");
        return;
    }

    struct Viagem passagens[120]; 
    int count = 0;

    while (fread(&passagens[count], sizeof(struct Viagem), 1, arquivo) == 1) {
        if (strcmp(passagens[count].codigoViagem, codigoDaViagem) == 0) {
            count++;
        }
    }
    fclose(arquivo);

    if (count == 0) {
        printf("Nenhum passageiro nesta viagem.\n");
        return;
    }
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (passagens[j].poltrona > passagens[j + 1].poltrona) {
                struct Viagem temp = passagens[j];
                passagens[j] = passagens[j + 1];
                passagens[j + 1] = temp;
            }
        }
    }

    printf("\nPassageiros da viagem %s:\n\n", codigoDaViagem);
    printf("%-10s | %s\n", "Poltrona", "Nome do Passageiro");
    printf("-----------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-10d | %s\n", passagens[i].poltrona, passagens[i].nomePassageiro);
    }
}

//Função para listar todos os motoristas cadastrados
void listarMotoristas() {
    FILE* arquivo = fopen("Motoristas.dat", "rb");
    if (arquivo == NULL) {
        printf("Nenhum motorista cadastrado.\n");
        return;
    }

    struct DadosMotoristas motorista;
    printf("\nID      | Nome\n");
    printf("-----------------------------\n");

    while (fread(&motorista, sizeof(struct DadosMotoristas), 1, arquivo) == 1) {
        printf("%-8d| %s\n", motorista.id, motorista.nomeMotorista);
    }
    fclose(arquivo);
}

//Menu de area dos motoristas
void areaMotoristaMenus(char codigoViagem[3][10]) {
    int opcao;
    do {
        printf("\n--- Area do Motorista ---\n");
        printf("1 -> Ver frotas\n");
        printf("2 -> Cadastrar novo motorista\n");
        printf("3 -> Motoristas ativos\n");
        printf("0 -> Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        removerBuffer();

        switch (opcao) {
            case 1:
                printf("Escolha a viagem (1-3):\n");
                printf("1 - %s\n2 - %s\n3 - %s\n", codigoViagem[0], codigoViagem[1], codigoViagem[2]);
                int viag;
                scanf("%d", &viag);
                removerBuffer();
                if (viag >= 1 && viag <= 3) {
                    frotas(codigoViagem[viag - 1]);
                } else {
                    printf("ERRO: Opcao invalida!\n");
                }
                break;
            case 2:
                cadastrarMotorista();
                break;
            case 3:
                listarMotoristas();
                break;
            case 0:
                break;
            default:
                printf("ERRO: Opcao invalida!\n");
        }
    } while (opcao != 0);
}

//Login dos motoristas para acessar area dos motoristas
void loginMotorista(char codigoViagem[3][10]) {
    FILE* arquivo = fopen("Motoristas.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao acessar dados\n");
        return;
    }

    struct DadosMotoristas digitado, lido;
    printf("ID: ");
    scanf("%d", &digitado.id);
    removerBuffer();

    printf("Senha: ");
    scanf("%d", &digitado.senha);
    removerBuffer();

    int achou = 0;
    while (fread(&lido, sizeof(struct DadosMotoristas), 1, arquivo) == 1) {
        if (lido.id == digitado.id && lido.senha == digitado.senha) {
            achou = 1;
            break;
        }
    }
    fclose(arquivo);

    if (achou) {
        areaMotoristaMenus(codigoViagem);
    } else {
        printf("ERRO: Credenciais incorretas.\n");
    }
}

int main() {
    float precos[3] = {109.49, 98.50, 199.27};
    char codigoViagem[3][10] = {"SP1RJ2AA", "SP1BH2BB", "SP1VIX2C"};

    int opcao;
    do {
        opcao = menu();
        switch (opcao) {
            case 1:
                rotas(precos, codigoViagem);
                break;
            case 2:
                reservarPassagem(precos, codigoViagem);
                break;
            case 3:
                loginMotorista(codigoViagem);
                break;
            case 4:
                printf("\nNos, alunos KEVIN SILVA MOREIRA e TULIO RODRIGUES SILVA, criamos este simulador de terminal rodoviario como projeto final na materia de PROGRAMACAO E ALGORITMOS.Este programa tem como finalidade simular um site ou aplicativo de um terminal rodoviario, oferecendo servicos para clientes e funcionarios.\n");
                break;
            case 0:
                printf("Saida efetuada com sucesso!\n");
                break;
            default:
                printf("ERRO: Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
