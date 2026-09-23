# Decisoes da pratica A

Explique, com referencia a uma chamada do programa:

1. Na falta de calibracao, qual funcao lanca, qual apenas propaga e qual recupera a falha? Responda para C++ e Python.
2. Por que a captura de `FalhaCalibracao` vem antes da de `FalhaLeitura`? Quando a sessao e liberada em cada linguagem?
3. Como `FonteNivel` e `FonteConstante` podem ser consultadas pelo mesmo contrato? Dê um exemplo observado em `make run`.

### Análise do Fluxo de Exceções (Prática A)

1. Onde a falha é lançada: A exceção FalhaCalibracao é lançada diretamente na função adquirir se a fonte estiver disponível mas não calibrada.
2. Onde a falha é propagada: A falha atravessa a função intermediária lerServico sem ser capturada, pois essa função não possui contexto ou decisão útil para tratar o problema com o operador.
3. Onde a falha é capturada: Ela é capturada na fronteira do cliente, especificamente na função executarCiclo / executar_ciclo, que intercepta o erro e formata uma resposta segura.
4. Liberação de Recursos: O recurso (sessão) é liberado antes de ocorrer a captura. Em C++, isso é garantido pelo padrão RAII através do destrutor da classe Sessao ao sair do escopo de adquirir. Em Python, isso ocorre dentro do bloco finally da mesma função. Isso impede o vazamento de sessões abertas.
5. Ordem de Captura: Como FalhaCalibracao herda de FalhaLeitura, a captura específica deve obrigatoriamente vir antes. Se a genérica viesse primeiro, ela capturaria o erro de calibração por polimorfismo, escondendo a causa real do operador.
