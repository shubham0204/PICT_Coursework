#include<iostream>
using namespace std;
class Node
{
	public:
		int data;
		Node*left,*right;
		int lthread,rthread;
		Node()
		{
			data=0;
			left=right=NULL;
			lthread=rthread=0;
		}
		Node(int a)
		{
			data=a;
			left=right=NULL;
			lthread=rthread=0;
		}
};
class TBT
{
	public:
		Node*root,*header;
		TBT()
		{
			root=NULL;
			header=NULL;
		}
		void create();
		void create1(int );
		void inorder();
		Node*insuc(Node*);
		Node*inpred(Node*);
		void preorder();
		void display()
		{
			cout<<"\nInorder : ";
			inorder();
			cout<<"\nPreorder : ";
			preorder();
		}
		Node* del(Node*,int);
	Node* case_a(Node*root,Node*pr,Node*pt) ;
		Node* case_b(Node*root,Node*pr,Node*pt); 
	Node* case_c(Node*root,Node*par,Node*ptr); 
};
int main()
{
	int ch,n;
	TBT T;
	Node*t;
	cout<<"****** Menu ******"<<"\n1.Create the threaded binary tree "
		<<"\n2.Display it"
		<<"\n3.Delete the node you want to delete";
		while(1)
		{
			cout<<"\n-----------------------------------";
			cout<<"\nEnter your choice : ";
			cin>>ch;
			switch(ch)
			{
				case 1: T.create();
						break;
				case 2:	cout<<"\nEnter the node to delete : ";
						cin>>n;
						t=T.del(T.root,n);
						T.root=t;
						T.display();
						break;
				case 3: T.display();
						break;
				default : cout<<"\nWrong choice ";					
			}
			if(ch>=4)
			{
				break;
			}
		}
}
void TBT::create()
{
	int n,x;
	cout<<"\nEnter the number of nodes : ";
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"Enter data = ";
		cin>>x;
		this->create1(x);
	}
}
void TBT::create1(int a)
{
	Node*ptr,*temp;
	if(root==NULL)
	{
		header=new Node(-99);
		header->right=header;
		root=new Node(a);
		root->lthread=0;
		root->rthread=0;
		root->left=header;
		root->right=header;
		header->left=root; 
		return;
	}
	else
	{
		ptr=root;
		temp=new Node(a);
		while(1)
		{
			if(ptr->data>a)
			{
				if(ptr->lthread!=0)
				{
					ptr=ptr->left;
				}
				else
				{
					temp->lthread=0;
					temp->rthread=0;
					temp->left=ptr->left;
					temp->right=ptr;
					ptr->lthread=1;
					ptr->left=temp;
					return;
				}
			}
			else
			{
				if(ptr->rthread!=0)
				{
					ptr=ptr->right;
				}
				else
				{
					temp->left=ptr;
					temp->right=ptr->right;
					temp->lthread=temp->rthread=0;
					ptr->right=temp;
					ptr->rthread=1;
					return;
				}
			}
		}	
	}
}
Node *TBT::insuc(Node*T)
{
	if(T->rthread==0)
	{
		return (T->right);
	}
	T=T->right;
	while(T->lthread==1)
	{
		T=T->left;
	}
	return T;
}
Node*TBT::inpred(Node*T)
{
	if(T->lthread==0)
	{
		return (T->left);
	}
	T=T->left;
	while(T->rthread==1)
	{
		T=T->right;
	}
	return T;
}
void TBT::inorder()
{
	if(root==NULL)
	{
		cout<<"empty tree";
		
	}
	Node*ptr=root;
	while(ptr->lthread==1)
	{
		ptr=ptr->left;
	}
	while(ptr!=header)
	{
		cout<<ptr->data<<" ";
		ptr=insuc(ptr);
	}
}
void TBT::preorder()
{
	if(root==NULL)
	{
		cout<<"\nEmpty tree";
		return;
	}
	Node*ptr=root;
	while(ptr!=header)
	{
		cout<<ptr->data<<" ";
		if(ptr->lthread==1)
		{
			ptr=ptr->left;
		}
		else if(ptr->rthread==1)
		{
			ptr=ptr->right;
		}
		else
		{
			while(ptr!=header&& ptr->rthread!=1)
			{
				ptr=ptr->right;
				
			}
			if(ptr!=header)
			{
					ptr=ptr->right;
			}
		
		}
	}
}
Node* TBT::del(Node*r,int k)
{
	Node*par,*ptr;
	int flag=0;
	ptr=root;
	par=header;
	while(ptr!=header)
	{
		if(k==ptr->data)
		{
			flag=1;
			break;
		}
		par=ptr;
		if(k<ptr->data)
		{
			if(ptr->lthread==1)
			{
				ptr=ptr->left;
			}
			else
			{
				break;
			}
		}
	}
	if(flag==0)
	{
		cout<<"\nkey not found ";
	}
	else if(ptr->lthread==1 && ptr->rthread==1)
	{
		root=case_c(root,par,ptr);
	}
	else if(ptr->lthread==1)
	{
		root=case_b(root,par,ptr);
	}
	else if(ptr->rthread==1)
	{
		root=case_b(root,par,ptr);
	}
	else
	{
		root=case_a(root,par,ptr);
	}
	return root;
}
Node* TBT::case_a(Node*root,Node*pr,Node*pt)  // if it is leaf node
{
	if(pr==NULL)
	{
		root=NULL;
	}
	else if(pt==pr->left)
	{
		pr->lthread=0;
		pr->left=pt->left;
	}
	else
	{
		pr->rthread=0;
		pr->right=pt->right;
	}
	delete pt;
	return root;
}
Node*TBT::case_b(Node*root,Node*pr,Node*pt)  //node to be deleted has only one child
{
	Node*child,*s,*p;
	if(pt->lthread==1)
	{
		child=pt->left;
	}
	else
		child=pt->right;
	if(pr==NULL)
	{
		root=child;
	}
	else if(pt=pr->left)
	{
		pr->left=child;
	}
	else
	{
		pr->right=child;
	}
	s=insuc(pt);
	p=inpred(pt);                 //inorder predecessor
	if(pt->lthread==1)
	{
		p->right=s;
	}
	else
	{
		if(pt->rthread==1)
		{
				s->left=p;
		}
	}
	delete pt;
	return root;
}
Node*TBT::case_c(Node*root,Node*par,Node*ptr)  //node to be deleted has two childs
{
	Node*succ,*parsucc;
	parsucc=ptr;
	succ=ptr->right;
	while(succ->left!=NULL)
	{
		parsucc=succ;
		succ=succ->left;
	}
	ptr->data=succ->data;
	if(succ->lthread==0 && succ->rthread==0)
	{
		root=case_a(root,parsucc,succ);
	}
	else
	{
		root=case_b(root,parsucc,succ);
	}
}





