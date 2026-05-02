print("DO NOT RUN")
exit(1)

import typing as T

##############################################################################
# Accept or return subclass with types
class Base:
    pass


class Sub1(Base):
    pass


class Sub2(Base):
    pass


# NOTE: builtin 'type' is preferred to 'T.Type', but only works on Python3.9+
def accept_and_return__subclass(
    b: bool, base: T.Type[Base], sub: T.Type[Base]
) -> T.Type[Base]:
    if b:
        return sub
    return base


##############################################################################
# Pass function as parameter with types
def func_as_param(text: str, f: T.Callable[[str], bool]):
    return f(text)


func_as_param("hello", str.isalnum)
