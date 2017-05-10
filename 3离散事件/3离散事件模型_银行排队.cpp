#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cassert>

// 2017_04_25 ��д

//  ��Ĵ����д���  �����˺ü���
#define SIZE_QUEUE  4   //�ͻ�����Ϊ  4
#define SIZE_INTERVAL_TIME  5  //���ڵ������û�Ϊ  5
#define SIZE_BUSINESS_TIME 30  //�û�����ʱ��/����ҵ����Ҫʱ��


struct event_t //�����¼�
{
    int occur_time;//�¼�����ʱ��
    size_t type; //�����¼�  -1 �Ƿ����¼�  ���ָô�������¼�
};

#define EVENT_TYPE_ARRIVED  -1

typedef event_t * event_ptr_t;

struct node_t
{
    event_t event_data;
    node_t * next;
};

typedef node_t * node_ptr_t;

static size_t g_list_node_log =0;

node_ptr_t list_node_alloc()
{
    ++g_list_node_log;
    return (node_ptr_t)malloc(sizeof(node_t));
}
void list_node_free(node_ptr_t * p)
{
    --g_list_node_log;
    free(*p);
    *p =NULL;
}

struct list_t
{
    node_ptr_t head;
    node_ptr_t tail;
    size_t size;
};

typedef list_t * list_ptr_t;

void list_init(list_ptr_t list)
{
    node_ptr_t x = list_node_alloc();
    x->next = NULL;

    list->head = x;
    list->tail = x;
    list->size = 0;
}

void list_insert(list_ptr_t list, event_ptr_t event_data, int(*pfn_compare_event)(event_ptr_t p1, event_ptr_t p2))
{
    node_ptr_t pre = list->head;
    node_ptr_t cur = pre->next; // һ������ NULL

    // �ȽϷ���ʱ��  ���뵽  pre cur ֮��
    while ( cur && pfn_compare_event(&(cur->event_data),event_data) <0 )
    {
        pre = cur;
        cur = cur->next;
    }

    node_ptr_t p = list_node_alloc();
    p->event_data = *event_data;
    p->next = NULL;
    pre->next = p;
    p->next  = cur;
    
    ++list->size;

    // ���ǲ嵽β����
    if (!cur)
    {
        list->tail = p;
    }
}

bool list_is_empty(list_ptr_t list)
{
    return list->size == 0;
}

void list_free(list_ptr_t  list)
{
    if (!list)
    {
        return ;
    }

    node_ptr_t head = (list)->head;

    node_ptr_t * x = &head;
    for (;*x;)
    {
        node_ptr_t p = (*x)->next;
        list_node_free(x);
        *x = p;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size =0;
}

// ���� head ����Ľ�㣬�������޳������� size �� 1
void list_delete_first_of(list_ptr_t list, node_ptr_t head, node_ptr_t * out_node)
{
    node_ptr_t p = head->next;

    if (p)
    {
        head->next = p->next;
        if (p->next == NULL)
        {
            list->tail = head;
        }
        --(list->size);
    }
    *out_node = p;
}

void list_next_event(list_ptr_t list, event_ptr_t out_event)
{
    node_ptr_t temp = NULL;
    list_delete_first_of(list,list->head,&temp);
    *out_event = temp->event_data;
    list_node_free(&temp);
}

struct queue_element_t
{
    int arrival_time;//����ʱ��
    int business_time;//������Ҫ��ʱ��
};
typedef queue_element_t * queue_element_ptr_t;

struct queue_node_t
{
    queue_element_t queue_data;
    queue_node_t * next;
};
typedef queue_node_t * queue_node_ptr_t;

static size_t g_link_queue_node_log =0;

queue_node_ptr_t queue_node_alloc()
{
    ++g_link_queue_node_log;
    return (queue_node_ptr_t)malloc(sizeof(queue_node_t));
}

void queue_node_free(queue_node_ptr_t * p)
{
    --g_link_queue_node_log;
    free(*p);
    *p=NULL;
}

struct link_queue_t
{
    queue_node_ptr_t front;
    queue_node_ptr_t rear;
    size_t size;
};

typedef link_queue_t * link_queue_ptr_t;

void link_queue_init(link_queue_ptr_t queue)
{
    queue_node_ptr_t p = queue_node_alloc();
    p->next = NULL;
    queue->front = p;
    queue->rear = p;
    queue->size = 0;
}

void link_queue_free(link_queue_ptr_t queue)
{
    queue_node_ptr_t head_ = queue->front;

    queue_node_ptr_t * head = &head_;

    for (;*head;)
    {
        queue_node_ptr_t p = (*head)->next;
        queue_node_free(head);
        *head = p;
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size=0;
}

bool link_queue_is_empty(link_queue_ptr_t queue)
{
    return (queue->front == queue->rear) && queue->front->next == NULL;
}

void link_queue_size(link_queue_ptr_t queue, size_t * out_size)
{
    size_t s = 0;
    queue_node_ptr_t p = queue->front->next;
    for (;p;)
    {
        ++s;
        p=p->next;
    }
    *out_size = s;
    assert(queue->size == s);
}

// ���в���β��
void link_queue_push(link_queue_ptr_t queue, queue_element_ptr_t queue_data)
{
    queue_node_ptr_t p = queue_node_alloc();
    p->queue_data = *queue_data;
    p->next = NULL;
    queue->rear->next = p;
    queue->rear = p;
    ++queue->size;
}

// ���д�ͷȡ
bool link_queue_pop(link_queue_ptr_t queue, queue_element_ptr_t out_data)
{
    if (!(queue && queue->front && queue->rear && queue->front != queue->rear))
    {
        return false;
    }

    queue_node_ptr_t  p = queue->front->next;
    if (p)
    {
        *out_data =  p->queue_data;
        queue->front->next = p->next;
        if (p == queue->rear) // û����Ч�����
        {
            queue->rear = queue->front;
        }
        --queue->size;
        queue_node_free(&p);
    }
    return false;

}

bool link_queue_peek(link_queue_ptr_t queue, queue_element_ptr_t out_data)
{
    if(link_queue_is_empty(queue)) return false;

    *out_data = queue->front->next->queue_data;
    return true;
}



int compare_event(event_ptr_t a,event_ptr_t b)
{
    return  (a->occur_time - b->occur_time);  //1  ���� -1 ������
}

void random(int* business_time,int* interval_time)
{
    //srand((unsigned)time(NULL));
    *business_time = rand()%SIZE_BUSINESS_TIME+1;
    *interval_time = rand()%SIZE_INTERVAL_TIME+1;
}

//��������4�������г�Ա���ٵĲ�����
void get_min_link_queue(link_queue_ptr_t queue_windows, size_t * out_min_size_index)
{
    size_t sizes[SIZE_QUEUE];

    for (size_t i=0;i<SIZE_QUEUE;++i)
    {
        size_t s = 0;
        link_queue_size(&queue_windows[i],&s);
        sizes[i] = s;
    }

    // �ҵ���С������̶���
    size_t m = sizes[0];
    size_t r_index = 0;

    for (size_t i=1;i<SIZE_QUEUE;++i)
    {
        if (sizes[i] < m)
        {
            m = sizes[i];
            r_index = i;
        }
    }

    *out_min_size_index = r_index;

}


int main()
{

    list_t list;// �¼�����
    memset(&list,0,sizeof(list));

    event_t event_current;//��ǰ�û�
    event_t event_next;//	�¸��û�

    

    link_queue_t queue_windows[SIZE_QUEUE]; // ���д��ڣ�ÿ�����ڶ��Ƕ���
    memset(queue_windows,0,sizeof(link_queue_t)*SIZE_QUEUE);

    int TotalTime = 0;  //�ۼƿͻ�����ʱ��
    int CustomNum = 0;  //�ͻ�����
    int CloseTime = 0;

    printf("Input CloseTime\n");
    //scanf_s("%d",&CloseTime);
    CloseTime =10;

    list_init(&list);



    //����һ�¼����� ʱ��Ϊ 0
    event_current.occur_time = 0;
    event_current.type = EVENT_TYPE_ARRIVED;// ����

    //���¼��������ǵ��¼�������
    list_insert(&list,&event_current,compare_event);

    //�����ǵ�4���������
    for (size_t i =0;i<SIZE_QUEUE;++i)
    {
        link_queue_init(&(queue_windows[i]));
    }


    list_ptr_t list_ptr = &list;
    
    for (;!list_is_empty(list_ptr);)
    {
        list_next_event(list_ptr,&event_current);

        // �ͻ�����
        if (event_current.type == EVENT_TYPE_ARRIVED)
        {

            ++CustomNum;


            // ������һ���û��ĵ���ʱ�䣬��ǰ�û���ҵ�����ʱ��
            int business_time = 0; //������Ҫ��ʱ��
            int interval_time = 0;//����ʱ��
            random(&business_time,&interval_time);     //   �ͻ�����ʱ��Ϳͻ���ͻ�֮��ļ��ʱ���������


            //����ʱ��Ҫ�����ʱ����бȽϣ�û���žͿ��Խ��ܰ�������ҵ���Ѿ����ܵ�ҵ����Ȼʱ�䳬������ʱ�䣬����ҲҪ�������
            if (event_current.occur_time + interval_time <CloseTime)   
            {
                //�����¼��������ǵ��¼�����
                event_next.occur_time = event_current.occur_time + interval_time;
                event_next.type = EVENT_TYPE_ARRIVED; //����
                list_insert(list_ptr,&event_next,compare_event);
            }	
            //���㳤����̵Ķ���
            size_t index=SIZE_QUEUE;
            get_min_link_queue(queue_windows,&index); //��ö��е����������û�����


            queue_element_t queue_data;
            queue_data.arrival_time = event_current.occur_time;
            queue_data.business_time = business_time;
            

            
            link_queue_push(&queue_windows[index],&queue_data);

            size_t l=0;
            link_queue_size(&queue_windows[index],&l);

            printf("�µ��û� ����ʱ��:%d,ҵ���ʱ:%d, ������ %d �����ô��ڹ��� %d ��(���������)\n",
                queue_data.arrival_time,queue_data.business_time,index,l);

            if (l==1) // Ϊʲô������ 1 �Ͳ�������û�������¼��أ� ��Ϊ����û����Ŷӣ������� 1 ˵�����ڰ���
            {
                // ��һ���û�������¼��ĵ���ʱ���Ǵ˴��û�����ʱ�� + ������ҵ���ʱ��
                event_next.occur_time = event_current.occur_time + business_time;
                event_next.type=index;
                list_insert(list_ptr,&event_next,compare_event);
            }
            else
            {
                int j =0;
            }

        }
        // �ͻ����������ϣ��뿪
        else
        {
            //�Ӷ�����ɾ�������û�������ʱ�����

            size_t index;
            queue_element_t custom_data;

            index = event_current.type;
            link_queue_pop(&queue_windows[index],&custom_data);

            size_t l = 0;
            link_queue_size(&queue_windows[index],&l);
            printf("�û��뿪���� %d ����ʱ��:%d,ҵ���ʱ:%d,�ô��ڹ��� %d ��(ȥ�������)\n",
                index,custom_data.arrival_time,custom_data.business_time,l);

            TotalTime += event_current.occur_time - custom_data.arrival_time;//????
           
            // �����������һ���û���������û���Ҫ��������¼�
            //����ö�����֮����û������뵽�¼�������
            if (!link_queue_is_empty(&queue_windows[index]))
            {
                link_queue_peek(&queue_windows[index],&custom_data);
                event_next.occur_time = event_current.occur_time+custom_data.business_time;
                event_next.type = index;
                list_insert(list_ptr,&event_next,compare_event);
            }
        }
    }

    printf("Custom Count:%d   %d Min    Average Time%d Min\n",CustomNum,TotalTime,TotalTime/CustomNum);
    
    list_free(&list);
    for (size_t i=0;i<SIZE_QUEUE;++i)
    {
        link_queue_free(&(queue_windows[i]));
    }

    if ( !(0 == g_list_node_log && 0 == g_link_queue_node_log))
    {
        printf("memory leak\n");
    }

    return 0;



}

// Input CloseTime
// 30
// Custom Count:17   250 Min    Average Time14 Min
// Press any key to continue




// Input CloseTime
// 10
// Custom Count:4   54 Min    Average Time13 Min
// Press any key to continue
