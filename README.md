# Pratica integrada A — colaboracao e excecoes

Starter independente para os capitulos 09 e 10, planejado para 1h de estudo. O programa inicial compila e executa: painel e fontes funcionam, mas a aquisicao ainda nao distingue falta de calibracao. O codigo das demonstracoes anteriores nao e necessario.

O [guia da pratica no GitHub Pages](https://rafaelrezo.github.io/poo-colaboracao-excecoes/) conduz o primeiro incremento e delimita a extensao. A pagina fonte esta em `docs/index.md`.

## Para estudantes

1. Faca fork deste repositorio, clone o **seu fork** e confira que o unico remoto e `origin` apontando para ele.
2. Crie a branch `pratica/integrada-a`.
3. Execute `make run` para observar `Painel: 20`, `Fonte simulada: 42.5 %` e `Sem calibracao: leitura indevida: 20`; depois use `make test ETAPA=A` para ler a primeira pendencia.
4. Em `include/estacao.hpp` e `src/estacao.py`, lance `FalhaCalibracao` na condicao indicada; teste e registre um commit.
5. Capture essa falha antes de `FalhaLeitura` e devolva motivo `calibracao`. Confira `make run` e `make test ETAPA=A`; registre outro commit.
6. Preencha `docs/decisoes.md` e `AI_LOG.md`, envie a branch e abra uma PR para a `main` **do seu fork**. Anexe saida local, link da CI e justificativa tecnica.

O comando de teste e sempre `make test ETAPA=A`. Os testes sao cumulativos e visiveis; uma PR verde tambem precisa de revisao do diff e explicacao do aluno. Nunca abra PR para o repositorio do docente.

## Para o docente

O GitHub Pages usa `main` e `/docs`. Use `make run` para a conferencia visual local. O teste inicial deve falhar no lancamento de `FalhaCalibracao`; apos o incremento guiado deve falhar na classificacao da captura. Valide a solucao de referencia em uma copia privada antes de publicar alteracoes no starter. A CI executa testes funcionais nos pushes da branch prevista e na PR; a execucao da `main` confirma a baseline executavel.
