/************************************************
Michael McLaughlin
Comp Arch
Professor Menendez
Project 1.8 - BST
BST is a program that creates and maintains a binary search tree based on the instructions
read in from a file.
************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct binNode
{
	int item;
	struct binNode *left;
	struct binNode *right;
} Node;

Node *duplicate(Node*);
Node *treeSearch(int);
int insertNode(Node*);
int createNode(int);
int deleteNode(int);
void printTree(Node*);
void freeTree(Node*);

static Node *root;

int main(int argc, char **argv)
{
	FILE *filePoint;
	char nextChar;
	//Open the file.  Return error if file does not exist
	filePoint = fopen(argv[1], "r");
	if (filePoint == NULL)
	{
		printf("error\n");
		return 0;
	}
	//Check and return a zero for an empty list if file is empty
	nextChar = fgetc(filePoint);
	if (nextChar == EOF)
	{
		printf("0\n\n");
		return 0;
	}
	//Count number of lines in file to use later
	int lineCount = 0;
	while (nextChar != EOF)
	{
		if (nextChar == '\n') {lineCount++;}
		nextChar = fgetc(filePoint);
	}
	rewind(filePoint);
	//Sets up space for an array of strings and saves instructions from file
	char instructions[lineCount + 1][15];
	int i = 0;
	while (fgets(instructions[i], 15, filePoint) != NULL)
	{
		i++;
	}
	//Local variables used to iterate through instructions and perform tasks
	char *startPtr;
	char *endPtr;
	long number;
	int deleteIndex;
	int j;
	Node *searchNode;
	//Determines what type of instruction is encountered, and responds accordingly
	for (j = 0; j < lineCount + 1; j++)
	{
		if (instructions[j][0] == 'i')
		{
			startPtr = instructions[j];
			startPtr += 2;
			number = strtol(startPtr, &endPtr, 10);
			createNode((int)number);
		}
		if (instructions[j][0] == 's')
		{
			startPtr = instructions[j];
			startPtr += 2;
			number = strtol(startPtr, &endPtr, 10);
			searchNode = treeSearch((int)number);
			if (searchNode != NULL) {printf("present\n");}
			else if (searchNode == NULL) {printf("absent\n");}
			free(searchNode);
		}
		if (instructions[j][0] == 'p')
		{
			if (root == NULL) {printf("\n"); continue;}
			printTree(root);
			printf("\n");
		}
		if (instructions[j][0] == 'd')
		{
			startPtr = instructions[j];
			startPtr += 2;
			number = strtol(startPtr, &endPtr, 10);
			deleteIndex = deleteNode((int)number);
			if (deleteIndex == 1) {printf("deleted\n");}
		}
	}
	freeTree(root);
	return 0;
}

//Function freeTree() takes in a pointer of type Node, and iterates through the tree to
//free up any memory that is currently being used.  Void - returns nothing
void freeTree(Node *node)
{
	if (node == NULL) {return;}
	if (node->left != NULL) {freeTree(node->left);}
	if (node->right != NULL) {freeTree(node->right);}
	free(node);
	return;
}

//Function duplicate() creates a copy of a node, so that when searching the list,
//a node is not accidentally tampered with or deleted.  Accepts a pointer of type Node,
//and returns a pointer of type Node.
Node *duplicate(Node *node)
{
	Node *duplicated;
	duplicated = (Node*)malloc(sizeof(Node));
	*duplicated = *node;
	duplicated->left = NULL;
	duplicated->right = NULL;
	return duplicated;
}

//Function treeSearch() iterates through the tree and searches for a specific value.  If
//the value is found, a duplicate of that node is returned.  If the value isn't found, a
//null pointer is returned.  Accepts an integer as the value to search for, and returns
//a pointer of type Node.
Node *treeSearch(int item)
{
	Node *thisNode;
	thisNode = root;
	while ((thisNode != NULL) && (thisNode->item != item))
	{
		//Deciding whether to traverse left or right based on given value
		if (item < thisNode->item) {thisNode = thisNode->left;}
		else {thisNode = thisNode->right;} 
	}
	if (thisNode == NULL) {return thisNode;}
	else {return (duplicate(thisNode));}
}

//Function insertNode() takes an already created node and inserts it into the tree.  Accepts
//a pointer of type Node, and returns an integer: 1 if successful, 0 if unsuccessful.
int insertNode(Node *newNode)
{
	Node *thisNode;
	Node *parent;
	thisNode = root;
	parent = NULL;
	if (newNode == NULL) {printf("error\n"); return 0;}
	//Traverse tree until desired location is found	
	while (thisNode != NULL)
	{
		parent = thisNode;
		if (newNode->item < thisNode->item) {thisNode = thisNode->left;}
		else {thisNode = thisNode->right;}
	}
	//If new spot, place node.  Otherwise, place in proper sub-branch
	if (parent == NULL) {root = newNode;}
	else
	{
		if (newNode->item < parent->item) {parent->left = newNode;}
		else {parent->right = newNode;}
	}
	return 1;
}

//Function createNode() creates a new node to be eventually inserted into the tree.
//Accepts an integer as the input, which is the value the node is to contain.  Returns
//an integer depending on result: 1 if successful, 0 if not.
int createNode(int item)
{
	if (treeSearch(item) != NULL) {printf("duplicate\n"); return 0;}
	Node *newNode;
	newNode = (Node*)malloc(sizeof(Node));	//Use malloc to create the node
	newNode->item = item;			//Populate with data given
	newNode->left = newNode->right = NULL;	//Set children to NULL
	printf("inserted\n");
	return (insertNode(newNode));		//Call upon function to insert new node
}

//Function deleteNode() deletes a node based on the value held inside.  Accepts an integer as
//the input, which is the value contained in the node which is to be deleted.  Returns
//an integer depending on result: 1 if successful, 0 if not.
int deleteNode(int item)
{
	Node *parent;
	Node *thisNode;
	Node *deletedParent;
	Node *nodeToDelete;
	thisNode = root;
	parent = NULL;
	//Traverse tree to find the desired node 
	while ((thisNode != NULL) && (item != thisNode->item))
	{
		parent = thisNode;
		if (item < thisNode->item) {thisNode = thisNode->left;}
		else {thisNode = thisNode->right;}
	}
	//In case the node is not found in the tree, print 'absent' and return
	if (thisNode == NULL) {printf("absent\n"); return 0;}
	else
	{
		if (thisNode == root)
		{
			nodeToDelete = root;
			deletedParent = NULL; 
		}                
		else
		{
			nodeToDelete = thisNode;
			deletedParent = parent;
		}
	}
	//In the event that there is only one sub-tree or none at all 
	if (nodeToDelete->right == NULL)
	{
		if (deletedParent == NULL)   
		{
			root = nodeToDelete->left;
			free(nodeToDelete);
			return 1;
		}
		else
		{
			if (deletedParent->left == nodeToDelete)
			{
				deletedParent->left = nodeToDelete->left;
			}
			else {deletedParent->right = nodeToDelete->left;}
			free(nodeToDelete);
			return 1;
		}
	}
	//In the event that there is one or more sub-trees
	else 
	{
		if (nodeToDelete->left == NULL)
		{
			if (deletedParent == NULL)    
			{
				root = nodeToDelete->right;
				free (nodeToDelete);
				return 1;
			}
			else
			{
				if (deletedParent->left == nodeToDelete)
				{
					deletedParent->left = nodeToDelete->right;
				}
				else {deletedParent->right = nodeToDelete->right;}
				free(nodeToDelete);
				return 1;
			}
		}
		else
		{               
			thisNode = nodeToDelete->left;
			parent = nodeToDelete;
			while (thisNode->right != NULL)
			{
				parent = thisNode;
				thisNode = thisNode->right;
			} 
			nodeToDelete->item = thisNode->item; 
			if (parent == nodeToDelete) {parent->left = thisNode->left;}
			else {parent->right = thisNode->left;}
			free(thisNode);
			return 1;
		}
	}
}

//Function printTree() traverses the tree in an in-order traversal, and prints the values
//accordingly.  It accepts a pointer of type Node as an argument.  Void - returns nothing.
void printTree(Node *node)
{
	if(node != NULL)
	{
		printf("(");
		printTree(node->left);
		printf("%d", node->item);
		printTree(node->right);
		printf(")");
	}
}
