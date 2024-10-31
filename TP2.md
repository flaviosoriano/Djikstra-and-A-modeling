

# Escapando da floresta da neblina

## 

## 

## Flávio Soriano de Souza Filho

2023001999

## **DCC \- UFMG**

# Introdução

O problema computacional envolve ajudar o herói lendário Linque a escapar da floresta da neblina, modelada como um grafo direcionado onde as clareiras são vértices e as trilhas são arestas. Além das trilhas, existem portais mágicos que conectam alguns vértices sem custo de energia. O objetivo é determinar se Linque pode chegar do vértice inicial (clareira 0\) ao vértice final (clareira n-1) consumindo no máximo uma quantidade determinada de energia e utilizando um número limitado de portais.

Para resolver esse problema, utilizamos os algoritmos de Dijkstra e A\*. Ambos foram adaptados para considerar as restrições de energia e uso de portais. O algoritmo de Dijkstra encontra o caminho de menor custo sem arestas de peso negativo, enquanto o algoritmo A\* utiliza uma heurística para guiar a busca de forma mais eficiente. Esta documentação detalha a implementação desses algoritmos, as adaptações realizadas, e apresenta uma análise experimental do desempenho das diferentes abordagens.

# Método

* #### Linguagens e Frameworks utilizados 

	Os métodos e seus testes foram escritos em c++ e compilados pelo compilador G++ da GNU Compiler Collection, todos os métodos utilizados são parte da STL e não foram utilizadas nenhuma estrutura de dados além do array simples. Os gráficos foram feitos em python, utilizando as bibliotecas “Pandas” (para os dataframes, obtidos através dos arquivos CSV), “matplot” (para a de fato plotagem dos gráficos), “scipy” (para o ajuste de curvas) e “sklearn” (para calcular o coeficiente de determinação (R²) para avaliar a qualidade do ajuste da curva).

* #### Estrutura de dados 

**ParOrdenado:** Representa as coordenadas x e y de um vértice, além de implementar um método que recebe outra coordenada e calcula a distância euclidiana entre elas.

**Vertex**: Representa um vértice no grafo e contém um identificador único, um conjunto de coordenadas (utilizando ParOrdenado), um ponteiro para uma lista de arestas (Aresta) e um contador de arestas que partem desse vértice. O struct Aresta é utilizado para armazenar e gerenciar as conexões entre o vértice e outros vértices. Cada aresta inclui um ponteiro para o vértice conectado, o tamanho da aresta e um indicador se é um portal, permitindo a criação e a navegação através da lista de adjacência de forma eficiente.

**PriorityQueue**: Implementa uma fila de prioridade usando um heap máximo. Utiliza o struct Caminho para armazenar e gerenciar os estados dos caminhos durante a execução dos algoritmos de Dijkstra e A\*. Cada instância de Caminho contém um ponteiro para o vértice atual, a distância acumulada até esse vértice, o número de portais usados e a heurística associada. O heap máximo é ajustado para manter o caminho com a menor distância no topo, facilitando a extração do caminho mais promissor e a inserção de novos caminhos durante a busca.

**Aresta**: Representa uma conexão entre dois vértices no grafo. Cada aresta possui um ponteiro para o vértice conectado, o tamanho da aresta, um indicador de se a aresta é um portal e um ponteiro para a próxima aresta. Este struct é utilizado para armazenar e gerenciar as conexões entre vértices na implementação do grafo.

**Caminho**: Representa um estado no processo de busca de caminho, utilizado nos algoritmos de Dijkstra e A\*. Inclui o vértice atual, o identificador do vértice, a distância acumulada até o vértice, o número de portais usados e a heurística associada. O struct é essencial para a gestão dos estados de caminhos na fila de prioridade durante a execução dos algoritmos de busca.

**GrafoL**: Classe que implementa um grafo usando uma lista de adjacência. Armazena o número total de vértices e arestas, uma lista de vértices e métodos para adicionar vértices e arestas. Implementa os algoritmos de Dijkstra e A\*, que utilizam a lista de adjacência para encontrar o caminho mais curto considerando o número máximo de portais e a energia disponível.

**GrafoM**: Classe que implementa um grafo usando uma matriz de adjacência. Contém atributos para o número de vértices e uma matriz que representa as arestas e seus respectivos pesos. Os métodos dijkstra e aEstrela realizam a busca de caminhos no grafo, utilizando a PriorityQueue e adaptados para trabalhar com a matriz de adjacência e considerar o máximo de portais e energia disponível.

* #### Funções e Métodos


	**Algoritmo de Dijkstra**

**Funcionamento:**

1. **Inicialização:**  
   * Criei uma matriz para armazenar as menores distâncias para cada vértice, considerando o número de portais utilizados. Iniciei todas as distâncias com um valor alto, representando que ainda não foram visitadas.  
   * Utilizei uma fila de prioridade para manter os vértices a serem processados, onde cada vértice tem uma prioridade baseada na sua distância acumulada.  
2. **Execução:**  
   * O processo inicia com o vértice inicial, que é colocado na fila de prioridade com distância zero.  
   * Em cada etapa, o vértice com a menor distância acumulada é retirado da fila e seus vizinhos são avaliados.  
   * Para cada aresta conectada ao vértice atual, calculei a nova distância e o número de portais utilizados. Se a nova distância encontrada é menor do que a anteriormente registrada, atualizei o valor e re-adicionei o vértice na fila de prioridade.  
3. **Conclusão:**  
   * O algoritmo continua até que o destino seja alcançado ou todos os possíveis caminhos sejam avaliados.  
   * Ao final, verifiquei se a menor distância encontrada até o destino está dentro da energia disponível e retornei o resultado correspondente.

obs: A única diferença entre as implementações em Grafos por Lista de adjacência ou por Matriz de adjacência é a maneira de percorrer as arestas (o primeiro por uma lista encadeada, enquanto o segundo percorre todas as colunas de uma linha na matriz) e a maneira de recuperar o tamanho da aresta (o primeiro utiliza a o atributo do struct aresta enquanto o segundo recupera o float guardado na matriz)

### **Algoritmo A\***

**Funcionamento:**

1. **Inicialização:**  
   * Inicializa uma matriz de distâncias similar ao algoritmo de Dijkstra, mas desta vez, inclui uma estimativa heurística que calcula o custo total até o destino.  
   * A fila de prioridade gerencia os vértices com base no custo total estimado, que é a soma da distância acumulada e da heurística.  
2. **Execução:**  
   * O algoritmo começa com o vértice inicial, colocando-o na fila com uma distância inicial e a heurística calculada para o destino.  
   * Em cada iteração, o vértice com o menor custo total estimado é retirado da fila e seus vizinhos são processados.  
   * Para cada aresta conectada ao vértice atual, calculei a nova distância e a heurística estimada. Se essa nova distância é menor do que a registrada e está dentro das restrições de energia e portais, os valores são atualizados e o vértice re-adicionado na fila de prioridade.  
3. **Conclusão:**  
   * O algoritmo continua até que o destino seja alcançado ou todos os caminhos possíveis sejam explorados.  
   * Ao final, compara-se o custo total mínimo encontrado com a energia disponível e retorna se o caminho é viável dentro das restrições.

# **Análise de Complexidade Teórica:**

**Matriz de Adjacência**

* **Tempo**:  
  * Verificar a existência de uma aresta O(1)  
  * Verificar os vizinhos de um vértice O(n)  
* Espaço: O(n2)

**Priority Queue:**

* Inserção (inserir): O(log n)  
* Remoção (retirar): O(log n)  
* Heapificação (maxHeapify): O(log n)  
* Verificação de vazio (empty): O(1)

**Lista de Adjacência**

* **Tempo:**  
  * Verificar a existência de uma aresta: O(n)  
  * Verificar os vizinhos de um vértice: O(n) no pior caso. No entanto, para grafos esparsos, a operação é geralmente mais rápida.  
* **Espaço**: Tem caso médio O(∣V∣+∣E∣), mas pode chegar a O(n²) no pior caso (grafos denso)

**Algoritmos na Lista de Adjacência**

**Dijkstra**: Utilizando uma lista de adjacência e uma fila de prioridade (heap), a complexidade do algoritmo é O((∣V∣+∣E∣)log⁡∣V∣, tendo pior caso em grafos densos: O (n² log n).. A eficiência é melhorada em comparação com a matriz de adjacência, especialmente em grafos esparsos, devido ao processamento reduzido das arestas.

***A*****\*:**  Para a lista de adjacência, a complexidade do A\* é O((∣V∣+∣E∣)log⁡∣V∣). A busca é mais eficiente devido ao uso da heurística, que ajuda a direcionar a busca e reduz o número de vértices processados em comparação com Dijkstra, garantindo, apesar do mesmo pior caso, resultados, em média, mais rápidos

**Algoritmos na Matriz de Adjacência**

**Dijkstra**: A complexidade do algoritmo de Dijkstra, utilizando uma matriz de adjacência e uma fila de prioridade, é O (VE) x O(log n), sendo V e E o número de vértices e arestas. Assim, como a matriz sempre registra V arestas,  temos a complexidade O (n² log n)

***A*****\*:** Similar ao Dijkstra, a complexidade do A\* com matriz de adjacência é O(n² log n) no pior caso, pois o algoritmo pode precisar avaliar todos os pares de vértices

# **Estratégias de robustez**

Para garantir a robustez e a eficiência do sistema, foram adotadas várias estratégias que englobam verificação de dados, tratamento de erros, validação de resultados intermediários e modularização do código

1- **Verificação de Integridade dos Dados de Entrada:**

* **Validação de Vértices e Arestas:** Ao adicionar vértices e arestas, o sistema realiza verificações para garantir que os identificadores dos vértices sejam válidos e que os dados sejam coerentes. É assegurado que arestas sejam adicionadas somente entre vértices existentes para evitar referências inválidas.  
  * **Checagem de Capacidade:** São implementadas verificações para garantir que o número de vértices e arestas não ultrapasse os limites definidos, evitando assim sobrecarga e falhas.

2. **Tratamento de Exceções e Erros:**  
   * **Mensagens de Erro:** São emitidas mensagens de erro em condições anormais, como ao tentar adicionar arestas entre vértices não existentes ou ao atingir a capacidade máxima permitida.  
   * **Controle de Fluxo:** O sistema controla o fluxo de execução para evitar o processamento de dados inválidos ou excessivos e interrompe a execução quando necessário para prevenir falhas.  
3. **Validação de Resultados Intermediários:**  
   * **Condições de Parada:** Algoritmos como Dijkstra e A\* incorporam condições de parada para interromper os cálculos quando o objetivo é alcançado ou quando não há mais caminhos viáveis.  
   * **Verificação de Distâncias e Portais:** Os resultados intermediários, como distâncias e número de portais usados, são validados durante a execução para garantir que não excedam os limites especificados.  
4. **Modularização do Código:**  
   * **Separação de Componentes:** O código é modularizado através da divisão em componentes distintos, como classes e funções específicas para manipulação de grafos, gerenciamento de filas de prioridade e execução de algoritmos. Essa separação facilita a manutenção e o entendimento do sistema.  
   * **Encapsulamento e Reutilização:** Utilizam-se classes e métodos encapsulados para abstrair a complexidade das operações internas e promover a reutilização de código. Por exemplo, a implementação de diferentes tipos de grafos (listas de adjacência e matrizes de adjacência) e algoritmos de busca são organizadas em módulos distintos.

Essas estratégias contribuem para um sistema mais robusto e flexível, com uma estrutura que facilita a identificação e resolução de problemas, além de permitir melhorias e expansões futuras

# **Análise Experimental da Complexidade**

Análise com variação de arestas:

Análise com variação de vértices:

#### **Comparação Dijkstra e A\* com Lista de Adjacência**

1. **Gráficos de Variação de Vértices:**  
   * Dijkstra e A\* têm comportamentos similares em termos de complexidade.  
   * Para a lista de adjacência, ambos os algoritmos parecem seguir a complexidade O((∣V∣+∣E∣)log⁡∣V∣)  
   * A linha de ajuste n log n tem um bom ajuste (R² \> 0.60), indicando que essa é uma boa representação da complexidade para ambos os algoritmos.  
2. **Gráficos de Variação de Arestas:**  
   * A complexidade n log⁡ novamente se ajusta bem aos dados.  
   * O A\* apresenta um R² significativamente maior (0.97) do que Dijkstra (0.61), indicando que o A\* pode ser mais eficiente com o aumento do número de arestas.

#### **Comparação Dijkstra e A\* com Matriz de Adjacência**

1. **Gráficos de Variação de Vértices:**  
   * A complexidade esperada para a matriz de adjacência é O(n2log⁡n),  devido ao maior número de operações necessárias para verificar a existência de arestas.  
   * A linha de ajuste n2log⁡nn^2 \\log nn2logn tem um R² de 0.59, o que é consistente com a complexidade teórica O(n2log⁡n)O(n^2 \\log n)O(n2logn).  
   * A menor precisão do ajuste, em comparação com a lista de adjacência, reflete o impacto da complexidade espacial e temporal maior da matriz de adjacência.  
2. **Gráficos de Variação de Arestas:**  
   * A complexidade n² log n se ajusta razoavelmente bem aos dados, com valores de R² próximos a 0.70.  
   * Assim, a complexidade teórica é comprovada pelo teste experimental.

### **Comparação de Implementações (Matriz vs. Lista de Adjacência)**

* **Impacto na Execução:**  
  * A lista de adjacência geralmente apresenta um desempenho melhor devido ao menor espaço e tempo necessários para verificar e processar arestas.  
  * Para grafos esparsos, a lista de adjacência é significativamente mais eficiente.  
  * A matriz de adjacência apresenta desempenho inferior, especialmente para grafos muito grandes, onde o espaço necessário é O(n2).  
* **Observações sobre o Ajuste dos Modelos:**  
  * O ajuste n log n é mais adequado para listas de adjacência, refletindo a eficiência melhorada com o aumento dos vértices e arestas.  
  * Para matrizes de adjacência, o ajuste n² log n se aproxima mais da complexidade esperada, refletindo o maior custo computacional.  
  * Além disso, a possibilidade de criar um grafo com mais de 1000000 de vértices para o experimento reflete a grande vantagem que a lista tem em relação a matriz, que sequer foi possível fazer grafos maiores do que 45.000 vértices sem que o próprio OS finalizasse a operação por uso excessivo de memória.

### **Conclusão**

* *Dijkstra vs. A:*\* O algoritmo A\* mostra uma eficiência melhor devido ao uso da heurística, o que é refletido nos altos valores de R² para a linha de ajuste n log n.  
* **Lista vs. Matriz de Adjacência:** A lista de adjacência é mais eficiente em termos de tempo de execução, especialmente para grafos esparsos. A matriz de adjacência, embora mais simples de implementar, é menos eficiente, refletindo a maior complexidade espacial e temporal.

**Análise da localidade de referência:**

A matriz de adjacência pode apresentar uma baixa localidade de referência em grafos esparsos devido ao grande número de entradas nulas, o que prejudica a eficiência do cache. Isso ocorre porque a memória é ocupada por dados que frequentemente não são utilizados, resultando em acesso não otimizado. Em contraste, a lista de adjacência organiza arestas em listas encadeadas, favorecendo uma localidade de referência mais eficiente ao acessar apenas as arestas existentes e mantendo dados relacionados próximos. Essa estrutura reduz as falhas de cache e melhora o desempenho, especialmente em grafos esparsos.

# Análise Experimental da Qualidade dos resultados

**Consistência das Soluções**

* **Dijkstra**: Sempre encontra a solução mais curta se um caminho viável existir, devido à sua busca exaustiva.  
* **A**\*: Mais rápido, mas pode não encontrar a solução ideal se a heurística não for adequada ou se os recursos forem limitados.

**Impacto dos Parâmetros de Entrada**

* **Energia**: Como demonstrado no gráfico acima, mais energia permite que ambos os algoritmos explorem mais nós, reduzindo a diferença de acerto entre Dijkstra e A\*. Com energia suficiente, A\* se aproxima do desempenho de Dijkstra.

**Variação dos Parâmetros**

* **Energia**: Aumentar a energia melhora o desempenho de A\*, tornando-o mais próximo ao de Dijkstra. Com baixa energia, Dijkstra mantém a vantagem.  
* **Portais**: Menos portais prejudicam ambos, mas Dijkstra, com sua busca completa, ainda encontra soluções melhores dentro das novas restrições, enquanto A\* é mais impactado pela heurística utilizada e, por isso, acaba não utilizando tão bem os portais

Resumindo, Dijkstra é mais confiável para soluções ótimas, enquanto A\* é mais rápido com possibilidade de resultados subótimos. Mais energia diminui a diferença de acerto entre eles

# Conclusão

Neste trabalho, investigamos os algoritmos de Dijkstra e A\* para encontrar o caminho mais eficiente em um grafo com restrições de energia e portais mágicos. A análise mostrou que o A\* é mais eficiente devido ao uso de heurísticas que melhoram o desempenho na busca, especialmente em grafos densos. Por outro lado, Dijkstra garante a solução ótima, sendo mais confiável em situações com restrições severas.

Comparando representações de grafos, a lista de adjacência demonstrou melhor desempenho do que a matriz de adjacência, principalmente para grafos grandes e esparsos, devido à sua menor complexidade espacial e temporal. A quantidade de energia disponível influencia o desempenho dos algoritmos, com o A\* se aproximando do desempenho do Dijkstra quando há mais energia.

Em suma, o A\* é mais rápido e eficiente com heurísticas adequadas, enquanto o Dijkstra é mais confiável para garantir soluções ótimas. A lista de adjacência é preferível à matriz de adjacência para a maioria dos casos práticos, especialmente em grafos grandes.

# Bibliografia

* Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.  
    
* Sedgewick, R., & Wayne, K. (2011). *Algorithms* (4th ed.). Addison-Wesley Professional.

  