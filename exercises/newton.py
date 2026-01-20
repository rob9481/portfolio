def main():
    square = 42
    guess = 100000000
    epsilon = 0.0001
    while True:
        guess = 1/2 * (guess + square / guess)
        print(guess)
        if abs(guess ** 2 - 42) < epsilon:
            break
        

if __name__ == "__main__":
    main()
