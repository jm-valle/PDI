<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [PDI - Trabalho Final - Matrizes de Co-ocorrência e Análise de Textura](#pdi---trabalho-final---matrizes-de-co-ocorr%C3%AAncia-e-an%C3%A1lise-de-textura)
  - [1. Aplicação](#1-aplica%C3%A7%C3%A3o)
  - [2. Introdução](#2-introdu%C3%A7%C3%A3o)
  - [3. Referencial Teórico](#3-referencial-te%C3%B3rico)
  - [4. Métodologia](#4-m%C3%A9todologia)
    - [4.1 Descritores de Haralick](#41-descritores-de-haralick)
  - [5. Interface](#5-interface)
  - [6. Código Desenvolvido](#6-c%C3%B3digo-desenvolvido)
- [Cálculo de Co-ocorrências e momentos estatísticos de uma região da imagem](#c%C3%A1lculo-de-co-ocorr%C3%AAncias-e-momentos-estat%C3%ADsticos-de-uma-regi%C3%A3o-da-imagem)
- [Cálculo de Co-ocorrências e momentos estatísticos de uma região da imagem](#c%C3%A1lculo-de-co-ocorr%C3%AAncias-e-momentos-estat%C3%ADsticos-de-uma-regi%C3%A3o-da-imagem-1)
  - [7. Explicação do Código](#7-explica%C3%A7%C3%A3o-do-c%C3%B3digo)
  - [8. Uso da aplicação](#8-uso-da-aplica%C3%A7%C3%A3o)
  - [9. Conclusões](#9-conclus%C3%B5es)
  - [10. Referências](#10-refer%C3%AAncias)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# PDI - Trabalho Final - Matrizes de Co-ocorrência e Análise de Textura
Autores: João Marcos Araújo do Valle <jmarcos.araujo96@gmail.com>, Vanessa Dantas <vanessa.dantas796@gmail.com>

---
Este material consiste no Trabalho Final da disciplina DCA0445 - Processamento Digital de Imagens lecionada por Agostinho Brito Jr.

## 1. Aplicação
Acessar via [Aplicação](index.hmtml)

---

## 2. Introdução
<p>Ao longo da terceira unidade da disciplina DCA0445 - Processamento Digital de Imagens, foram expostos em sala de aula vários métodos para a representação e descrição de regiões. Um desses foi a descrição de regiões por análise de textura, através de descritores de Haralick, calculados a partir de matrizes de co-ocorrência.</p>
<p>Esse trabalho teve por objetivo criar uma aplicação JavaScript onde uma imagem é carregada e a partir desta, são calculados, em tempo real, seis tipos de descritores diferentes para uma região de interesse específica da imagem, que é selecionada pelo usuário da aplicação.
</p>

---

## 3. Referencial Teórico
<p>A textura é normalmente definida como uma superfície topográfica, com pontos altos e baixos. Uma textura áspera geralmente é caracterizada por uma grande diferença entre esses pontos em um espaço pequeno. Já uma textura lisa é caracterizada por pouca diferença em um espaço de mesmo tamanho.</p>
<p>A partir dessa definição de textura, podemos fazer um paralelo com texturas de imagens, onde, ao invés de termos diferenças entre pontos altos e baixos, temos a diferença entre o brilho dos pixels em uma região pré-estabelecida.
A análise da textura de uma imagem pode ser realizada de diversas maneiras. Uma destas maneiras é através da matriz de co-ocorrência, foco deste trabalho.</p> 
<p>A matriz de co-ocorrência é utilizada para retirar informações sobre as posições relativas dos pixels de uma imagem. Existem várias formas de se calcular uma matriz de co-ocorrência, e a sua finalidade é contabilizar a quantidade de vezes em que tons de cinza ocorreram lado a lado. Por exemplo, para a matriz de co-ocorrência G, os seus elementos gij contabilizam a quantidade de vezes que o tom de cinza j ocorreu à direita do tom de cinza i. Sendo assim, podemos definir a matriz de co-ocorrência como uma tabela de combinações de valores de níveis de cinza que ocorrem em uma imagem.</p>
<p>É importante ressaltar que esse método de analisar os pixels à direita é apenas uma de várias maneiras de se calcular a matriz de co-ocorrência. Essas estratégias serão mostradas mais a frente.
Também é importante destacar que geralmente as imagens analisadas apresentam até 256 tons de cinza, o que resultaria numa matriz de co-ocorrência de tamanho 256 x 256. Como essa matriz é relativamente grande, é comum quantizar as imagens, resultando assim em matrizes menores e cálculos mais rápidos.</p>

---

## 4. Métodologia
<p>Foi mencionado anteriormente que existem vários métodos de se calcular a matriz de co-ocorrência de uma imagem, o que é fácil de perceber quando relacionado com o conceito de vizinhança de um pixel. Se a matriz de co-ocorrência é definida como uma tabela de combinações de tons de cinza ocorridos em uma imagem, é justificável que essa tabela possa ser criada de qualquer combinação entre pixels relacionados através de uma vizinhança. Isso quer dizer que uma matriz de co-ocorrência pode ser calculada utilizando qualquer um dos oito pixels da vizinhança do pixel atual.</p>
<p>Matematicamente, uma matriz de co-ocorrência P pode ser definida em função de quatro valores _P(i, j, d, Theta)_. Onde i e j são os pixels vizinhos de acordo com a distância d. Essa distância d entre os pixels i e j é analisada de acordo com uma direção Theta, como pode ser observado na imagem abaixo.</p>

[](/imagens/imagem1.png)
Figure 2. Valores possíveis para Theta

<p>Para cada ângulo (0º, 45º, 90º e 135º) é possível calcular duas matrizes de co-ocorrência, totalizando assim oito matrizes no total. Também é possível calcular uma matriz para cada direção orientada por ângulo, o que resulta em quatro matrizes (horizontal, vertical e duas diagonais). Existem várias vantagens no cálculo desse tipo de matriz, uma delas é que a matriz de co-ocorrência conterá mais informação que uma criada apenas para apenas uma direção orientada por um ângulo.</p>
<p>Outra vantagem da matriz de co-ocorrência para cada direção orientada por ângulo é que ela pode ser facilmente calculada a partir da matriz de co-ocorrência normal de cada direção, visto que ela será a soma dos elementos da matriz espelhados pela diagonal da matriz.</p>

[](/imagens/imagem2.png)
Figure 2. Cálculo da matriz de co-ocorrência para P(i,j,1,0º)

<p>Após P ser calculada, normalmente, é também normalizada pela soma total de seus valores, criando assim uma matriz de probabilidade de co-ocorrências p(i,j) onde</p>

[](/imagens/imagem3.png)
Figure 3. Matriz de probabilidade

<p>A partir dessa matriz de probabilidades _p(i,j)_ é que as principais informações contidas na imagem serão retiradas.</p>


### 4.1 Descritores de Haralick
<p>Apesar de uma matriz de co-ocorrência, por si só, apresentar muita informação, esta informação geralmente não é de fácil entendimento. Sendo assim, a partir dessa matriz, são calculados valores numéricos que facilitam o entendimento da informação que a matriz trás.</p>
<p>Estes valores, denominados descritores, são fundamentais para a análise de uma matriz de co-ocorrência. Haralick, em 1973, propôs 14 descritores diferentes que poderiam ser utilizados para a extração de informação da matriz de co-ocorrência, neste trabalho, foram implementados seis descritores de Haralick, mostrados na tabela abaixo.</p>

[](/imagens/imagem4.png)
Figure 4. Tabela com o cálculo dos descritores de Haralick

---

## 5. Interface
<p>Para a aplicação desenvolvida, implementamos uma interface dividida entre cabeçalho, corpo e rodapé. No cabeçalho, inserimos o título do trabalho "Cálculo de Co-ocorrências e momentos estatísticos de  uma região da imagem". No corpo, foram criadas duas regiões, uma destinada para o carregamento da imagem e exibição da região de interesse, e outra, para exibir as informações de co-ocorrências e modificar os parâmetros que delimitam a região de interesse (representada por um quadrado preto). No rodapé, apenas inserimos informações acerca do trabalho e direitos autorais. Além disso, foi feito um botão de retorno, permitindo ao usuário voltar a página do relatório do trabalho. Conforme a imagem:</p>

[](/imagens/imagem5.png)
Figure 5. Interface da aplicação

## 6. Código Desenvolvido
<p> Para o trabalho descrito, desenvolvemos um código utilizando as linguagens Html e JavaScript. O Html foi responsável pela criação da estrutura da página WEB, já o CSS permitiu estilização da página. Por fim, o JavaScript corresponde ao funcionamento da estrutura WEB. Ele que possibilitou o uso de recursos do openCV.js para manipulação de imagens. Abaixo, o código desenvolvido: </p>

´´´html

        <html>

        <head>
        <meta charset="utf-8">
        <div id="header" style="background-color:#4A708B;">
        <h1 align="center" style="margin-bottom:0;color:white;" >Cálculo de Co-ocorrências e momentos estatísticos de uma região da imagem</h1>

        </div>

        </head>

        <body>

        <div id="Informacoes" style="background-color:#6CA6CD;height:100%;width:25%;float:right;">


        <h2 align="center" style="color:Black;" > Co-ocorrências </h2>



        <text1 style="margin-left:1em;" id="ProbMax"> Probabilidade Máxima </text1>

        <br />

        <text2 style="margin-left:1em;" id="Correlacao"> Correlação </text2>

        <br />

        <text3 style="margin-left:1em;" id="Contraste"> Contraste </text3>

        <br />

        <text4 style="margin-left:1em;" id="Uniformidade"> Uniformidade </text4>

        <br />

        <text5 style="margin-left:1em;" id="Homogeneidade"> Homogeneidade </text5>

        <br />

        <text6 style="margin-left:1em;" id="Entropia"> Entropia </text6>

        <br />

        <h3 align="center" style="color:Black;" > Definir Área de Interesse</h3>

        <div class="slidecontainer" id="slideContainer" style="margin-left:1em;height:30%">

                  <p>Mover Horizontalmente:</p>
                  <input type="range" min="0" max="100" value="50" id="moverHorizontalmente" onchange="change()">

                  <p>Mover Verticalmente:</p>
                  <input type="range" min="0" max="100" value="50" id="moverVerticalmente" onchange="change()">

        <p>Tamanho da Região de Interesse:</p>
                  <input type="range" min="1" max="100" value="50" id="ladoQuadrado" onchange="change()">


        </div>

        <!-- Botao para retornar à página principal-->

        <button onclick="Retornar()" id="botaoRetornar" style="margin-left:45%;">Retornar</button>


        </div>

        <div id="CarregamentoDaImagem">
                <table style="background-color:#B0E2FF;height:100%;width:75%;" cellpadding="0" cellspacing="0" width="0" border="0" id="table">

        <tr>
                <td>
                        <div class="caption" id="inputcaption">Imagem de Entrada</div>
                </td>
                <td>
                        <div class="caption" id="ouputcaption">Região de Interesse</div>
                </td>
                </tr>


                <tr>
                <td>
                        <input type="file" name="myFile" id="fileUpload"/> <br />
                </td>
                <td>
                                <p>A região de interesse está limitada pelo retângulo</p>

                </td>

                </tr>

                <tr>
                <td>
                        <img src="" alt="Carregar Imagem..." width="350em" height="" style="border:1px solid #d3d3d3;" id="imagem"/>
                </td>
                <td>
                        <canvas id="canvasOutput" width="" height="" style="border:1px solid #d3d3d3;"></canvas>
                </td>

                </tr>

        </table>
        </div>
        <!-- Javascript -->
        <script src="opencv.js" type="text/javascript"></script>
        <script type="text/javascript">
                //carregar imagem
                let imgElement = document.getElementById('imagem');
                let inputElement = document.getElementById('fileUpload');
                inputElement.addEventListener('change', (e) => {
                imgElement.src = URL.createObjectURL(e.target.files[0]);
                }, false);

                imgElement.onload = function() {
                change();
                };

                function change(){

                        var largura=document.getElementById("imagem").width;

                        //com base nos trackbars definimos a regiao de interesse RI
                var posHor=document.getElementById("moverHorizontalmente").value;
                var posVert=document.getElementById("moverVerticalmente").value;


                var altura=document.getElementById("imagem").height;


                var tamLado=document.getElementById("ladoQuadrado").value;
                tamLado=tamLado*largura/100;

                var RI_yIn=posHor*largura/100;
                var RI_xIn=posVert*altura/100;

                var RI_xFim=RI_xIn+tamLado;
                var RI_yFim=RI_yIn+tamLado;

                if(RI_xFim>altura){
                        tamLado=(altura-RI_xIn);
                        RI_xFim=RI_xIn+tamLado;
                                RI_yFim=RI_yIn+tamLado;
                }
                        if(RI_yFim>largura){
                        tamLado=(largura-RI_yIn);
                        RI_xFim=RI_xIn+tamLado;
                                RI_yFim=RI_yIn+tamLado;
                }

                //converter imagem para matriz para tons de cinza
                        let mat = cv.imread(imgElement);
                        let image = new cv.Mat();
                        let gray = new cv.Mat();
                        cv.cvtColor(mat, gray, cv.COLOR_RGBA2GRAY, 0);
                        gray.copyTo(image);

                //desenhar retangulo (Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
                let rect = new cv.Rect(RI_yIn,RI_xIn,tamLado,tamLado);
                        let rectangleColor = new cv.Scalar(0, 0, 0);

                        let point1 = new cv.Point(rect.x, rect.y);
                        let point2 = new cv.Point(rect.x + rect.width, rect.y + rect.height);
                        cv.rectangle(gray, point1, point2, rectangleColor, 2, cv.LINE_AA, 0);

                //exibir imagem com o retangulo desenhado
                        cv.imshow('canvasOutput', gray);


                        //calcular co-ocorrencias
                        var soma =0;
                        var i;
                        var j;

                        for (i = RI_yIn; i < RI_yFim; i++) {
                                for(j = RI_xIn; j< RI_xFim;j++){
                                        soma=soma+image.ucharPtr(i,j)[0];
                                }
                        }
                        //pij == image/soma

                        //probabilidade maxima

                        let result = cv.minMaxLoc(image);
                        let max = result.maxVal;
                let probMax=max/soma;
                document.getElementById("ProbMax").innerHTML='Probabilidade Máxima: '+probMax.toString();

                //correlacao

                //calcular mr
                let mr=0;
                for (i = RI_yIn; i < RI_yFim; i++) {
                                for(j = RI_xIn; j< RI_xFim;j++){
                                        mr=mr+i*(image.ucharPtr(i,j)[0]/soma);
                                }
                        }

                        //calcular mc
                        let mc=0;
                        for(j = RI_xIn; j< RI_xFim;j++){
                                for (i = RI_yIn; i < RI_yFim; i++) {
                                        mc=mc+j*(image.ucharPtr(i,j)[0]/soma);
                                }
                        }

                        //calcular deltar
                        let deltar=0;
                for (i = RI_yIn; i < RI_yFim; i++) {
                                for(j = RI_xIn; j< RI_xFim;j++){
                                        deltar=deltar+(i-mr)*(i-mr)*(image.ucharPtr(i,j)[0]/soma);
                                }
                        }
                        deltar=Math.sqrt(deltar);
                        //calcular deltac
                        let deltac=0;
                        for(j = RI_xIn; j< RI_xFim;j++){
                                for (i = RI_yIn; i < RI_yFim; i++) {
                                        deltac=deltac+(j-mc)*(j-mc)*(image.ucharPtr(i,j)[0]/soma);
                                }
                        }
                        deltac=Math.sqrt(deltac);

                        //Agora podemos calcular a correlacao
                        let correlacao=0;

                        for (i = RI_yIn; i < RI_yFim; i++) {
                                for(j = RI_xIn; j< RI_xFim;j++){
                                        correlacao=correlacao+(i-mr)*(j-mc)*(image.ucharPtr(i,j)[0]/soma)/(deltac*deltar);
                                }
                        }

                        document.getElementById("Correlacao").innerHTML='Correlação: '+correlacao.toString();
                        //contraste

                        let contraste=0;

                        for (i = RI_yIn; i < RI_yFim; i++) {
                                for(j = RI_xIn; j< RI_xFim;j++){
                                        contraste=contraste+(i-j)*(i-j)*(image.ucharPtr(i,j)[0]/soma);
                                }
                        }



                        document.getElementById("Contraste").innerHTML='Contraste: '+contraste.toString();

                        //uniformidade

                        let uniformidade=0;

                        for (i = RI_yIn; i < RI_yFim; i++) {
                                for(j = RI_xIn; j< RI_xFim;j++){
                                        uniformidade=uniformidade+(image.ucharPtr(i,j)[0]/soma)*(image.ucharPtr(i,j)[0]/soma);
                                }
                        }

                        document.getElementById("Uniformidade").innerHTML='Uniformidade: '+uniformidade.toString();

                        //homogeneidade

                        let homogeneidade=0;

                        for (i = RI_yIn; i < RI_yFim; i++) {
                                for(j = RI_xIn; j< RI_xFim;j++){
                                        homogeneidade=homogeneidade+(image.ucharPtr(i,j)[0]/soma)/(1+Math.abs(i-j));
                                }
                        }


                        document.getElementById("Homogeneidade").innerHTML='Homogeneidade: '+homogeneidade.toString();

                        //entropia

                        let entropia=0;

                        for (i = RI_yIn; i < RI_yFim; i++) {
                                for(j = RI_xIn; j< RI_xFim;j++){
                                        if(image.ucharPtr(i,j)[0]!=0){
                                                entropia=entropia+(image.ucharPtr(i,j)[0]/soma)*Math.log2(soma/image.ucharPtr(i,j)[0]);
                                        }else{
                                                entropia=entropia+(image.ucharPtr(i,j)[0]/soma)*Math.log2(soma/0.0001);
                                        }

                                }
                        }
                        document.getElementById("Entropia").innerHTML='Entropia: '+entropia.toString();

                        mr.delete();
                        mc.delete();
                        deltar.delete();
                        deltac.delete();
                        correlacao.delete();
                        contraste.delete();
                        probMax.delete();
                        uniformidade.delete();
                        homogeneidade.delete();
                        entropia.delete();
                        max.delete();
                        result.delete();
                        pij.delete();
                        posHor.delete();
                        posVert.delete().
                        tamLado.delete();
                        altura.delete();
                        largura.delete();
                        RI_xIn.delete();
                        RI_yIn.delete();
                        RI_xFim.delete();
                        RI_yFim.delete();
                        gray.delete();
                        mat.delete();
                image.delete();
                rect.delete();
                rectangleColor.delete();
                point1.delete();
                point2.delete();

                }


                //redirecionar para a pagina inicial do trabalho
                function Retornar()
                {
                        location.href="https://vanessadants.github.io/PDI/TrabFinal/index.html";
                }

                function onOpenCvReady() { // eslint-disable-line no-unused-vars
                document.getElementById('status').innerHTML = '<b>OpenCV.js is ready</b>.' +
                        'You can upload an image.<br>' +
                        'The <b>imageSrc</b> is a &lt;img&gt; element used as cv.Mat input. ' +
                        'The <b>canvasOutput</b> is a &lt;canvas&gt; element used as cv.Mat output.';
                }

                function onOpenCvError() { // eslint-disable-line no-unused-vars
                let element = document.getElementById('status');
                element.setAttribute('class', 'err');
                element.innerHTML = 'Failed to load opencv.js';
                }




        </script>
        <script async src="opencv.js" type="text/javascript" onload="onOpenCvReady();" onerror="onOpenCvError();"></script>

        </body>

        <footer>
                <div id="footer" style="background-color:#9FB6CD;clear:both;text-align:center;float:bottom;font-size:12">
                Trabalho da terceira unidade de Processamento Digital de Imagens da Universidade Federal do RN do curso de Engenharia da Computação. Este trabalho foi feito por Vanessa Dantas de Souto Costa (vanessa.dantas796@gmail.com) e  João Marcos Araújo do Valle (jmarcos.araujo96@gmail.com), professor orientador: Agostinho Brito Jr.
                </div>

        </footer>

        </html>
´´´

## 7. Explicação do Código
<p>Primeiramente, na estrutura do html implementamos o cabeçalho <head>, nele especificamos a cor de fundo através de style="background-colo:#4A708B". Veja: </p>

´´´html

        <html>

        <head>
        <meta charset="utf-8">
        <div id="header" style="background-color:#4A708B;">
        <h1 align="center" style="margin-bottom:0;color:white;" >Cálculo de Co-ocorrências e momentos estatísticos de uma região da imagem</h1>

        </div>

        </head>
´´´

<p>Em seguida, na primeira parte do corpo da estrutura html "<body>", foi criada a região para exibir os cálculoiis das co-ocorrências e os sliders responsáveis pela delimitação da região de interesse, bem como o botão de retorno. Esta região foi criada com id="Informacoes".</p>

 <p>Para as informações de co-ocorrências exibidas, apenas criamos uma região do tipo texto, na qual pudéssemos exibir os resultados calculados.</p>

 ´´´javascript

        <h2 align="center" style="color:Black;" > Co-ocorrências </h2>



        <text1 style="margin-left:1em;" id="ProbMax"> Probabilidade Máxima </text1>

        <br />

        <text2 style="margin-left:1em;" id="Correlacao"> Correlação </text2>

        <br />

        <text3 style="margin-left:1em;" id="Contraste"> Contraste </text3>

        <br />

        <text4 style="margin-left:1em;" id="Uniformidade"> Uniformidade </text4>

        <br />

        <text5 style="margin-left:1em;" id="Homogeneidade"> Homogeneidade </text5>

        <br />

        <text6 style="margin-left:1em;" id="Entropia"> Entropia </text6>

        <br />

        <h3 align="center" style="color:Black;" > Definir Área de Interesse</h3>
 ´´´

 <p>Quanto aos sliders, utilizamos a classe "slidecontainer" que permite criar um elemento do tipo slider com range determinado (podemos determinar o valor mínimo e máximo). Qualquer modificação do valor do slider resulta na chamada da função change(), em onchange="change()".</p>

 ´´´javascript

    <div class="slidecontainer" id="slideContainer" style="margin-left:1em;height:30%">

                  <p>Mover Horizontalmente:</p>
                  <input type="range" min="0" max="100" value="50" id="moverHorizontalmente" onchange="change()">

                  <p>Mover Verticalmente:</p>
                  <input type="range" min="0" max="100" value="50" id="moverVerticalmente" onchange="change()">

                <p>Tamanho da Região de Interesse:</p>
                  <input type="range" min="1" max="100" value="50" id="ladoQuadrado" onchange="change()">


        </div>
 ´´´

<p>Ainda, a última função implementada na div de id="Informacoes" foi o botão de retorno. Para tanto, criamos um elemento do tipo button que ao ser clicado executa a função Retornar em onclick="Retornar()", conforme:</p>
 ´´´javascript

<!-- Botao para retornar à página principal-->

        <button onclick="Retornar()" id="botaoRetornar" style="margin-left:45%;">Retornar</button>
´´´
<p>Em seguida, na segunda parte do corpo da estrutura html <body>, foi criada a região para carregamento da imagem e exibição da região de interesse com id="CarregamentoDaImagem".</p>

<p>Para o carregamento da imagem, utilizamos o tipo file para escolher o arquivo a ser carregado em:</p>
´´´javacript

        <input type="file" name="myFile" id="fileUpload"/> <br />
´´´
<p>Este determinou a imagem a ser exibida no tipo imagem:</p>
´´´javascript

        <img src="" alt="Carregar Imagem..." width="350em" height="" style="border:1px solid #d3d3d3;" id="imagem"/>
´´´
<p>Uma vez a imagem carregada, podemos determinar a região de interesse. Essa última foi exibida em uma estrutura do tipo canvas, própria para manipulação de imagens com o openCV.js</p>
´´´javascript

        <canvas id="canvasOutput" width="" height="" style="border:1px solid #d3d3d3;"></canvas>
´´´
<p>Então exibimos essa estrutura inteira como uma tabela, para que a imagem de entrada e região de interesse ficassem uma ao lado da outra. Para isso usamos o tipo tabela:</p>
´´´javascript

        <table style="background-color:#B0E2FF;height:100%;width:75%;" cellpadding="0" cellspacing="0" width="0" border="0" id="table">
´´´
<p>O responsável pelo carregamento da imagem e cálculo das co-ocorrências foi o script na linguagem JavaScript. Este inicia com:</p>
´´´javascript

        <script src="opencv.js" type="text/javascript"></script>
        <script type="text/javascript">
´´´
<p>Permitindo o uso do openCV.js e finaliza com:</p>
´´´javascript

        </script>
        <script async src="opencv.js" type="text/javascript" onload="onOpenCvReady();" onerror="onOpenCvError();"></script>
´´´
<p>Neste script, a primeira função realizada é a de abertura e carregamento da imagem. Isto é feia através de: </p>
´´´javascript
//carregar imagem
        let imgElement = document.getElementById('imagem');
        let inputElement = document.getElementById('fileUpload');
        inputElement.addEventListener('change', (e) => {
            imgElement.src = URL.createObjectURL(e.target.files[0]);
        }, false);

        imgElement.onload = function() {
            change();
        };
´´´
<p>Nesta vemos que imgElement recebe o elemento imagem e que o inputElement recebe o file que foi escolhido pelo usuário para ser carregado. Assim, adicionamos o elemento a lista de eventos e fazemos a imagem receber como src o url do file escolhido. Ao carregar a imagem, chamamos a função change();</p>

<p>Na função change(), primeiramente definimos a região de interesse, através do código:</p>
´´´javascript

//com base nos trackbars definimos a regiao de interesse RI
            var posHor=document.getElementById("moverHorizontalmente").value;
            var posVert=document.getElementById("moverVerticalmente").value;


            var altura=document.getElementById("imagem").height;


            var tamLado=document.getElementById("ladoQuadrado").value;
            tamLado=tamLado*largura/100;

            var RI_yIn=posHor*largura/100;
            var RI_xIn=posVert*altura/100;

            var RI_xFim=RI_xIn+tamLado;
            var RI_yFim=RI_yIn+tamLado;

            if(RI_xFim>altura){
                    tamLado=(altura-RI_xIn);
                    RI_xFim=RI_xIn+tamLado;
                           RI_yFim=RI_yIn+tamLado;
            }
                if(RI_yFim>largura){
                    tamLado=(largura-RI_yIn);
                    RI_xFim=RI_xIn+tamLado;
                           RI_yFim=RI_yIn+tamLado;
            }
´´´
<p>Neste, calculamos o x inicial e final, bem como o y inicial e final. Em outras palavras, para cálculo das co-ocorrências, percorremos a imagem apenas nessa região. Vale ressaltar que utilizamos o sistema de coordenadas de openCV, cuja orientação é dada por:</p>

![](/imagens/imagem6.png)
Figure 6. Orientação utilizada, x corresponde à altura e y à largura da imagem

<p>Agora, podemos exibir a imagem (a imagem precisa ser em tons de cinza, por isso é feita uma conversão) no canvas e sua região de interesse, fazemos isso em:</p>
´´´javascript
        //converter imagem para matriz para tons de cinza
                let mat = cv.imread(imgElement);
                let image = new cv.Mat();
                let gray = new cv.Mat();
                cv.cvtColor(mat, gray, cv.COLOR_RGBA2GRAY, 0);
                gray.copyTo(image);

            //desenhar retangulo (Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
            let rect = new cv.Rect(RI_yIn,RI_xIn,tamLado,tamLado);
                let rectangleColor = new cv.Scalar(0, 0, 0);

                let point1 = new cv.Point(rect.x, rect.y);
                let point2 = new cv.Point(rect.x + rect.width, rect.y + rect.height);
                cv.rectangle(gray, point1, point2, rectangleColor, 2, cv.LINE_AA, 0);

            //exibir imagem com o retangulo desenhado
                cv.imshow('canvasOutput', gray);
´´´
<p>No passo seguinte, é calculado os descritores de Haralick. Para isso, precisamos da somatória dos valores da matriz image de entrada dentro da região de interesse:</p>
´´´javascript

                var soma =0;
                var i;
                var j;

                for (i = RI_yIn; i < RI_yFim; i++) {
                        for(j = RI_xIn; j< RI_xFim;j++){
                                soma=soma+image.ucharPtr(i,j)[0];
                        }
                }
                //pij == image/soma
´´´
<p>O cálculo da probabilidade máxima mostrado na "Figure4: Tabela com o cálculo dos descritores de Haralick" é então feito e exibido na região de texto destinada a mesma.</p>
´´´javascript
        //probabilidade maxima

                let result = cv.minMaxLoc(image);
                let max = result.maxVal;
            let probMax=max/soma;
            document.getElementById("ProbMax").innerHTML='Probabilidade Máxima: '+probMax.toString();
´´´
<p>O cálculo da correlação mostrado na "Figure4" é então feito e exibido na região de texto destinada a mesma.</p>
´´´javascript
        //correlacao

            //calcular mr
            let mr=0;
            for (i = RI_yIn; i < RI_yFim; i++) {
                        for(j = RI_xIn; j< RI_xFim;j++){
                                mr=mr+i*(image.ucharPtr(i,j)[0]/soma);
                        }
                }

                //calcular mc
                let mc=0;
                for(j = RI_xIn; j< RI_xFim;j++){
                        for (i = RI_yIn; i < RI_yFim; i++) {
                                mc=mc+j*(image.ucharPtr(i,j)[0]/soma);
                        }
                }

                //calcular deltar
                let deltar=0;
            for (i = RI_yIn; i < RI_yFim; i++) {
                        for(j = RI_xIn; j< RI_xFim;j++){
                                deltar=deltar+(i-mr)*(i-mr)*(image.ucharPtr(i,j)[0]/soma);
                        }
                }
                deltar=Math.sqrt(deltar);
                //calcular deltac
                let deltac=0;
                for(j = RI_xIn; j< RI_xFim;j++){
                        for (i = RI_yIn; i < RI_yFim; i++) {
                                deltac=deltac+(j-mc)*(j-mc)*(image.ucharPtr(i,j)[0]/soma);
                        }
                }
                deltac=Math.sqrt(deltac);

                //Agora podemos calcular a correlacao
                let correlacao=0;

                for (i = RI_yIn; i < RI_yFim; i++) {
                        for(j = RI_xIn; j< RI_xFim;j++){
                                correlacao=correlacao+(i-mr)*(j-mc)*(image.ucharPtr(i,j)[0]/soma)/(deltac*deltar);
                        }
                }

                document.getElementById("Correlacao").innerHTML='Correlação: '+correlacao.toString();
´´´javascript
<p>O cálculo do contraste mostrado na "Figure4" é então feito e exibido na região na região de texto destinada a mesma.</p>
´´´javascript
                //contraste

                let contraste=0;

                for (i = RI_yIn; i < RI_yFim; i++) {
                        for(j = RI_xIn; j< RI_xFim;j++){
                                contraste=contraste+(i-j)*(i-j)*(image.ucharPtr(i,j)[0]/soma);
                        }
                }



                document.getElementById("Contraste").innerHTML='Contraste: '+contraste.toString();
´´´
<p>O cálculo da uniformidade máxima mostrada na "Figure4" é então feito e exibido na região de texto destinada a mesma.</p>
´´´javascript
                //uniformidade

                let uniformidade=0;

                for (i = RI_yIn; i < RI_yFim; i++) {
                        for(j = RI_xIn; j< RI_xFim;j++){
                                uniformidade=uniformidade+(image.ucharPtr(i,j)[0]/soma)*(image.ucharPtr(i,j)[0]/soma);
                        }
                }
                document.getElementById("Uniformidade").innerHTML='Uniformidade: '+uniformidade.toString();
´´´
<p>O cálculo da homogeneidade máxima mostrado na "Figure4" é então feito e exibido na região de texto destinada a mesma.</p>
´´´javascript
                //homogeneidade

                let homogeneidade=0;

                for (i = RI_yIn; i < RI_yFim; i++) {
                        for(j = RI_xIn; j< RI_xFim;j++){
                                homogeneidade=homogeneidade+(image.ucharPtr(i,j)[0]/soma)/(1+Math.abs(i-j));
                        }
                }
                document.getElementById("Homogeneidade").innerHTML='Homogeneidade: '+homogeneidade.toString();
´´´
<p>O cálculo da entropia máxima mostrada na "Figure4" é então feito e exibido na região de texto destinada a mesma.</p>
´´´javascript
                //entropia

                let entropia=0;

                for (i = RI_yIn; i < RI_yFim; i++) {
                        for(j = RI_xIn; j< RI_xFim;j++){
                                if(image.ucharPtr(i,j)[0]!=0){
                                        entropia=entropia+(image.ucharPtr(i,j)[0]/soma)*Math.log2(soma/image.ucharPtr(i,j)[0]);
                                }else{
                                        entropia=entropia+(image.ucharPtr(i,j)[0]/soma)*Math.log2(soma/0.0001);
                                }

                        }
                }
                document.getElementById("Entropia").innerHTML='Entropia: '+entropia.toString();
´´´
<p>Antes de finalizar a função change(), liberamos o espaço ocupado pelas variáveis:</p>
´´´javascript
                mr.delete();
                mc.delete();
                deltar.delete();
                deltac.delete();
                correlacao.delete();
                contraste.delete();
                probMax.delete();
                uniformidade.delete();
                homogeneidade.delete();
                entropia.delete();
                max.delete();
                result.delete();
                pij.delete();
                posHor.delete();
                posVert.delete().
                tamLado.delete();
                altura.delete();
                largura.delete();
                RI_xIn.delete();
                RI_yIn.delete();
                RI_xFim.delete();
                RI_yFim.delete();
                gray.delete();
                mat.delete();
                    image.delete();
                    rect.delete();
                    rectangleColor.delete();
                    point1.delete();
                    point2.delete();
´´´
<p>Em seguida, descrevemos a função que permite que retorne à página anterior, ao clicar neste botão:</p>
´´´javascript
        //redirecionar para a pagina inicial do trabalho
        function Retornar()
        {
                location.href="https://vanessadants.github.io/PDI/TrabFinal/index.html";
        }
´´´
<p>As funções seguintes, servem para verificar se o openCV.js está pronto executar ou se houve erro:</p>
´´´javascript
        function onOpenCvReady() { // eslint-disable-line no-unused-vars
            document.getElementById('status').innerHTML = '<b>OpenCV.js is ready</b>.' +
                'You can upload an image.<br>' +
                'The <b>imageSrc</b> is a &lt;img&gt; element used as cv.Mat input. ' +
                'The <b>canvasOutput</b> is a &lt;canvas&gt; element used as cv.Mat output.';
        }

        function onOpenCvError() { // eslint-disable-line no-unused-vars
            let element = document.getElementById('status');
            element.setAttribute('class', 'err');
            element.innerHTML = 'Failed to load opencv.js';
        }
´´´
<p>Finalizado o script JavaScript e o corpo do html, inserimos um rodapé com informações sobre direitos autorais do trabalho.</p>
´´´javascript

<footer>
        <div id="footer" style="background-color:#9FB6CD;clear:both;text-align:center;float:bottom;font-size:12">
        Trabalho da terceira unidade de Processamento Digital de Imagens da Universidade Federal do RN do curso de Engenharia da Computação. Este trabalho foi feito por Vanessa Dantas de Souto Costa (vanessa.dantas796@gmail.com) e  João Marcos Araújo do Valle (jmarcos.araujo96@gmail.com), professor orientador: Agostinho Brito Jr.
        </div>

</footer>
´´´

---
## 8. Uso da aplicação

<p>Passo 1: Carregar a imagem</p>

![](/imagens/imagem7.png)
Figure 7. Clique para abrir o explorador de arquivos

![](/imagens/imagem8.png)
Figure 8. Escolher a imagem a ser aberta

<p>Passo 2: Delimitar a região de interesse.</p>

![](/imagens/imagem9.png)
Figure 9. Movendo os sliders é possível delimitar a região de interesse

<p>Pode-se perceber que modificar a região de interesse afeta diretamente nos cálculos:</p>

![](/imagens/imagem10.png)
Figure 10. Região de interesse 1

![](/imagens/imagem11.png)
Figure 11. Região de interesse 2

## 9. Conclusões

<p>Para a proposta do trabalho, pode-se perceber que o programa desenvolvido obteve boa performance. Para tanto, os requisitos tidos como desejáveis foram: interface amigável e fácil de usar, cálculo de co-ocorrências que variasse dependendo da região de interesse delimitada, possibilidade de ajuste da região de interesse e possibilidade de carregar imagens coloridas e em tons de cinza. Nesses requisitos, a apllicação atendeu a todos.</p>

<p>A importância dos descritores de Haralick se dá também no campo de identificação de objetos usando inteligência artificial, uma vez que, esses descritores permitem aprimorar o processo de extração de features para "alimentar" a IA. Por isso, vemos que o desenvolvimento desse trabalho foi imprescindível para nossa formação acadêmica.</p>

## 10. Referências

