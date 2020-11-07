class CompressedGene:
    __encodings = {"A": 0b00, "C": 0b01, "G": 0b10, "T": 0b11}
    __decodings = {value: key for key, value in __encodings.items()}

    def __init__(self, gene: str) -> None:
        self._compress(gene)

    def __str__(self) -> str:
        return self.decompress()

    def _compress(self, gene: str) -> None:
        self.bit_string: int = 1  # start with a sentinel
        for nucleotide in gene.upper():
            try:
                self.bit_string <<= 2  # shift left two bits
                self.bit_string |= self.__encodings[nucleotide]
            except KeyError:
                raise ValueError("Invalid Nucleotide: {}".format(nucleotide))

    def decompress(self) -> str:
        gene: str = ""
        i: int
        for i in range(0, self.bit_string.bit_length() - 1, 2):  # -1 to exclude sentinel
            bits: int = self.bit_string >> i & 0b11  # get 2 relevant bits
            try:
                gene += self.__decodings[bits]
            except KeyError:
                raise ValueError("Invalid bits: {}".format(bits))

        return gene[::-1]  # reverse the string


if __name__ == "__main__":
    from sys import getsizeof

    original = \
        "TAGGGATTAACCGTTATATATATATAGCCATGGATCGATTATATAGGGATTAACCGTTATATATATATAGCCATGGATCGATTATA" \
        * 100

    print("original is {} bytes".format(getsizeof(original)))
    compressed = CompressedGene(original)

    print("compressed is {} bytes".format(getsizeof(compressed)))

    print(compressed)
    print("original and decompressed are the same: {}".format(original == compressed.decompress()))
