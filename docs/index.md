# Prática A: colaboração e exceções

## Estado inicial

O sensor nasce com 10 e passa a 20. O painel acompanha o sensor e a fonte simulada responde 42,5. Execute `make run` no seu fork: essas duas consultas já funcionam e mostram a colaboração estudada no capítulo 09.

Antes de editar, observe `Sem calibracao: leitura indevida: 20`. A aquisição ainda aceita uma fonte que deveria rejeitar. Esse é o problema que você corrigirá.

## Incremento guiado: lançar a falha específica

Em `adquirir`, preserve a verificação de indisponibilidade e acrescente a rejeição de uma fonte disponível sem calibração, lançando `FalhaCalibracao`. Use o exemplo de lançamento da [seção 2 do capítulo 10](https://rafaelrezo.github.io/curso-poo/fundamentos_poo_cpp_python/11_excecoes/). Execute `make test ETAPA=A`: a nova mensagem agora pede que o cliente diferencie a causa.

## Extensão: capturar na fronteira do cliente

`FalhaCalibracao` deriva de `FalhaLeitura`. Em `executarCiclo` e `executar_ciclo`, a captura específica deve vir antes da geral para devolver o motivo `calibracao`. A sessão fecha mesmo quando a exceção atravessa `lerServico`; preserve esse código fornecido. Compare a ordem das capturas com a [seção 4 do capítulo 10](https://rafaelrezo.github.io/curso-poo/fundamentos_poo_cpp_python/11_excecoes/).

Execute `make run` e confira `Sem calibracao: sem leitura (calibracao) | sessoes: 0`, seguido de `Ciclo seguinte: leitura disponivel: 20 | sessoes: 0` em C++ e Python. Depois execute `make test ETAPA=A`. Leia a primeira mensagem de falha antes de modificar outro arquivo. Quando os dois idiomas passarem, revise o diff e explique onde a falha é lançada, propagada e capturada.
