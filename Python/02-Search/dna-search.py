from enum import IntEnum
from typing import Tuple, List

Nucleotide: IntEnum = IntEnum('Nucleotide', ('A', 'C', 'G', 'T'))
Codon = Tuple[Nucleotide, Nucleotide, Nucleotide]
Gene = List[Codon]

gene_str: str = 'ACGTGGCTCTCTAACGTACGTACGTACGGGGTTTATATATACCCTAGGACTCCCTTT'


def string_to_gene(s: str) -> Gene:
    gene: Gene = []

    for i in range(0, len(s), 3):
        if (i + 2) >= len(s):       # don't run off the end
            return gene

        # initialize codon out of three nucleotieds
        codon: Codon = (Nucleotide[s[i]], Nucleotide[s[i + 1]], Nucleotide[s[i + 2]])
        gene.append(codon)

    return gene


def linear_contains(gene: Gene, key_codeon: Codon) -> bool:
    for codon in gene:
        if codon == key_codeon:
            return True

    return False


def binary_contains(gene: Gene, key_codeon: Codon) -> bool:
    low: int = 0
    high: int = len(gene) -1
    while low <= high:
        mid: int = (low + high) // 2
        if gene[mid] < key_codeon:
            low = mid + 1
        elif gene[mid] > key_codeon:
            high = mid - 1
        else:
            return True

    return False


my_gene: Gene = string_to_gene(gene_str)
acg: Codon = (Nucleotide.A, Nucleotide.C, Nucleotide.G)
gat: Codon = (Nucleotide.G, Nucleotide.A, Nucleotide.T)

print('Find acg in gene (linear search)', linear_contains(my_gene, acg))
print('Find gat in gene (linear search)', linear_contains(my_gene, gat))

my_sorted_gene: Gene = sorted(my_gene)

print('Find acg in gene (binary search)', binary_contains(my_sorted_gene, acg))
print('Find gat in gene (binary search)', binary_contains(my_sorted_gene, gat))
