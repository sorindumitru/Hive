#include <stdio.h>

#include <platform.h>
#include <node.h>
#include <timer.h>

struct timers_data {
	struct node node;
	struct timer *simple;
	struct timer *recursive;
};

void simple_callback(void *_)
{
	printf("SUCESS\n");
}

void recursive_callback(void *_)
{
	static int count = 0;

	printf("Timer called %d times\n", ++count);
}

void *timers_init(void)
{
	struct timers_data *data= plat_alloc(sizeof(*data));
	plat_memset(data, 0, sizeof(*data));

	data->simple = timer_new(simple_callback, 10);
	data->recursive = timer_new_recursive(recursive_callback, 5);

	timer_add(data->simple);
	timer_add(data->recursive);

	return data;
}

struct node *timers_getnode(void *priv)
{
	struct timers_data *data = priv;
	return &data->node;
}

void timers_exit(void *priv)
{
	struct timers_data *data = priv;

	timer_free(data->simple);
	timer_free(data->recursive);

	plat_free(data);
}

void timers_start(void *priv)
{
}

void timers_stop(void *priv)
{
}