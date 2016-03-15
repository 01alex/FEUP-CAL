# FEUP-CAL

# Trabalho Prático 1 - EasyPilot: Sistema de Navegação

A navegação GPS é uma tecnologia amplamente utilizada atualmente, equipando cada vez mais veículos, e disponível em diferentes apps para dispositivos móveis, como smartphones, tablets, e mesmo relógios de pulso. As funcionalidades básicas de um navegador geralmente incluem a deteção da posição atual, a partir da qual se escolhe um destino, para o qual se calcula um caminho. O navegador enumera a sequência de ações e detalha o itinerário a seguir, muitas vezes com recurso ao processamento de voz.

<img src= "https://lh6.googleusercontent.com/Wlt3vfe6XEfaT7zzXcjUwuyO9GwJEgo2GWgGFdr4BEOW9CMOgPKBHGT3ctlj0Et-IudrgJT5aeSP7yomjMNt6W73ptJd_hOTY1vhWi5b-sBqFDR_MpSVqeh1BAI1u0Mg0bO6msVX" width="600" height="300"/> 

Neste trabalho, pretende-se implementar um navegador que identifique o caminho a seguir, numa dada rede, a partir de uma origem até ao destino desejado. O itinerário poderá ser simples, ou ainda incluir vários pontos de interesse (POIs), como bombas de combustível para reabastecimento, monumentos, ou outros cuja posição sejam indicadas pelo utilizador; outros critérios a utilizar poderão incluir menor distância, menor tempo de viagem, e ainda a existência ou não de pontos de portagem.
Avalie a conectividade do grafo, a fim de evitar que destinos sejam selecionados em zonas inacessíveis; por exemplo, obras em uma dada via podem torar certos destinos inacessíveis.
Considere a possibilidade de utilizar mapas reais, extraídos do OpenStreetMaps (www.openstreetmap.org), localizando, no mapa, endereços e pontos de interesse.
