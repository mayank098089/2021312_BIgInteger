#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct BigInteger
{
    struct node *l;
    int sign;
    int length;
};

void sign_rev(struct node *head);
struct BigInteger initialize(char *str);


struct BigInteger add(struct BigInteger a,struct BigInteger b);
struct BigInteger add_plus(struct BigInteger a,struct BigInteger b,int sign);
struct BigInteger add_m(struct BigInteger a,struct BigInteger b,int sign);



struct BigInteger sub(struct BigInteger a,struct BigInteger b);

struct BigInteger mul(struct BigInteger a,struct BigInteger b);
struct BigInteger multiply_b(struct BigInteger a , struct BigInteger b ,int sign);

struct BigInteger div1(struct BigInteger a , struct BigInteger b );
struct BigInteger division_c(struct BigInteger a , struct BigInteger b , int sign , int choice);
void divide_alan(struct node *p1 ,struct node *p2 ,struct node *p3 ,int *l );
void div_subtract(struct node *p1 ,struct node *p2 ,struct node *p3 );
int compare(struct BigInteger h1 , struct BigInteger h2);
int compare_sub(struct node *h1 , struct node *h2);


void display(struct BigInteger c);
void print_head(struct node *head);

void ternate(struct BigInteger dev);

void dumpling(struct BigInteger c);

struct BigInteger mod(struct BigInteger a , struct BigInteger b);
//struct BigInteger mod_sub(struct BigInteger a , struct BigInteger b);