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

#define DEGREE 3 // B���Ľ���
typedef int KEY_VALUE;

typedef struct _btree_node
{
    KEY_VALUE *keys;                // �ڵ㱾���keys����
    struct _btree_node **childrens; // �ӽ������
    int num;                        // �ڵ㱾��keys������
    int leaf;                       // �Ƿ���Ҷ�ӽڵ� 1��yes  0��no
} btree_node;

typedef struct _btree
{
    btree_node *root; //���ڵ�
    int t;            // ��ʼʱ�Ľڵ�����
} btree;

btree_node *btree_create_node(int t, int leaf) {}
void btree_destroy_node(btree_node *node) {}
void btree_create(btree *T, int t) {}

// ��ӣ�����
// 1.�ҵ���Ӧ�Ľڵ㣬���ҽڵ�δ��
// 2.�ҵ��ڵ�����
//     ���ڽڵ��������ڽڵ����
//     �ҵ�Ҷ�ӽڵ�������Ҷ�ӽڵ����

// x�ڵ�ĵ�i���������з���
void btree_split_child(btree *T, btree_node *x, int i) {}
// ����һ�������Ľڵ�
void btree_insert_nonfull(btree *T, btree_node *x, KEY_VALUE k) {}
void btree_insert(btree *T, KEY_VALUE key) {}
void btree_traverse(btree_node *x) {}
void btree_print(btree *T, btree_node *node, int layer) {}
int btree_bin_search(btree_node *node, int low, int high, KEY_VALUE key)
{
}

// ɾ�����ϲ�
// �ж�����key���� M/2 - 1
// 1.������������ ����M/2 - 1���ϲ�
// 2.�����������M/2 - 1����ڵ�
// 3.�ұ���������M/2 - 1����ڵ�

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