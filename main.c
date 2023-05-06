#include "gCofo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct _aluno_ {
  int id;
  char nome[30];
  float media;
} Aluno;

int findById(void *item, void *key) {
  Aluno *a = (Aluno *)item;

  if (a->id == *(int *)key) {
    return TRUE;
  }

  return FALSE;
}
int findByName(void *item, void *key) {
  Aluno *a = (Aluno *)item;

  if (!strcmp(a->nome, (char *)key)) {
    return TRUE;
  }

  return FALSE;
}

int findByMedia(void *item, void *key) {
  Aluno *a = (Aluno *)item;

  if (a->media == *(float *)key) {
    return TRUE;
  }

  return FALSE;
}

void getAllElements(Aluno *aluno, gCofo *cofo) {
  aluno = (Aluno *)gcofGetFirst(cofo);

  do {
    printf("id -----> %i \n", aluno->id);
    printf("média --> %.1f \n", aluno->media);
    printf("nome ---> %s \n\n", aluno->nome);

    aluno = gcofGetNext(cofo);
  } while (aluno != NULL);
}

int main(void) {
  int id, maxItems = 0, escolhaBusca, escolhaRemocao, destruido = FALSE;
  float media;
  char nome[30];
  Aluno *aluno;

  printf("Insira um tamanho máximo para a Coleção: ");
  scanf("%d", &maxItems);
  gCofo *cofo = gCofCreate(maxItems);

  if (cofo != NULL) {
    aluno = ((Aluno *)malloc(sizeof(Aluno)));

    if (aluno != NULL) {
      printf(" \n");
      printf("Coloque as informações dos alunos a serem adicionados!  \n \n");
      for (int i = 0; i < maxItems; i++) {
        aluno = ((Aluno *)malloc(sizeof(Aluno)));
        printf("Qual o nome do aluno? ");
        scanf("%s", aluno->nome);

        printf("Qual a média desse aluno? ");
        scanf("%f", &aluno->media);

        aluno->id = i;

        printf("\n");
        printf("Adicionando essas informações à coleção... \n");
        int aux = gCofInsert(cofo, (Aluno *)aluno);

        if (aux) {
          printf("id -----> %i \n", aluno->id);
          printf("média --> %.1f \n", aluno->media);
          printf("nome ---> %s \n", aluno->nome);
          printf("Informações adicionadas com sucesso!! \n \n");
        } else {
          printf("Erro ao inserir informações");

          return FALSE;
        }
      }

      printf("\n");
      printf("Listando os elementos... \n");

      getAllElements(aluno, cofo);

      printf("\n");
      printf("Por qual elemento deseja buscar na coleção? \n");
      printf("[1] - id \n");
      printf("[2] - nome\n");
      printf("[3] - média\n");
      scanf("%i", &escolhaBusca);

      switch (escolhaBusca) {
      case 1:
        printf("insira o id que deseja buscar: ");
        scanf("%i", &id);
        aluno = (Aluno *)gcofQuery(cofo, (void *)&id, &findById);

        if (aluno != NULL) {
          printf("Aluno encontrado!\n");
          printf("id -----> %i \n", aluno->id);
          printf("média --> %.1f \n", aluno->media);
          printf("nome ---> %s \n", aluno->nome);
        } else {
          printf("Aluno não encontrado!");
        }

        break;
      case 2:
        printf("insira o nome que deseja buscar: ");
        scanf("%s", nome);
        aluno = (Aluno *)gcofQuery(cofo, (void *)nome, &findByName);

        if (aluno != NULL) {
          printf("\n");
          printf("Aluno encontrado!\n");
          printf("id -----> %i \n", aluno->id);
          printf("média --> %.1f \n", aluno->media);
          printf("nome ---> %s \n", aluno->nome);
        } else {
          printf("Aluno não encontrado!");
        }

        break;
      case 3:
        printf("insira a media que deseja buscar: ");
        scanf("%f", &media);
        aluno = (Aluno *)gcofQuery(cofo, (void *)&media, &findByMedia);

        if (aluno != NULL) {
          printf("\n");
          printf("Aluno encontrado!\n");
          printf("id -----> %i \n", aluno->id);
          printf("média --> %.1f \n", aluno->media);
          printf("nome ---> %s \n\n", aluno->nome);
        } else {
          printf("Aluno não encontrado!\n");
        }

        break;
      }

      printf("\n");
      printf("Através de qual elemento deseja remover da coleção? \n");
      printf("[1] - id \n");
      printf("[2] - nome\n");
      printf("[3] - média\n");
      scanf("%i", &escolhaRemocao);

      switch (escolhaRemocao) {
      case 1:
        printf("insira o id que deseja remover: ");
        scanf("%i", &id);
        aluno = (Aluno *)gcofRemove(cofo, (void *)&id, &findById);

        if (aluno == NULL) {
          printf("Aluno não encontrado!");
        }

        break;
      case 2:
        printf("insira o nome que deseja remover: ");
        scanf("%s", nome);
        aluno = (Aluno *)gcofRemove(cofo, (void *)nome, &findByName);

        if (aluno == NULL) {
          printf("Aluno não encontrado!");
        }

        break;
      case 3:
        printf("insira a media que deseja remover: ");
        scanf("%f", &media);
        aluno = (Aluno *)gcofRemove(cofo, (void *)&media, &findByMedia);

        if (aluno == NULL) {
          printf("Aluno não encontrado!");
        }

        break;
      }

      printf("\n");
      printf("Elementos atualizados: \n");
      getAllElements(aluno, cofo);

      printf("\n");
      printf("Esvaziando a coleção... \n");

      int naoLimpo = gCofClearAll(cofo);

      if (naoLimpo == FALSE) {
        printf("\n");

        printf("Elementos removidos com sucesso! \n");
      } else {
        printf("Erro ao esvaziar a coleção");
      }

      printf(" \n");
      printf("Destruindo coleção... \n");
      destruido = gCofEmptyDestroy(cofo);

      if (destruido) {
        printf("Coleção destruída com sucesso! \n");
      } else {
        printf("Erro ao destruir coleção \n");
      }

    } else {
      printf("Erro ao criar estrutura aluno \n");
    }

    printf("Finalizando... \n");
  } else {
    printf("Não foi possível criar a coleção");
  }

  return 0;
}