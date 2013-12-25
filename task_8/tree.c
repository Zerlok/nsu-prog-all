#include "mod.h"

// struct Tree {
// 	int value;
// 	struct Tree *left;
// 	struct Tree *right;
// };

void print_help() {
	printf("Help\n");
}

struct Tree *stree(struct Tree *root, struct Tree *new_root, int val) {
	if (!new_root) {
		new_root = (struct Tree*) malloc(sizeof(struct Tree));
		if (!new_root) {
			printf("ERROR: Not enough memory.\n");
			return NULL;
		}
		new_root->left = NULL;
		new_root->right = NULL;
		new_root->value = val;
		if (!root) return new_root;
		if (val < root->value) root->left = new_root;
		else root->right = new_root;
		return new_root;
	}
	if (val < new_root->value) {
		stree(new_root, new_root->left, val);
	} else {
		stree(new_root, new_root->right, val);
	}
}

struct Tree *insert(struct Tree *root, int val) {
	if (!root) {
		root = (struct Tree*) malloc(sizeof(struct Tree));
		root->left = NULL;
		root->right = NULL;
		root->value = val;
		return root;
	}
	if (val < root->value) {
		root->left = insert(root->left, val);
		return root;
	} else if (val == root->value) {
		return root;
	} else {
		root->right = insert(root->right, val);
		return root;
	}
}

void print_tree(struct Tree *root) {
	if (root) {
		printf("%d\n", root->value);
		print_tree(root->left);
		print_tree(root->right);
	}
}