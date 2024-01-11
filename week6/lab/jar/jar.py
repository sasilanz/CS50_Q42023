import sys


class Jar:
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError
        else:
            self._capacity = capacity
            self._size = 0

    def __str__(self):
        if self._size == 0:
            return "Empty"
        else:
            n = self._size
            return str("🍪" * n)
        #

    def deposit(self, n):
        if n < 0 or n > self._capacity:
            raise ValueError
        else:
            self._size += n

    def withdraw(self, n):
        if n > self._size:
            raise ValueError
        else:
            self._size -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size

def main():
    jar = Jar()
    print(str(jar.capacity))
    print(str(jar))

    jar.deposit(5)
    print(str(jar))
    jar.withdraw(1)
    print(str(jar))

main()
