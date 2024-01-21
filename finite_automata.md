# Finite Automata and Regular Expressions

## 1. Playing with marbles

$D$ és un estat d'acceptació.

Donada una seqüència de caniques: $ABBA$, s'accepta donada la posició inicial i canvia les palanques que toca.

$Estat = EDE_{si/no}$

La taula de transició

|               | A          | B          |
| ------------- | ---------- | ---------- |
| $EEE_{no/si}$ | $DEE_{no}$ | $EDD_{no}$ |
| $DEE_{no/si}$ | $EDE_{no}$ | $DDD_{no}$ |
| $EDD_{no/si}$ | $DDD_{no}$ | $EDE_{si}$ |
| $EDE_{no/sí}$ | $DEE_{no}$ | $EED_{si}$ |
| ...           | ...        | ...        |

## 2. From informal description to DFA

$\sum = \{0, 1\}$

###### a) Accepta paralues acaben en 00

$010100 \: \checkmark$

$10 \: \times$



|     | A   | B   | C   |
| --- | --- | --- | --- |
| A   | 1   | 1   | 1   |
| B   | 0   | -   | -   |
| C   | -   | 0   | 0   |

###### b) Començem amb i que representen un multiple de 5 en binari.

$10100_2 = 20_{10} \: \checkmark$

Treballem mòdul 5



Estat adicional al inici on si tenim un 0 el programa falla, si tenim un 1 ens movem a l'estat 0.



|     | 0   | 1   | 2   | 3   | 4   |
| --- | --- | --- | --- | --- | --- |
| 0   | 0   |     | 1   |     |     |
| 1   | 1   |     |     | 0   |     |
| 2   |     | 0   |     | 1   |     |
| 3   |     | 1   |     |     | 0   |
| 4   |     |     | 0   |     | 1   |

###### 

## 3. Verification of a DFA

|      | 0   | 1   |
| ---- | --- | --- |
| A    | A   | B   |
| $*B$ | B   | A   |

$10010 \: \times$

$111 \: \checkmark$

Accepta un nombre senar de 1's. Amb un zero es queda quiet, amb un 1 es mou, amb un nombre parell de 1's et quedes igual també, amb un senar acabes a B, que és l'estat d'acceptació.



$\forall n \geq0$, si $|\omega| = n$ aleshores

1) Si $\omega$ té nombre parell de 1's l'autòmat acaba a $A$.

2) Si $\omega$ té nombre senar de 1's l'autòmat acaba a $B$.



$D./$

Amb inducció sobre n

##### Cas base $n=0$

Aleshores $\omega$ és la paraula buida $\implies$ acaba en $A$, $\omega$ té un nombre parell de 1's.

###### Cas inductiu $n > 0$

$\underbrace{\hat{\omega}}_{n-1}b$

$\hat{\omega}b$ on $|\hat{\omega}| = n-1$ i $b \in \{0, 1\}$

1. Si $\omega$ té nombre parell de 1's
   
   -   Si $b=0 \implies \hat{\omega}$ té nombre parell de 1's $\implies$ després de $\hat{\omega}$ acabem a $A$.
   
    -    Si $b=1 \implies \hat{\omega}$ té nombre senar de 1's $\implies$ després de $\hat{\omega}$ acabem a $B$.

El cas anàleg es pot fer per $\omega$ amb nombre senar.



## 4. From NFA to DFA

|     | 0    | 1        |
| --- | ---- | -------- |
| p   | p, q | p        |
| q   | r    | r        |
| r   | s    | $\empty$ |
| s   | s    | s        |



|      | p   | pq  | pqr | pr  | $*PQS$ | $*PQRS$ | $*PRS$ | $*PS$ |
| ---- | --- | --- | --- | --- | ------ | ------- | ------ | ----- |
| p    | 1   |     |     | 1   |        |         |        |       |
| pq   | 0   |     |     |     |        |         |        |       |
| pqr  |     | 0   |     |     |        |         |        |       |
| pr   |     | 1   | 1   |     |        |         |        |       |
| pqs  |     |     |     | 0   |        |         | 0      | 0     |
| pqrs |     |     | 0   |     | 0      | 0       |        |       |
| prs  |     |     |     |     | 1      | 1       |        |       |
| ps   |     |     |     |     |        |         | 1      | 1     |

Qualsevol estat que conté un estat d'acceptació ($S$), és un estat d'acceptació. 
