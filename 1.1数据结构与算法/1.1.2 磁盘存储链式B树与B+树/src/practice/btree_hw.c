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

#define DEGREE 3 // B树的阶数
typedef int KEY_VALUE;

typedef struct _btree_node
{
    KEY_VALUE *keys;                // 节点本身的keys数组
    struct _btree_node **childrens; // 子结点数组
    int num;                        // 节点本身keys的数量
    int leaf;                       // 是否是叶子节点 1：yes  0：no
} btree_node;

typedef struct _btree
{
    btree_node *root; //根节点
    int t;            // 开始时的节点数量
} btree;

btree_node *btree_create_node(int t, int leaf) {}
void btree_destroy_node(btree_node *node) {}
void btree_create(btree *T, int t) {}

// 添加，分裂
// 1.找到对应的节点，并且节点未满
// 2.找到节点已满
//     找内节点已满，内节点分裂
//     找到叶子节点已满，叶子节点分裂

// x节点的第i颗子树进行分裂
void btree_split_child(btree *T, btree_node *x, int i) {}
// 插入一个不满的节点
void btree_insert_nonfull(btree *T, btree_node *x, KEY_VALUE k) {}
void btree_insert(btree *T, KEY_VALUE key) {}
void btree_traverse(btree_node *x) {}
void btree_print(btree *T, btree_node *node, int layer) {}
int btree_bin_search(btree_node *node, int low, int high, KEY_VALUE key)
{
}

// 删除，合并
// 判断子树key数量 M/2 - 1
// 1.相邻两颗子树 都是M/2 - 1，合并
// 2.左边子树大于M/2 - 1，借节点
// 3.右边子树大于M/2 - 1，借节点

//{child[idx], key[idx], child[idx+1]}
void btree_merge(btree *T, btree_node *node, int idx) {}
void btree_delete_key(btree *T, btree_node *node, KEY_VALUE key)
{
}
int btree_delete(btree *T, KEY_VALUE key) {}
int main()
{
    return 0;
}