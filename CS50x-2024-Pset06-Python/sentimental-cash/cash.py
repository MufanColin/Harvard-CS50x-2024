from cs50 import get_float

while True:
    try:
        change = get_float("Changes: ")
        if change >= 0:
            break
    except ValueError:
        pass


change = int(change * 100)
min_coins = 0

for coin_value in [25, 10, 5, 1]:
    if change <= 0:
        break
    else:
        min_coins += change // coin_value
        change -= coin_value * (change // coin_value)


print(min_coins)
