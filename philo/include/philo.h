/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:47:56 by ppaquet           #+#    #+#             */
/*   Updated: 2023/08/29 15:12:51 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <string.h>

// ---------------------------------------------------------------< MACROS >====
# ifndef INT32_MAX
#  define INT32_MAX 2147483647
# endif

# define MIN_ARG 5
# define MAX_ARG 6

# define FD_ERR 2
# define DEFAULT 0

# define MALLOC 1
# define CALLOC 0

// --- CONDITIONS ---
# define YES 1
# define NO 0
# define SUCCESS 0
# define FAILURE -1

// --- TIMING ---
# define S_MS 1000
# define US_MS 0.001
# define MS_US 1000
# define DELAY_MARGIN 0.8

// --- STATES ---
# define AVBL 1
# define UVBL -1
# define NO_EAT_LIMIT -1
# define ALIVE 1
# define DEAD 0
# define SATIATED 0

// --- COLORS ---
# define GRN_TXT "\x1b[1;32m"
# define YLW_TXT "\x1b[1;33m"
# define BLU_TXT "\x1b[1;34m"
# define RST_TXT "\x1b[0m"
# define RED_TXT "\x1b[1;31m"

// --- MESSAGES ---
# define TAKE_CS "has taken a \x1b[1;33mfork\x1b[0m"
# define EAT "is \x1b[1;32meating\x1b[0m"
# define THINK "is thinking"
# define SLEEP "is \x1b[1;34msleeping\x1b[0m"
# define DIE "\x1b[1;31mdied\x1b[0m"

// -----------------------------------------------------------< STRUCTURES >====
/**
 * @param state Availability of chopstick
 * @param cs_mutex Mutual exclusion for chopstick management
*/
typedef struct s_cstick
{
	int				state;
	pthread_mutex_t	cs_mutex;

}	t_cstick;

/**
 * @param tag Philosopher's identification number
 * @param thd_id Thread identification
 * @param t_t_die Philosopher's own TIME_TO_DIE
 * @param t_t_slp Philosopher's own TIME_TO_SLEEP
 * @param t_t_eat Philosopher's own TIME_TO_EAT
 * @param d_line Philosopher's own DEAD_LINE (Timestamp that marks its
 * possible death if not eating)
 * @param cs1 Pointer to FIRST chopstick ("or left fork")
 * @param cs2 Pointer to SECOND chopstick ("or right fork")
 * @param must_eat Remaining eating occurrences (depending on the 6th argument)
 * @param state Living state of the philosopher - <ALIVE> OR <DEAD>
 * @param env Pointer to the environment (data)
*/
typedef struct s_philosopher
{
	int					tag;
	pthread_t			thd_id;
	long long			t_t_die;
	long long			t_t_slp;
	long long			t_t_eat;
	long long			d_line;
	t_cstick			*cs1;
	t_cstick			*cs2;
	long long			must_eat;
	bool				state;
	struct s_philo_env	*env;
}	t_philosopher;

/**
 * @param ac Copy of the original <argc>
 * @param av Pointer to the original <argv>
 * @param philo_amt Total amount of philosophers
 * @param time_to_die Delay (in milliseconds) between <start eating>/<death> OR 
 * between <begin of simulation>/<death>
 * @param time_to_eat Time a philosopher takes to eat (needs 2 chopsticks -
 * "2 forks" - to eat)
 * @param time_to_sleep Time philosopher takes to sleep
 * @param must_eat_amt (Only if <argc> == 6) Amount of time each philosopher 
 * needs to eat (countdown)
 * @param death Pointer to the dead philosopher
 * @param death_mutex Mutual exclusion used for death management/verifications
 * @param print_mutex Mutual exclusion used for printing the simulation's 
 * timestamps, philosopher(s) tag(s) and action(s)
 * @param chopsticks Array of available chopsticks (equal to the number of 
 * philosophers)
 * @param csticks_mutex Mutual exclusion for chopsticks state management/
 * verifications
 * @param philo Array of all philosophers in the simulation
*/
typedef struct s_philo_env
{
	int				ac;
	char			**av;
	int				philo_amt;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat_amt;
	t_philosopher	*death;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	t_cstick		*chopsticks;
	pthread_mutex_t	csticks_mutex;
	t_philosopher	*philo;
}	t_philo_env;

// --------------------------------------------------------< NUMERIC UTILS >====

int				philo_num_lenght(int n);
int				philo_is_digit(const char c);
int				philo_is_whitespace(const char c);
long long		philo_ascii_to_num(char *n);
char			*philo_num_to_ascii(int n);

// ---------------------------------------------------------< STRING UTILS >====

int				philo_strlen(const char *s);
void			philo_putchar_fd(char c, int fd);
void			philo_putstr_fd(const char *s, int fd);
void			philo_putendl_fd(const char *s, int fd);
int				philo_strcmp(const char *s1, const char *s2);

// ----------------------------------------------------------< ENVIRONMENT >====

t_philo_env		*philo_env_init(void);
int				philo_env_mutexes_init(t_philo_env *env);
t_philo_env		*philo_env_pull(void);
int				philo_environment(int ac, char **av);

// --------------------------------------------------------------< PARSING >====

int				philo_min_max_argc_check(int argc);
int				philo_args_retain(t_philo_env *env, int ac, char **av);
int				philo_args_check(t_philo_env *env);
int				philo_args_parse(t_philo_env *env);

// ----------------------------------------------------< MEMORY ALLOCATION >====

int				philo_nullify(void *memory, unsigned long long n);
void			*philo_alloc(bool type, int n, int size);

// ----------------------------------------------------------< PHILOSOPHER >====
// --- THREADS ---

void			*philo_launching(void *arg);
int				philo_thread_init(t_philo_env *env);
int				philo_thread_join(t_philo_env *env);

// --- INITIALIZATION ---

int				philo_philosophers_fill_data(t_philo_env *env, t_philosopher \
					*philo, int i);
int				philo_philosophers_init(t_philo_env *env);
int				philo_chopsticks_init(t_philo_env *env);
int				philosophers(t_philo_env *env);

// -----------------------------------------------------------< TIME UTILS >====

long long		philo_fetch_time(void);
int				philo_long_usleep(t_philosopher *philo, long long delay);
void			philo_usleep(t_philosopher *philo, long long delay);

// --------------------------------------------------------------< ACTIONS >====

int				philo_takes_cs(t_philosopher *philo);
int				philo_returns_cs(t_philosopher *philo);
int				philo_eating(t_philosopher *philo);
int				philo_sleeping(t_philosopher *philo);
int				philo_thinking(t_philosopher *philo);

// -------------------------------------------------------< UTILS & CHECKS >====

void			philo_death_flagger(t_philosopher *philo);
int				philo_death_check(t_philosopher *philo);
int				philo_chopsticks_availability(t_philosopher *philo);
int				philo_before_eating(t_philosopher *philo);

// ----------------------------------------------------------------< PRINT >====
int				philo_err_msg(const char *msg, int fd);
int				philo_msg(t_philosopher *philo, char *message);

// --------------------------------------------------------< ERRORS & EXIT >====

t_philosopher	*philo_philosophers_free(t_philosopher **philo, int index);
void			philo_chopsticks_mutex_destroy(t_cstick **cs, int index, \
					int *status);
t_cstick		*philo_chopsticks_free(t_cstick **cs, int index, int *status);
int				philo_env_mutex_destroy(t_philo_env **env, int *status);
int				philo_env_free(t_philo_env **env);

#endif