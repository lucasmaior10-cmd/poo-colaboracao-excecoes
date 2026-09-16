#include "estacao.hpp"
#include <iostream>

int main() {
    SensorNivel sensor{10};
    PainelFixo painel{sensor};
    FonteNivel fonte{sensor};
    int abertas = 0;
    sensor.atualizar(20);
    std::cout << "Painel: " << painel.leitura() << '\n';
    for (bool disponivel : {true, false, true}) {
        const auto resultado = executarCiclo(fonte, disponivel, true, abertas);
        if (resultado.sucesso) std::cout << "Leitura: " << resultado.valor;
        else std::cout << "Sem leitura";
        std::cout << " | sessoes: " << abertas << '\n';
    }
}
