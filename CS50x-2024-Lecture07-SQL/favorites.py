import csv

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = {} # an empty dictionary

    for row in reader:
        favorite = row["language"]
        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

for favorite in counts:
    print(f"{favorite}: {counts[favorite]}")

print("----------------------------------")

for favorite in sorted(counts):
    # sort alphabetically(key)
    print(f"{favorite}: {counts[favorite]}")

print("----------------------------------")

for favorite in sorted(counts, key=counts.get):
    # sort according to the value in ascending order, but not the key
    print(f"{favorite}: {counts[favorite]}")

print("----------------------------------")

for favorite in sorted(counts, key=counts.get, reverse=True):
    # sort according to the value in descending order, but not the key
    print(f"{favorite}: {counts[favorite]}")
