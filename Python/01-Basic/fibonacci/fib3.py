import click
from functools import lru_cache


@lru_cache(maxsize=None)
def fib3(n):
    if n == 0:
        return 0
    elif n == 1 or n == 2:
        return 1
    else:
        return fib3(n - 1) + fib3(n - 2)


@click.command()
@click.argument("num", type=click.INT)
def run_fib(num):
    print("fib = ", fib3(num))


if __name__ == '__main__':
    run_fib()
