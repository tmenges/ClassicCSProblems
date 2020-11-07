import click


def fib4(n):
    if n == 0:
        return 0, 0

    last_f = 0   # initially set to fib(0)
    next_f = 1   # initially set to fib(1)

    for _ in range(1, n):
        last_f, next_f = next_f, last_f + next_f

    return next_f


@click.command()
@click.argument("num", type=click.INT)
def run_fib(num):
    f = fib4(num)
    print("fib = ", f)


if __name__ == '__main__':
    run_fib()
