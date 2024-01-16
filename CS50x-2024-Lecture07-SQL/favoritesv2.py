import csv
from collections import Counter

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = Counter()

    for row in reader:
        counts[row["language"]] += 1

for language, num_people in counts.most_common():
    # most_common is a helpful method inside Counter class
    print(f"{language}: {num_people}")
