# Guião sobre comunicação entre processos usando *pipes*

![IST](img/IST_DEI.png)

## Objetivos

No final deste guião, deverá ser capaz de:

- Entender e implementar *pipes* simples para comunicação entre um processo pai e um processo filho;
- Entender e implementar *named pipes* para comunicação entre quaisquer processos.

## Introdução

Os processos possuem espaços de endereçamento separados. 
Por este motivo, um processo não pode, em condições normais, aceder diretamente às variáveis ou à memória de outro processo.

Quando dois processos precisam de trocar informação, o sistema operativo disponibiliza mecanismos de comunicação entre processos (IPC, *Inter-Process Communication*).

Um dos mecanismos de IPC disponibilizados pelos sistemas POSIX é o *pipe*.

## 1. Comunicação entre processos pai e filho usando *pipes* simples

Um *pipe* pode ser visto como um canal através do qual um processo escreve uma sequência de *bytes* e outro processo os lê.

**1.1.** Clone este repositório, usando o Git: `git clone https://github.com/tecnico-so/lab_pipes.git`

**1.2.** Estude o programa `pipes.c`, no qual um processo pai envia uma sequência de mensagens a um processo filho, que por sua vez as imprime no *stdout* (*standard output*).

**1.3.** Compile o programa `pipes.c` e experimente executá-lo, confirmando que o resultado é o esperado.

**1.4.** Experimente colocar uma chamada à função `sleep` entre mensagens escritas, observando que as fronteiras entre mensagens se perdem.

**1.5.** Pretende-se que, após cada linha enviada pelo processo pai, este fique à espera que o filho lhe envie um único *byte* (qualquer) como uma confirmação (*acknowledgement* ou apenas *ack*) de que recebeu a mensagem.
Experimente usar o mesmo *pipe* (colocando `sleep` no pai).
O que correu mal?
Porquê?
Resolva usando dois *pipes*.

## 2. Comunicação entre processos usando *named pipes*

Quando se pretende comunicar entre processos lançados independentemente, pode utilizar-se um *named pipe* (canal com nome), também designado por *fifo*, abreviatura de *First-In, First-Out*.

Apesar de o *named pipe* possuir um nome no sistema de ficheiros, os dados são consumidos pela leitura e **não** ficam armazenados como num ficheiro regular.

**2.1.** Estude os programas `named_pipes_sender.c` e `named_pipes_receiver.c`, que implementam a mesma lógica do exemplo anterior, mas agora entre dois processos lançados autonomamente.
Para tal, recorrem aos chamados *named pipes*, criados com a operação [`mkfifo`](https://man7.org/linux/man-pages/man3/mkfifo.3.html).

**2.2.** Compile os programas e experimente executá-los (lançando ambos os processos), confirmando que o resultado é o esperado.

**2.3.** Tal como antes, pretende-se que, a cada linha recebida pelo processo que corre o programa recetor (*receiver*), este envie uma confirmação (*ack*) para o processo emissor (*sender*).
Tal como acontece com os *pipes* simples, os *named pipes* são unidirecionais, pelo que será preciso recorrer a dois *named pipes* para permitir este novo comportamento:

**a)** Implemente esta variante usando um segundo *named pipe*.
Assuma que o código de ambos os programas conhece o nome desse *pipe* (declare-o simplesmente numa *macro* ou constante).

**b)** Pretende-se agora criar uma variante mais flexível em que o nome do *pipe* para as respostas *ack* é passado como um argumento de linha de comandos do processo emissor, sendo o processo emissor que cria o *named pipe*.
Neste caso, o nome do *named pipe* é previamente desconhecido do processo *receiver*, logo o processo *sender* deve enviar o nome do novo canal ao processo *receiver* para que este o possa abrir.

----

## Conclusão

Neste laboratório estudámos dois mecanismos de comunicação entre processos: *pipes* e *named pipes*.

Um *pipe* permite transportar um fluxo ordenado de *bytes* entre processos. 
Quando é criado antes de um `fork`, os seus descritores podem ser herdados pelo processo filho, tornando-o particularmente adequado para comunicação entre processos relacionados desta forma.

Um *named pipe* aplica princípios semelhantes, mas possui um nome no sistema de ficheiros. 
Por esse motivo, pode ser aberto por processos lançados independentemente e constitui uma forma simples de comunicação entre processos que não partilham uma relação pai-filho.

Um *pipe* não preserva, por si só, as fronteiras entre mensagens.
A interpretação do fluxo de *bytes* depende do protocolo definido pela aplicação, ou seja, os processos têm de concordar sobre a ordem, o formato e o significado dos dados que trocam entre si.

---

Contactos para sugestões/correções: [LEIC-Alameda](mailto:leic-so-alameda@disciplinas.tecnico.ulisboa.pt), [LEIC-Tagus](mailto:leic-so-tagus@disciplinas.tecnico.ulisboa.pt), [LETI](mailto:leti-so-tagus@disciplinas.tecnico.ulisboa.pt)
