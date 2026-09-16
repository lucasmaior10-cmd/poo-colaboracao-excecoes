from estacao import FonteConstante, FonteNivel, PainelFixo, SensorNivel, Sessao, executar_ciclo


def main():
    sensor = SensorNivel(10)
    painel = PainelFixo(sensor)
    fonte = FonteNivel(sensor)
    simulada = FonteConstante()
    sessao = Sessao()
    sensor.atualizar(20)
    print(f"Painel: {painel.leitura()}")
    sucesso, valor = executar_ciclo(simulada, True, True, sessao)
    if sucesso:
        print(f"Fonte simulada: {valor} {simulada.unidade()} | sessoes: {sessao.abertas}")
    for disponivel in (True, False, True):
        sucesso, valor = executar_ciclo(fonte, disponivel, True, sessao)
        mensagem = f"Leitura: {valor}" if sucesso else "Sem leitura"
        print(f"{mensagem} | sessoes: {sessao.abertas}")
    sucesso, valor = executar_ciclo(fonte, True, False, sessao)
    mensagem = f"leitura indevida: {valor}" if sucesso else "sem leitura"
    print(f"Sem calibracao: {mensagem} | sessoes: {sessao.abertas}")
    sucesso, valor = executar_ciclo(fonte, True, True, sessao)
    mensagem = f"leitura disponivel: {valor}" if sucesso else "sem leitura"
    print(f"Ciclo seguinte: {mensagem} | sessoes: {sessao.abertas}")


if __name__ == "__main__":
    main()
