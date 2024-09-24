#include <iostream>
#include <bitset>

int invertirBits(int num, int n) {
    int invertido = 0;
    for (int i = 0; i < n; ++i) {
        if (!(num & (1 << i))) {
            invertido |= (1 << i);  // Si el bit es 0, poner 1 en esa posición.
        }
    }
    return invertido;
}

int complemento2(int num, int n) {
    int invertido = invertirBits(num, n);
    int carry = 1; 
    
    for (int i = 0; i < n; ++i) {
        if (invertido & (1 << i)) {
            invertido &= ~(1 << i);  // Si el bit es 1, ponerlo en 0 y llevar el acarreo.
        } else {
            invertido |= (1 << i);  // Si el bit es 0, poner 1 y detener el acarreo.
            carry = 0;
            break;
        }
    }

    return invertido & ((1 << n) - 1);
}

void corrimientoAritmetico(int &A, int &Q, int &Q_1, int n) {
    int A_sign = A & (1 << (n - 1));
    Q_1 = Q & 1;  
    Q = (Q >> 1) | (A & 1) << (n - 1);  // Corrimiento de Q con el bit menos significativo de A
    A = (A >> 1) | A_sign;  // Corrimiento aritmetico de A manteniendo el bit de signo
}


int boothMultiplication(int M, int Q, int n) {
    int A = 0;  
    int Q_1 = 0; 
    int multiplicandoNeg = complemento2(M, n);  // Complemento a 2 del multiplicando M

    for (int i = 0; i < n; i++) {
        if ((Q & 1) == 1 && Q_1 == 0) {
            A = (A + multiplicandoNeg) & ((1 << n) - 1);  // A = A - M (complemento a 2)
        }else if ((Q & 1) == 0 && Q_1 == 1) {
            A = (A + M) & ((1 << n) - 1);
        }
        corrimientoAritmetico(A, Q, Q_1, n);
    }
    return (A << n) | Q;
}

int main() {
    int M, Q, n;
    std::cout << "Introduce el multiplicando (M): ";
    std::cin >> M;
    std::cout << "Introduce el multiplicador (Q): ";
    std::cin >> Q;
    std::cout << "Introduce la cantidad de bits (n): ";
    std::cin >> n;

    int resultado = boothMultiplication(M, Q, n);


    std::cout << "Resultado en binario: " << std::bitset<16>(resultado) << std::endl;
    std::cout << "Resultado en decimal: " << resultado << std::endl;

    return 0;
}
