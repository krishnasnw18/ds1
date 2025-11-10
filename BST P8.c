#include <stdio.h>
#include <stdlib.h>

// Structure for a BST node
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// i. Insert new node
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

// ii. Find number of nodes in longest path from root (Height of the tree)
int findLongestPathNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = findLongestPathNodes(root->left);
    int rightHeight = findLongestPathNodes(root->right);
    return 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
}

// iii. Minimum data value found in the tree
struct Node* findMin(struct Node* node) {
    if (node == NULL) {
        return NULL;
    }
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// iv. Change a tree so that the roles of the left and right pointers are swapped at every node (Mirror Tree)
void mirrorTree(struct Node* node) {
    if (node == NULL) {
        return;
    }
    struct Node* temp;

    mirrorTree(node->left);
    mirrorTree(node->right);

    // Swap pointers
    temp = node->left;
    node->left = node->right;
    node->right = temp;
}

// v. Search a value
struct Node* search(struct Node* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }
    if (value < root->data) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

// Inorder traversal to display the tree (for verification)
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    struct Node* root = NULL;

    // Constructing the BST by inserting values
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int num_values = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < num_values; i++) {
        root = insert(root, values[i]);
    }

    printf("BST constructed. Inorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    // i. Insert new node
    printf("Inserting 25...\n");
    root = insert(root, 25);
    printf("Inorder traversal after inserting 25: ");
    inorderTraversal(root);
    printf("\n");

    // ii. Find number of nodes in longest path from root
    printf("Number of nodes in longest path from root (Height): %d\n", findLongestPathNodes(root));

    // iii. Minimum data value found in the tree
    struct Node* minNode = findMin(root);
    if (minNode != NULL) {
        printf("Minimum data value in the tree: %d\n", minNode->data);
    } else {
        printf("Tree is empty, no minimum value.\n");
    }

    // iv. Change a tree so that the roles of the left and right pointers are swapped at every node
    printf("Mirroring the tree...\n");
    mirrorTree(root);
    printf("Inorder traversal after mirroring: ");
    inorderTraversal(root);
    printf("\n");

    // v. Search a value
    int searchValue = 60;
    struct Node* foundNode = search(root, searchValue);
    if (foundNode != NULL) {
        printf("Value %d found in the tree.\n", searchValue);
    } else {
        printf("Value %d not found in the tree.\n", searchValue);
    }

    // Free allocated memory (important for larger applications)
    // A proper deallocation function would be needed for a full implementation.

    return 0;
}
