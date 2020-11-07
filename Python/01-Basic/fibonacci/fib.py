import click


def fib(n):
    if n == 0:
        return 0
    elif n == 1 or n == 2:
        return 1
    else:
        return fib(n - 1) + fib(n - 2)


@click.command()
@click.argument("num", type=click.INT)
def run_fib(num):
    print("fib = ", fib(num))


if __name__ == '__main__':
    run_fib()
