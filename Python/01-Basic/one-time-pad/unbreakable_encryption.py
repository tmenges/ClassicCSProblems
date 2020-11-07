from secrets import token_bytes


def random_key(length):
    # generate length random bytes
    tb = token_bytes(length)

    # convert the random bytes into a bit string
    return int.from_bytes(tb, "big")


def encrypt(original):
    original_bytes = original.encode()
    dummy = random_key(len(original_bytes))
    original_key = int.from_bytes(original_bytes, "big")
    encrypted = original_key ^ dummy

    return dummy, encrypted


def decrypt(key1, key2):
    decrypted = key1 ^ key2
    temp = decrypted.to_bytes((decrypted.bit_length() + 7) // 8, "big")
    return temp.decode()


if __name__ == "__main__":
    k1, k2 = encrypt("One time pad!")
    result = decrypt(k1, k2)
    print(result)
