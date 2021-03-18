# Philosopher (42 school)

## Subject
> In this project, you will learn the basics of threading a process and how to work on the same memory space. You will learn how to make threads. You will discover the mutex, semaphore and shared memory.<br>

> 이 프로젝트에서 프로세스를 스레딩 하는 방법과 같은 메모리 공간을 사용하는 방법에 대해 배우게 됩니다. 스레드를 만드는 방법을 배우고 mutex, semaphore와 공유메모리에 대해서 알게될 것입니다.

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
- Philosophers don’t speak with each other.
- Philosophers don’t know when another philosopher is about to die.
- Each time a philosopher has finished eating, he will drop his forks and start sleeping.
- When a philosopher is done sleeping, he will start thinking.
- The simulation stops when a philosopher dies.
- Each program should have the same options: number_of_philosophers time_to_die time_to_eat time_to_sleep (number_of_times_each_philosopher_must_eat)

    **number_of_philosophers**: is the number of philosophers and also the number of forks<br>
**time_to_die**: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies<br>
**time_to_eat**: is in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks.<br>
**time_to_sleep**: is in milliseconds and is the time the philosopher will spend sleeping.<br>
**number_of_times_each_philosopher_must_eat**: argument is optional, if all
philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the
simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.<br>
- Each philosopher should be given a number from 1 to ’number_of_philosophers’.
- Philosopher number 1 is next to philosopher number ’number_of_philosophers’. Any other philosopher with number N is seated between philosopher N - 1 and philosopher N + 1
- Any change of status of a philosopher must be written as follows (with X replaced with the philosopher number and timestamp_in_ms the current timestamp in milliseconds)

    *timestamp_in_ms* X has taken a fork<br>
*timestamp_in_ms* X is eating<br>
*timestamp_in_ms* X is sleeping<br>
*timestamp_in_ms* X is thinking<br>
*timestamp_in_ms* X died<br>
- The status printed should not be scrambled or intertwined with another philosopher’s status.
- You can’t have more than 10 ms between the death of a philosopher and when it will print its death.
- Again, philosophers should avoid to die!

<br>

이 프로젝트에는 공통의 기본 룰을 갖고 있는 세 개의 서로 다른 프로그램이 있습니다:
- 이 프로젝트는 C언어로 작성되었습니다. 42 학교 자체 코드 컨벤션을 지켜야 하며 메모리 누수, 크래시, 비정상적인 작동은 0점 처리됩니다.
- 다수의 철학자들이 둥그런 식탁에 앉아서 식사를 하거나(eating) 생각을 하거나(thinking) 잠을 잡니다(sleeping).
- 먹을 때는 생각하거나 잠을 자지 않고, 잘 때는 먹거나 생각하지 않고, 생각할 때는 먹거나 자지 않습니다.
- 철학자들은 식탁에 둥그렇게 앉아있고 식탁 가운데에는 스파게티가 들어있는 커다란 그릇이 놓여있습니다.
- 식탁에는 몇 개의 포크가 있습니다.
- 스파게티는 포크 하나로 접시에 옮겨담아 먹기 힘들기 때문에 철학자들은 양 손에 두 개의 포크를 들고 식사한다고 가정합니다.
- 철학자들은 굶어서는 안 됩니다.
- 모든 철학자는 스파게티를 먹어야 합니다.
- 철학자들은 서로 이야기 하지 않습니다.
- 철학자들은 다른 철학자가 언제 죽을지 모릅니다.
- 철학자가 먹기를 끝내면 포크를 놔두고 잠을 자기 시작합니다.
- 철학자가 잠을 다 잤으면 생각하기 시작합니다.
- 이 시뮬레이션은 한 명의 철학자라도 죽으면 멈춥니다.
- 각각의 프로그램은 같은 옵션이 있습니다: number_of_philosophers time_to_die time_to_eat time_to_sleep (number_of_times_each_philosopher_must_eat)

    **number_of_philosophers**: 철학자의 수와 포크의 개수<br>
**time_to_die**: 단위는 밀리세컨(1000분의 1초)입니다. 철학자가 마지막 식사를 한 시간 또는 시뮬레이션이 시작한 시간에서 ’time_to_die’ 시간이 지나도록 철학자가 먹기를 시작하지 않으면 그 철학자는 죽습니다.<br>
**time_to_eat**: 단위는 밀리세컨(1000분의 1초)입니다. 철학자가 먹는데 걸리는 시간. 이 시간 동안은 해당 철학자가 두 개의 포크를 갖고 있습니다.<br>
**time_to_sleep**: 단위는 밀리세컨(1000분의 1초)입니다. 철학자가 잠자는데 쓰는 시간.<br>
**number_of_times_each_philosopher_must_eat**: 이 옵션은 선택사항입니다. 만약에 모든 철학자가 최소한 ’number_of_times_each_philosopher_must_eat’ 번의 먹기를 하면 시뮬레이션은 멈춥니다. 이 옵션이 명시돼있지 않으면 시뮬레이션은 철학자가 죽었을 때만 멈춥니다.<br>

- 각각의 철학자는 고유의 번호를 갖는데 1 ~ ’number_of_philosophers’ 까지 중 한 번호를 갖습니다.
- 철학자 번호 1은 철학자 번호 ’number_of_philosophers’ 옆에 위치합니다. 다른 모든 철학자들도 본인의 철학자 번호가 N이라면 N - 1 과 N + 1 사이에 위치합니다.
- 철학자의 상태 변화는 아래와 같이 출력돼야 합니다. (아래의 X 는 철학자 번호를 말하고 timestamp_in_ms 는 현재 시간(밀리세컨)을 말합니다.)

    *timestamp_in_ms* X has taken a fork<br>
*timestamp_in_ms* X is eating<br>
*timestamp_in_ms* X is sleeping<br>
*timestamp_in_ms* X is thinking<br>
*timestamp_in_ms* X died<br>
- 위의 상태 메세지는 다른 철학자의 상태 메세지와 뭉개지거나 겹쳐서 출력되면 안 됩니다.
- 철학자가 죽고 나서 철학자의 죽은 상태 메세지를 출력하는데 까지 걸리는 시간은 10밀리세컨이상이 되면 안 됩니다.
- 다시 한 번 말하지만 철학자는 죽음을 피해야 합니다.
---
### philo_one
- **Program name(프로그램 이름)**: philo_one
- **Turn in files(제출할 파일)**: philo_one/
- **Makefile**: Yes
- **Arguments(인자)**: number_of_philosophers, time_to_die, time_to_eat,
time_to_sleep [number_of_times_each_philosopher_must_eat]
- **External functs(허용되는 외부 함수)**:
```
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
```
- **Libft authorized(libft 라이브러리 사용가능 여부)**: No
- **Description(설명)**: philosopher with threads and mutex(철학자는 스레드이고 mutex를 이용한다)
<br>

In this version the non common rules will be:

- One fork between each philosopher, therefore there will be a fork at the right and
at the left of each philosopher.
- To avoid philosophers duplicating forks, you should protect the forks state with a
mutex for each of them.
- Each philosopher should be a thread.
<br><br>

이 프로그램에서 지켜야 할 규칙은 다음과 같습니다:

- 각각의 철학자들 사이에 포크가 놓여 있기 때문에, 포크는 모든 철학자의 왼 편과 오른 편에 놓여져 있습니다.
- 철학자가 동시에 포크를 사용하는 것을 방지하기 위해 모든 각각의 포크 상태를 mutex를 이용해서 보호해야 합니다.
- 모든 철학자들은 각각 스레드여야 합니다.

---
### philo_two
- **Program name(프로그램 이름)**: philo_two
- **Turn in files(제출할 파일)**: philo_two/
- **Makefile**: Yes
- **Arguments(인자)**: number_of_philosophers, time_to_die, time_to_eat,
time_to_sleep [number_of_times_each_philosopher_must_eat]
- **External functs(허용되는 외부 함수)**:
```
memset, printf, malloc, free, write, usleep,
gettimeofday, pthread_create, pthread_detach,
pthread_join, sem_open, sem_close, sem_post,
sem_wait, sem_unlink
```
- **Libft authorized(libft 라이브러리 사용가능 여부)**: No
- **Description(설명)**: philosopher with threads and semaphore(철학자는 스레드이고 semaphore를 이용한다)
<br>

In this version the non common rules will be:

- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented by
a semaphore.
- Each philosopher should be a thread.

<br>

이 프로그램에서 지켜야 할 규칙은 다음과 같습니다:

- 모든 포크는 식탁의 가운데에 위치해있습니다.
- 포크들은 메모리에 포크 상태를 저장하지 않고 사용 가능한 포크의 개수는 semaphore로 나타납니다.
- 모든 철학자들은 각각 스레드여야 합니다.
---
### philo_three
- **Program name(프로그램 이름)**: philo_three
- **Turn in files(제출할 파일)**: philo_three/
- **Makefile**: Yes
- **Arguments(인자)**: number_of_philosophers, time_to_die, time_to_eat,
time_to_sleep [number_of_times_each_philosopher_must_eat]
- **External functs(허용되는 외부 함수)**:
```
memset, printf, malloc, free, write, fork, kill,
exit, pthread_create, pthread_detach, pthread_join,
usleep, gettimeofday, waitpid, sem_open, sem_close,
sem_post, sem_wait, sem_unlink
```
- **Libft authorized(libft 라이브러리 사용가능 여부)**: No
- **Description(설명)**: philosopher with processes and semaphore
(철학자는 프로세스이고 semaphore를 이용한다)
<br>

In this version the non common rules will be:

- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented by
a semaphore.
- Each philosopher should be a process and the main process should not be a philosopher.

<br>

이 프로그램에서 지켜야 할 규칙은 다음과 같습니다:

- 모든 포크는 식탁의 가운데에 위치해있습니다.
- 포크들은 메모리에 포크 상태를 저장하지 않고 사용 가능한 포크의 개수는 semaphore로 나타납니다.
- 모든 철학자들은 각각 프로세스여야 하고 메인 프로세스는 철학자가 아니어야 합니다.
---
#### Contact: zuzudnf@gmail.com