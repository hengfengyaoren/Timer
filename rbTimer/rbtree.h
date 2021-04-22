
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */

//nginx源码趴出来的红黑树
#ifndef _NGX_RBTREE_H_INCLUDED_
#define _NGX_RBTREE_H_INCLUDED_

typedef unsigned int  ngx_rbtree_key_t;
typedef unsigned int  ngx_uint_t;
typedef int   ngx_rbtree_key_int_t;
typedef unsigned char u_char;
#ifndef NULL
    #define NULL ((void*)0)
#endif

typedef struct ngx_rbtree_node_s  ngx_rbtree_node_t;

//红黑树结点
struct ngx_rbtree_node_s {
    ngx_rbtree_key_t       key;
    ngx_rbtree_node_t     *left;
    ngx_rbtree_node_t     *right;
    ngx_rbtree_node_t     *parent;
    u_char                 color;
    u_char                 data;
};

typedef struct ngx_rbtree_s  ngx_rbtree_t;

typedef void (*ngx_rbtree_insert_pt) (ngx_rbtree_node_t *root,
    ngx_rbtree_node_t *node, ngx_rbtree_node_t *sentinel);

//红黑树的结构
struct ngx_rbtree_s {
    ngx_rbtree_node_t     *root;
    ngx_rbtree_node_t     *sentinel;
    ngx_rbtree_insert_pt   insert;
};

/////////////////////////////////////////////////////////////////////
//初始化
#define ngx_rbtree_init(tree, s, i)                                           \
    ngx_rbtree_sentinel_init(s);                                              \
    (tree)->root = s;                                                         \
    (tree)->sentinel = s;                                                     \
    (tree)->insert = i

/////////////////////////////////////////////////////////////////////
//插入结点
void 
ngx_rbtree_insert(ngx_rbtree_t *tree, ngx_rbtree_node_t *node);

//删除结点
void
ngx_rbtree_delete(ngx_rbtree_t *tree, ngx_rbtree_node_t *node);

//插入结点值
void
ngx_rbtree_insert_value(ngx_rbtree_node_t *root, ngx_rbtree_node_t *node,
    ngx_rbtree_node_t *sentinel);
   
//插入时间值 
void
ngx_rbtree_insert_timer_value(ngx_rbtree_node_t *root,
    ngx_rbtree_node_t *node, ngx_rbtree_node_t *sentinel);

//结点的下一个值
ngx_rbtree_node_t *
ngx_rbtree_next(ngx_rbtree_t *tree,
    ngx_rbtree_node_t *node);

#define ngx_rbt_red(node)               ((node)->color = 1)
#define ngx_rbt_black(node)             ((node)->color = 0)
#define ngx_rbt_is_red(node)            ((node)->color)
#define ngx_rbt_is_black(node)          (!ngx_rbt_is_red(node))
#define ngx_rbt_copy_color(n1, n2)      (n1->color = n2->color)

/* a sentinel must be black */

#define ngx_rbtree_sentinel_init(node)  ngx_rbt_black(node)

//求出红黑树的最小结点
static ngx_rbtree_node_t *
ngx_rbtree_min(ngx_rbtree_node_t *node, ngx_rbtree_node_t *sentinel)
{
    while (node->left != sentinel) {
        node = node->left;
    }

    return node;
}

#endif /* _NGX_RBTREE_H_INCLUDED_ */
