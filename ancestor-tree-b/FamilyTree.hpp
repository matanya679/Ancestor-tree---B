#ifndef FAMILY_TREE_HPP
#define FAMILY_TREE_HPP

#include <iostream>
#include <string>
#include <stdexcept>

namespace family
{
	class Node
	{
	public:

		std::string name;
		std::string relationship;
		Node* mother;
		Node* father;
		char gender;

	public:
		Node(std::string name);
		Node(std::string name, char gender);
	};

	class Tree
	{
		Node* root;

	public:

		Tree(std::string rootName);
		Tree& addMother(std::string decendentName, std::string motherName);
		Tree& addFather(std::string decendentName, std::string fatherName);
		void display();
		std::string relation(std::string parentName);
		std::string find(std::string familyRelation);
		void remove(std::string falmilyMemberName);
		Node* findFamilyMember(Node* ptr, std::string decendantName);
		std::string findFamilyRelationName(Node* ptr, std::string familyRelation);
	};
}
#endif