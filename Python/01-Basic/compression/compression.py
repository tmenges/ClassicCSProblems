class CompressedGene:
    def __init__(self, gene: str) -> None:
        self._compress(gene)

    def __str__(self) -> str:
        return self.decompress()

    def _compress(self, gene: str) -> None:
        self.bit_string: int = 1  # start with a sentinel
        for nucleotide in gene.upper():
            self.bit_string <<= 2  # shift left two bits
            if nucleotide == "A":  # A -- 00
                self.bit_string |= 0b00
            elif nucleotide == "C":  # C -- 01
                self.bit_string |= 0b01
            elif nucleotide == "G":  # G -- 10
                self.bit_string |= 0b10
            elif nucleotide == "T":  # T -- 11
                self.bit_string |= 0b11
            else:
                raise ValueError("Invalid Nucleotide: {}".format(nucleotide))

    def decompress(self) -> str:
        gene: str = ""
        i: int
        for i in range(0, self.bit_string.bit_length() - 1, 2):     # -1 to exclude sentinel
            bits: int = self.bit_string >> i & 0b11                 # get 2 relevant bits
            if bits == 0b00:
                gene += "A"
            elif bits == 0b01:
                gene += "C"
            elif bits == 0b10:
                gene += "G"
            elif bits == 0b11:
                gene += "T"
            else:
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
