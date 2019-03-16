# SOMBRA
SOMBRA (Simple Objects Minimal Bidimensional RAsterizer) é um programa que renderiza imagens bidimensionais simples a partir de uma descrição de cena definida em um arquivo XML.

## Como executar
Basta utilizar o comando make para compilar o executável e em seguida executá-lo com
````
bin/exe [arquivo_de_entrada] [nome_do_arquivo_de saida]
````
Esse comando executará o renderizador lendo um dado arquivo XML e criará um arquivo de imagem .ppm com o nome de saída inserido.

Exemplo de execução:
````
bin/exe example.xml example
````

## Linguagem de Descrição
O arquivo de descrição lê objetos a partir do arquivo XML fornecido e os desenha na imagem final. A seguir são descritos os tipos de objetos existentes.

### Canvas
O canvas no qual a imagem será desenhado. É composto por um conjunto de pontos (x, y) tendo o seu valor (0, 0) na ponta do topo da esquerda, com valores de x crescendo para a direita e de y crescendo para baixo. Todos os objetos a serem desenhados devem ser criados dentro do Canvas. Seus atributos são:
* width: Largura do canvas, obrigatório
* height: Altura do canvas, obrigatório
* color: Cor do canvas, branco por padrão

### Line
Linha básica. Desenha uma linha na imagem dado dois pontos. Seus atributos são:
* x1: Valor x do primeiro ponto, obrigatório
* y1: Valor y do primeiro ponto, obrigatório
* x2: Valor x do segundo ponto, obrigatório
* y3: Valor y do segundo ponto, obrigatório
* color: Cor da linha, preto por padrão
* width: Largura da linha, 1 por padrão

### Circle
Desenha um círculo na imagem. O círculo pode tanto ter uma cor para seu preenchimento como também para seu traçado. Seus atributos são:
* x: Valor x do centro do círculo, obrigatório
* y: Valor y do centro do círculo, obrigatório
* radius: Raio do círculo, obrigatório
* stroke_color: Cor do traçado, preto por padrão
* fill_color: Opcional

### Polyline
Desenha várias retas que passam por cada um de seus pontos em ordem. Os pontos desse objeto devem ser definidos dentro da descrição XML do mesmo. Seus atributos são:
* width: Largura das linhas, 1 por padrão
* color: Cor das linhas, preto por padrão

### Polygon
Desenha um polígono com vértices em cada um dos pontos dados. Os pontos desse objeto devem ser definidos dentro da descrição XML do mesmo. Seus atributos são:
* width: Largura das linhas, 1 por padrão
* stroke_color: Cor das linhas, preto por padrão
* fill_color: Cor das linhas, opcional

### Point
Descreve um ponto no canvas. Utilizado na descrição de Polyline e Polygon. Seus atributos são:
* x: Valor x do ponto, obrigatório
* y: Valor y do ponto, obrigatório

### Descrição das Cores
Para descrever as cores, é possível tanto fornecer o nome de uma cor como também preencher os valores RGB de cada atributo individualmente. Para descrever os valores de qualquer atributo de cor, basta adicionar "_r", "_g", ou "_b" no fim do mesmo. Por exemplo: 
````
stroke_color_r = "100"
````
As cores disponíveis por nome são:
* black
* red
* green
* blue
* cyan
* yellow
* magenta
* orange
* purple
* white

## Exemplo de Arquivo de Descrição
No arquivo de descrição a seguir é possível ver todos os tipos de objetos sendo utilizado ao mesmo tempo.
```` xml
<?xml version="1.0" ?>
<canvas width="400" height="400" color="white">
	<line x1="20" y1="20" x2="330" y2="90" width="30" color="black"/>
	<circle x="60" y="200" radius="50" fill_color_r="127" fill_color_g="34" fill_color_b="56" stroke_color="black"/>
	<polyline color="black">
		<point x="220" y="230"/>
		<point x="330" y="260"/>
		<point x="180" y="330"/>
	</polyline>
	<polygon width="2" stroke_color="black" fill_color="green">
		<point x="110" y="110"/>
		<point x="170" y="200"/>
		<point x="200" y="205"/>
		<point x="300" y="150"/>
	</polygon>
</canvas>
````