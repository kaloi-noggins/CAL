#include <stdio.h>

void calcularNotasEMoedas(float valor) {
    int notas50, notas20, notas10, notas5, notas1;
    int moedas50, moedas25, moedas10, moedas5, moedas1;
    int centavos;

    // Convertendo o valor para centavos
    centavos = (int)(valor * 100);

    // Inicializando todas as variáveis com zero
    notas50 = notas20 = notas10 = notas5 = notas1 = 0;
    moedas50 = moedas25 = moedas10 = moedas5 = moedas1 = 0;

    // Calculando notas de 50
    notas50 = centavos / 5000;
    centavos %= 5000;

    // Calculando notas de 20
    notas20 = centavos / 2000;
    centavos %= 2000;

    // Calculando notas de 10
    notas10 = centavos / 1000;
    centavos %= 1000;

    // Calculando notas de 5
    notas5 = centavos / 500;
    centavos %= 500;

    // O que sobrar são notas de 1
    notas1 = centavos / 100;
    centavos %= 100;

    // Calculando moedas de 50 centavos
    moedas50 = centavos / 50;
    centavos %= 50;

    // Calculando moedas de 25 centavos
    moedas25 = centavos / 25;
    centavos %= 25;

    // Calculando moedas de 10 centavos
    moedas10 = centavos / 10;
    centavos %= 10;

    // Calculando moedas de 5 centavos
    moedas5 = centavos / 5;
    centavos %= 5;

    // O que sobrar são moedas de 1 centavo
    moedas1 = centavos;

    // Exibindo o resultado
    printf("%d x 50.00\n", notas50);
    printf("%d x 20.00\n", notas20);
    printf("%d x 10.00\n", notas10);
    printf("%d x 5.00\n", notas5);
    printf("%d x 1.00\n", notas1);
    printf("%d x 0.50\n", moedas50);
    printf("%d x 0.25\n", moedas25);
    printf("%d x 0.10\n", moedas10);
    printf("%d x 0.05\n", moedas5);
    printf("%d x 0.01\n", moedas1);
}

int main() {
    float valor;

    scanf("%f", &valor);

    calcularNotasEMoedas(valor);

    return 0;
}
