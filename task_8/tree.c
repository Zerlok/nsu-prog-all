#include "mod.h"

void print_help() {
	printf("Help\n");
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