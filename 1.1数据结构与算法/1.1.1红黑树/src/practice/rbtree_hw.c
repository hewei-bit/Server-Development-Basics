/**
 * @File Name: rbtree_hw.c
 * @Brief :
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
//
typedef struct _rbtree_node
{
    unsigned char color;         //��ɫ
    struct _rbtree_node *right;  //���������ȱ����
    struct _rbtree_node *left;   // ���������ȱ���С
    struct _rbtree_node *parent; // ���ڵ�
    KEY_TYPE key;                // �ڵ㱾���ֵ
    void *value;
} rbtree_node;

typedef struct _rbtree
{
    rbtree_node *root; // ��ͷ
    rbtree_node *nil;  // ����Ҷ�ӽڵ�ָ��nil��ͨ�õ�Ҷ�ӽڵ�
} rbtree;

// �ҵ���С
rbtree_node *rbtree_mini(rbtree *T, rbtree_node *x) {}
// �ҵ����
rbtree_node *rbtree_maxi(rbtree *T, rbtree_node *x) {}
//
rbtree_node *rbtree_successor(rbtree *T, rbtree_node *x) {}
// ����
void rbtree_left_rotate(rbtree *T, rbtree_node *x) {}
// ����
void rbtree_right_rotate(rbtree *T, rbtree_node *y) {}
// ����
void rbtree_insert_fixup(rbtree *T, rbtree_node *z) {}
void rbtree_insert(rbtree *T, rbtree_node *z) {}
// ɾ��
void rbtree_delete_fixup(rbtree *T, rbtree_node *x) {}
rbtree_node *rbtree_delete(rbtree *T, rbtree_node *z) {}
// ����
rbtree_node *rbtree_search(rbtree *T, KEY_TYPE key) {}
// �õݹ�ʵ���������
void rbtree_traversal(rbtree *T, rbtree_node *node) {}
int main()
{
    return 0;
}
// ��������游���������������
//     1. �����Ǻ�ɫ��
//     2. �����Ǻ�ɫ�ģ����ҵ�ǰ������Һ���
//     3. �����Ǻ�ɫ�ģ����ҵ�ǰ���������

// ��ǰ����Ǹ����������������
//     1. ��ǰ�����ֵܽ���Ǻ�ɫ��
//     2. ��ǰ�����ֵܽ���Ǻ�ɫ�ģ������ֵܽ���
//     �������ӽ�㶼�Ǻ�ɫ��
//     3. ��ǰ�����ֵܽ���Ǻ�ɫ�ģ������ֵܽ���
//     �����Ǻ�ɫ�ģ��Һ����Ǻ�ɫ��
//     ��ǰ����Ǹ����������������
//     4. ��ǰ�����ֵܽ���Ǻ�ɫ�ģ������ֵܽ���
//     �Һ����Ǻ�ɫ��