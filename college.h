/*****************************
	Kaylee Poole
	2/28/17
	Container class using a linked list that holds course objects.
******************************/

#include"course.h"
#include"node.h"
#include<string>
#include<iostream>
#ifndef COLLEGE_H
#define COLLEGE_H

class College{
	public:
		College(std::string fullname=std::string(), node *hd=NULL);
		//Big 3
		~College();
		College(const College& other);
		College& operator=(const College& other);

		void add(course& c);
		void display(std::ostream& outs);
		void remove(std::string target);
		double hours();
		double gpa();
		void load(std::istream& ins);
		void save(std::ostream& outs);

	private:
		node *head;
		std::string name;
};

#endif
