import time
import os
import random

def hash_CRC(key: str) -> int:
    h = 0
    for ki in key:
        high_order = h & 0xf8000000
        h = h << 5
        h = h ^ (high_order >> 27)
        h = h ^ ord(ki)
    return h

def hash_PJW(key: str) -> int:
    h = 0
    for ki in key:
        h = (h << 4) + ord(ki)
        g = h & 0xf0000000
        if g != 0:
            h = h ^ (g >> 24)
            h = h ^ g
    return h

def hash_BUZ(key: str) -> int:
    h = 0
    R = dict()
    for ki in key:
        high_order = h & 0x80000000
        h = h << 1
        h = h ^ (high_order >> 31)
        if not (ki in R):
            R[ki] = random.randint(0, 0xFFFFFFFF)
        h = h ^ R[ki]
    return h

def search_duplicate(files: list[str], hash: callable) -> list[str]:
    duplicates = []
    work_hash = []
    for file in files:
        with open(file, 'r') as f:
            body = f.read()
            hashed_body = hash(body)
            if hashed_body in work_hash:
                duplicates.append(file)
            else:
                work_hash.append(hashed_body)
    return duplicates

if __name__ == '__main__':
    print("---------------------------------")
    path = "data/"
    files = [path + file for file in os.listdir(path) if file.endswith(".txt")]
    hashes = [hash_CRC, hash_PJW, hash_BUZ, hash]
    for hash in hashes:
        start_time = time.time()
        duplicates = search_duplicate(files, hash)
        end_time = time.time()
        print(f"function: {hash.__name__}")
        print(f"count of duplicates: {len(duplicates)}")
        print(f"time: {round(end_time - start_time, 2)} seconds")
        print("---------------------------------")