/*
VERSAO: 5.0
*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h> 

//Variaveis Globais------------------------------------------------------------------------------------------------------
int TotUse = 0;
char Nome[50][50];
char Senha[50][50];

//Procedimentos----------------------------------------------------------------------------------------------------------
void menu();
void AdiUser();
void Alterar();
void excluir ();
void Creditos();
void Classifica();
void arquivo (int comando);
void listar();

//Funcoes----------------------------------------------------------------------------------------------------------------
bool ValSenha(char senha[30]);
int BuscaUser(char busca[30]);
char* Criptografa(char *s);
char* Descriptografa(char *s);

//Main-------------------------------------------------------------------------------------------------------------------
int main() {
    arquivo(0);
    SetConsoleOutputCP(CP_UTF8);	
    menu();
    arquivo(1);
    arquivo(0);
    return 0;
}
//Menu-------------------------------------------------------------------------------------------------------------------
void menu() {
    int p = 1, x, tecla;
    char item[7][11] = {"", " Incluir ", " Alterar "," Listar ", " Excluir ", " Creditos", " Sair    "};

    do {
        system("cls");
        for (x = 1; x <= 6; x++) {
            if (x == p) {
                printf(">> %s <<\n", item[x]);
            } else {
                printf("   %s\n", item[x]);
            }
        }

        tecla = getch();
        if (tecla == 224 || tecla == 0) {
            tecla = getch();
        }

        switch (tecla) {
            case 72:
                p--;
                break;
            case 80:
                p++;
                break;
        }

        if (p == 0) p = 6;
        if (p == 7) p = 1;

        if (tecla == 13) {
            switch (p) {
                case 1:
                    AdiUser();
                    break;
                case 2:
                    Alterar();
                    break;
                case 3:
                    listar();
                    break;
                case 4:
                    excluir();
                    break;    
                case 5:
                    Creditos();
                    break;
                case 6:
                    printf("Tem certeza que deseja sair? (S/N): ");
                    char sn;
                    do {
                        sn = getchar();
                        sn = toupper(sn);
                    } while (sn != 'S' && sn != 'N');
                    
                    if (sn == 'S') return;
                    break;
            }
        }

    } while (tecla != 27);
}
//Creditos----------------------------------------------------------------------------------------------------
void Creditos() {
    system("cls || clear"); 

    const char *mensagem = 
        "Programa desenvolvido pelos alunos Gabriel Campos Feiten, Guilherme Tamioso Bueno do Prado, Rodrigo Augusto da Silva Virgilino \n"
        "como projeto da AEP de engenharia de software 2024/Unicesumar.\n"
        "Requisitos: CRUD (create/read/update/delete) de users\n"
        "com criptografia dos dados salvos em arquivo texto.\n"
        "Possui funcionalidades como procedimentos, funcoes, passagem de parametros por valor e por referencia,\n" 
        "variaveis gobais e locais, criptografia, vetores, arquivo texto e classificacao.\n";
    
//Exibe o texto----------------------------------------------------------------------------------------------------------
    while (*mensagem) {
        printf("%c", *mensagem);
        fflush(stdout);
        Sleep(25); 
        mensagem++;
    }

    printf("\n\nPressione ENTER para retornar ao menu...");
    getchar(); 

    system("cls || clear"); 
}

//Crip------------------------------------------------------------------------------------------------------------------
char* Criptografa(char *s){
    static char tmp[256];
    int x,c;
    tmp[0]='\0';
    for (x=0;x < strlen(s);x++){
        c=(int)s[x];
        tmp[x]=(char)(c+x+10);
    }
    tmp[x]='\0';

    return tmp;
}

//Descrip------------------------------------------------------------------------------------------------------------------
char* Descriptografa(char *s){
    static char tmp[256];
    int x,c;
    tmp[0]='\0';
    for (x=0;x<strlen(s);x++){
        c=(int)s[x];
        tmp[x]=(char)(c-x-10);
    }
    tmp[x]='\0';

    return tmp;
}

//Arquivo_txt-------------------------------------------------------------------------------------------------------------
void arquivo(int tp){ //0 - leitura / 1 - gravacao
  char linha[30],tmp[30]; 
  int x;
  FILE *file; 
    file = fopen("users.txt", "r");
    if (file != NULL && tp == 0) {
        TotUse=0;
        x=0;
        while (fgets(linha, sizeof(linha), file) != NULL && strlen(linha)>0) { 
          linha[strlen(linha)-1]='\0'; 
            if (x%2==0){
              TotUse++; 
              strcpy(Nome[TotUse-1],Descriptografa(linha));
              }
            else 
              strcpy(Senha[TotUse-1],Descriptografa(linha));
              x++;
        }
    }
    else{
      file = fopen("users.txt", "w"); 
        for (x=0;x<TotUse;x++){ 
          strcpy(tmp,Nome[x]);
          fprintf(file, "%s\n", Criptografa(tmp));
          strcpy(tmp,Senha[x]);
          fprintf(file, "%s\n", Criptografa(tmp));
        } 
   }
    fclose(file);
}
//Classifica----------------------------------------------------------------------------------------------------------------------------------------------
void Classifica() { //selection short
    char tmp [50];
    for (int x = 0; x < TotUse-1; x++) {    
        for(int y = x+1; y < TotUse; y++) {        
            if(strcmp(Nome[y], Nome[x]) == -1) {
                strcpy(tmp, Nome[x]);
                strcpy(Nome[x], Nome[y]);
                strcpy(Nome[y], tmp);

                strcpy(tmp, Senha[x]);
                strcpy(Senha[x], Senha[y]);
                strcpy(Senha[y], tmp);
            }
        }
    }
}
//Buscar-----------------------------------------------------------------------------------------------------------------
int BuscaUser (char busca [50]) { //busca sequencial
   int x;
    for (x=0; x<TotUse; x++)
      if(strcmp(busca,Nome[x]) == 0)
        return x;
    return -1;  
}


//Adicionar-------------------------------------------------------------------------------------------------------------------
void AdiUser() {
int x;     
    system("cls || clear");
    char Repsenha[50];
    printf("---------------------------------------------");
    printf("\n          ADICIONAR USUARIO\n");
    printf("---------------------------------------------");
    printf("\n\n");
    do {
        printf("Informe o Nome: ");
        gets(Nome[TotUse]);
    } while (strlen(Nome[TotUse]) <= 3 || strlen(Nome[TotUse]) >= 30);
    x = BuscaUser(Nome[TotUse]);
    if (x >= 0) {       
        printf("\nNome de usuario existente ");
        printf("\n--------------------------------------------------------");
	    printf("\nPressione ENTER para voltar ao MENU ");
        getchar();
    }
    else
    {
        do {
            printf("Informe a senha: ");
            gets(Senha[TotUse]);
            if(ValSenha(Senha[TotUse]) == false) {    
                printf("\nSENHA INVALIDA\nA senha deve conter:\n1-Caracter Especial(@);\n1-Letra Mauiscula(A);\n1-Letra Minuscula(a);\n1-Caracter Numérico;\n");
            }
        } while(ValSenha(Senha[TotUse]) != true); 
        do {
            printf("Repita a senha: ");
            gets(Repsenha);
        }while(strcmp(Senha[TotUse],Repsenha) != 0);
        TotUse++;
        Classifica();
    }
    arquivo(1); 
}
//Validacao------------------------------------------------------------------------------------------------------------------------------------------------------
bool ValSenha (char senha [30])
{
    bool ver1 = false, ver2 = false, ver3 = false, ver4 = false, ver5 = false; // Verificacoes

    if(strlen(senha) >= 8 && strlen(senha) <= 20) ver5 = true;
    
    for(int x = 0; senha[x] != '\0'; x++)
    {
        int y = senha[x];
        if(isupper(senha[x])) ver1 = true;
        else if (islower(senha[x])) ver2 = true;
        else if (y >= 48 && y <= 57) ver3 = true;
        else if (ispunct(senha[x])) ver4 = true;
    }

    if(ver1 && ver2 & ver3 & ver4 & ver5) return true;
    else return false;
}

//Listar----------------------------------------------------------------------------------------------------------------------------------------------------
void listar(){
	int x;
    system("cls");
	printf("\n--------------------------------------------------------");
	printf("\nUsuario          x       Senha");
	printf("\n--------------------------------------------------------");
    printf("\nTotal de Usuarios: %d ",TotUse);
    for(x=0;x < TotUse; x++) {
        printf("\n%d   %s        x       %s",x,Nome[x], Criptografa(Senha[x]));
    }
	printf("\n--------------------------------------------------------");
	printf("\nPressione ENTER para voltar ao MENU ");
    getchar();
   
}
//Alterar------------------------------------------------------------------------------------------------------------------
void Alterar(){
    system("cls");
    char nome [50];
    char senha [50];
    char Repsenha[50];
    int a;
    printf("---------------------------------------------");
    printf("\n          ALTERAR SENHA\n");
    printf("---------------------------------------------");
    printf("\n\n");
    do {
        printf("Nome do usuario: ");
        gets(nome);
    } while (strlen(nome) <= 3 || strlen(nome) >= 30);
    a = BuscaUser(nome);
    if (a == -1) { 
        printf("\n            Nome de usuario nao existente ");
        printf("\n--------------------------------------------------------");
        printf("\n         Pressione ENTER para voltar ao MENU ");
        getchar();
    }
    else {
        do {
            printf("Nova senha: ");
            gets(senha);

            if(ValSenha(senha) == false) {
                printf("\nSENHA INVALIDA\nA senha deve conter:\n1-Caracter Especial(@);\n1-Letra Mauiscula(A);\n1-Letra Minuscula(a);\n1-Caracter Numérico;\n");
            }
        } while(ValSenha(senha) != true);

        do {
            printf("Repita a senha: ");
            gets(Repsenha);
        }
        while(strcmp(senha,Repsenha) != 0);
        strcpy(Senha[a],senha);
        
        arquivo(1);
    }
}
//Excluir--------------------------------------------------------------------------------------------------------------------------------------------------
void excluir(){
    system("cls");
    char nome [50];
    char senha [50];
    char Repsenha[50];
    char sn;
    int x,y;
    printf("---------------------------------------------");
    printf("\n         EXCLUIR\n");
    printf("---------------------------------------------");
    printf("\n\n");
    do {
        printf("Nome do usuario: ");
        gets(nome);
    } while (strlen(nome) <= 3 || strlen(nome) >= 30);
    x = BuscaUser(nome);
    if (x == -1) { 
        printf("\n            Nome de usuario nao existente ");
        printf("\n--------------------------------------------------------");
        printf("\n         Pressione ENTER para voltar ao MENU ");
        getchar();
    }
    else{
        printf("Confirma exclusao:  ");
        scanf("%c",&sn);
        if (toupper(sn) == 'S'){
            for (y=x;y<TotUse;y++){    
                strcpy(Nome[y],Nome[y+1]);
                strcpy(Senha[y],Senha[y+1]);
            }
            TotUse--;
        }
        arquivo(1);
    }
}

