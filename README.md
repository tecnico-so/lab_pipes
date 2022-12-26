# Guião sobre comunicação entre processos usando _pipes_

![IST](img/IST_DEI.png)

## Objectivos

No final deste guião, deverá ser capaz de:

- Entender e implementar _pipes_ simples para comunicação entre processo pai e um processo filho;
- Entender e implementar _named pipes_ para comunicação entre quaisquer processos.

## Comunicação entre processos pai e filho usando _pipes_ simples

1. Clone este repositório, usando o comando: `git clone https://github.com/tecnico-so/lab_pipes.git`
2. Estude o programa `pipes.c`, no qual um processo pai envia uma sequência de mensagens a um processo filho, que por sua vez as imprime no _stdout_ (_standard output_).
3. Compile o programa `pipes.c` e experimente executá-lo, confirmando que o resultado é o esperado.
4. Experimente colocar uma chamada à função `sleep` entre mensagens escritas, observando que fronteiras entre mensagens se perdem.
5. Pretende-se que, após cada linha enviada pelo processo pai, este fique à espera que o filho lhe envie um único _byte_ (qualquer) como uma confirmação (_acknowledgement_ ou apenas _ack_) que este recebeu a mensagem.
Experimente usar o mesmo _pipe_ (colocando `sleep` no pai).
O que correu mal?
Porquê?
Resolva usando 2 _pipes_.

## Comunicação entre processos usando _named pipes_

1. Estude os programas `named_pipes_sender.c` e `named_pipes_receiver.c`, que implementam a mesma lógica do exemplo anterior, mas agora entre dois processos lançados autonomamente.
Para tal, recorrem aos chamados _named pipes_ (canais com nome), criado com a operação [`mkfifo`](https://man7.org/linux/man-pages/man3/mkfifo.3.html).
2. Compile o programa e experimente executá-lo (lançando ambos os processos), confirmando que o resultado é o esperado.
3. Tal como antes, pretende-se que, a cada linha recebida pelo processo que corre o programa receptor (_receiver_), este envie uma confirmação (_ack_) para o processo emissor (_sender_).
Tal como acontece com os _pipes_ simples, os _named pipes_ são unidirecionais, logo será preciso recorrer a dois _named pipes_ para permitir este novo comportamento:
    1. Implemente esta variante usando um segundo _named pipe_.
    Assuma que o código de ambos os programas conhece o nome desse _pipe_ (declare-o simplesmente numa _macro_/constante).
    2. Pretende-se agora criar uma variante mais flexível em que o nome do _pipe_ para as respostas _ack_ é passado como um argumento de linha de comandos do processo emissor, sendo o processo emissor que cria o _named pipe_.
    Neste caso, o nome do _named pipe_ é previamente desconhecido do processo _receiver_, logo o processo _sender_ deve enviar o nome do novo canal ao processo _receiver_ para que este o possa abrir.

----

## Conclusão

Neste laboratório vimos como usar _pipes_ e _named pipes_ para a comunicação entre processos.

---

Contactos para sugestões/correções: [LEIC-Alameda](mailto:leic-so-alameda@disciplinas.tecnico.ulisboa.pt), [LEIC-Tagus](mailto:leic-so-tagus@disciplinas.tecnico.ulisboa.pt), [LETI](mailto:leti-so-tagus@disciplinas.tecnico.ulisboa.pt)
