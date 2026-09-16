from estacao import FonteNivel, PainelFixo, SensorNivel, Sessao, executar_ciclo


def main():
    sensor = SensorNivel(10)
    painel = PainelFixo(sensor)
    fonte = FonteNivel(sensor)
    sessao = Sessao()
    sensor.atualizar(20)
    print(f"Painel: {painel.leitura()}")
    for disponivel in (True, False, True):
        sucesso, valor = executar_ciclo(fonte, disponivel, True, sessao)
        mensagem = f"Leitura: {valor}" if sucesso else "Sem leitura"
        print(f"{mensagem} | sessoes: {sessao.abertas}")


if __name__ == "__main__":
    main()
