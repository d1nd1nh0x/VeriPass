#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>  // Para funções como isdigit() e isupper()

// estrutura da senha digitada
typedef struct {
    char userPassword[64 + 1];          // Conter senha digitada pelo usuário
    int length;                         // Tamanho da senha digitada pelo usuário
    int contains_special;               // 1 - Sim, contém caracteres especiais 0 - Não contém caractere especial
    int contains_uppercase;             // 1 - Sim, contém caracteres em uppercase 0 - Não contém caractere em uppercase
    int contains_numbers;               // 1 - Sim, contém números 0 - Não contém números
    int security_level;                 // Irá conter o nível de segurança da senha
} password;

// Constantes para verificação
#define MIN_LENGTH 8
#define MID_LENGTH 12
#define MAX_SPECIAL_CHARS 8
#define SPECIAL_CHARS "!#$%&*@^"

// Procedimentos de verificações
void check_password_length(password * secretKey);
void check_special_chars(password * secretKey);
void check_digits_in_password(password * secretKey);
void check_uppercase_in_password(password * secretKey);

// Funções auxiliares
int contains_char(const char *str, const char *set);
void show_password_requirements(password secretKey);

int main(void) {
    password passwordEntry;
    printf("Digite sua senha -> ");
    fgets(passwordEntry.userPassword, sizeof(passwordEntry.userPassword), stdin);
    passwordEntry.userPassword[strcspn(passwordEntry.userPassword, "\n")] = 0;  // Remover \n
    passwordEntry.length = strlen(passwordEntry.userPassword);

    // Verificações de segurança
    check_password_length(&passwordEntry);
    check_special_chars(&passwordEntry);
    check_digits_in_password(&passwordEntry);
    check_uppercase_in_password(&passwordEntry);

    // Exibindo o resultado
    #ifdef WIN32
        system("cls");
    #else
        system("clear");
    #endif
    show_password_requirements(passwordEntry);
}

// Verificação de tamanho da senha
void check_password_length(password * secretKey) {
    secretKey->security_level = 0; // Inicializando o nível de segurança
    if (secretKey->length <= MIN_LENGTH) {
        secretKey->security_level += 1;
    } else if (secretKey->length <= MID_LENGTH) {
        secretKey->security_level += 2;
    } else {
        secretKey->security_level += 3;
    }
}

// Verificação de caracteres especiais
void check_special_chars(password * secretKey) {
    secretKey->contains_special = 0;
    if (contains_char(secretKey->userPassword, SPECIAL_CHARS)) {
        secretKey->contains_special = 1;
        secretKey->security_level += 1;
    }
}

// Verificação de números
void check_digits_in_password(password * secretKey) {
    secretKey->contains_numbers = 0;
    if (contains_char(secretKey->userPassword, "0123456789")) {
        secretKey->contains_numbers = 1;
        secretKey->security_level += 1;
    }
}

// Verificação de letras maiúsculas
void check_uppercase_in_password(password * secretKey) {
    secretKey->contains_uppercase = 0;
    if (contains_char(secretKey->userPassword, "ABCDEFGHIJKLMNOPQRSTUVWXYZ")) {
        secretKey->contains_uppercase = 1;
        secretKey->security_level += 1;
    }
}

// Função auxiliar para verificar a presença de caracteres em uma string
int contains_char(const char *str, const char *set) {
    while (*str) {
        if (strchr(set, *str)) {
            return 1; // Encontrou um caractere válido
        }
        str++;
    }
    return 0; // Nenhum caractere válido encontrado
}

// Exibe os requisitos e características da senha
void show_password_requirements(password secretKey) {
    puts("A senha digitada possui as seguintes características:");
    putchar('\n');
    printf("- Tamanho: %d de caracteres\n", secretKey.length);
    printf("- Caracteres especiais: [%c]\n", secretKey.contains_special ? '*' : ' ');
    printf("- Dígitos presentes: [%c]\n", secretKey.contains_numbers ? '*' : ' ');
    printf("- Letras maiúsculas: [%c]\n", secretKey.contains_uppercase ? '*' : ' ');

    if (secretKey.security_level < 5) {
        printf("- Nível de segurança: Baixo\n");
    } else if (secretKey.security_level <= 10) {
        printf("- Nível de segurança: Médio\n");
    } else {
        printf("- Nível de segurança: Alto\n");
    }
}
