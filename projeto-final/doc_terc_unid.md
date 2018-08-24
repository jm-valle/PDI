#PDI - Trabalho Final - Matrizes de Co-ocorrência e Análise de Textura
Autores: João Marcos Araújo do Valle <jmarcos.araujo96@gmail.com>, Vanessa Dantas <vanessa.dantas796@gmail.com>

##Aplicação
Acessar via [Aplicação][link]

##Introdução
<p>Ao longo da terceira unidade da disciplina DCA0445 - Processamento Digital de Imagens, foram expostos em sala de aula vários métodos para a representação e descrição de regiões. Um desses foi a descrição de regiões por análise de textura, através de descritores de Haralick, calculados a partir de matrizes de co-ocorrência.</p>
<p>Esse trabalho teve por objetivo criar uma aplicação JavaScript onde uma imagem é carregada e a partir desta, são calculados, em tempo real, seis tipos de descritores diferentes para uma região de interesse específica da imagem, que é selecionada pelo usuário da aplicação.
</p>

##Referencial Teórico
<p>A textura é normalmente definida como uma superfície topográfica, com pontos altos e baixos. Uma textura áspera geralmente é caracterizada por uma grande diferença entre esses pontos em um espaço pequeno. Já uma textura lisa é caracterizada por pouca diferença em um espaço de mesmo tamanho.</p>
<p>A partir dessa definição de textura, podemos fazer um paralelo com texturas de imagens, onde, ao invés de termos diferenças entre pontos altos e baixos, temos a diferença entre o brilho dos pixels em uma região pré-estabelecida.
A análise da textura de uma imagem pode ser realizada de diversas maneiras. Uma destas maneiras é através da matriz de co-ocorrência, foco deste trabalho.</p> 
<p>A matriz de co-ocorrência é utilizada para retirar informações sobre as posições relativas dos pixels de uma imagem. Existem várias formas de se calcular uma matriz de co-ocorrência, e a sua finalidade é contabilizar a quantidade de vezes em que tons de cinza ocorreram lado a lado. Por exemplo, para a matriz de co-ocorrência G, os seus elementos gij contabilizam a quantidade de vezes que o tom de cinza j ocorreu à direita do tom de cinza i. Sendo assim, podemos definir a matriz de co-ocorrência como uma tabela de combinações de valores de níveis de cinza que ocorrem em uma imagem.</p>
<p>É importante ressaltar que esse método de analisar os pixels à direita é apenas uma de várias maneiras de se calcular a matriz de co-ocorrência. Essas estratégias serão mostradas mais a frente.
Também é importante destacar que geralmente as imagens analisadas apresentam até 256 tons de cinza, o que resultaria numa matriz de co-ocorrência de tamanho 256 x 256. Como essa matriz é relativamente grande, é comum quantizar as imagens, resultando assim em matrizes menores e cálculos mais rápidos.</p>

---

###Métodos para o cálculo da matriz de co-ocorrência
<p>Foi mencionado anteriormente que existem vários métodos de se calcular a matriz de co-ocorrência de uma imagem, o que é fácil de perceber quando relacionado com o conceito de vizinhança de um pixel. Se a matriz de co-ocorrência é definida como uma tabela de combinações de tons de cinza ocorridos em uma imagem, é justificável que essa tabela possa ser criada de qualquer combinação entre pixels relacionados através de uma vizinhança. Isso quer dizer que uma matriz de co-ocorrência pode ser calculada utilizando qualquer um dos oito pixels da vizinhança do pixel atual.</p>
<p>Matematicamente, uma matriz de co-ocorrência P pode ser definida em função de quatro valores _P(i, j, d, Theta)_. Onde i e j são os pixels vizinhos de acordo com a distância d. Essa distância d entre os pixels i e j é analisada de acordo com uma direção Theta, como pode ser observado na imagem abaixo.</p>
IMAGEM 1

<p>Para cada ângulo (0º, 45º, 90º e 135º) é possível calcular duas matrizes de co-ocorrência, totalizando assim oito matrizes no total. Também é possível calcular uma matriz para cada direção orientada por ângulo, o que resulta em quatro matrizes (horizontal, vertical e duas diagonais). Existem várias vantagens no cálculo desse tipo de matriz, uma delas é que a matriz de co-ocorrência conterá mais informação que uma criada apenas para apenas uma direção orientada por um ângulo. 
</p>
<p>Outra vantagem da matriz de co-ocorrência para cada direção orientada por ângulo é que ela pode ser facilmente calculada a partir da matriz de co-ocorrência normal de cada direção, visto que ela será a soma dos elementos da matriz espelhados pela diagonal da matriz.</p>
IMAGEM 2

<p>Após P ser calculada, normalmente, é também normalizada pela soma total de seus valores, criando assim uma matriz de probabilidade de co-ocorrências p(i,j) onde</p>
<p>A partir dessa matriz de probabilidades _p(i,j)_ é que as principais informações contidas na imagem serão retiradas.</p>

---

###Descritores de Haralick
<p>Apesar de uma matriz de co-ocorrência, por si só, apresentar muita informação, esta informação geralmente não é de fácil entendimento. Sendo assim, a partir dessa matriz, são calculados valores numéricos que facilitam o entendimento da informação que a matriz trás.</p>
<p>Estes valores, denominados descritores, são fundamentais para a análise de uma matriz de co-ocorrência. Haralick, em 1973, propôs 14 descritores diferentes que poderiam ser utilizados para a extração de informação da matriz de co-ocorrência, neste trabalho, foram implementados seis descritores de Haralick, mostrados na tabela abaixo.</p>
IMAGEM 3






