/**
 * @File Name: btree_hw.c
 * @Brief : B树实现
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2022-03-13
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

// 一颗M阶B树T，满足以下条件
// 1. 每个结点至多拥有M颗子树
// 2. 根结点至少拥有两颗子树
// 3. 除了根结点以外，其余每个分支结点至少拥有M/2课子树
// 4. 所有的叶结点都在同一层上
// 5. 有k颗子树的分支结点则存在k-1个关键字，关键字按照递增顺序进行排序
// 6. 关键字数量满足ceil(M/2)-1 <= n <= M-1

#define DEGREE 3       // B树的阶数
typedef int KEY_VALUE; //树节点包含的key的类型

typedef struct _btree_node
{
    KEY_VALUE *keys;                // 节点本身的keys数组首地址
    struct _btree_node **childrens; // 子结点数组首地址
    int num;                        // 节点本身keys的数量
    int leaf;                       // 是否是叶子节点 1：yes  0：no
} btree_node;

typedef struct _btree
{
    btree_node *root; // 根节点
    int t;            // 开始时的节点数量
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

// 添加，分裂
// 1.找到对应的节点，并且节点未满
// 2.找到节点已满
//     找内节点已满，内节点分裂
//     找到叶子节点已满，叶子节点分裂

// x节点的第i颗子树进行分裂
void btree_split_child(btree *T, btree_node *x, int i)
{
    // 这个是规定的节点数量
    int t = T->t;

    btree_node *y = x->childrens[i];
    // 新节点 Z 的创建与赋值
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

    //  把 z 连接到 x 下面，z并不一定是x的最末尾
    for (j = x->num; j >= i + 1; j--)
    {
        x->childrens[j + 1] = x->childrens[j];
    }
    x->childrens[i + 1] = z;

    //  把 y 中间的那个key 放进 x 的keys数组里面，这个key并不一定是x的keys数组最末尾
    for (j = x->num; j >= i + 1; j--)
    {
        x->keys[j + 1] = x->keys[j];
    }
    x->keys[i] = y->keys[t - 1];
    x->num += 1;
}

// 往插入一个不满的节点 x 插入一个 k
void btree_insert_nonfull(btree *T, btree_node *x, KEY_VALUE k)
{
    int i = x->num - 1;
    // 区分是否叶子节点
    if (x->leaf == 1)
    {
        // 找到合适的位置把k插入，比k小的往后移
        while (i >= 0 && x->keys[i] > k)
        {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->num += 1;
    }
    // 如果不是叶子节点先往孩子里面塞进去，如果孩子满了就把孩子先分裂了
    else
    {
        while (i >= 0 && x->keys[i] > k)
            i--;
        // 如果x的这个孩子满了，要先进行分裂
        if (x->childrens[i + 1]->num == (2 * (T->t)) - 1)
        {
            btree_split_child(T, x, i + 1);
            // 找位置
            if (k > x->keys[i + 1])
                i++;
        }
        // 插入
        btree_insert_nonfull(T, x->childrens[i + 1], k);
    }
}

// 综合的插入
void btree_insert(btree *T, KEY_VALUE key)
{
    // 通过创造一个空的父节点来进行根节点的分裂
    btree_node *r = T->root;
    // 如果满了就先分裂再插入
    if (r->num == 2 * T->t - 1)
    {
        // 创造一个空的父节点，非叶子节点
        btree_node *node = btree_create_node(T->t, 0);
        T->root = node;
        // 该节点的孩子是原来的父节点
        node->childrens[0] = r;
        // 进行分裂
        btree_split_child(T, node, 0);
        // 找位置
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

// 删除，合并
// 判断子树key数量 M/2 - 1
// 1.相邻两颗子树 都是M/2 - 1，合并
// 2.左边子树大于M/2 - 1，借节点
// 3.右边子树大于M/2 - 1，借节点

//{child[idx], key[idx], child[idx+1]}
// 把node的左右两个孩子合并起来
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