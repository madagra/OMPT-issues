#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>
#include <unistd.h>
#include <string.h>

#include <omp.h>
#include <ompt.h>

/************ TOOL ************/

static ompt_set_callback_t     ompt_set_callback_fn;
static ompt_get_thread_data_t  ompt_get_thread_data_fn;

/* Register start time for more human-readable timings */
static double start_time = 0;

#define register_callback_t(name, type)                              \
    do{                                                              \
        type f_##name = &my_##name;                                  \
        if (ompt_set_callback_fn(name, (ompt_callback_t)f_##name) == \
                    ompt_set_never)                                  \
            printf("0: Could not register callback '" #name "'\n");  \
    } while(0)
#define register_callback(name) register_callback_t(name, name##_t)

static void my_ompt_callback_idle(ompt_scope_endpoint_t state)
{
    ompt_data_t *thread_data = ompt_get_thread_data_fn();
    switch(state)
    {
        case(ompt_scope_begin):
            printf("[thread %p] idle start at %lf\n",thread_data,
                   omp_get_wtime() - start_time);
            break;
        case(ompt_scope_end):
            printf("[thread %p] idle end at %lf\n",thread_data,
                   omp_get_wtime() - start_time);
            break;
    }
}

static void my_ompt_callback_sync_region_wait(
            ompt_sync_region_kind_t kind,
            ompt_scope_endpoint_t state,
            ompt_data_t *parallel_data,
            ompt_data_t *task_data,
            const void *ret_addr)
{
    ompt_data_t *thread_data = ompt_get_thread_data_fn();
    switch(state)
    {
        case(ompt_scope_begin):
            printf("[thread %p] sync region start at %lf\n",thread_data,
                   omp_get_wtime() - start_time);
            break;
        case(ompt_scope_end):
            printf("[thread %p] sync region end at %lf\n",thread_data,
                   omp_get_wtime() - start_time);
            break;
    }
}

int ompt_initialize(
            ompt_function_lookup_t lookup,
            ompt_data_t* tool_data)
{

    /* registering OMPT API functions */
    ompt_set_callback_fn    = (ompt_set_callback_t)    lookup("ompt_set_callback");
    ompt_get_thread_data_fn = (ompt_get_thread_data_t) lookup("ompt_get_thread_data");

    /* registering thread event callabacks */
    register_callback_t(ompt_callback_sync_region_wait, ompt_callback_sync_region_t);
    register_callback(ompt_callback_idle);

    start_time = omp_get_wtime();
    /* success */
    return 1;
}

void ompt_finalize(ompt_data_t* tool_data)
{

}

ompt_start_tool_result_t* ompt_start_tool(
            unsigned int omp_version,
            const char *runtime_version)
{

    (void) omp_version;
    (void) runtime_version;

    static ompt_start_tool_result_t ompt_start_tool_result = {
        .initialize = &ompt_initialize,
        .finalize   = &ompt_finalize,
        .tool_data  = { .value = 0 }
    };
    return &ompt_start_tool_result;
}

/*********** DRIVER ***********/

int main() {

    #pragma omp parallel num_threads(4)
    {
        int tid = omp_get_thread_num();
        if (0 == tid) {
            printf("[region1] number of OpenMP threads: %d\n",omp_get_num_threads());
        }
        sleep(4);
    }

    /* Here we observe that sleep time goes into sync_region_wait instead of idle */
    sleep(6);

    #pragma omp parallel num_threads(4)
    {
        int tid = omp_get_thread_num();
        if (0 == tid) {
            printf("[region2] number of OpenMP threads: %d\n",omp_get_num_threads());
        }

        sleep(4);
    }

    /* Here we observe that sleep time goes into sync_region_wait instead of idle */
    sleep(6);

    return 0;
}
