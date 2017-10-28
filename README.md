# ratimbum
Projeto de eletrônica aplicada.

### Eventos

1. **Primeiro Evento ->** Um sensor ultrassônico roda infinitamente e sem delay até que um objeto fique a 75mm de distância ou menos.

Quando essa condição é satisfeita, é aplicado um delay de 1s, e o motor de passos é ativado, girando em sentido anti-horário até completar 5 voltas (na última volta, a velocidade é reduzida pela metade) para elevar a carga. 

Após 10 segundos, o motor gira em sentido horário até completar 5 voltas (na última volta, a velocidade é reduzida pela metade) para abaixar a plataforma. 

O programa não roda novamente até ser resetado (pode ser alterado facilmente).

2. **Segundo Evento ->**

Ao iniciar, o servo motor é automaticamente setado em 90º.

Um sensor LDR roda infinitamente e sem delay até que o ambiente fique escuro. Quando essa condição é satisfeita, é aplicado um delay de 500ms e um motor de passos gira ~60º no sentido anti-horário para subir a ponte.

Após completar o movimento, um delay de 1s é aplicado, e o servo motor é setado em 0º para liberar o caminho da bolinha.

Após 10 segundos, o servo motor volta aos 90º e o motor de passos volta ~60º no sentido horário.

O programa não roda novamente até ser resetado (pode ser alterado facilmente).
