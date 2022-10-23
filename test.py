from sys import stdout


def write(*string: str, flush: bool = False, sep: str = " ", end: str = "\r\n") -> None:
    for s in string:
        stdout.write(s)
        stdout.write(sep)
    stdout.write(end)
    if flush:
        stdout.flush()


write("Hello World", "World")
