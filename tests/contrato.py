import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "src"))

from estacao import (  # noqa: E402
    FalhaCalibracao, FalhaLeitura, FonteConstante, FonteNivel, PainelFixo,
    SensorNivel, Sessao, adquirir, executar_ciclo,
)


class FonteQuebrada:
    def valor(self):
        raise RuntimeError("defeito inesperado")

    def unidade(self):
        return "%"


def conferir(condicao, mensagem):
    if not condicao:
        raise AssertionError(mensagem)


def main():
    sensor = SensorNivel(10)
    painel = PainelFixo(sensor)
    real = FonteNivel(sensor)
    simulada = FonteConstante()
    sessao = Sessao()
    conferir(painel.leitura() == 10, "GUIADO: painel deve consultar o sensor associado (10)")
    sensor.atualizar(20)
    conferir(painel.leitura() == 20, "GUIADO: painel deve refletir a atualizacao (20)")
    conferir(real.valor() == 20 and simulada.valor() == 42.5,
             "CONTRATO: fontes diferentes devem responder pela mesma interface")
    conferir(executar_ciclo(real, True, True, sessao) == (True, 20, "")
             and sessao.abertas == 0, "CONTRATO: leitura valida e sessao liberada")
    conferir(executar_ciclo(real, False, True, sessao) == (False, 0, "indisponivel")
             and sessao.abertas == 0,
             "CONTRATO: indisponibilidade classificada e sessao liberada")
    try:
        adquirir(real, False, False, sessao)
        conferir(False, "GUIADO: indisponibilidade deve ter prioridade")
    except FalhaCalibracao:
        conferir(False, "GUIADO: indisponibilidade tem prioridade sobre calibracao")
    except FalhaLeitura:
        pass
    conferir(sessao.abertas == 0, "CONTRATO: sessao liberada apos propagacao")
    try:
        adquirir(real, True, False, sessao)
        conferir(False, "GUIADO: falta de calibracao deve lancar FalhaCalibracao")
    except FalhaCalibracao:
        pass
    conferir(sessao.abertas == 0, "EXTENSAO: sessao liberada apos FalhaCalibracao")
    conferir(executar_ciclo(real, True, False, sessao) == (False, 0, "calibracao")
             and sessao.abertas == 0,
             "EXTENSAO: capture FalhaCalibracao antes de FalhaLeitura e informe calibracao")
    try:
        executar_ciclo(FonteQuebrada(), True, True, sessao)
        conferir(False, "CONTRATO: defeito inesperado nao pode ser convertido em ausencia")
    except RuntimeError:
        pass
    conferir(sessao.abertas == 0, "CONTRATO: sessao liberada apos defeito inesperado")
    conferir(executar_ciclo(real, True, True, sessao) == (True, 20, "")
             and sessao.abertas == 0, "CONTRATO: proximo ciclo continua apos falha")
    print("OK pratica integrada A (Python)")


if __name__ == "__main__":
    main()
