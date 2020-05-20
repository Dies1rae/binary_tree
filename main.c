/*
 * main.c
 *
 *  Created on: Jul 25, 2019
 *      Author: dies
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


typedef struct tree {
    int lik;                                    //информационное поле
    struct tree *l, *r;                                //адресное поле
} tree;

void see_inorder(tree *);    					//функция симметричного вывода дерева
void see_preorder(tree *);   					//функция прямого вывода дерева
void see_postorder(tree *);						//функция обратного вывода дерева
void add(tree *);                               //функция добавление элементов в дерево
void printTree(tree *, int le);					//функция отображения дерева
int delete(tree *);                             //функция очищения памяти дерева

int main() {
    int x, i;
    tree *dr;
    dr=NULL;
    dr=(tree*)calloc(1, sizeof(tree));          //выделение памяти под корень
    if(dr){
        printf("Введите число, для создания корня дерева: ");
        for(i=0;i<1;i++){
            if(!scanf("%d", &dr->lik)){
                printf("\n[ОШИБКА]:Создание корня невозможно. Вероятно вы ввели букву!!! Повторите ввод: ");
                fflush(stdin);
                i--;
            }
        }
    }
    do{
        printf("\nМеню программы:");
        printf("\n1 - Добавление элементов в дерево\n2 - Вывод дерева в симметричном порядке\n3 - Вывод дерева в прямом порядке\n4 - Вывод дерева в обратном порядке\n5 - Вывод дерева\n0 - Выход из программы.\n");
        for(i=0;i<1;i++){
            scanf("%d", &x);                    //выбор действия
            if(x>5||x<0){
                printf("\n[ОШИБКА]:Возможно вы ввели число > 5 или < 0, или введена буква!!! Повторите ввод: ");
                i--;
                fflush(stdin);
            }
        }
        switch(x){
        case 0 : printf("Доброго дня!\n"); delete(dr); return 0;
        case 1 : add(dr); break;
        case 2 : see_inorder(dr); break;
        case 3 : see_preorder(dr); break;
        case 4 : see_postorder(dr); break;
        case 5 : printTree(dr, 0); break;
        default : printf("ERROR!\n"); break;
        }
    } while(1);
}

void add(tree *dr){
    int ind, n, i;
    int c;
    tree *dr1, *dr2;
    do{
        ind=0;                              //флаг принимает значение 0 для хода по дереву
        dr1=dr;                             //присваивание для хода по дереву
        if(!dr1){
            printf("\nДерево не создано.\n");
            return;
        }
        printf("Введите число: ");
        fflush(stdin);
        for(i=0;i<1;i++){                                   //ввод числа
            if(!scanf("%d", &n)){
                printf("\n[ОШИБКА]:Добавление числа в дерево невозможно. Вероятно вы ввели букву!!! Повторите ввод: ");
                i--;
                fflush(stdin);
            }
        }
        do{
            if(n<dr1->lik){
                if(dr1->l){
                    dr1=dr1->l;             //переход в левое поддерево
                }else{
                    ind=1;                  //достигнут конец
                }
            }else{
            	if(dr1->r){
            		dr1=dr1->r;             //переход в правое поддерево
            	}else{
                    ind=1;                  //достигнут конец
            	}
            }
        }
        while(ind==0);
        dr2=(tree*)calloc(1,sizeof(tree));  //выделение памяти под новое поддерево
        if(n<dr1->lik){
            dr1->l=dr2;                 //ссылка в dr1 налево
        }else{
        	dr1->r=dr2;                 //ссылка в dr1 направо
        }
        dr2->lik=n;                 //запись числа в поддерево
        printf("Хотите закончить ввод?\n1-выход в меню.\n2-продолжить добавление: ");
        for(i=0;i<1;i++){
            if((!scanf("%d", &c))||c>2||c<1){
                printf("\n[ОШИБКА]:Возможно вы ввели число > 2 или < 1, или введена буква!!! Повторите ввод: ");
                i--;
                fflush(stdin);
            }
        }
        switch(c){
        case 1 : return;
        case 2 : break;
        }
    }
    while(1);
}

void see_inorder(tree *dr1){
    if(!dr1){
        printf("\nДерево не создано.\n");
        return;
    }
    if(dr1){
        if(dr1->l){
        	see_inorder(dr1->l);
        }
        printf("--%4d",dr1->lik);
        if(dr1->r){
        	see_inorder(dr1->r);
        }
    }
}
void see_preorder(tree *dr1){
    if(!dr1){
        printf("\nДерево не создано.\n");
        return;
    }
    if(dr1){
        printf("-->%4d",dr1->lik);
        if(dr1->l){
        	see_preorder(dr1->l);
        }
        if(dr1->r){
        	see_preorder(dr1->r);
        }
    }
}
void see_postorder(tree *dr1){
    if(!dr1){
        printf("\nДерево не создано.\n");
        return;
    }
    if(dr1){
        if(dr1->l){
        	see_postorder(dr1->l);
        }
        if(dr1->r){
        	see_postorder(dr1->r);
        }
        printf("<--%4d",dr1->lik);
    }
}
int delete(tree *dr){
	if (dr != NULL){
		delete(dr->l);
		delete(dr->r);
	 free(dr);
	 }
	 return 0;
}
void printTree(tree *dr, int le){
	le = 0;
	int i;
	if (dr != NULL) {
		printTree(dr->r, le+1);
		for (i=0; i < le; i++){
			printf("	");
		}
		printf("%4d", dr->lik);
		printTree(dr->l, le+1);
	 }
	 else printf("\n");
}

