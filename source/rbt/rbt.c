#include <stdlib.h>
#include <stdbool.h>

#include "mem.h"
#include "rbt.h"

static void rbt_free(void* v_tree){
	rbt_t* tree = (rbt_t*) v_tree;
	if(tree && tree->root) mem_release(tree->root);
}

static void rbt_node_free(void* v_node){
	rbt_node_t* node = (rbt_node_t*) v_node;
	if(node){
		mem_release(node->contents);
		if(node->left) mem_release(node->left);
		if(node->right) mem_release(node->right);
	}
}

static int rbt_default_comparator(void* a, void* b){
	return (a == b ? 0 : (a<b ? -1 : 1 ));
}

rbt_node_t* rbt_node_new(void* contents){
	rbt_node_t* node = mem_allocate(sizeof(rbt_node_t), &rbt_node_free);
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->contents = contents;
	node->color = RED;
	return node;
}

rbt_t* rbt_new(comparator_t comparator){
	rbt_t* tree = mem_allocate(sizeof(rbt_t), &rbt_free);
	tree->root = NULL;
	tree->comp = comparator ? comparator : rbt_default_comparator;
	return tree;
}

//leaves are NULL and black implicitly
static rbt_color_t node_color(rbt_node_t* node){
	return (node ? node->color : BLACK);
}

typedef enum {
	LEFT = 0, RIGHT
} direction_t;

static void rotate(rbt_t* tree, rbt_node_t* node, direction_t direction){
	rbt_node_t* edon = (direction == LEFT) ? node->right : node->left;
	if(edon){
		if(NULL == node->parent) tree->root = edon;
		else if(node->parent->left == node) node->parent->left = edon;
		else node->parent->right = edon;
		edon->parent = node->parent;
		if(direction == LEFT){
			node->right = edon->left; //safe to overwrite node->right : is edon
			if(edon->left) edon->left->parent = node;
			edon->left = node;
		} else { //mirror of above
			node->left = edon->right; //safe to overwrite node->left : is edon
			if(edon->right) edon->right->parent = node;
			edon->right = node;
		}
		node->parent = edon;
	} /* else rotation isn't allowed */
}

static void rbt_ins_rebalance(rbt_t* tree, rbt_node_t* node, direction_t heavy_side){
	rbt_node_t* parent = node->parent;
	rbt_node_t* grandparent = (parent ? parent->parent : NULL);
	rotate(tree, grandparent, (heavy_side == LEFT ? RIGHT : LEFT));
	parent->color = BLACK;
	grandparent->color = RED;
}

//NODE:the node to be inserted
static void rbt_ins_recolor(rbt_t* tree, rbt_node_t* node){
	rbt_node_t* parent = node->parent;
	rbt_node_t* grandparent = (parent ? parent->parent : NULL);
	rbt_node_t* uncle = (grandparent ? (parent == grandparent->left ? grandparent->right : grandparent->left) : NULL);
	if(NULL == parent){
		node->color = BLACK;
	}else if(BLACK == node_color(parent)){
		/* dont need to do anything */
	}else if(node_color(uncle) == RED){
		//parent and uncle are both red. both can be painted black
		grandparent->color = RED;
		parent->color = BLACK;
		uncle->color = BLACK;
		rbt_ins_recolor(tree, grandparent);
	}else{
		direction_t node_side = (node == parent->left ? LEFT : RIGHT);
		direction_t parent_side = (parent == grandparent->left ? LEFT : RIGHT);
		if(node_side != parent_side){ // "inside" case
			rotate(tree, parent, parent_side); //transform to "outside" case
			node = parent; //parent now lowest node.
		}
		rbt_ins_rebalance(tree, node, parent_side);
	}
}

static void rbt_insert_node(rbt_t* tree, rbt_node_t* node, rbt_node_t* parent){
	if(NULL == parent){ /* inserting root of the tree */
		tree->root = node;
		rbt_ins_recolor(tree, node);
	}else if(tree->comp(node->contents, parent->contents) < 0){
		if(parent->left){
			rbt_insert_node(tree, node, parent->left);
		}else{
			node->parent = parent;
			parent->left = node;
			rbt_ins_recolor(tree, node);
		}
	}else{
		if(parent->right){
			rbt_insert_node(tree, node, parent->right);
		}else{
			node->parent = parent;
			parent->right = node;
			rbt_ins_recolor(tree, node);
		}
	}
}

rbt_node_t* rbt_insert(rbt_t* tree, void* value){
	rbt_node_t* new_node = rbt_node_new(value);
	rbt_insert_node(tree, new_node, tree->root);
	return new_node;
}


static rbt_node_t* rbt_lookup_node(rbt_t* tree, rbt_node_t* node, void* value){
	rbt_node_t* ret = NULL;
	if(node){
		int c = tree->comp(value, node->contents);
		if(c == 0) ret = node;
		else if(c > 0) ret = rbt_lookup_node(tree, node->right, value);
		else if(c < 0) ret = rbt_lookup_node(tree, node->left, value);
	}
	return ret;
}

rbt_node_t* rbt_lookup(rbt_t* tree, void* value){
	return rbt_lookup_node(tree, tree->root, value);
}

//node has a count -1 of black nodes to leaves relative to the rest of the tree
static void rbt_del_rebalance(rbt_t* tree, rbt_node_t* node){
	rbt_node_t* parent = node->parent;
	if(parent){
		direction_t node_side = (node == parent->left ? LEFT : RIGHT);
		rbt_node_t* sib = (node_side == LEFT ? parent->right : parent->left);
		rbt_node_t* inside_nibling = sib ? (node_side == LEFT ? sib->left : sib->right) : NULL;
		rbt_node_t* outside_nibling = sib ? (node_side == LEFT ? sib->right : sib->left) : NULL;
		if(RED == node_color(sib)){
			//rotate so sib is black & recurse w/ new scenario
			rotate(tree, parent, node_side);
			parent->color = RED;
			sib->color = BLACK;
			rbt_del_rebalance(tree, node);
		}else if(BLACK == node_color(inside_nibling) && BLACK == node_color(outside_nibling)){
			//both niblings are black ; can paint sib red & rebalance on parent
			sib->color = RED;
			if(RED == node_color(parent)) parent->color = BLACK;
			else rbt_del_rebalance(tree, parent);
		}else if(BLACK == node_color(outside_nibling)){
			//convert "inside" case to "outside" case & recurse w/ new scenario
			rotate(tree, sib, (node_side == LEFT ? RIGHT : LEFT));
			sib->color = RED;
			inside_nibling->color = BLACK;
			rbt_del_rebalance(tree, node);
		}else{
			rotate(tree, parent, node_side);
			sib->color = parent->color;
			parent->color = BLACK;
			outside_nibling->color = BLACK;
		}
	}else{
		node->color = BLACK; //TODO: verify this is necessary
	}
}

static rbt_node_t* rightmost_descendent(rbt_node_t* node){
	return (node->right) ? rightmost_descendent(node->right) : node;
}

static void rbt_delete_node(rbt_t* tree, rbt_node_t* node){
	rbt_node_t* parent = node->parent;
	if(node->left && node->right){
		rbt_node_t* replacement = rightmost_descendent(node->left);
		mem_retain(replacement);
		rbt_delete_node(tree, replacement);
		if(node->left) node->left->parent = replacement;
		if(node->right) node->right->parent = replacement;
		replacement->left = node->left;
		replacement->right = node->right;
		replacement->parent = node->parent;
		replacement->color = node->color;
		if(NULL == parent) tree->root = replacement;
		else if(node == parent->left) parent->left = replacement;
		else parent->right = replacement;
	}else{
		//node has at most one non-leaf child
		rbt_node_t* child = NULL;
		if(RED == node_color(node)){
			//node cannot have children
			if(node == parent->left) parent->left = NULL;
			else parent->right = NULL;
		} else if(RED == node_color(node->left) || RED == node_color(node->right)){
			child = node->left ? node->left : node->right;
			child->color = BLACK;
		} else {
			rbt_del_rebalance(tree, node);
			//reset child/parent after rebalance; tree may have been rotated
			parent = node->parent;
			child = node->left ? node->left : node->right;
		}
		if(child) child->parent = parent;
		if(NULL == parent) tree->root = child;
		else if(node == parent->right) parent->right = child;
		else parent->left = child;
	}
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	mem_release(node);
}
void rbt_delete(rbt_t* tree, void* value){
	rbt_node_t* doomed = rbt_lookup(tree, value);
	if(doomed) rbt_delete_node(tree, doomed);
}

/* THE FOLLOWING FUNCTIONS (TO EOF) ARE USED FOR TESTING PURPOSES ONLY */

//if path to the left != path to the right, return -1 (invalid)
int count_black_nodes_to_leaf(rbt_node_t* node){
	int ret = 0;
	if(node){
		int leftcount = count_black_nodes_to_leaf(node->left);
		int rightcount = count_black_nodes_to_leaf(node->right);
		if(leftcount != rightcount) ret = -1;
		else if(node->color == BLACK) ret = leftcount+1;
		else ret = leftcount;
	}
	return ret;
}

static rbt_status_t rbt_check_node(rbt_t* tree, rbt_node_t* node, void* min_val, void* max_val){
	rbt_status_t ret = OK;
	void* neg1 = mem_box(-1);
	if(node){
		if(node->color != RED && node->color != BLACK) ret = UNKNOWN_COLOR;
		else if(node->color == RED && (node_color(node->left) != BLACK && node_color(node->right) != BLACK))
			ret = RED_WITH_RED_CHILD;
		else if(tree->comp(min_val, neg1) > 0 && tree->comp(node->contents, min_val) < 0) ret = OUT_OF_ORDER;
		else if(tree->comp(max_val, neg1) > 0 && tree->comp(node->contents, max_val) > 0) ret = OUT_OF_ORDER;
		else if(node->left == node || node->right == node) ret = SELF_REFERENCE;
		else if(node->left && node->left->parent != node) ret = BAD_PARENT_POINTER;
		else if(node->right && node->right->parent != node) ret = BAD_PARENT_POINTER;
		if(ret == OK) ret = rbt_check_node(tree, node->left, min_val, node->contents);
		if(ret == OK) ret = rbt_check_node(tree, node->right, node->contents, max_val);
	}
	mem_release(neg1);
	return ret;
}

//check the contents of the given tree/node as valid
rbt_status_t rbt_check_status(rbt_t* tree){
	rbt_status_t ret = OK;
	void* neg1 = mem_box(-1);
	if(tree){
		ret = rbt_check_node(tree, tree->root, neg1, neg1);
		if(ret == OK && tree->root && tree->root->parent) ret = BAD_PARENT_POINTER;
		if(ret == OK && node_color(tree->root) != BLACK) ret = BAD_ROOT_COLOR;
		if(ret == OK && count_black_nodes_to_leaf(tree->root) == -1) ret = BLACK_NODES_UNBALANCED;
	}
	mem_release(neg1);
	return ret;
}

