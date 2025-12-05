# Sistema de Iniciativa RPG (ED1)

Trabalho de Estruturas de Dados I.

- Estrutura principal: lista estatica de personagens (vetor)
- Cada personagem tem: nome, nivel, dado de iniciativa, valor de iniciativa
- A iniciativa e recalculada a cada turno como: nivel + dado

## Funcionalidades

- Criar personagens manualmente
- Carregar personagens do arquivo `personagem.txt` (apenas leitura)
- Recalcular iniciativa de todos a cada turno
- Ordenar pela iniciativa usando:
- Merge Sort (metodo 0)
- Insertion Sort (metodo 1)
- Adicionar e remover personagens durante o combate

## Para compilar No terminal:

```bash
gcc main.c lista.c utils.c ordenacao.c personagem.c -o iniciativa
```
## Depois para rodar:
```bash
./iniciativa
```






## Personagens e Classes de 4Story(JOGO DE MMORPG de 2007)

Kameria — dragão criado por Bergelius

Leya — deusa da criação, luz e vida. 

Bergelius — deus das trevas adversário de Leya. 

Parakelius — servo/leal de Bergelius

Pauldron — God of Thunder (patrono e NPC do jogo). 

Rumapark — deus do fogo (associado a guerreiros; NPC/altar/quests). 

Rekamies — deus da água (patrono dos sacerdotes). 

Endendros — deus da terra (patrono dos invocadores/summoners). 

Pendatron — deus das trevas/negro (associado a assassinos/night walkers). 

Lapiris — deusa associada aos arqueiros (dá precision/power).