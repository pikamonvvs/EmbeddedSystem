#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

#define GOLDEN_RATIO_PRIME_32 0x9e370001UL
typedef unsigned int u32;
#define PAGE_MAX  (40)

struct page
{
	int pfn;
	int data;
	struct hlist_node hnode;
	struct list_head  list;
};

void page_init( struct page *pages )
{
	int i;
	for(i=0; i<PAGE_MAX; i++ )
	{
		pages[i].pfn = i;
		pages[i].data = i+1000;
	}
}


static inline u32 hash_32(u32 val, unsigned int bits)
{
	/* On some cpus multiply is faster, on others gcc will do shifts */
	u32 hash = val * GOLDEN_RATIO_PRIME_32;

	/* High bits are more random, so use them. */
	return hash >> (32 - bits);
}

#define hash_long(val, bits) hash_32(val, bits)

#define page_hash(pfn)	\
	hash_long((unsigned long)pfn, 3)

void display( struct hlist_head *heads, struct list_head *head )
{
	int i,j;
	struct hlist_node *h_temp;
	struct list_head  *l_temp;
	struct page *page;
	printf("[HASH TABLE]\n");
	for(i=0; i<8; i++ )
	{
		printf("[%d]", i );
		for( h_temp = heads[i].first; h_temp != 0; h_temp = h_temp->next ) 
		{
			page = list_entry( h_temp, struct page, hnode );
			printf("<->[%2d]", page->pfn);
		}
		printf("\n");
	}
	printf("\n\n");
	printf("[LRU LIST]\n");
	printf("[lru]");
	for( j=0,l_temp = head->next; l_temp != head; l_temp = l_temp->next, j++ ) 
	{
		page = list_entry( l_temp, struct page, list );
		printf("<->[%2d]", page->pfn);
		if( (j+1)%10 == 0 )
			printf("\n");
	}
	printf("\n");
}

struct page *hash_search( struct hlist_head *heads, int pfn )
{
	struct page *page;
	struct hlist_node *h_temp;
	for( h_temp = heads[page_hash(pfn)].first; h_temp != 0; h_temp = h_temp->next ) 
	{
		page = list_entry( h_temp, struct page, hnode );
		if( pfn == page->pfn )
			break;
	}
	if( h_temp == 0 )
		page = 0;
	return page;
}

int main()
{
	srand( time(0) );
	struct list_head head = {&head,&head};
	struct hlist_head heads[8] = {0,};
	struct page pages[PAGE_MAX];
	struct page *page;
	int pfn, page_count=0;
	page_init( pages );
	system("clear");
	display(heads, &head);
	getchar();
	while(1)
	{
		system("clear");
		pfn = rand() % PAGE_MAX; 
		printf("pfn = %d 접근\n", pfn);
		page = hash_search( heads, pfn );
	
		if( page == 0 )
		{
			if( page_count < 20 )
			{
				page_count++;
			}
			else
			{
				struct page *temp;
				temp = list_entry( head.prev, struct page, list );
				list_del( head.prev  );
				hlist_del(&temp->hnode);
				printf("page 꽉참 , pfn=%d 퇴출\n", temp->pfn ); 
			}
			hlist_add_head(&pages[pfn].hnode, &heads[page_hash(pfn)] );
			list_add( &pages[pfn].list, &head );
			printf("새로운 page, 해쉬에 추가, 현재 page 수 = %d\n" , page_count);
			display(heads, &head);
		}
		else
		{
			list_move( &page->list, &head );
			printf("기존 페이지 접근, data=%d\n", page->data  );
			display(heads, &head);
		}
		getchar();
	}
	return 0;
}
