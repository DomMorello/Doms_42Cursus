# Philosopher functions (42 school)

## pthread_create
> 새로운 스레드를 생성하는 함수

`#include <pthread.h>`

`int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
void *(*start_routine)(void *), void *arg);`

1. thread : 성공적으로 함수가 호출되면 이곳에 thread ID가 저장됩니다. 이 인자로 넘어온 값을 통해서 pthread_join과 같은 함수를 사용할 수 있습니다.
2. attr : 스레드의 특성을 정의합니다. 기본적으로 NULL을 지정합니다. 만약 스레드의 속성을 지정하려고 한다면 pthread_attr_init등의 함수로 초기화해야합니다.
3. start_routine : 어떤 로직을 할지 함수 포인터를 매개변수로 받습니다. 
4. arg : start_routine에 전달될 인자를 말합니다. start_routine에서 이 인자를 변환하여 사용합니다.

## pthread_detach
> 스레드를 분리합니다.<br>
> 이 함수를 실행해서 분리되어 독립적인 동작을 하는 대신에 스레드가 끝이나면 반드시 자원을 반환시켜야합니다. pthread_join함수를 사용해서 모든 스레드가 끝나기를 기다린 후에 프로그램이 종료되면 자원이 전부 반환이ㅏ 되지만 그렇지 않 은 경우 pthread_create만으로 스레드를 생성하면 루틴이 끝나서도 자원이 반환되지 않습니다. 그러한 문제점을 해결해주는 함수가 바로 pthread_detach입니다. 

`int pthread_detach(pthread_t thread);`
1. thread: 분리시킬 스레드.


## pthread_join
> 스레드의 종료를 기다리는 함수

`int pthread_join(pthread_t thread, void **value_ptr);`

1. thread : 우리가 join하려고 하는 thread를 명시해줍니다.
2. value_ptr : pthread_create에서 start_routine이 반환하는 반환값을 여기에 저장합니다. 

## pthread_mutex_init
> 뮤텍스를 생성하는 함수<br>
mutex 는 여러개의 쓰레드가 공유하는 데이타를 보호하기 위해서 사용되는 도구로써, 
보호하고자 하는 데이타를 다루는 코드영역을 단지 '한번에 하나의 쓰레드만' 실행가능 하도록 하는 방법으로 공유되는 데이타를 보호합니다. 
이러한 코드영역(하나의 쓰레드만 점유가능한)을 critical section 이라고 하며, mutex 관련 API 를 이용해서 관리할수 있습니다.

`int    pthread_mutex_init(pthread_mutex_t *mutex, conspthread_mutexattr_t *attr);`

1. mutex: 생성할 뮤텍스
2. attr: 뮤텍스 특성 설정 (fast, recursive, error checking 이 있는데 NULL일 경우 디폴트인 fast로 설정)
## pthread_mutex_destroy
> 뮤텍스에 할당된 자원을 반환하는 함수

`int pthread_mutex_destroy(pthread_mutex_*mutex);`

## pthread_mutex_lock
> 뮤텍스를 잠그는 함수

`int pthread_mutex_lock(pthread_mutex_t *mutex);`
## pthread_mutex_unlock
> 뮤텍스 잠금을 푸는 함수

`int    pthread_mutex_unlock(pthread_mutex_*mutex);`

## sem_open
> 세마포어를 초기화하고 생성한다.

> 세마포어는 공유자원의 개수를 갖고 있는 변수이다. 예를 들어 5개로 설정돼있으면 한 스레드나 프로세스가 세마포어를 통해 공유자원을 쓰게 되면 세마포어 내부에 저장된 공유자원의 개수를 1 감소시킨다. 이렇게 다른 스레드나 프로세스가 또 들어오면 1 감소되고 이 과정이 반복되면서 0이 되면 더이상 스레드나 프로세스가 공유자원을 사용할 수 없게 lock되는 것이다. 세마포어를 통해 공유자원을 쓰던 스레드나 프로세스가 세마포어를 나가면서 세마포어 내부에 저장된 공유자원의 개수가 1증가돼서 다른 스레드나 프로세스가 또 unlock돼서 들어올 수 있게 되는 원리이다.

`sem_t *    sem_open(const char *name, int oflag, ...);`
1. name: 서로 다르게 구분되는 세마포어의 이름
2. oflag: 세마포어 생성시 플래그. 아래 두가지 조합으로 사용 가능: O_CREAT, O_EXCL

## sem_close
> 이름있는 세마포어를 닫는다.

`int    sem_close(sem_t *sem);`
## sem_post
> 세마포어 잠금을 푼다.

`int   sem_post(sem_t *sem);`
## sem_wait
> 세마포어를 잠근다.

`int   sem_wait(sem_t *sem);`

## sem_unlink
> 이름 있는 세마포어를 제거한다.

`int    sem_unlink(const char *name);`

### reference
- (https://reakwon.tistory.com/56)
- (https://bitsoul.tistory.com/172)
- 공식 메뉴얼
