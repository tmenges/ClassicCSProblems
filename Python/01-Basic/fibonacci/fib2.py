import click


def fib2(n):
    if n == 0:
        return 0, 0
    elif n == 1:
        return 1, 0
    elif n == 2:
        return 1, 1
    else:
        m, p = fib(n - 1)
        return m + p, m


@click.command()
@click.argument("num", type=click.INT)
def run_fib(num):
    f, _ = fib2(num)
    print("fib = ", f)


if __name__ == '__main__':
    run_fib()
