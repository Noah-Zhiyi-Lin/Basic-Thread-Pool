/**
 * @author Noah Zhiyi Lin
 * @license MIT
 * @refernce C-Thread-Pool by Johan Hanssen Seferidis
 */

#ifndef _TPOOL_
#define _TPOOL_

// Add compability with C++
#ifdef __cplusplus
extern "C" {
#endif

// =======================Functions=============================

typedef struct thread_pool_t* tpool;// OOP-like

/**
 * @brief Initialize a thread pool
 * 
 * Initialize a thread pool by give the number of threads in the pool.
 * The function will not return until all threads have been initialized successfully.
 * 
 * @example
 * 
 * ...
 * tpool pool;// Declare a thread pool
 * pool = tpool_init(8);// Initialize it with 8 threads
 * ...
 * 
 * @param num_threads    number of threads in thread pool
 * 
 * @return tpool    created thread pool on success, NULL on error
 */

tpool tpool_init(int num_threads);

/**
 * @brief Add a job to the job queue
 * 
 * In multi-threads programming, we usually pack a function and its argument as a job.
 * You can add the job to the job queue to let a thread execute the function.
 * If you want to add a function with more than one arguments, the way to implement this
 * is to pass a pointer to a structure.
 * 
 * @example
 * 
 * int print_num(int num)
 * {
 *     printf("%d\n", num);
 * }
 * 
 * int main()
 * {
 *     ...
 *     int a = 10;
 *     tpool_add_job(pool, (void*)print_num, (void*)a);
 *     ...
 * }
 * 
 * @param tpool    thread pool the job added to
 * @param job_func    pointer to the function which you want to execute
 * @param arg    pointer to the argument of the function
 * 
 * @return 0 on suceess, -1 otherwise
 */
int tpool_add_job(tpool, void (*job_func)(void*), void* arg);

/**
 * @brief Wait for all jobs to finish
 * 
 * The calling thread will be blocked to wait all jobs -- both queued and running to finish.
 * Once the queue is empty and all jobs have been finished, the calling thread will continue.
 * 
 * @example
 * 
 * tpool pool = tpool_init(8);
 * ...
 * // Add a brunch of jobs
 * ...
 * tpool_wait(pool);
 * printf("All jobs have been finished\n");
 * ...
 * 
 * @param tpool    the thread pool to wait for
 * @return nothing
 */
void tpool_wait(tpool);

/**
 * @brief Block all threads immediately
 *
 * Block all threads no matter whether they are idle or running.
 * Threads will return their previous state once tpool_unblock() is called.
 * 
 * NOTICE: You can add jobs to the job queue when threads are blocked.
 * 
 * @example
 * 
 * tpool pool = tpool_init(8);
 * tpool_block(pool);
 * 
 * ...
 * // Add a brunch of jobs
 * ...
 * 
 * tpool_unblock(pool);// Threads will continue
 * 
 * @param tpool    the thread pool to be blocked
 * @return nothing
 */
void tpool_block(tpool);

/**
 * @brief Unblock all threads if they are blocked
 * 
 * @example
 * 
 * tpool pool = tpool_init(8);
 * tpool_block(pool); // Block
 * sleep(10);// Wait for 10 seconds
 * tpool_unblock;// Unblock
 * 
 * @param tpool    the thread pool to be unblocked
 * @return nothing
 */
void tpool_unblock(tpool);

/**
 * @brief Destroy the thread pool
 * 
 * Wait for all jobing threads to finish, then shutdown the thread pool and free up memory.
 * 
 * @example
 * 
 * tpool pool = tpool_init(8);
 * ...
 * // A series of operations
 * ...
 * tpool_destroy(pool);// Destroy the thread pool
 * 
 * @param tpool    the thread pool to destory
 * @return nothing
 */
void tpool_destroy(tpool);

/**
 * @brief Get number of working threads
 * 
 * Working threads are threads which are performing jobs(not idle).
 * 
 * @example
 * 
 * int main()
 * {
 *     tpool pool = tpool_init(8);
 *     ...
 *     // A series of operations
 *     ...
 *     printf("Number of working threads is %d\n", tpool_num_working_threads(pool));
 *     return 0;
 * }
 * 
 * @param tpool    the thread pool to get number of working threads
 * @return number of working therads
 */
int tpool_num_working_threads(tpool);

#ifdef __cplusplus
}
#endif

#endif // _TPOOL_