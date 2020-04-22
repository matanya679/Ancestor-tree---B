#include "FamilyTree.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <iterator>

#define COUNT 10

namespace family
{
Node::Node(std::string name)
{
	this->name = name;
	this->relationship = "me";
	this->father = nullptr;
	this->mother = nullptr;
	this->gender = 'm';
}

Node::Node(std::string name, char gender)
{
	this->name = name;
	this->relationship = "";
	this->father = nullptr;
	this->mother = nullptr;
	this->gender = gender;
}

Tree::Tree(std::string rootName)
{
	this->root = new Node(rootName);
}

Node *Tree::findFamilyMember(Node *root, std::string familyMem)
{

	Node *current, *pre;
	Node *matchNode = nullptr;
	if (root == NULL)
		return nullptr;

	current = root;
	while (current != NULL)
	{

		if (current->mother == NULL)
		{
			if (current->name.compare(familyMem) == 0)
			{
				matchNode = current;
			}
			current = current->father;
		}
		else
		{

			/* Find the inorder predecessor of current */
			pre = current->mother;
			while (pre->father != NULL && pre->father != current)
				pre = pre->father;

			/* Make current as the right child of its inorder
				   predecessor */
			if (pre->father == NULL)
			{
				pre->father = current;
				current = current->mother;
			}

			/* Revert the changes made in the 'if' part to restore
				   the original tree i.e., fix the right child
				   of predecessor */
			else
			{
				pre->father = NULL;
				if (current->name.compare(familyMem) == 0)
				{
					matchNode = current;
				}
				current = current->father;
			} /* End of if condition pre->right == NULL */
		}	  /* End of if condition current->left == NULL*/
	}		  /* End of while */
	return matchNode;
}

Tree &Tree::addMother(std::string decendentName, std::string motherName)
{
	Node *temp = findFamilyMember(this->root, decendentName);
	if (temp != nullptr)
	{
		if(temp->mother!=nullptr)
		{
			throw std::runtime_error("Error! ,  there is already mother to "+temp->name
			+" by the name "+temp->mother->name);
		}
		temp->mother = new Node(motherName, 'f');
		temp->mother->relationship = relation(temp->mother->name);
		return *this;
	}
		throw std::runtime_error("Error! ,  there is no decendant by the name"+decendentName
			+"in the family tree");
	
}
Tree &Tree::addFather(std::string decendentName, std::string fatherName)
{
	Node *temp = findFamilyMember(this->root, decendentName);
	if (temp != nullptr)
	{
		if(temp->father!=nullptr)
		{
			throw std::runtime_error("Error! ,  there is already mother to "+temp->name
			+" by the name "+temp->father->name);
		}
		temp->father = new Node(fatherName, 'm');
		temp->father->relationship = relation(temp->father->name);
			return *this;
	}
	throw std::runtime_error("Error! ,  there is no decendant by the name"+decendentName
			+"in the family tree");
}
void print2DUtil(Node *root, int space)
{
	// Base case
	if (root == NULL)
		return;

	// Increase distance between levels
	space += COUNT;

	// Process right child first
	print2DUtil(root->father, space);

	// Print current node after space
	// count
	std::cout << std::endl;
	for (int i = COUNT; i < space; i++)
		std::cout << " ";
	std::cout << root->name << "\n";

	// Process left child
	print2DUtil(root->mother, space);
}
void Tree::display()
{
	// Pass initial space count as 0
	print2DUtil(this->root, 0);
}
int findWhichGeneration(Node *start, Node *end, int level)
{

	if (start == NULL)
		return 0;

	if (start == end)
		return level;

	int downlevel = findWhichGeneration(start->mother,
										end, level + 1);
	if (downlevel != 0)
		return downlevel;

	downlevel = findWhichGeneration(start->father,
									end, level + 1);
	return downlevel;
}

std::string moreThan2Generation(int generaiton, Node *familyMen)
{
	std::string relationStr = "";
	for (int i = 0; i < generaiton - 3; i++)
	{
		relationStr += "great";
		relationStr += "-";
	}
	relationStr += familyMen->gender == 'm' ? "grandfather" : "grandmother";
	return relationStr;
}
std::string creatingString(int generation, Node *familyMem)
{
	if (generation == 0)
	{
		return std::string("Error,the root is null!");
	}
	if (generation == 1)
	{
		return std::string("me");
	}
	if (generation == 2)
	{
		if (familyMem->gender == 'm')
		{
			return std::string("father");
		}
		else
		{
			return std::string("mother");
		}
	}

	return moreThan2Generation(generation, familyMem);
}

std::string Tree::relation(std::string parentName)
{

	Node *familyMem = findFamilyMember(this->root, parentName);

	if (familyMem != nullptr)
	{
		int whichGeneration = findWhichGeneration(this->root, familyMem, 1);
		return creatingString(whichGeneration, familyMem);
	}
	return std::string("unrelated");
}
std::string Tree::findFamilyRelationName(Node *root, std::string familyRelation)
{
	
	Node *current, *pre;
	std::string matchStr = "";
	bool finisheReverte = true;
	if (root == NULL)
		return matchStr;

	current = root;
	while (current != NULL && finisheReverte)
	{

		if (current->mother == NULL)
		{
			if (current->relationship.compare(familyRelation) == 0)
			{
				matchStr = current->name;
			}
			current = current->father;
		}
		else
		{

			/* Find the inorder predecessor of current */
			pre = current->mother;
			while (pre->father != NULL && pre->father != current)
				pre = pre->father;

			/* Make current as the right child of its inorder
				   predecessor */
			if (pre->father == NULL)
			{
				pre->father = current;
				current = current->mother;
			}

			/* Revert the changes made in the 'if' part to restore
				   the original tree i.e., fix the right child
				   of predecessor */
			else
			{
				pre->father = NULL;
				if (current->relationship.compare(familyRelation) == 0)
				{
					matchStr = current->name;
				}
				current = current->father;
				if (matchStr.compare("") != 0)
				{
					finisheReverte = false;
				}
			} /* End of if condition pre->right == NULL */
		}	  /* End of if condition current->left == NULL*/
	}		  /* End of while */
	if (matchStr.compare("") != 0)
	{
		return matchStr;
	}

	throw std::runtime_error("The tree cannot handle the \'" + familyRelation + "\' relation");
}
std::string Tree::find(std::string familyRelation)
{
	try
	{
		return findFamilyRelationName(this->root, familyRelation);
	}
	catch (const std::exception &ex)
	{
		throw;
	}
}

void removeNodesChildren(Node *&node)
{
	if (node != nullptr)
	{
		if (node->father != nullptr)
		{
			removeNodesChildren(node->father);
		}
		if (node->mother != nullptr)
		{
			removeNodesChildren(node->mother);
		}
		delete node;
		node = nullptr;
	}
}
void findNodeToRemove(Node *&node, std::string familyMemberName)
{
	if (node != nullptr)
	{
		if (node->name.compare(familyMemberName) == 0)
		{
			removeNodesChildren(node);
			return;
		}
		if (node->father != nullptr)
		{
			findNodeToRemove(node->father, familyMemberName);
		}
		if (node->mother != nullptr)
		{
			findNodeToRemove(node->mother, familyMemberName);
		}
	}
}
void Tree::remove(std::string familyMemberName)
{
	if(this->root->name.compare(familyMemberName)==0)
	{
			throw std::runtime_error("Error!, we cant remove the root.");
	}
	Node* temp=findFamilyMember(this->root,familyMemberName);
	if(temp!=nullptr)
	{
		if(temp->name.compare(familyMemberName)==0)
		{
			findNodeToRemove(this->root, familyMemberName);
			return;
		}		
	}
	throw std::runtime_error("The tree cannot handle the \'" + familyMemberName + "\' relation");

}
}
 // namespace family