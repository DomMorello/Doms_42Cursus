# Philosopher (42 school)

## Subject
> In this project, you will learn the basics of threading a process and how to work on the same memory space. You will learn how to make threads. You will discover the mutex, semaphore and shared memory.<br>

> �� ������Ʈ���� ���μ����� ������ �ϴ� ����� ���� �޸� ������ ����ϴ� ����� ���� ���� �˴ϴ�. �����带 ����� ����� ���� mutex, semaphore�� �����޸𸮿� ���ؼ� �˰Ե� ���Դϴ�.

## Compile
- `git clone https://github.com/DomMorello/philosophers.git`
- `cd philosohper`
- `cd philo_one`    // or philo_tow or philo_three
- `make`
- `./philo_one 4 410 200 200 6`     // or ./philo_tow or ./philo_three

## Requirements
There are 3 different programs but they will have the same basic rules:
- This project is coded in C, following the Norm(42 school code convention). Any leak, crash, undefined behavior or norm error means 0 to the project.
- A number of philosophers are sitting at a round table doing one of three things:eating, thinking or sleeping.
- While eating, they are not thinking or sleeping, while sleeping, they are not eating or thinking and of course, while thinking, they are not eating or sleeping.
- The philosophers sit at a circular table with a large bowl of spaghetti in the center.
- There are some forks on the table.
- As spaghetti is difficult to serve and eat with a single fork, it is assumed that a philosopher must eat with two forks, one for each hand.
- The philosophers must never be starving.
- Every philosopher needs to eat.
- Philosophers don��t speak with each other.
- Philosophers don��t know when another philosopher is about to die.
- Each time a philosopher has finished eating, he will drop his forks and start sleeping.
- When a philosopher is done sleeping, he will start thinking.
- The simulation stops when a philosopher dies.
- Each program should have the same options: number_of_philosophers time_to_die time_to_eat time_to_sleep (number_of_times_each_philosopher_must_eat)

    **number_of_philosophers**: is the number of philosophers and also the number of forks<br>
**time_to_die**: is in milliseconds, if a philosopher doesn��t start eating ��time_to_die�� milliseconds after starting his last meal or the beginning of the simulation, it dies<br>
**time_to_eat**: is in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks.<br>
**time_to_sleep**: is in milliseconds and is the time the philosopher will spend sleeping.<br>
**number_of_times_each_philosopher_must_eat**: argument is optional, if all
philosophers eat at least ��number_of_times_each_philosopher_must_eat�� the
simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.<br>
- Each philosopher should be given a number from 1 to ��number_of_philosophers��.
- Philosopher number 1 is next to philosopher number ��number_of_philosophers��. Any other philosopher with number N is seated between philosopher N - 1 and philosopher N + 1
- Any change of status of a philosopher must be written as follows (with X replaced with the philosopher number and timestamp_in_ms the current timestamp in milliseconds)

    *timestamp_in_ms* X has taken a fork<br>
*timestamp_in_ms* X is eating<br>
*timestamp_in_ms* X is sleeping<br>
*timestamp_in_ms* X is thinking<br>
*timestamp_in_ms* X died<br>
- The status printed should not be scrambled or intertwined with another philosopher��s status.
- You can��t have more than 10 ms between the death of a philosopher and when it will print its death.
- Again, philosophers should avoid to die!

<br>

�� ������Ʈ���� ������ �⺻ ���� ���� �ִ� �� ���� ���� �ٸ� ���α׷��� �ֽ��ϴ�:
- �� ������Ʈ�� C���� �ۼ��Ǿ����ϴ�. 42 �б� ��ü �ڵ� �������� ���Ѿ� �ϸ� �޸� ����, ũ����, ���������� �۵��� 0�� ó���˴ϴ�.
- �ټ��� ö���ڵ��� �ձ׷� ��Ź�� �ɾƼ� �Ļ縦 �ϰų�(eating) ������ �ϰų�(thinking) ���� ��ϴ�(sleeping).
- ���� ���� �����ϰų� ���� ���� �ʰ�, �� ���� �԰ų� �������� �ʰ�, ������ ���� �԰ų� ���� �ʽ��ϴ�.
- ö���ڵ��� ��Ź�� �ձ׷��� �ɾ��ְ� ��Ź ������� ���İ�Ƽ�� ����ִ� Ŀ�ٶ� �׸��� �����ֽ��ϴ�.
- ��Ź���� �� ���� ��ũ�� �ֽ��ϴ�.
- ���İ�Ƽ�� ��ũ �ϳ��� ���ÿ� �Űܴ�� �Ա� ����� ������ ö���ڵ��� �� �տ� �� ���� ��ũ�� ��� �Ļ��Ѵٰ� �����մϴ�.
- ö���ڵ��� ����� �� �˴ϴ�.
- ��� ö���ڴ� ���İ�Ƽ�� �Ծ�� �մϴ�.
- ö���ڵ��� ���� �̾߱� ���� �ʽ��ϴ�.
- ö���ڵ��� �ٸ� ö���ڰ� ���� ������ �𸨴ϴ�.
- ö���ڰ� �Ա⸦ ������ ��ũ�� ���ΰ� ���� �ڱ� �����մϴ�.
- ö���ڰ� ���� �� ������ �����ϱ� �����մϴ�.
- �� �ùķ��̼��� �� ���� ö���ڶ� ������ ����ϴ�.
- ������ ���α׷��� ���� �ɼ��� �ֽ��ϴ�: number_of_philosophers time_to_die time_to_eat time_to_sleep (number_of_times_each_philosopher_must_eat)

    **number_of_philosophers**: ö������ ���� ��ũ�� ����<br>
**time_to_die**: ������ �и�����(1000���� 1��)�Դϴ�. ö���ڰ� ������ �Ļ縦 �� �ð� �Ǵ� �ùķ��̼��� ������ �ð����� ��time_to_die�� �ð��� �������� ö���ڰ� �Ա⸦ �������� ������ �� ö���ڴ� �׽��ϴ�.<br>
**time_to_eat**: ������ �и�����(1000���� 1��)�Դϴ�. ö���ڰ� �Դµ� �ɸ��� �ð�. �� �ð� ������ �ش� ö���ڰ� �� ���� ��ũ�� ���� �ֽ��ϴ�.<br>
**time_to_sleep**: ������ �и�����(1000���� 1��)�Դϴ�. ö���ڰ� ���ڴµ� ���� �ð�.<br>
**number_of_times_each_philosopher_must_eat**: �� �ɼ��� ���û����Դϴ�. ���࿡ ��� ö���ڰ� �ּ��� ��number_of_times_each_philosopher_must_eat�� ���� �Ա⸦ �ϸ� �ùķ��̼��� ����ϴ�. �� �ɼ��� ��õ����� ������ �ùķ��̼��� ö���ڰ� �׾��� ���� ����ϴ�.<br>

- ������ ö���ڴ� ������ ��ȣ�� ���µ� 1 ~ ��number_of_philosophers�� ���� �� �� ��ȣ�� �����ϴ�.
- ö���� ��ȣ 1�� ö���� ��ȣ ��number_of_philosophers�� ���� ��ġ�մϴ�. �ٸ� ��� ö���ڵ鵵 ������ ö���� ��ȣ�� N�̶�� N - 1 �� N + 1 ���̿� ��ġ�մϴ�.
- ö������ ���� ��ȭ�� �Ʒ��� ���� ��µž� �մϴ�. (�Ʒ��� X �� ö���� ��ȣ�� ���ϰ� timestamp_in_ms �� ���� �ð�(�и�����)�� ���մϴ�.)

    *timestamp_in_ms* X has taken a fork<br>
*timestamp_in_ms* X is eating<br>
*timestamp_in_ms* X is sleeping<br>
*timestamp_in_ms* X is thinking<br>
*timestamp_in_ms* X died<br>
- ���� ���� �޼����� �ٸ� ö������ ���� �޼����� �������ų� ���ļ� ��µǸ� �� �˴ϴ�.
- ö���ڰ� �װ� ���� ö������ ���� ���� �޼����� ����ϴµ� ���� �ɸ��� �ð��� 10�и������̻��� �Ǹ� �� �˴ϴ�.
- �ٽ� �� �� �������� ö���ڴ� ������ ���ؾ� �մϴ�.
---
### philo_one
- **Program name(���α׷� �̸�)**: philo_one
- **Turn in files(������ ����)**: philo_one/
- **Makefile**: Yes
- **Arguments(����)**: number_of_philosophers, time_to_die, time_to_eat,
time_to_sleep [number_of_times_each_philosopher_must_eat]
- **External functs(���Ǵ� �ܺ� �Լ�)**:
```
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
```
- **Libft authorized(libft ���̺귯�� ��밡�� ����)**: No
- **Description(����)**: philosopher with threads and mutex(ö���ڴ� �������̰� mutex�� �̿��Ѵ�)
<br>

In this version the non common rules will be:

- One fork between each philosopher, therefore there will be a fork at the right and
at the left of each philosopher.
- To avoid philosophers duplicating forks, you should protect the forks state with a
mutex for each of them.
- Each philosopher should be a thread.
<br><br>

�� ���α׷����� ���Ѿ� �� ��Ģ�� ������ �����ϴ�:

- ������ ö���ڵ� ���̿� ��ũ�� ���� �ֱ� ������, ��ũ�� ��� ö������ �� ��� ���� �� ������ �ֽ��ϴ�.
- ö���ڰ� ���ÿ� ��ũ�� ����ϴ� ���� �����ϱ� ���� ��� ������ ��ũ ���¸� mutex�� �̿��ؼ� ��ȣ�ؾ� �մϴ�.
- ��� ö���ڵ��� ���� �����忩�� �մϴ�.

---
### philo_two
- **Program name(���α׷� �̸�)**: philo_two
- **Turn in files(������ ����)**: philo_two/
- **Makefile**: Yes
- **Arguments(����)**: number_of_philosophers, time_to_die, time_to_eat,
time_to_sleep [number_of_times_each_philosopher_must_eat]
- **External functs(���Ǵ� �ܺ� �Լ�)**:
```
memset, printf, malloc, free, write, usleep,
gettimeofday, pthread_create, pthread_detach,
pthread_join, sem_open, sem_close, sem_post,
sem_wait, sem_unlink
```
- **Libft authorized(libft ���̺귯�� ��밡�� ����)**: No
- **Description(����)**: philosopher with threads and semaphore(ö���ڴ� �������̰� semaphore�� �̿��Ѵ�)
<br>

In this version the non common rules will be:

- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented by
a semaphore.
- Each philosopher should be a thread.

<br>

�� ���α׷����� ���Ѿ� �� ��Ģ�� ������ �����ϴ�:

- ��� ��ũ�� ��Ź�� ����� ��ġ���ֽ��ϴ�.
- ��ũ���� �޸𸮿� ��ũ ���¸� �������� �ʰ� ��� ������ ��ũ�� ������ semaphore�� ��Ÿ���ϴ�.
- ��� ö���ڵ��� ���� �����忩�� �մϴ�.
---
### philo_three
- **Program name(���α׷� �̸�)**: philo_three
- **Turn in files(������ ����)**: philo_three/
- **Makefile**: Yes
- **Arguments(����)**: number_of_philosophers, time_to_die, time_to_eat,
time_to_sleep [number_of_times_each_philosopher_must_eat]
- **External functs(���Ǵ� �ܺ� �Լ�)**:
```
memset, printf, malloc, free, write, fork, kill,
exit, pthread_create, pthread_detach, pthread_join,
usleep, gettimeofday, waitpid, sem_open, sem_close,
sem_post, sem_wait, sem_unlink
```
- **Libft authorized(libft ���̺귯�� ��밡�� ����)**: No
- **Description(����)**: philosopher with processes and semaphore
(ö���ڴ� ���μ����̰� semaphore�� �̿��Ѵ�)
<br>

In this version the non common rules will be:

- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented by
a semaphore.
- Each philosopher should be a process and the main process should not be a philosopher.

<br>

�� ���α׷����� ���Ѿ� �� ��Ģ�� ������ �����ϴ�:

- ��� ��ũ�� ��Ź�� ����� ��ġ���ֽ��ϴ�.
- ��ũ���� �޸𸮿� ��ũ ���¸� �������� �ʰ� ��� ������ ��ũ�� ������ semaphore�� ��Ÿ���ϴ�.
- ��� ö���ڵ��� ���� ���μ������� �ϰ� ���� ���μ����� ö���ڰ� �ƴϾ�� �մϴ�.
---
#### Contact: zuzudnf@gmail.com