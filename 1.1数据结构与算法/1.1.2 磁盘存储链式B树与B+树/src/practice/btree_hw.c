/**
 * @File Name: btree_hw.c
 * @Brief : B��ʵ��
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2022-03-13
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

// һ��M��B��T��������������
// 1. ÿ���������ӵ��M������
// 2. ���������ӵ����������
// 3. ���˸�������⣬����ÿ����֧�������ӵ��M/2������
// 4. ���е�Ҷ��㶼��ͬһ����
// 5. ��k�������ķ�֧��������k-1���ؼ��֣��ؼ��ְ��յ���˳���������
// 6. �ؼ�����������ceil(M/2)-1 <= n <= M-1

#define DEGREE 3       // B���Ľ���
typedef int KEY_VALUE; //���ڵ������key������

typedef struct _btree_node
{
    KEY_VALUE *keys;                // �ڵ㱾���keys�����׵�ַ
    struct _btree_node **childrens; // �ӽ�������׵�ַ
    int num;                        // �ڵ㱾��keys������
    int leaf;                       // �Ƿ���Ҷ�ӽڵ� 1��yes  0��no
} btree_node;

typedef struct _btree
{
    btree_node *root; // ���ڵ�
    int t;            // ��ʼʱ�Ľڵ�����
} btree;

btree_node *btree_create_node(int t, int leaf)
{
    btree_node *node = (btree_node *)calloc(1, sizeof(btree_node));
    if (node == NULL)
    {
        assert(0);
    }

    node->leaf = leaf;
    node->keys = (KEY_VALUE *)calloc(1, (2 * t - 1) * sizeof(KEY_VALUE));
    node->childrens = (btree_node *)calloc(1, (2 * t) * sizeof(btree_node));
    node->num = 0;

    return node;
}

void btree_destroy_node(btree_node *node)
{
    assert(node);

    free(node->childrens);
    free(node->keys);
    free(node);
}

void btree_create(btree *T, int t)
{
    T->t = t;

    btree_node *x = btree_create_node(t, 1);
    T->root = x;
}

// ��ӣ�����
// 1.�ҵ���Ӧ�Ľڵ㣬���ҽڵ�δ��
// 2.�ҵ��ڵ�����
//     ���ڽڵ��������ڽڵ����
//     �ҵ�Ҷ�ӽڵ�������Ҷ�ӽڵ����

// x�ڵ�ĵ�i���������з���
void btree_split_child(btree *T, btree_node *x, int i)
{
    // ����ǹ涨�Ľڵ�����
    int t = T->t;

    btree_node *y = x->childrens[i];
    // �½ڵ� Z �Ĵ����븳ֵ
    btree_node *z = btree_create_node(t, y->leaf);
    z->num = t - 1;

    int j = 0;
    for (j = 0; j < t - 1; j++)
    {
        z->childrens[j] = y->childrens[j + t];
    }
    if (y->leaf == 0)
    {
        for (j = 0; j < t; j++)
        {
            z->childrens[j] = y->childrens[j + t];
        }
    }
    y->num = t - 1;

    //  �� z ���ӵ� x ���棬z����һ����x����ĩβ
    for (j = x->num; j >= i + 1; j--)
    {
        x->childrens[j + 1] = x->childrens[j];
    }
    x->childrens[i + 1] = z;

    //  �� y �м���Ǹ�key �Ž� x ��keys�������棬���key����һ����x��keys������ĩβ
    for (j = x->num; j >= i + 1; j--)
    {
        x->keys[j + 1] = x->keys[j];
    }
    x->keys[i] = y->keys[t - 1];
    x->num += 1;
}

// ������һ�������Ľڵ� x ����һ�� k
void btree_insert_nonfull(btree *T, btree_node *x, KEY_VALUE k)
{
    int i = x->num - 1;
    // �����Ƿ�Ҷ�ӽڵ�
    if (x->leaf == 1)
    {
        // �ҵ����ʵ�λ�ð�k���룬��kС��������
        while (i >= 0 && x->keys[i] > k)
        {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->num += 1;
    }
    // �������Ҷ�ӽڵ�����������������ȥ������������˾ͰѺ����ȷ�����
    else
    {
        while (i >= 0 && x->keys[i] > k)
            i--;
        // ���x������������ˣ�Ҫ�Ƚ��з���
        if (x->childrens[i + 1]->num == (2 * (T->t)) - 1)
        {
            btree_split_child(T, x, i + 1);
            // ��λ��
            if (k > x->keys[i + 1])
                i++;
        }
        // ����
        btree_insert_nonfull(T, x->childrens[i + 1], k);
    }
}

// �ۺϵĲ���
void btree_insert(btree *T, KEY_VALUE key)
{
    // ͨ������һ���յĸ��ڵ������и��ڵ�ķ���
    btree_node *r = T->root;
    // ������˾��ȷ����ٲ���
    if (r->num == 2 * T->t - 1)
    {
        // ����һ���յĸ��ڵ㣬��Ҷ�ӽڵ�
        btree_node *node = btree_create_node(T->t, 0);
        T->root = node;
        // �ýڵ�ĺ�����ԭ���ĸ��ڵ�
        node->childrens[0] = r;
        // ���з���
        btree_split_child(T, node, 0);
        // ��λ��
        int i = 0;
        if (node->keys[0] < key)
            i++;
        btree_insert_nonfull(T, node->childrens[i], key);
    }
    else
    {
        btree_insert_nonfull(T, r, key);
    }
}

void btree_traverse(btree_node *x)
{
    int i = 0;

    for (i = 0; i < x->num; i++)
    {
        if (x->leaf == 0)
        {
            btree_traverse(x->childrens[i]);
        }
        printf("%c", x->keys[i]);
    }
    if (x->leaf == 0)
        btree_traverse(x->childrens[i]);
}

void btree_print(btree *T, btree_node *node, int layer)
{
    btree_node *p = node;
    int i;
    if (p)
    {
        printf("\nlayer = %d keynum = %d is_leaf = %d\n", layer, p->num, p->leaf);
        for (i = 0; i < node->num; i++)
            printf("%c ", p->keys[i]);
        printf("\n");
        layer++;
        for (i = 0; i <= p->num; i++)
            if (p->childrens[i])
                btree_print(T, p->childrens[i], layer);
    }
    else
        printf("the tree is empty\n");
}

int btree_bin_search(btree_node *node, int low, int high, KEY_VALUE key)
{
    int mid;
    if (low > high || low < 0 || high < 0)
    {
        return -1;
    }

    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (key > node->keys[mid])
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return low;
}

// ɾ�����ϲ�
// �ж�����key���� M/2 - 1
// 1.������������ ����M/2 - 1���ϲ�
// 2.�����������M/2 - 1����ڵ�
// 3.�ұ���������M/2 - 1����ڵ�

//{child[idx], key[idx], child[idx+1]}
// ��node�������������Ӻϲ�����
void btree_merge(btree *T, btree_node *node, int idx)
{
    btree_node *left = node->childrens[idx];
    btree_node *right = node->childrens[idx + 1];

    int i = 0;

    // data merge

    // destroy right

    // node
}

void btree_delete_key(btree *T, btree_node *node, KEY_VALUE key)
{
}

int btree_delete(btree *T, KEY_VALUE key)
{
    if (!T->root)
        return -1;

    btree_delete_key(T, T->root, key);
    return 0;
}

int main()
{
    btree T = {0};

    btree_create(&T, 3);

    int i = 0;
    char key[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (i = 0; i < 26; i++)
    {
        printf("%c ", key[i]);
        btree_insert(&T, key[i]);
    }

    btree_print(&T, T.root, 0);
    for (i = 0; i < 26; i++)
    {
        printf("\n---------------------------------\n");
        btree_delete(&T, key[25 - i]);
        // btree_traverse(T.root);
        btree_print(&T, T.root, 0);
    }
    return 0;
}