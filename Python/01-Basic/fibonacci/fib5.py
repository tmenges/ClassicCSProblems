import click


def fib5(n):
    yield 0          # special case
    if n > 0:
        yield 1      # special case

    last_f = 0       # initially set to fib(0)
    next_f = 1       # initially set to fib(1)

    for _ in range(1, n):
        last_f, next_f = next_f, last_f + next_f
        yield next_f   # main generation step


@click.command()
@click.argument("num", type=click.INT)
def run_fib(num):
    for i in fib5(num):
        print(i)


if __name__ == '__main__':
    run_fib()
