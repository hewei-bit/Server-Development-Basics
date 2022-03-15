/**
 * @File Name: rbtree_hw.c
 * @Brief : �����ʵ��
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2022-03-13
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. �ڵ��Ǻ�ɫ���ɫ��
// 2. ���ڵ��Ǻ�ɫ��
// 3. ÿ��Ҷ�ڵ��Ǻ�ɫ�ġ�
// 4. ÿ����ɫ�ڵ�������ӽڵ㶼�Ǻ�ɫ��(��ÿ��Ҷ�ӵ���������·���ϲ��������������ĺ�ɫ�ڵ�)
// 5. ����һ�ڵ㵽��ÿ��Ҷ�ӵ�����·����������ͬ��Ŀ�ĺ�ɫ�ڵ㡣
#define RED 1
#define BLACK 2

typedef int KEY_TYPE;
//������ڵ�
typedef struct _rbtree_node
{
    unsigned char color;         //��ɫ
    struct _rbtree_node *right;  //���������ȱ����
    struct _rbtree_node *left;   // ���������ȱ���С
    struct _rbtree_node *parent; // ���ڵ�
    KEY_TYPE key;                // �ڵ㱾���ֵ
    void *value;                 // �ýڵ���ص�ֵ
} rbtree_node;

typedef struct _rbtree
{
    rbtree_node *root; // ��ͷ
    rbtree_node *nil;  // ����Ҷ�ӽڵ�ָ��nil��ͨ�õ�Ҷ�ӽڵ�
} rbtree;

// �ҵ���С
rbtree_node *rbtree_mini(rbtree *T, rbtree_node *x)
{
    while (x->left != T->nil)
    {
        x = x->left;
    }
    return x;
}

// �ҵ����
rbtree_node *rbtree_maxi(rbtree *T, rbtree_node *x)
{
    while (x->right != T->nil)
    {
        x = x->right;
    }
    return x;
}

//�ҵ���ӽ���������
rbtree_node *rbtree_successor(rbtree *T, rbtree_node *x)
{
    rbtree_node *y = x->parent;
    // ���x����Ҷ�ӽڵ㣬�򷵻ص�x����������Сֵ
    if (x->right != T->nil)
    {
        return rbtree_mini(T, x->right);
    }

    while ((y != T->nil) && (x == y->right))
    {
        x = y;
        y = y->parent;
    }
    return y;
}

// ����
void rbtree_left_rotate(rbtree *T, rbtree_node *x)
{
    // x  --> y  ,  y --> x,   right --> left,  left --> right
    rbtree_node *y = x->right;

    x->right = y->left;
    // y������������Ҷ�ӽڵ�
    if (y->left != T->nil)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;
    // ȷ�� y �Ǹ��ڵ㻹������������������
    if (x->parent == T->nil)
    {
        T->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }

    // ��������x��y
    y->left = x;
    x->parent = y;
}

// �������������е�x��y�������ɣ�
void rbtree_right_rotate(rbtree *T, rbtree_node *y)
{
    rbtree_node *x = y->left;

    y->left = x->right;
    if (x->right != T->nil)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == T->nil)
    {
        T->root = x;
    }
    else if (y == y->parent->right)
    {
        y->parent->right = x;
    }
    else
    {
        y->parent->left = x;
    }

    x->right = y;
    y->parent = x;
}

// ���벹��
// ��������游���������������
//     1. �����Ǻ�ɫ��
//     2. �����Ǻ�ɫ�ģ����ҵ�ǰ������Һ���
//     3. �����Ǻ�ɫ�ģ����ҵ�ǰ���������
void rbtree_insert_fixup(rbtree *T, rbtree_node *z)
{
    while (z->parent->color == RED)
    {
        // z ---> RED
        if (z->parent == z->parent->parent->left)
        {
            rbtree_node *y = z->parent->parent->right;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    rbtree_left_rotate(T, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbtree_right_rotate(T, z->parent->parent);
            }
        }
        else
        {
            rbtree_node *y = z->parent->parent->left;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent; // z --> RED
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rbtree_right_rotate(T, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbtree_left_rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}

// ����
void rbtree_insert(rbtree *T, rbtree_node *z)
{
    rbtree_node *y = T->nil;
    rbtree_node *x = T->root;

    // �ҵ�����ĵط�
    while (x != T->nil)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else if (z->key > x->key)
        {
            x = x->right;
        }
        else
        {
            // �Ѿ�����
            return;
        }
    }

    // ȷ��z��y������������������
    z->parent = y;
    if (y == T->nil)
    {
        T->root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }

    // �ȵ���Ҷ�ӽڵ�
    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;

    // ��ʼ����
    rbtree_insert_fixup(T, z);
}

// ɾ������
// ��ǰ����Ǹ����������������
//     1. ��ǰ�����ֵܽ���Ǻ�ɫ��
//     2. ��ǰ�����ֵܽ���Ǻ�ɫ�ģ������ֵܽ���
//     �������ӽ�㶼�Ǻ�ɫ��
//     3. ��ǰ�����ֵܽ���Ǻ�ɫ�ģ������ֵܽ���
//     �����Ǻ�ɫ�ģ��Һ����Ǻ�ɫ��
//     ��ǰ����Ǹ����������������
//     4. ��ǰ�����ֵܽ���Ǻ�ɫ�ģ������ֵܽ���
//     �Һ����Ǻ�ɫ��
void rbtree_delete_fixup(rbtree *T, rbtree_node *x)
{
    while ((x != T->root) && (x->color == BLACK))
    {
        if (x == x->parent->left)
        {
            rbtree_node *w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;

                rbtree_left_rotate(T, x->parent);
                w = x->parent->right;
            }

            if ((w->left->color == BLACK) && (w->right->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rbtree_right_rotate(T, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rbtree_left_rotate(T, x->parent);

                x = T->root;
            }
        }
        else
        {
            rbtree_node *w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rbtree_right_rotate(T, x->parent);
                w = x->parent->left;
            }

            if ((w->left->color == BLACK) && (w->right->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {

                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    rbtree_left_rotate(T, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rbtree_right_rotate(T, x->parent);

                x = T->root;
            }
        }
    }

    x->color = BLACK;
}

rbtree_node *rbtree_delete(rbtree *T, rbtree_node *z)
{
    rbtree_node *y = T->nil;
    rbtree_node *x = T->nil;
    // �����滻�õĽڵ�y
    // 1.û����������
    // 2.����������������
    if ((z->left == T->nil) || (z->right == T->nil))
    {
        y = z;
    }
    // 3.������������������
    else
    {
        y = rbtree_successor(T, z);
    }

    //����y�������Ժ��λ��
    if (y->left != T->nil)
    {
        x = y->left;
    }
    else if (y->right != T->nil)
    {
        x = y->right;
    }

    // �ڰ�y����֮ǰ�ȰѿӲ���
    x->parent = y->parent;
    if (y->parent == T->nil)
    {
        T->root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    // ��y����z��λ����
    if (y != z)
    {
        z->key = y->key;
        z->value = y->value;
    }

    if (y->color == BLACK)
    {
        rbtree_delete_fixup(T, x);
    }

    return y;
}

// ����
rbtree_node *rbtree_search(rbtree *T, KEY_TYPE key)
{
    rbtree_node *node = T->root;
    while (node != T->nil)
    {
        if (key < node->key)
        {
            node = node->left;
        }
        else if (key > node->key)
        {
            node = node->right;
        }
        else
        {
            return node;
        }
    }
    return T->nil;
}

// �õݹ�ʵ���������
void rbtree_traversal(rbtree *T, rbtree_node *node)
{
    if (node != T->nil)
    {
        rbtree_traversal(T, node->left);
        printf("key:%d, color:%d\n", node->key, node->color);
        rbtree_traversal(T, node->right);
    }
}

int main()
{
    int keyArray[20] = {24, 25, 13, 35, 23, 26, 67, 47, 38, 98, 20, 19, 17, 49, 12, 21, 9, 18, 14, 15};

    rbtree *T = (rbtree *)malloc(sizeof(rbtree));
    if (T == NULL)
    {
        printf("malloc failed\n");
        return -1;
    }

    T->nil = (rbtree_node *)malloc(sizeof(rbtree_node));
    T->nil->color = BLACK;
    T->root = T->nil;

    rbtree_node *node = T->nil;
    int i = 0;
    for (i = 0; i < 20; i++)
    {
        node = (rbtree_node *)malloc(sizeof(rbtree_node));
        node->key = keyArray[i];
        node->value = NULL;

        rbtree_insert(T, node);
    }

    rbtree_traversal(T, T->root);
    printf("----------------------------------------\n");

    for (i = 0; i < 20; i++)
    {
        rbtree_node *node = rbtree_search(T, keyArray[i]);
        rbtree_node *cur = rbtree_delete(T, node);

        free(cur);

        rbtree_traversal(T, T->root);
        printf("----------------------------------------\n");
    }

    return 0;
}
