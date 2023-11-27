typedef struct move {
	int pos1;
	int pos2;
}move;
typedef struct element {
	move ruch;
	struct element* nastepny;
}element;
element* utworz(move ruch, element* head)
{
	if (head)
	{
		if (head->nastepny)
		{
			return utworz(ruch, head->nastepny);
		}
		else
		{
			head->nastepny = malloc(sizeof(element));
			*(head->nastepny) = (element){ .ruch = ruch,.nastepny = NULL };
			return head->nastepny;
		}
	}
	else
	{
		element* ptr = malloc(sizeof(element));
		*ptr = (element){ .ruch = ruch,.nastepny = NULL };
		return ptr;
	}
}
void zniszcz(element* head)
{
	if(head->nastepny)zniszcz(head->nastepny);
	free(head);
}
void showL(element* head)
{
	while(head!=NULL)
	{
		printf("z %d na %d\n",head->ruch.pos1,head->ruch.pos2);
		head=head->nastepny;
	}
}
