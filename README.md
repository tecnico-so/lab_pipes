# Guião 7: Comunicação entre processos usando pipes

![IST](img/IST_DEI.png)

## Objectivos

No final deste guião, deverá ser capaz de:

- ...

## Comunicação entre processos pai e filho usando **pipes** simples

1. Estude o programa `pipes.c`, no qual um processo pai envia uma sequência de mensagens a um processo filho, que por sua vez as imprime no **stdout**.
2. Compile o programa `pipes.c` e experimente executá-lo, confirmando que o *output* é o esperado.
3. Experimente colocar uma chamada à função `sleep` entre mensagens escritas, observando que fronteiras entre mensagens que se perdem.
4. Pretende-se que, após cada linha enviada pelo processo pai, este fique à espera que o filho lhe envie um único byte (qualquer) como um acknowledgement ("ack") que este recebeu a mensagem. Experimente usando o mesmo pipe (colocando `sleep` no pai), observar que corre mal, porquê? Resolva usando 2 pipes.

## Comunicação entre processos usando **named pipes**

1. Estude os programas `named_pipes_sender.c` e `named_pipes_receiver.c`, que implementam a mesma lógica da 1ª alínea da seccção anterior, mas agora entre dois processos lançados autonomamente. Para tal, recorrem a **named pipes**.
2. Compile o programa e experimente executá-lo (lançando ambos os processos), confirmando que o **output** é o esperado.
3. Tal como antes, pretende-se que, a cada linha recebida pelo processo que corre o programa **receiver**, este envie um ack para o processo **sender**. Tal como com **pipes** simples, os **named pipes** são unidirecionais, logo será preciso recorrer a dois **named pipes** para suportar este novo comportamento.
    1. Implemente esta variante usando um segundo **named pipe**. Assuma que o código de ambos os programas conhecem o nome desse **pipe** (declare-o simplesmente numa macro/constante).
    2. Pretende-se agora uma variante mais flexível em que o nome do **pipe** para as respostas "ack" é passado como um argumento de linha de comandos do processo emissor, sendo o processo emissor que cria o **named pipe**. Neste caso, o nome do **named pipe** é previamente desconhecido do processor **receiver**, logo o processo **sender** deve enviar o nome do novo **pipe** ao processo **receiver** para que este o possa abrir.

## Conclusão

...
