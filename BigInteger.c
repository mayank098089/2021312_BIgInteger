#include"BigInteger.h"



void sign_re(struct node *head)
{
    if(head==0)return;
    head->data *= -1;
    sign_re(head->next);
}
struct node* reverse13(struct node *head)
{
   if (head==NULL||head->next==NULL)
   {
      return head;
   }
  struct node *rev=reverse13(head->next);
   head->next->next=head;
   head->next=NULL;
   return rev;
   
}

struct BigInteger initialize(char *str)
{
    struct BigInteger d;
    d.l=0;
    d.length=0;
    struct node *head=0;
    int i=0 ,j=0, sign=1;;
    if(str[i]=='-')
    {
        sign = -1;
        i++;
    }
    d.sign=sign;

    while(str[i]!='\n' && str[i]!='\0')
    {
        if(str[i]!='0')
        break;
        i++;
    }
    while (str[i]!='\n' && str[i]!='\0')
    {
        struct node *temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory Allocation failed\n");
            return d;
        }
        temp->data=str[i]-'0';
        temp->next=0;
        if(!head)
        {
            head=temp;
        }
        else
        {
            temp->next=head;
            head=temp;
        }
        i++;
        j++;
    }
    d.l=head;
    d.length=j;

    return d;
}

struct BigInteger add(struct BigInteger ao, struct BigInteger bo)
{
    if (ao.sign == 1 && bo.sign == 1)
    {
        if (compare(ao, bo) == -1)
            return add_plus(bo, ao, 1);
        return add_plus(ao, bo, 1);
    }
    else if (ao.sign == -1 && bo.sign == 1)
    {
        if (compare(ao, bo) == -1)
            return add_m(bo, ao, 1);
        
        return add_m(ao, bo, -1);
    }
    else if (ao.sign == 1 && bo.sign == -1)
    {
        if (compare(ao, bo) == -1)
            return add_m(bo, ao, -1);

        return add_m(ao, bo, 1);
    }
    else if (ao.sign == -1 && bo.sign == -1)
    {
        if (compare(ao, bo) == -1)
            return add_plus(bo, ao, -1);
        return add_plus(ao, bo, -1);
    }
}

struct BigInteger add_plus(struct BigInteger ao, struct BigInteger bo, int sign)
{
    struct BigInteger result;
    result.sign = sign;
    result.length = ao.length;
    result.l = 0;
    struct node *head = 0, *p1 = ao.l, *p2 = bo.l, *itr, *t;
    int c=0, d;
    
    while (p2)
    {
        t = (struct node *)malloc(sizeof(struct node));
        if (!t)
        {
            printf("Memory allocation failed. Unable to add\n");
            return result;
        }

        d = p1->data + p2->data + c;

        t->data = d % 10;
        c = d / 10;

        t->next = 0;
        if (!head)
        {
            head = t;
            itr = head;
        }
        else
        {
            itr->next = t;
            itr = t;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    while (p1)
    {
        t = (struct node *)malloc(sizeof(struct node));
        if (!t)
        {
            printf("Memory allocation failed. Unable to add\n");
            return result;
        }
        t->data = p1->data + c;
        if (t->data > 0)
        {
            c = t->data / 10;
            t->data = t->data % 10;
        }
        else
        {
            c = 0;
        }
        t->next = 0;
        if (!head)
        {
            head = t;
            itr = head;
        }

        itr->next = t;
        itr = t;
        p1 = p1->next;
    }
    if (c != 0)
    {
        t = (struct node *)malloc(sizeof(struct node));
        if (!t)
        {
            printf("Memory allocation failed. Unable to add\n");
            return result;
        }
        result.length += 1;
        itr->next = t;
        t->data = c;
        t->next = 0;
    }
    result.l = head;
    ternate(result);
    return result;
}



struct BigInteger add_m(struct BigInteger a1, struct BigInteger b1, int sign)
{
    struct BigInteger result;
    result.sign = sign;
    result.l = 0;
    result.length = a1.length;
    struct node *head = 0, *p1 = a1.l, *p2 = b1.l, *t, *itr;
    int number, c = 0;
    sign_re(p2);

    while (p2)
    {
        t = (struct node *)malloc(sizeof(struct node));
        if (!t)
        {
            printf("Memory allocation failed. Unable to add\n");
            return result;
        }

        number = p1->data + p2->data + c;

        if (number < 0)
        {
            t->data = number + 10;
            c = -1;
        }
        else
        {
            t->data = number;
            c = 0;
        }

        t->next = 0;
        if (!head)
        {
            head = t;
            itr = head;
        }
        else
        {
            itr->next = t;
            itr = t;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    while (p1)
    {
        t = (struct node *)malloc(sizeof(struct node));
        if (!t)
        {
            printf("Memory allocation failed. Unable to add\n");
            return result;
        }
        t->data = p1->data + c;
        if (t->data < 0)
        {
            t->data = t->data + 10;
            c = -1;
        }
        else
        {
            c = 0;
        }

        t->next = 0;
        if (!head)
        {
            itr = head = t;
        }

        itr->next = t;
        itr = t;
        p1 = p1->next;
    }
    result.l = head;
    sign_re(b1.l);
    ternate(result);
    return result;
}


void ternate(struct BigInteger result)
{
    struct node *temp = 0, *ptr = result.l;
    if (!result.l)
        return;
    while (ptr->next)
    {
        if (ptr->next->data == 0 && temp == 0)
        {
            temp = ptr;
            ptr = ptr->next;
            continue;
        }
        if (ptr->data != 0 && temp)
        {
            temp = 0;
        }
        ptr = ptr->next;
    }
    if (ptr->data != 0)
    {
        temp = 0;
    }

    if (temp)
    {
        ptr = temp;
        temp = temp->next;
        ptr->next = 0;
        while (temp)
        {
            ptr = temp;
            temp = temp->next;
            free(ptr);
            result.length -= 1;
        }
    }
}



void display(struct BigInteger c)
{
    struct node *itr=c.l,*temp;
    if(!itr)
    {
        printf("0\n");
        return;
    }
    if(c.sign==-1 && itr->data || itr->next && c.sign==-1)
    {
        printf("-");
    }
    print_head(c.l);
    printf("\n");
}

void print_head(struct node *head)
{
    if(!head)
    {
        return;
    }
    print_head(head->next);
    printf("%d",head->data);
}


struct BigInteger sub(struct BigInteger ao, struct BigInteger bo)
{
    if (ao.sign == 1 && bo.sign == 1)
    {
        if (compare(ao, bo) == -1)
            return add_m(bo, ao, -1);

        return add_m(ao, bo, 1);
    }
    else if (ao.sign == -1 && bo.sign == 1)
    {
        if (compare(ao, bo) == -1)
            return add_plus(bo, ao, -1);
        return add_plus(ao, bo, -1);
    }
    else if (ao.sign == 1 && bo.sign == -1)
    {
        if (compare(ao, bo) == -1)
            return add_plus(bo, ao, 1);
        return add_plus(ao, bo, 1);
    }
    else if (ao.sign == -1 && bo.sign == -1)
    {
        if (compare(ao, bo) == -1)
            return add_m(bo, ao, 1);

        return add_m(ao, bo, -1);
    }
}


struct BigInteger mul(struct BigInteger ao, struct BigInteger bo)
{
    if (!ao.l || !bo.l)
    {
        struct BigInteger d = {0, 0, 0};
        return d;
    }
    if (ao.sign == 1 && bo.sign == 1 || ao.sign == -1 && bo.sign == -1)
    {
        return multiply_b(ao, bo, 1);
    }
    else
    {
        return multiply_b(ao, bo, -1);
    }
}

struct BigInteger multiply_b(struct BigInteger ao, struct BigInteger bo, int sign)
{
    struct BigInteger result;
    result.l = 0;
    result.sign = sign;
    struct node *itrFront, *pt2, *itr, *head = 0, *p1 = ao.l, *p2 = bo.l;
    int i, num, c, n = ao.length + bo.length;
    result.length = n;
    for (i = 1; i <= n; i++)
    {
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        if (!temp)
        {
            printf("Memory Allocation failed\n");
            return result;
        }
        temp->data = 0;
        temp->next = 0;
        if (!head)
        {
            head = temp;
        }
        else
        {
            temp->next = head;
            head = temp;
        }
    }
    result.l = head;

    itr = itrFront = head;

    while (p1)
    {
        pt2 = p2;
        c = 0;
        while (pt2)
        {
            num = (p1->data) * (pt2->data) + c;

            itr->data += num;
            c = (itr->data) / 10;
            itr->data = (itr->data) % 10;

            pt2 = pt2->next;
            itr = itr->next;
        }
        if (!pt2 && c > 0)
        {
            itr->data += c;
        }
        itrFront = itrFront->next;
        itr = itrFront;
        p1 = p1->next;
    }
    ternate(result);
    return result;
}


void dumpling(struct BigInteger c)
{
    struct node *temp;
    while(c.l)
    {
        temp=c.l;
        c.l=c.l->next;

        free(temp);
    }
    c.l=0;
}



struct BigInteger div1(struct BigInteger ao, struct BigInteger bo)
{
    struct BigInteger result = {0, 0, 0};
    if (!bo.l || !ao.l)
    {
        printf("Invalid input\n");
        return result;
    }
    if (compare(ao, bo) == -1)
    {
        return result;
    }
    else
    {
        if (ao.sign == 1 && bo.sign == 1 || ao.sign == -1 && bo.sign == -1)
        {
            return division_c(ao, bo, 1, 1);
        }
        else
        {
            return division_c(ao, bo, -1, 1);
        }
    }
}


struct node *duplicate_one_to_three(struct node *head)
{
    struct node *h1=0,*itr, *temp;
    while(head)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory allocations failed. Unable to add\n");
            return h1;
        }
        temp->data=head->data;
        temp->next=0;
        if(!h1)
        {
            h1=temp;
            itr=temp;
        }
        else
        {
            itr->next=temp;
            itr=temp;
        }
        head=head->next;
    }
    return h1;
}



struct BigInteger division_c(struct BigInteger ao, struct BigInteger bo, int sign, int choice)
{
    struct BigInteger result;
    result.l = 0;
    result.length = 0;
    result.sign = sign;
    int comp, length = bo.length;
    struct node *head = 0, *itr, *temp, *p2 = bo.l, *head_quotient = (struct node *)malloc(sizeof(struct node));
    if (!head_quotient)
    {
        printf("memory allocation failed\n");
        return result;
    }

    if ((comp = compare(ao, bo)) < 1)
    {
        if (comp == 0)
        {
            if (choice == 0)
            {
                result.l = duplicate_one_to_three(ao.l);
                return result;
            }
            head_quotient->data = 1;
            head_quotient->next = 0;
            result.l = head_quotient;
            result.length = 1;
            return result;
        }
        if (choice == 0)
        {
            result.l = duplicate_one_to_three(ao.l);
            return result;
        }
        return result;
    }

    head = duplicate_one_to_three(p2);

    head_quotient->data = 1;
    head_quotient->next = 0;
    result.length = 1;
    while (ao.length >= length + 1)
    {
        itr = (struct node *)malloc(sizeof(struct node));
        temp = (struct node *)malloc(sizeof(struct node));
        if (!temp && !itr)
        {
            printf("Memory allocation failed\n");
            return result;
        }
        temp->data = itr->data = 0;
        temp->next = head;
        head = temp;
        itr->next = head_quotient;
        head_quotient = itr;
        length += 1;
    }

    result.l = head;
    result.length = length;
    if ((comp = compare(ao, result)) == -1)
    {
        temp = head;
        head = head->next;
        free(temp);
        temp = head_quotient;
        head_quotient = head_quotient->next;
        free(temp);
        length -= 1;
    }
    while (ao.length > length)
        divide_alan(head, bo.l, head_quotient, &length);

    result.l = head;
    result.length = length;
    while ((comp = compare(ao, result)) != -1 && comp != 0)
    {
        divide_alan(head, bo.l, head_quotient, &result.length);
    }

    if (comp == 0)
    {
        if (choice == 0)
        {
            result.l = head_quotient;
            dumpling(result);
            result.l = head;
            result.length = ao.length;
            return result;
        }
        result.l = head;
        dumpling(result);
        result.l = head_quotient;
        result.length = length;
        return result;
    }
    if (compare(ao, result) == -1)
    {
        div_subtract(head, bo.l, head_quotient);

        ternate(result);
    }
    if (choice == 0)
    {
        result.l = head_quotient;
        dumpling(result);
        result.l = head;
        result.length = ao.length;
        ternate(result);
        return result;
    }
    result.l = head;
    dumpling(result);
    result.l = head_quotient;
    ternate(result);
    return result;
}

int compare(struct BigInteger h1 , struct BigInteger h2)
{
    if(h1.length < h2.length)
        return -1;
    else if(h1.length > h2.length)
        return 1;
    else
    return compare_sub(h1.l,h2.l);
}


int compare_sub(struct node *n1, struct node *n2)
{
    static int x;
    x = 0;

    if (!n1 && !n2)
    {
        return x;
    }
    compare_sub(n1->next, n2->next);

    if (x == -1)
        return x;
    else if (n1->data > n2->data)
    {
        x = 1;
    }
    else if (n1->data < n2->data && x == 0)
    {
        x = -1;
    }

    return x;
}


void divide_alan(struct node *p1, struct node *p2, struct node *p3, int *l)
{
    struct node *temp = 0, *ptr;
    int num, c = 0;
    while (p2)
    {
        p1->data = p1->data + p2->data + c;
        c = (p1->data) / 10;
        p1->data = (p1->data) % 10;

        if (p1->next == 0)
        {
            ptr = p1;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    while (p1)
    {
        if (p1->next == 0)
        {
            ptr = p1;
        }
        p1->data = p1->data + c;
        c = (p1->data) / 10;
        p1->data = (p1->data) % 10;

        if (c == 0)
        {
            break;
        }
        p1 = p1->next;
    }
    if (c != 0)
    {
        temp = (struct node *)malloc(sizeof(struct node));
        if (!temp)
        {
            printf("Memory allocation failed. Unable to add\n");
            return;
        }
        ptr->next = temp;
        temp->data = c;
        temp->next = 0;
        *l += 1;
    }
    c = 1;
    while (p3)
    {
        p3->data = p3->data + c;
        c = (p3->data) / 10;
        p3->data = (p3->data) % 10;
        p3 = p3->next;
        if (c == 0)
        {
            return;
        }
        if (p3->next == 0)
        {
            ptr = p3;
        }
    }
    if (c != 0)
    {
        temp = (struct node *)malloc(sizeof(struct node));
        if (!temp)
        {
            printf("Memory allocation failed. Unable to add\n");
            return;
        }
        ptr->next = temp;
        temp->data = c;
        temp->next = 0;
        *l += 1;
    }
}


void div_subtract(struct node *n1, struct node *n2, struct node *n3)
{
    struct node *ptr = n2;
    int num, c = 0; // Change "carry" to "c"
    sign_re(n2);

    while (n2)
    {
        n1->data = n1->data + n2->data + c; // Change "carry" to "c"

        if (n1->data < 0)
        {
            n1->data = n1->data + 10;
            c = -1; // Change "carry" to "c"
        }
        else
        {
            c = 0; // Change "carry" to "c"
        }

        n1 = n1->next;
        n2 = n2->next;
    }
    while (n1)
    {
        n1->data = n1->data + c; // Change "carry" to "c"
        if (n1->data < 0)
        {
            n1->data = n1->data + 10;
            c = -1; // Change "carry" to "c"
        }
        else
        {
            c = 0; // Change "carry" to "c"
        }
        if (c == 0) // Change "carry" to "c"
        {
            break;
        }
        n1 = n1->next;
    }
    sign_re(ptr);

    c = -1; // Change "carry" to "c"
    while (n3)
    {
        n3->data = n3->data + c; // Change "carry" to "c"
        if (n3->data < 0)
        {
            n3->data += 10;
            c = -1; // Change "carry" to "c"
        }
        else
        {
            c = 0; // Change "carry" to "c"
        }
        if (c == 0) // Change "carry" to "c"
        {
            return;
        }
        n3 = n3->next;
    }
}

struct BigInteger mod(struct BigInteger ao, struct BigInteger bo)
{
    struct BigInteger result = {0, 0, 0};
    if (!bo.l || !ao.l)
    {
        printf("Invalid input\n");
        return result;
    }
    if (compare(ao, bo) == -1)
    {
        result.l = duplicate_one_to_three(ao.l);
        result.length = ao.length;
        return result;
    }
    else
    {
        if (ao.sign == 1 && bo.sign == 1 || ao.sign == -1 && bo.sign == -1)
        {
            result = division_c(ao, bo, 1, 0);
        }
        else
        {
            result = division_c(ao, bo, -1, 0);
        }
    }
    if (compare(ao, result) == 0)
    {
        result.l = duplicate_one_to_three(ao.l);
        result.length = ao.length;
        return result;
    }
    return add_m(ao, result, 1);
}
