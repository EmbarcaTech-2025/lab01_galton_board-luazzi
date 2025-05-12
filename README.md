
# Projetos de Sistemas Embarcados - EmbarcaTech 2025

Autor: **Luan Felipe Azzi**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Campinas, maio de 2025

---

# Galton Board

Neste repositório é apresentado o projeto da Galton Board na BitDogLab.

## Funcionalidades

Ao iniciar, o display apresenta um tabuleiro triangular onde as bolas caem e, quando se colidem com um pino do tabuleiro, selecionam aleatóriamente entre esquerda e direita, caindo em outro pino e repetindo o processo, até que ele caia em uma das canaletas (de 1 a 10). Com um número suficiente de iterações, uma distribuiçao normal é apresentada nas canaletas.

## Modo de uso

O programa já se inicia automaticamente, no entando, conforme as bolas caem nas canaletas, o número no canto superior da tela aumenta (contador de bolas) e o gráfico de bolas por canaleta no canto superior esquerdo se altera. Caso o usuário queira ver o gráfico no display todo, o botão A deve ser pressionado. Ao pressioná-lo novamente, o display volta a mostrar a galton board.

## Função geradora de número aleatório

Para criar uma função pseudoaleatória, utilizou-se três fontes de entropia do hardware (temperatura, tempo e ruído do ADC) para determinar a direção das bolas e um algoritmo eficiente de deslocamento de bits para misturar esses valores. Se o número gerado for ímpar, a bola vai para a direita; se for par, para a esquerda. 

---

## 📜 Licença
MIT License - MIT GPL-3.0.

