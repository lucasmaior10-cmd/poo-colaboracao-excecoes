#include "estacao.hpp"
#include <iostream>
#include <stdexcept>

void conferir(bool condicao, const char* mensagem) {
    if (!condicao) throw std::runtime_error(mensagem);
}

class FonteQuebrada final : public IFonteLeitura {
public:
    double valor() const override { throw std::logic_error("defeito inesperado"); }
    const char* unidade() const override { return "%"; }
};

int main() {
    try {
        SensorNivel sensor{10};
        PainelFixo painel{sensor};
        FonteNivel real{sensor};
        FonteConstante simulada;
        int abertas = 0;
        conferir(painel.leitura() == 10, "GUIADO: painel deve consultar o sensor associado (10)");
        sensor.atualizar(20);
        conferir(painel.leitura() == 20, "GUIADO: painel deve refletir a atualizacao (20)");
        conferir(real.valor() == 20 && simulada.valor() == 42.5,
                 "CONTRATO: fontes diferentes devem responder pela mesma interface");
        conferir(executarCiclo(real, true, true, abertas).valor == 20 && abertas == 0,
                 "CONTRATO: leitura valida e sessao liberada");
        conferir(!executarCiclo(real, false, true, abertas).sucesso && abertas == 0,
                 "CONTRATO: indisponibilidade tratada e sessao liberada");
        try {
            adquirir(real, false, false, abertas);
            conferir(false, "EXTENSAO: indisponibilidade deve ter prioridade");
        } catch (const FalhaCalibracao&) {
            conferir(false, "EXTENSAO: indisponibilidade tem prioridade sobre calibracao");
        } catch (const FalhaLeitura&) {}
        conferir(abertas == 0, "CONTRATO: sessao liberada apos propagacao");
        try {
            adquirir(real, true, false, abertas);
            conferir(false, "EXTENSAO: falta de calibracao deve lancar FalhaCalibracao");
        } catch (const FalhaCalibracao&) {}
        conferir(abertas == 0, "EXTENSAO: sessao liberada apos FalhaCalibracao");
        conferir(!executarCiclo(real, true, false, abertas).sucesso && abertas == 0,
                 "EXTENSAO: cliente recupera falha de calibracao");
        FonteQuebrada quebrada;
        try {
            executarCiclo(quebrada, true, true, abertas);
            conferir(false, "CONTRATO: defeito inesperado nao pode ser convertido em ausencia");
        } catch (const std::logic_error&) {}
        conferir(abertas == 0, "CONTRATO: sessao liberada apos defeito inesperado");
        conferir(executarCiclo(real, true, true, abertas).valor == 20 && abertas == 0,
                 "CONTRATO: proximo ciclo continua apos falha");
        std::cout << "OK pratica integrada A (C++)\n";
    } catch (const std::exception& erro) {
        std::cerr << erro.what() << '\n';
        return 1;
    }
}
