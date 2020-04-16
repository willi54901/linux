#define   MIN_WAIT_TASK_NUM 4
#define   DEFAULT_THREAD_NUM 4

#include <pthread.h>
/*任务*/
typedef struct
{
    void *(*function)(void *);
    void *arg;
} threadpool_task_t;
/*线程池管理*/
typedef struct
{
    pthread_mutex_t lock;           /* 锁住整个结构体 */
    pthread_mutex_t thread_counter; /* 用于使用忙线程数时的锁 */
    pthread_cond_t queue_not_full;  /* 条件变量，任务队列不为满 */
    pthread_cond_t queue_not_empty; /* 任务队列不为空 */

    pthread_t *threads;            /* 存放线程的tid,实际上就是管理了线 数组 */
    pthread_t admin_tid;           /* 管理者线程tid */
    threadpool_task_t *task_queue; /* 任务队列 */

    /*线程池信息*/
    int min_thr_num;       /* 线程池中最小线程数 */
    int max_thr_num;       /* 线程池中最大线程数 */
    int live_thr_num;      /* 线程池中存活的线程数 */
    int busy_thr_num;      /* 忙线程，正在工作的线程 */
    int wait_exit_thr_num; /* 需要销毁的线程数 */

    /*任务队列信息*/
    int queue_front; /* 队头 */
    int queue_rear;  /* 队尾 */
    int queue_size;

    /* 存在的任务数 */
    int queue_max_size; /* 队列能容纳的最大任务数 */
    /*线程池状态*/
    int shutdown; /* true为关闭 */
} threadpool_t;
 void *threadpool_thread(void *threadpool);
 int _is_thread_alive(pthread_t tid);
void *admin_thread(void *threadpool);
/**
 * 
 * 
 * 
 * 
 * 
 * */
class YAThread
{
public:
    YAThread();
    ~YAThread();

private:
    threadpool_t *pThreadPool;
 
    int threadpool_free(threadpool_t *pool);
   
public:
    int createFixedPools(int min_thr_num, int max_thr_num, int queue_max_size);
    int threadpool_destroy(threadpool_t *pool);
    int threadpool_add_task(void *(*function)(void *arg), void *arg);
};
