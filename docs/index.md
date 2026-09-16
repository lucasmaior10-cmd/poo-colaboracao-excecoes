# Prática A: colaboração e exceções

## Estado inicial

O sensor nasce com 10 e passa a 20. O painel ainda mostra zero. Execute `make run` no seu fork e localize a chamada `painel.leitura()` em `src/main.cpp` e `src/main.py`. O programa compila: o zero indica um comportamento pendente, não uma falha de compilação.

Antes de editar, preveja também o ciclo `Sem calibracao`: por que o starter ainda o apresenta como `leitura indevida: 20`? Essa é a segunda pendência, que será resolvida depois da consulta do painel.

## Incremento guiado: consultar o objeto associado

O painel já guarda o sensor recebido na construção. A cada leitura, precisa pedir o valor **àquele mesmo objeto**. Consulte o programa completo da [seção 2 do capítulo 09](https://rafaelrezo.github.io/curso-poo/fundamentos_poo_cpp_python/09_associacoes/) e altere somente `PainelFixo.leitura` nos dois arquivos da prática. Execute `make run` e espere `Painel: 20`. Depois execute `make test ETAPA=A`; a próxima mensagem passa a tratar de calibração.

## Extensão: decidir quando a aquisição falha

No capítulo 10, a fonte indisponível lança `FalhaLeitura`. A falta de calibração é outra falha prevista, representada por `FalhaCalibracao`. Em `adquirir`, observe a ordem das condições: quando a fonte está indisponível e sem calibração, a indisponibilidade deve ser comunicada primeiro. A sessão deve fechar mesmo quando a exceção atravessa `lerServico`. Acrescente apenas a decisão ausente, sem capturar dentro de `adquirir`.

Execute `make run` e confira `Sem calibracao: sem leitura | sessoes: 0`, seguido de `Ciclo seguinte: leitura disponivel: 20 | sessoes: 0` em C++ e Python. Depois execute `make test ETAPA=A`. Leia a primeira mensagem de falha antes de modificar outro arquivo. Quando os dois idiomas passarem, revise o diff e explique onde cada exceção é lançada e capturada.
