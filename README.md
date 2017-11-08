# ratimbum
Projeto de eletrônica aplicada.

### Eventos

1. **Primeiro Evento ->** 

Um sensor ultrassônico roda infinitamente até que um objeto fique a 80mm de distância ou menos.

Quando essa condição é satisfeita, é aplicado um delay de 1s, e o motor de passos é ativado, girando em sentido anti-horário até completar 5 voltas (na última volta, a velocidade é reduzida pela metade) para elevar a carga. 

2. **Segundo Evento ->**

Ao iniciar, o servo motor é automaticamente setado em 90º.

Um sensor LDR roda infinitamente até que o ambiente fique escuro. Quando essa condição é satisfeita, é aplicado um delay de 500ms e um motor de passos gira ~60º no sentido anti-horário para subir a ponte.

3. **Terceiro Evento ->**

Outro sensor LDR roda infinitamente até que o ambiente fique escuro. 

Quando essa condição é satisfeita, é aplicado um delay e a porta conectada à base do transistor é setada como HIGH, ativando o rele, e consequenemtente, ativando os LEDs.

4. **Quarto Evento ->**

Após a conclusão de todos os eventos, todos os motores voltam ao seu estado inicial, o LED é apagado, e todas as flags voltam ao estado inicial. Então, o programa aguarda pelo primeiro evento novamente para que tudo se repita.
