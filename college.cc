/*****************************
	Kaylee Poole
	2/28/17
	Implementation file for college.h, which is a linked list for course objects.
******************************/

#include"college.h"
#include"course.h"
#include"node.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

College::College(string fullname, node *hd)
{
	head=hd;
	name=fullname;
}

College::~College()
{
	node *tmp;
	while(head!=NULL)
	{
		tmp=head;
		head=head->link();
		delete tmp;
	}
}

College::College(const College& other)
{
	name=other.name;
	if(other.head==NULL)
	{
		head=NULL;	
	}
	else
	{
		node *s_ptr, *d_ptr; //source and head of new list pointers
		head=new node(other.head->data());
		s_ptr=other.head->link();
		d_ptr=head;
		while(s_ptr!=NULL)
		{
			d_ptr->set_link(new node(s_ptr->data()));
			d_ptr=d_ptr->link();
			s_ptr=s_ptr->link();
		}
	}
}

College& College::operator=(const College& other)
{
	node *tmp;
	if(this==&other)
	{
		return *this;
	}
	else
	{
		name=other.name;
		while(head!=NULL)
		{
			tmp=head;
			head=head->link();
			delete tmp;
		}	
		node *s_ptr, *d_ptr; //source and head of new list pointers
		if(other.head!=NULL)
		{
			head=new node(other.head->data());
			s_ptr=other.head->link();
			d_ptr=head;
			while(s_ptr!=NULL)
			{
				d_ptr->set_link(new node(s_ptr->data()));
				d_ptr=d_ptr->link();
				s_ptr=s_ptr->link();
			}
		}
		return *this;
	}
}

void College::add(course& c)
{
	node *tmp=head;
	node *previous;
	if(head==NULL) //nothing in list
	{
		head=new node(c);
	}
	else if(head->data().get_course_number()>c.get_course_number()) //adds to beginnging of list
	{
		head=new node(c);
		head->set_link(tmp);			
	}
	else 
	{
		while(tmp->link()!=NULL)
			{
				tmp=tmp->link();
			}
		if(tmp->data().get_course_number()<c.get_course_number()) //adds to end of list
		{
			tmp->set_link(new node(c));
		}
		else //adds between 2 objects
		{
			tmp=head;
			while(tmp->data().get_course_number()<c.get_course_number())
			{
				previous=tmp;
				tmp=tmp->link();
			}
			previous->set_link(new node(c));
			previous=previous->link();
			previous->set_link(tmp);
		}		
	}
}

void College::display(ostream& outs) 
{
	node *tmp=head;
	while(tmp!=NULL)
	{
		outs<<tmp->data();
		tmp=tmp->link();
	}
	outs<<name<<"'s Courses"<<endl;
}

void College::remove(string target)
{
	for(int i =0; i<target.length(); ++i) //segfaults if target is not capitalized 
	{
		target[i] = toupper(target[i]);
	}
	if(head->data().get_course_number()==target)
	{
		node *tmp=head;
		head=head->link();
		delete tmp;
	}
	else
	{
		node *tmp, *previous;
		tmp=head->link();
		previous=head;
		while(tmp->data().get_course_number()!=target)
		{
			previous=tmp;
			tmp=tmp->link();
		}
		previous->set_link(tmp->link());
		delete tmp;
	}
}

double College::hours()
{
	node *tmp=head;
	double total=0;
	while(tmp!=NULL)
	{
		total+=tmp->data().get_hours();
		tmp=tmp->link();
	}
	return total;
}

double College::gpa()
{
	node *tmp=head;
	double total=0;
	while(tmp!=NULL)
	{
		total+=tmp->data().get_number_grade()*tmp->data().get_hours();
		tmp=tmp->link();
	}
	return total/hours();
}

void College::load(istream& ins)
{
	course c;
	while(ins>>c)
	{
		add(c);
	}
	if(ins.peek() == '\n') ins.ignore();
	{
		getline(ins, name);
	}	
}

void College::save(ostream& outs)
{
	display(outs);
}
