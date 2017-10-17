# ratimbum
Projeto de eletrônica aplicada.

### Eventos

1. Primeiro Evento -> Um sensor ultrassônico roda infinitamente e sem delay até que um objeto fique a 75mm de distância ou menos. Quando essa condição é satisfeita, é aplicado um delay de 1s, e o motor de passos é ativado, girando em sentido anti-horário até completar 5 voltas (na última volta, a velocidade é reduzida pela metade) para elevar a carga. Após 10 segundos, o motor gira em sentido horário até completar 5 voltas (na última volta, a velocidade é reduzida pela metade) para abaixar a carga. O programa não roda novamente até ser resetado (pode ser alterado facilmente).