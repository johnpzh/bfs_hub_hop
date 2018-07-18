import sys

def verify():
    if len(sys.argv) < 2:
        print("Usage: python get_galois_output.py <file>")
        sys.exit(1)
    with open(sys.argv[1], 'r') as fin:
        last_head = "-1"
        for line in fin:
            head, tail = line.split()
            if head != last_head:
                tails = [tail]
                head = last_head
                continue
            if tail in tails:
                print("Error: ({}, {}) happened twice.".format(head, tail))
                sys.exit(1)
            else:
                tails.append(tail)


if __name__ == "__main__":
    verify()
