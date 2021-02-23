#include "./philo_one.h"

int main(int argc, char const *argv[])
{


	// init strcuture(arg, philo)
    // 5개 스레드(철학자)를 만들고
    // 5개 포크(뮤텍스)를 만든다
    // 각자의 스레드는 같은 함수를 실행한다
    // 포크를 쥘 때 좌우가 먹고 있는지를 검사한다
    // 좌우가 안 먹고 있다면 먹기 시작한다
    // 해당 포크에 대해서만 뮤텍스를 락한다
    // 그러면 인접한 철학자는 대기하고 있겠지

    return 0;
}
