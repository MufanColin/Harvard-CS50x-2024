def count_letters(text):
    num_letters = 0
    for letter in text:
        num_letters += letter.isalpha()
    return num_letters


def count_words(text):
    """This function returns the number of words in the text."""
    return len(text.split(" "))


def count_sentences(text):
    num_sentences = 0
    n = len(text)
    for i in range(n):
        if text[i] in [".", "!", "?"] and i - 1 >= 0 and text[i - 1].isalpha():
            num_sentences += 1
    return num_sentences


def main():
    text = input("Text: ")
    num_letters = count_letters(text)
    # print(f"Number of letters: {num_letters}")
    num_words = count_words(text)
    # print(f"Number of words: {num_words}")
    num_sentences = count_sentences(text)
    # print(f"Number of sentences: {num_sentences}")

    index = round(0.0588 * num_letters / num_words * 100 - 0.296 * num_sentences / num_words * 100 - 15.8)
    if (index < 1):
        print("Before Grade 1")
    elif (index >= 16):
        print("Grade 16+")
    else:
        print(f"Grade {index}")


main()
