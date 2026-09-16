#include "estacao.hpp"
#include <iostream>

int main() {
    SensorNivel sensor{10};
    PainelFixo painel{sensor};
    FonteNivel fonte{sensor};
    FonteConstante simulada;
    int abertas = 0;
    sensor.atualizar(20);
    std::cout << "Painel: " << painel.leitura() << '\n';
    const auto testeSimulado = executarCiclo(simulada, true, true, abertas);
    if (testeSimulado.sucesso)
        std::cout << "Fonte simulada: " << testeSimulado.valor << ' '
                  << simulada.unidade() << " | sessoes: " << abertas << '\n';
    for (bool disponivel : {true, false, true}) {
        const auto resultado = executarCiclo(fonte, disponivel, true, abertas);
        if (resultado.sucesso) std::cout << "Leitura: " << resultado.valor;
        else std::cout << "Sem leitura (" << resultado.motivo << ')';
        std::cout << " | sessoes: " << abertas << '\n';
    }
    const auto semCalibracao = executarCiclo(fonte, true, false, abertas);
    std::cout << "Sem calibracao: ";
    if (semCalibracao.sucesso) std::cout << "leitura indevida: " << semCalibracao.valor;
    else std::cout << "sem leitura (" << semCalibracao.motivo << ')';
    std::cout << " | sessoes: " << abertas << '\n';
    const auto recuperado = executarCiclo(fonte, true, true, abertas);
    std::cout << "Ciclo seguinte: ";
    if (recuperado.sucesso) std::cout << "leitura disponivel: " << recuperado.valor;
    else std::cout << "sem leitura (" << recuperado.motivo << ')';
    std::cout << " | sessoes: " << abertas << '\n';
}
