#include<stdio.h>
#include<stdlib.h>

struct tnode
{
	int data;
	struct tnode *left;
	struct tnode *right;
}*root=NULL;

struct snode
{
	struct tnode *t;
	struct snode *next;
};

void inorder(struct tnode * );
void delete(struct tnode ** ,int );
void push(struct snode ** ,struct tnode * );
struct tnode * pop(struct snode ** );
void height(struct tnode * );

int main()
{
	while(1)
	{	
		int choice,n,m;
		printf("1.insert\n2.delete\n3.display\n4.height\n5.exit\n");
		printf("enter choice\n");
		scanf("%d",&choice);
		switch(choice)
		{	
			case 1:
				printf("enter element : ");
				scanf("%d",&n);
				struct tnode *new=(struct tnode *)malloc(sizeof(struct tnode));
				new->data=n;
				new->left=NULL;
				new->right=NULL;
				if(root==NULL)
				{
					root=new;
				}
				else
				{
					struct tnode *temp=root,*p=root;
					while(temp!=NULL)
					{
						if(n>(temp->data))
						{
							p=temp;
							//printf("greater\n");
							temp=temp->right;
						}
						else if(n<(temp->data))
						{
							p=temp;
							temp=temp->left;
						}
						/*else
						{	
							if(n>(p->data))
							{
								p->right=new;
								printf("right\n");
							}
							else if(n<(p->data))
								p->left=new;
							else 
								printf("duplicate value\n");
							break;					
						}*/
					}
					if(n>p->data)
						p->right=new;
					else if(n<p->data)
						p->left=new;
					else
						printf("duplicate value\n");
				}
				break;
			
			case 2:
				printf("enter element to be deleted : ");
				scanf("%d",&m);
				delete(&root,m);
				break;
			
			case 3:
				inorder(root);
				break;
			case 4:
				height(root);
				break;
			case 5:
				exit(0);
			
		}	
	}
		return 0;
}

void height(struct tnode *root)
{
	int h1=0,h2=0;
	struct tnode *ptr=root;
	while(ptr!=NULL)
	{
		h1++;
		if(ptr->left!=NULL)
			ptr=ptr->left;
		else
			ptr=ptr->right;
	}
	ptr=root;
	while(ptr!=NULL)
	{
		h2++;
		if(ptr->right!=NULL)
			ptr=ptr->right;
		else
			ptr=ptr->left;
	}

	if(h1>h2)
		printf("height : %d\n",h1);
	else
		printf("height : %d\n",h2);
	
}

void inorder(struct tnode *root)
{	
	struct snode *s=NULL;
	struct tnode *current=root;
	if(current==NULL)
	{
		printf("tree empty\n");
		return;
	}
	while(1)
	{
		if(current!=NULL)
		{
			push(&s,current);
			current=current->left;
		}
		else
		{
			if(s!=NULL)
			{			
				current=pop(&s);
				printf("%d\t",current->data);
				current=current->right;
			}
			else
				break;
		}

	}
	printf("\n");

}

void push(struct snode **top,struct tnode *ptr)
{
	struct snode *new=(struct snode*)malloc(sizeof(struct snode));
	new->t=ptr;
	if(*top==NULL)
	{
		new->next=NULL;
		*top=new;
	}
	else
	{
		new->next=*top;
		*top=new;
	}
}

struct tnode * pop(struct snode **top)
{
	struct tnode *cur;
	struct snode *temp=*top;
	cur=(*top)->t;
	*top=(*top)->next;
	free(temp);
	return cur;
}

void delete(struct tnode **root,int m)
{
	struct tnode *ptr=*root,*parent=*root;
	int flag=0;
	while(1)
	{
		if(m>ptr->data)
		{
			parent=ptr;
			ptr=ptr->right;
		}
		else if(m<ptr->data)
		{
			parent=ptr;
			ptr=ptr->left;
		}
		else
		{
			flag=1;	
			if(ptr->left==NULL && ptr->right==NULL)
			{
				printf("deleting leaf node\n");
				if(parent->left==ptr)
					parent->left=NULL;
				else if(parent->right==ptr)
					parent->right=NULL;
				else
				{
					*root=NULL;
				}
				free(ptr);
				break;
			}
			else if(ptr->left==NULL || ptr->right==NULL)
			{
				struct tnode *temp;
				printf("deleting a node with one child\n");
				if(ptr->left!=NULL)
				{
					temp=ptr->left;
					ptr->data=temp->data;
					ptr->left=temp->left;
					ptr->right=temp->right;
				}
				else if(ptr->right!=NULL)
				{
					temp=ptr->right;
					ptr->data=temp->data;
					ptr->right=temp->right;
					ptr->left=temp->left;
				}
				free(temp);
				break;

			}
			else
			{
				int flag=0;
				struct tnode *temp=ptr,*temp2=temp;
				printf("deleting a node with two children\n");
				temp=temp->right;
				while(temp->left!=NULL)
				{
					flag=1;
					temp2=temp;
					temp=temp->left;
				}
				ptr->data=temp->data;
				ptr->right=temp->right;
				if(ptr==parent)
					ptr->right=NULL;
				else if(flag==0)
				{
					ptr->right=NULL;
					temp2->left==NULL;
				}
				free(temp);
				break;
			}
		}	
	
	}
	if(flag==0)
		printf("element not in tree\n");

}
